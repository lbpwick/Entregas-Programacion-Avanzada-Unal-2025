#include "SignalECG.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// -------------------------------------------------------------
// Constructor
// -------------------------------------------------------------
SignalECG::SignalECG() : head(nullptr), tail(nullptr), size(0) {}

// -------------------------------------------------------------
// Destructor
// -------------------------------------------------------------
SignalECG::~SignalECG() {
    limpiar();
}

// -------------------------------------------------------------
// Limpiar lista
// -------------------------------------------------------------
void SignalECG::limpiar() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* borrar = temp;
        temp = temp->next;
        delete borrar;
    }
    head = tail = nullptr;
    size = 0;
}

// -------------------------------------------------------------
// Cargar archivo txt
// -------------------------------------------------------------
bool SignalECG::cargarArchivo(const std::string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << filename << endl;
        return false;
    }

    limpiar();
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        double amp, t;
        char coma;

        if (!(ss >> amp >> coma >> t))
            continue;

        Node* nuevo = new Node(t, amp);

        if (!head) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            nuevo->prev = tail;
            tail = nuevo;
        }
        size++;
    }

    file.close();

    if (size == 0) {
        cout << "No se cargaron datos válidos." << endl;
        return false;
    }

    cout << "Archivo cargado correctamente. Muestras: " << size << endl;
    return true;
}

// -------------------------------------------------------------
// Calcular Ts promedio
// -------------------------------------------------------------
double SignalECG::calcularPeriodoMuestreo() {
    if (!head || !head->next) return 0;

    Node* actual = head;
    double suma = 0;
    int cuenta = 0;

    while (actual->next != nullptr) {
        suma += (actual->next->tiempo - actual->tiempo);
        actual = actual->next;
        cuenta++;
    }

    if (cuenta == 0) return 0;
    return suma / cuenta;
}

// -------------------------------------------------------------
// Calcular frecuencia de muestreo
// -------------------------------------------------------------
double SignalECG::calcularFrecuenciaMuestreo() {
    double Ts = calcularPeriodoMuestreo();
    if (Ts <= 0) return 0;
    return 1.0 / Ts;
}

// -------------------------------------------------------------
// NUEVO: Calcular coeficientes del filtro Butterworth
// -------------------------------------------------------------
void SignalECG::calcularCoeficientesButterworth(double fc, double fs, int orden,
                                                 vector<double>& b, vector<double>& a) {
    // Frecuencia normalizada (0 a 1, donde 1 es Nyquist)
    double Wn = fc / (fs / 2.0);
    
    // Pre-warping para transformación bilineal
    double wp = tan(M_PI * Wn / 2.0);
    
    if (orden == 2) {
        // Butterworth de orden 2
        double wp2 = wp * wp;
        double sqrt2 = sqrt(2.0);
        
        // Coeficientes en el dominio analógico normalizado
        double k = wp2;
        double d = sqrt2 * wp + wp2 + 1.0;
        
        // Coeficientes del numerador (b)
        b.resize(3);
        b[0] = k / d;
        b[1] = 2.0 * k / d;
        b[2] = k / d;
        
        // Coeficientes del denominador (a)
        a.resize(3);
        a[0] = 1.0;
        a[1] = 2.0 * (wp2 - 1.0) / d;
        a[2] = (1.0 - sqrt2 * wp + wp2) / d;
        
    } else if (orden == 4) {
        // Butterworth de orden 4 (cascada de dos secciones de orden 2)
        // Primera sección
        double q1 = 0.7654; // Factor Q para Butterworth orden 4
        double wp2 = wp * wp;
        double d1 = 1.0 + wp / q1 + wp2;
        
        vector<double> b1(3), a1(3);
        b1[0] = wp2 / d1;
        b1[1] = 2.0 * wp2 / d1;
        b1[2] = wp2 / d1;
        a1[0] = 1.0;
        a1[1] = 2.0 * (wp2 - 1.0) / d1;
        a1[2] = (1.0 - wp / q1 + wp2) / d1;
        
        // Segunda sección
        double q2 = 1.8478;
        double d2 = 1.0 + wp / q2 + wp2;
        
        vector<double> b2(3), a2(3);
        b2[0] = wp2 / d2;
        b2[1] = 2.0 * wp2 / d2;
        b2[2] = wp2 / d2;
        a2[0] = 1.0;
        a2[1] = 2.0 * (wp2 - 1.0) / d2;
        a2[2] = (1.0 - wp / q2 + wp2) / d2;
        
        // Combinar cascada (convolución de coeficientes)
        b.resize(5);
        a.resize(5);
        
        b[0] = b1[0] * b2[0];
        b[1] = b1[0] * b2[1] + b1[1] * b2[0];
        b[2] = b1[0] * b2[2] + b1[1] * b2[1] + b1[2] * b2[0];
        b[3] = b1[1] * b2[2] + b1[2] * b2[1];
        b[4] = b1[2] * b2[2];
        
        a[0] = a1[0] * a2[0];
        a[1] = a1[0] * a2[1] + a1[1] * a2[0];
        a[2] = a1[0] * a2[2] + a1[1] * a2[1] + a1[2] * a2[0];
        a[3] = a1[1] * a2[2] + a1[2] * a2[1];
        a[4] = a1[2] * a2[2];
    }
}

// -------------------------------------------------------------
// NUEVO: Aplicar filtro IIR (una dirección)
// -------------------------------------------------------------
void SignalECG::aplicarFiltroIIR(const vector<double>& entrada, vector<double>& salida,const vector<double>& b,const vector<double>& a) {
    int n = entrada.size();
    int nb = b.size();
    int na = a.size();
    
    salida.resize(n, 0.0);
    
    for (int i = 0; i < n; i++) {
        double y = 0.0;
        
        // Parte del numerador (feedforward)
        for (int j = 0; j < nb; j++) {
            if (i - j >= 0) {
                y += b[j] * entrada[i - j];
            }
        }
        
        // Parte del denominador (feedback)
        for (int j = 1; j < na; j++) {
            if (i - j >= 0) {
                y -= a[j] * salida[i - j];
            }
        }
        
        salida[i] = y / a[0];
    }
}

// -------------------------------------------------------------
// NUEVO: Filtro Butterworth con filtfilt (bidireccional)
// -------------------------------------------------------------
void SignalECG::filtrarButterworthFiltfilt(double fc_hz, int orden) {
    if (!head) {
        cout << "No hay datos cargados.\n";
        return;
    }
    
    if (size < 10) {
        cout << "Datos insuficientes para filtrar.\n";
        return;
    }
    
    double fs = calcularFrecuenciaMuestreo();
    if (fs <= 0) {
        cout << "Error: no se puede calcular la frecuencia de muestreo.\n";
        return;
    }
    
    if (fc_hz >= fs / 2.0) {
        cout << "Error: frecuencia de corte debe ser menor que Nyquist (" << (fs/2.0) << " Hz).\n";
        return;
    }
    
    cout << fixed;
    cout << "\n=== Parámetros del filtro ===" << endl;
    cout << "Frecuencia de muestreo (Fs): " << fs << " Hz" << endl;
    cout << "Frecuencia de corte (Fc): " << fc_hz << " Hz" << endl;
    cout << "Orden del filtro: " << orden << endl;
    cout << "Frecuencia de Nyquist: " << (fs/2.0) << " Hz" << endl;
    
    // Convertir lista enlazada a vector
    vector<double> datos(size);
    Node* actual = head;
    int idx = 0;
    while (actual != nullptr) {
        datos[idx++] = actual->amplitud;
        actual = actual->next;
    }
    
    // Calcular coeficientes del filtro
    vector<double> b, a;
    calcularCoeficientesButterworth(fc_hz, fs, orden, b, a);
    
    cout << "\nCoeficientes del numerador (b): ";
    for (size_t i = 0; i < b.size(); i++) {
        cout << b[i];
        if (i < b.size() - 1) cout << ", ";
    }
    cout << endl;
    
    // Aplicar filtrado hacia adelante
    vector<double> forward;
    aplicarFiltroIIR(datos, forward, b, a);
    
    // Invertir señal
    reverse(forward.begin(), forward.end());
    
    // Aplicar filtrado hacia atrás
    vector<double> backward;
    aplicarFiltroIIR(forward, backward, b, a);
    
    // Invertir nuevamente para obtener resultado final
    reverse(backward.begin(), backward.end());
    
    // Guardar resultado en la lista enlazada
    actual = head;
    idx = 0;
    while (actual != nullptr) {
        actual->filtrada = backward[idx++];
        actual = actual->next;
    }
    
    cout << "Filtrado bidireccional completado (filtfilt).\n";
    cout << "Orden efectivo: " << (orden * 2) << " (por filtrado bidireccional)\n";
}

// -------------------------------------------------------------
// Filtro pasa bajos simple (ANTIGUO - mantener por compatibilidad)
// -------------------------------------------------------------
void SignalECG::filtrarLowPassFc(double fc_hz) {
    if (!head) {
        cout << "No hay datos cargados.\n";
        return;
    }

    double Ts = calcularPeriodoMuestreo();
    if (Ts <= 0) {
        cout << "Error: no se puede calcular Ts.\n";
        return;
    }

    double alpha = 1.0 - exp(-2.0 * M_PI * fc_hz * Ts);

    cout << fixed;
    cout << "Frecuencia de corte (Fc): " << fc_hz << " Hz\n";
    cout << "Periodo de muestreo (Ts): " << Ts << " s\n";
    cout << "Alpha calculado: " << alpha << endl;

    Node* actual = head;
    actual->filtrada = actual->amplitud;

    while (actual->next != nullptr) {
        Node* nxt = actual->next;
        nxt->filtrada = alpha * nxt->amplitud + (1 - alpha) * actual->filtrada;
        actual = nxt;
    }

    cout << "Filtrado simple completado.\n";
}

// -------------------------------------------------------------
// Detectar picos
// -------------------------------------------------------------
void SignalECG::detectarPicos(double umbral, int& cantidadPicos, double& promedioRR) {
    cantidadPicos = 0;
    promedioRR = 0;

    if (!head || !head->next) {
        cout << "Datos insuficientes.\n";
        return;
    }

    double sumaRR = 0;
    double ultimoTiempo = -1;

    Node* actual = head->next;

    while (actual->next != nullptr) {
        if (actual->filtrada > umbral &&
            actual->filtrada > actual->prev->filtrada &&
            actual->filtrada > actual->next->filtrada) {

            cantidadPicos++;

            if (ultimoTiempo >= 0)
                sumaRR += (actual->tiempo - ultimoTiempo);

            ultimoTiempo = actual->tiempo;
        }
        actual = actual->next;
    }

    if (cantidadPicos > 1)
        promedioRR = sumaRR / (cantidadPicos - 1);

    cout << "Picos detectados: " << cantidadPicos << endl;
}

// -------------------------------------------------------------
// Guardar archivo
// -------------------------------------------------------------
void SignalECG::guardarArchivo(const std::string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo guardar." << endl;
        return;
    }

    Node* temp = head;

    while (temp) {
        file << temp->filtrada << "," << temp->tiempo << "\n";
        temp = temp->next;
    }

    file.close();
    cout << "Archivo guardado: " << filename << endl;
}

double SignalECG::calcularFrecuenciaCardiaca(double promedioRR) {
    if (promedioRR <= 0) return 0;
    return 60.0 / promedioRR;
}

// -------------------------------------------------------------
// MENÚ ACTUALIZADO
// -------------------------------------------------------------
void SignalECG::imprimirMenu() {
    cout << "\n====== MENU ECG ======\n";
    cout << "1. Cargar archivo ECG\n";
    cout << "2. Calcular frecuencia de muestreo (Fs)\n";
    cout << "3. Filtrar simple (pasa bajos exponencial)\n";
    cout << "4. Filtrar Butterworth con filtfilt (RECOMENDADO)\n";
    cout << "5. Detectar picos y frecuencia cardiaca\n";
    cout << "6. Guardar señal filtrada\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}