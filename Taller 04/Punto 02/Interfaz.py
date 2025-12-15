import sys
import serial
import serial.tools.list_ports
import threading
import time
import csv
import tkinter as tk
from tkinter import ttk, messagebox
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import collections

# --- CONFIGURACIÓN ---
BAUD_RATE = 115200
MAX_POINTS = 200 # Puntos a mostrar en la gráfica (ventana deslizante)

class HILInterface:
    def __init__(self, root):
        self.root = root
        self.root.title("Panel de Control HIL - Derivador & Planta")
        self.root.geometry("1000x700")

        # Variables de estado
        self.ser = None
        self.is_connected = False
        self.is_recording = False
        self.data_buffer = collections.deque(maxlen=MAX_POINTS)
        self.csv_file = None
        self.csv_writer = None
        
        # Buffers para gráficas
        self.t_data = collections.deque(maxlen=MAX_POINTS)
        self.ref_data = collections.deque(maxlen=MAX_POINTS)
        self.plant_data = collections.deque(maxlen=MAX_POINTS)
        self.z1_data = collections.deque(maxlen=MAX_POINTS)

        self.setup_ui()
        
    def setup_ui(self):
        # 1. Panel Superior (Conexión y Controles)
        control_frame = tk.Frame(self.root, bd=2, relief=tk.GROOVE)
        control_frame.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)

        # Selector de Puerto COM
        tk.Label(control_frame, text="Puerto COM:").pack(side=tk.LEFT, padx=5)
        self.port_combo = ttk.Combobox(control_frame, width=10)
        self.port_combo['values'] = [com.device for com in serial.tools.list_ports.comports()]
        if self.port_combo['values']: self.port_combo.current(0)
        self.port_combo.pack(side=tk.LEFT, padx=5)

        self.btn_connect = tk.Button(control_frame, text="Conectar", command=self.toggle_connection, bg="#DDDDDD")
        self.btn_connect.pack(side=tk.LEFT, padx=5)

        # Separador
        ttk.Separator(control_frame, orient=tk.VERTICAL).pack(side=tk.LEFT, fill=tk.Y, padx=10)

        # Selección de Señal
        tk.Label(control_frame, text="Señal Ref:").pack(side=tk.LEFT)
        self.signal_var = tk.StringVar(value="Escalón")
        signals = {"Escalón": 0, "Rampa": 1, "Senoidal": 2}
        
        def send_signal_cmd(*args):
            if self.is_connected:
                val = signals[self.signal_var.get()]
                self.send_command(f"SIG:{val}")

        self.opt_signal = tk.OptionMenu(control_frame, self.signal_var, *signals.keys(), command=send_signal_cmd)
        self.opt_signal.pack(side=tk.LEFT, padx=5)

        # Grabación
        self.btn_record = tk.Button(control_frame, text="Grabar .TXT", command=self.toggle_recording, bg="#FFCCCC")
        self.btn_record.pack(side=tk.RIGHT, padx=10)

        # 2. Panel Izquierdo (Parámetros Derivador)
        param_frame = tk.LabelFrame(self.root, text="Parámetros Derivador (Lambdas)")
        param_frame.pack(side=tk.LEFT, fill=tk.Y, padx=5, pady=5)

        self.entries = {}
        defaults = [("λ0", "1.3"), ("λ1", "1.85"), ("λ2", "2.79"), ("λ3", "6.48")]
        
        for i, (label, val) in enumerate(defaults):
            tk.Label(param_frame, text=label).grid(row=i, column=0, padx=5, pady=5)
            e = tk.Entry(param_frame, width=8)
            e.insert(0, val)
            e.grid(row=i, column=1, padx=5, pady=5)
            self.entries[label] = e

        tk.Button(param_frame, text="Actualizar Params", command=self.send_params, bg="lightblue").grid(row=4, column=0, columnspan=2, pady=10)

        # 3. Panel Central (Gráficas)
        plot_frame = tk.Frame(self.root)
        plot_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

        self.fig = Figure(figsize=(5, 4), dpi=100)
        self.ax1 = self.fig.add_subplot(211) # Arriba: Ref vs Planta
        self.ax2 = self.fig.add_subplot(212) # Abajo: Derivada estimada
        
        self.ax1.set_title("Seguimiento: Referencia vs Planta")
        self.ax2.set_title("Estimación Derivada (Estado z1)")
        self.fig.tight_layout(pad=3.0)

        self.line_ref, = self.ax1.plot([], [], 'b--', label='Referencia')
        self.line_plant, = self.ax1.plot([], [], 'r-', label='Planta')
        self.line_z1, = self.ax2.plot([], [], 'g-', label='z1 (Derivada)')
        
        self.ax1.legend(loc='upper right')
        self.ax2.legend(loc='upper right')

        self.canvas = FigureCanvasTkAgg(self.fig, master=plot_frame)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        # Timer para refrescar GUI
        self.root.after(50, self.update_plot)

    def toggle_connection(self):
        if not self.is_connected:
            try:
                port = self.port_combo.get()
                self.ser = serial.Serial(port, BAUD_RATE, timeout=1)
                self.is_connected = True
                self.btn_connect.config(text="Desconectar", bg="#CCFFCC")
                
                # Iniciar hilo de lectura
                self.thread = threading.Thread(target=self.serial_loop, daemon=True)
                self.thread.start()
            except Exception as e:
                messagebox.showerror("Error", f"No se pudo conectar: {e}")
        else:
            self.is_connected = False
            self.is_recording = False # Parar grabación si desconecta
            self.btn_connect.config(text="Conectar", bg="#DDDDDD")
            if self.ser: self.ser.close()

    def toggle_recording(self):
        if not self.is_recording:
            # Iniciar grabación
            filename = f"HIL_Data_{int(time.time())}.txt"
            try:
                self.csv_file = open(filename, mode='w', newline='')
                self.csv_writer = csv.writer(self.csv_file, delimiter='\t')
                # Header
                self.csv_writer.writerow(["Tiempo", "Ref", "Planta", "z0", "z1", "z2"])
                self.is_recording = True
                self.btn_record.config(text="DETENER GRABACIÓN", bg="red", fg="white")
                messagebox.showinfo("Info", f"Grabando en {filename}")
            except Exception as e:
                messagebox.showerror("Error", f"No se pudo crear archivo: {e}")
        else:
            # Detener grabación
            self.is_recording = False
            if self.csv_file: self.csv_file.close()
            self.btn_record.config(text="Grabar .TXT", bg="#FFCCCC", fg="black")

    def send_command(self, cmd):
        if self.is_connected and self.ser:
            self.ser.write((cmd + '\n').encode())

    def send_params(self):
        try:
            l0 = float(self.entries["λ0"].get())
            l1 = float(self.entries["λ1"].get())
            l2 = float(self.entries["λ2"].get())
            l3 = float(self.entries["λ3"].get())
            # Comando PAR:l0,l1,l2,l3
            cmd = f"PAR:{l0},{l1},{l2},{l3}"
            self.send_command(cmd)
            print(f"Enviado: {cmd}")
        except ValueError:
            messagebox.showerror("Error", "Los parámetros deben ser números")

    def serial_loop(self):
        while self.is_connected:
            try:
                if self.ser.in_waiting:
                    line = self.ser.readline().decode('utf-8').strip()
                    parts = line.split(',')
                    # Esperamos 6 valores: Time, Ref, Plant, z0, z1, z2
                    if len(parts) >= 6:
                        t = float(parts[0])
                        ref = float(parts[1])
                        plant = float(parts[2])
                        z1 = float(parts[4])

                        # Guardar en buffers para gráfica
                        self.t_data.append(t)
                        self.ref_data.append(ref)
                        self.plant_data.append(plant)
                        self.z1_data.append(z1)

                        # Guardar en archivo si está grabando
                        if self.is_recording and self.csv_writer:
                            self.csv_writer.writerow(parts)
            except Exception as e:
                print(f"Error Serial: {e}")
                break

    def update_plot(self):
        if self.is_connected and len(self.t_data) > 1:
            # Actualizar datos de las lineas
            self.line_ref.set_data(self.t_data, self.ref_data)
            self.line_plant.set_data(self.t_data, self.plant_data)
            self.line_z1.set_data(self.t_data, self.z1_data)

            # Reajustar ejes
            self.ax1.relim()
            self.ax1.autoscale_view()
            self.ax2.relim()
            self.ax2.autoscale_view()
            
            self.canvas.draw_idle()
        
        # Reprogramar loop
        self.root.after(100, self.update_plot)

if __name__ == "__main__":
    root = tk.Tk()
    app = HILInterface(root)
    root.mainloop()