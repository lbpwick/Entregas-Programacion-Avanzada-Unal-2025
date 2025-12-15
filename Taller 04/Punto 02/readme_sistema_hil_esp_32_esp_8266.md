# Sistema HIL (Hardware-in-the-Loop) con ESP32, ESP8266 y Python

## Descripción general
Este proyecto implementa un **sistema Hardware-in-the-Loop (HIL)** para el estudio y validación de un **derivador no lineal de alto orden** aplicado al seguimiento de una referencia y conectado a una **planta dinámica simulada en tiempo real**.

La arquitectura está dividida en **tres componentes principales**:

1. **ESP32 (ESP-WROOM-32)**: actúa como **maestro HIL**, generando señales de referencia, ejecutando el derivador no lineal y coordinando las comunicaciones.
2. **ESP8266**: actúa como **simulador de la planta**, implementando un modelo discreto de un sistema dinámico de tercer orden.
3. **Interfaz gráfica en Python**: permite al usuario **interactuar, visualizar resultados en tiempo real y grabar datos**.

Todo el sistema opera a una **frecuencia de muestreo de 250 Hz (Ts = 0.004 s)**.

---

## Arquitectura del sistema

```
┌────────────┐     UART (115200)     ┌────────────┐
│   Python   │◄────────────────────►│    ESP32   │
│  GUI HIL   │      USB Serial       │  Derivador │
└────────────┘                       └─────┬──────┘
                                                  UART (Serial2)
                                                  115200 baudios
                                           ┌─────▼──────┐
                                           │  ESP8266   │
                                           │   Planta   │
                                           └────────────┘
```

---

## 1. Código ESP32 (ESP-WROOM-32) – Maestro HIL

### Función principal
El ESP32 es el **núcleo del sistema HIL**. Sus responsabilidades son:

- Generar la **señal de referencia** (escalón, rampa o senoidal).
- Ejecutar un **derivador no lineal de cuarto orden** basado en parámetros \(\lambda_i\).
- Comunicarse con la **planta (ESP8266)** mediante UART.
- Enviar datos en tiempo real a **Python** para visualización y registro.
- Recibir comandos desde Python para modificar parámetros y señales.

### Comunicación
- **Serial (USB)**: Comunicación con Python (115200 baudios).
- **Serial2 (GPIO 16 RX, GPIO 17 TX)**: Comunicación con ESP8266.

### Señales de referencia
El tipo de señal se selecciona dinámicamente:

| Código | Señal | Descripción |
|------|------|-------------|
| 0 | Escalón | Activa a t > 1 s |
| 1 | Rampa | Pendiente 0.5 a partir de t > 1 s |
| 2 | Senoidal | Seno de 0.5 Hz |

### Derivador no lineal
El sistema implementa un **derivador de alto orden** con estados internos:

- `z0`: estimación de la señal
- `z1`: primera derivada estimada
- `z2`: segunda derivada estimada
- `z3`: tercera derivada estimada

La dinámica se define mediante una función no lineal `phi(i, error)` que depende de:

- El error entre referencia y estimación
- Los parámetros \(\lambda_0, \lambda_1, \lambda_2, \lambda_3\)
- El parámetro de ganancia global `L`

La integración se realiza de forma explícita usando el periodo de muestreo `Ts`.

### Protocolo de comandos (desde Python)

| Comando | Función |
|-------|--------|
| `SIG:x` | Cambia el tipo de señal (0,1,2) |
| `PAR:l0,l1,l2,l3` | Actualiza parámetros del derivador |

Al cambiar la señal, los estados internos se reinician automáticamente.

### Datos enviados a Python
Formato CSV por línea:

```
Tiempo, Referencia, Planta, z0, z1, z2
```

---

## 2. Código ESP8266 – Simulador de Planta

### Función principal
El ESP8266 simula una **planta dinámica de tercer orden** descrita por la función de transferencia:

\[
G(s) = \frac{7s^2 - 28s + 21}{s^3 + 9.8s^2 + 30.65s + 30.1}
\]

Esta planta se discretiza previamente (método Tustin / trapezoidal) para un periodo de muestreo de **0.004 s**.

### Implementación
- Se utiliza una **ecuación en diferencias** de orden 3.
- Se mantienen buffers de entradas y salidas pasadas:
  - `u[k], u[k-1], u[k-2], u[k-3]`
  - `y[k], y[k-1], y[k-2], y[k-3]`

La ecuación general es:

\[
y[k] = \frac{b_0u[k] + b_1u[k-1] + b_2u[k-2] + b_3u[k-3]
- a_1y[k-1] - a_2y[k-2] - a_3y[k-3]}{a_0}
\]

### Flujo de operación
1. Recibe la entrada `u(k)` desde el ESP32.
2. Calcula la salida `y(k)`.
3. Envía `y(k)` de vuelta al ESP32 por UART.

La comunicación es completamente **sincronizada por eventos** (cuando llega un dato).

---

## 3. Código Python – Interfaz Gráfica HIL

### Función principal
La aplicación Python proporciona una **interfaz gráfica completa** para:

- Seleccionar el puerto COM y conectarse al ESP32.
- Elegir el tipo de señal de referencia.
- Modificar parámetros del derivador en tiempo real.
- Visualizar gráficas en tiempo real.
- Grabar datos experimentales en archivos `.txt`.

### Tecnologías usadas
- `tkinter`: interfaz gráfica
- `pyserial`: comunicación serial
- `matplotlib`: visualización
- `threading`: lectura serial en segundo plano

### Paneles de la interfaz

#### Panel superior
- Selección de puerto COM
- Botón conectar/desconectar
- Selector de señal de referencia
- Control de grabación de datos

#### Panel izquierdo
- Edición de parámetros \(\lambda_0, \lambda_1, \lambda_2, \lambda_3\)
- Envío inmediato al ESP32

#### Panel central
- Gráfica superior: **Referencia vs Salida de la planta**
- Gráfica inferior: **Derivada estimada (z1)**

### Grabación de datos
- Los datos se guardan en formato `.txt` delimitado por tabulaciones.
- Incluye encabezados:

```
Tiempo   Ref   Planta   z0   z1   z2
```

---

## Flujo completo del sistema

1. El usuario conecta el ESP32 y selecciona el puerto en Python.
2. Python envía comandos de configuración (señal y parámetros).
3. El ESP32 genera la referencia y calcula el derivador.
4. El ESP32 envía la referencia al ESP8266.
5. El ESP8266 calcula la salida de la planta.
6. La salida regresa al ESP32.
7. El ESP32 transmite los datos a Python.
8. Python grafica y opcionalmente guarda los datos.

---

## Aplicaciones

- Validación de algoritmos de control y observadores
- Pruebas HIL sin planta física
- Análisis de derivadores no lineales
- Docencia en control digital y sistemas embebidos

---

## Notas importantes

- Los coeficientes de la planta deben validarse externamente (MATLAB/Python).
- El sistema depende de una comunicación serial estable a 115200 baudios.
- El tiempo real está limitado por la latencia de UART y Python.

---

## Autor
Proyecto desarrollado como plataforma experimental HIL para control y estimación en tiempo real.

