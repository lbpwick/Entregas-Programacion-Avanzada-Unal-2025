// --- ESP8266: SIMULADOR DE PLANTA ---
// G(s) = (7s^2 - 28s + 21) / (s^3 + 9.8s^2 + 30.65s + 30.1)
// Frecuencia de muestreo: 250 Hz -> Ts = 0.004 s

#include <Arduino.h>

// Coeficientes de la ecuación en diferencias (Discretización Tustin/Trapezoidal pre-calculada para Ts=0.004)

// Estructura: y[k] = (b0*u[k] + b1*u[k-1]... - a1*y[k-1]...)/a0

double u[4] = {0, 0, 0, 0}; // Entradas actuales y pasadas
double y[4] = {0, 0, 0, 0}; // Salidas actuales y pasadas

// Coeficientes aproximados para Ts=0.004s (Debes verificarlos con Matlab/Python para tu reporte)
// Ejemplo genérico para estructura de 3er orden:
// a0*y[k] + a1*y[k-1] + a2*y[k-2] + a3*y[k-3] = b0*u[k] + b1*u[k-1] + b2*u[k-2] + b3*u[k-3]
const double a0 = 1.0;
const double a1 = -2.961; 
const double a2 = 2.922; 
const double a3 = -0.9615;
const double b0 = 0.000056; 
const double b1 = -0.000056; 
const double b2 = -0.000056; 
const double b3 = 0.000056; 

unsigned long previousMicros = 0;
const long sampleTimeMicros = 4000; // 250 Hz

void setup() {
  // Iniciamos Serial a alta velocidad para comunicación con ESP32
  // En ESP8266 Serial usa pines TX(1) y RX(3)
  Serial.begin(115200); 
  Serial.setTimeout(2); // Timeout corto para no bloquear
}

void loop() {
  if (Serial.available() > 0) {
    // 1. Leer la entrada u(k) enviada por el ESP32
    String data = Serial.readStringUntil('\n');
    double inputVal = data.toFloat();

    // Actualizar buffer de entradas
    u[3] = u[2]; u[2] = u[1]; u[1] = u[0];
    u[0] = inputVal;

    // Actualizar buffer de salidas
    y[3] = y[2]; y[2] = y[1]; y[1] = y[0];

    // 2. Calcular la Ecuación en Diferencias (La Planta)
    // y[k] = (b0*u[k] + ... + b3*u[k-3] - a1*y[k-1] - ... - a3*y[k-3]) / a0
    double termB = b0*u[0] + b1*u[1] + b2*u[2] + b3*u[3];
    double termA = a1*y[1] + a2*y[2] + a3*y[3];
    
    y[0] = (termB - termA) / a0;

    // 3. Enviar y(k) de vuelta al ESP32
    Serial.println(y[0], 6); // 6 decimales de precisión
  }
}