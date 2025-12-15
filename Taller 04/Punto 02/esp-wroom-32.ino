// --- ESP32 HIL MASTER - CON SOPORTE DE COMANDOS ---
#include <HardwareSerial.h>
#include <math.h>

#define RXD2 16
#define TXD2 17

// --- Variables del Sistema ---
// Parámetros por defecto
double lambda0 = 1.3, lambda1 = 1.85, lambda2 = 2.79, lambda3 = 6.48;
int signalType = 0; // 0: Escalon, 1: Rampa, 2: Seno

// Estados del Derivador
double z0 = 0, z1 = 0, z2 = 0, z3 = 0;
const double L = 1.8;
const double Ts = 0.004; // 250Hz

unsigned long previousMicros = 0;
const long interval = 4000;
double t = 0;

void setup() {
  Serial.begin(115200); // Comms con Python
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // Comms con Planta (ESP8266)
}

// Función auxiliar Phi
double sign(double x) { return (x > 0) ? 1.0 : ((x < 0) ? -1.0 : 0.0); }
double phi(int i, double val) {
  int n = 3;
  double lam;
  if(i==0) lam = lambda3; else if(i==1) lam = lambda2;
  else if(i==2) lam = lambda1; else lam = lambda0;
  
  double expL = (double)(i + 1) / (n - i + 1);
  double expVal = (double)(n - i) / (n - i + 1);
  return -lam * pow(L, expL) * pow(fabs(val), expVal) * sign(val);
}

void loop() {
  // 1. RECEPCIÓN DE COMANDOS DESDE PYTHON
  // Formatos esperados: 
  // "SIG:1" -> Cambia señal a Rampa
  // "PAR:1.1,2.2,3.3,4.4" -> Cambia lambdas
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    
    if (cmd.startsWith("SIG:")) {
      signalType = cmd.substring(4).toInt();
      t = 0; z0=0; z1=0; z2=0; z3=0; // Reset
    }
    else if (cmd.startsWith("PAR:")) {
      // Parsear floats separados por coma
      int firstComma = cmd.indexOf(',');
      int secondComma = cmd.indexOf(',', firstComma + 1);
      int thirdComma = cmd.indexOf(',', secondComma + 1);
      
      String s0 = cmd.substring(4, firstComma);
      String s1 = cmd.substring(firstComma + 1, secondComma);
      String s2 = cmd.substring(secondComma + 1, thirdComma);
      String s3 = cmd.substring(thirdComma + 1);
      
      lambda0 = s0.toFloat();
      lambda1 = s1.toFloat();
      lambda2 = s2.toFloat();
      lambda3 = s3.toFloat();
    }
  }

  // 2. LOOP DE CONTROL (250Hz)
  unsigned long currentMicros = micros();
  if (currentMicros - previousMicros >= interval) {
    previousMicros = currentMicros;

    // Generar Referencia
    double ref = 0;
    if (signalType == 0) ref = (t > 1.0) ? 1.0 : 0.0;
    else if (signalType == 1) ref = (t > 1.0) ? (0.5 * (t - 1)) : 0.0;
    else ref = sin(2 * 3.1416 * 0.5 * t);

    // Comunicación con Planta
    Serial2.println(ref);
    double y_plant = 0;
    if(Serial2.available()) {
      String resp = Serial2.readStringUntil('\n');
      y_plant = resp.toFloat();
    }

    // Derivador
    double err = z0 - ref;
    double nz0 = z0 + Ts*phi(0,err) + Ts*z1 + (pow(Ts,2)/2)*z2 + (pow(Ts,3)/6)*z3;
    double nz1 = z1 + Ts*phi(1,err) + Ts*z2 + (pow(Ts,2)/2)*z3;
    double nz2 = z2 + Ts*phi(2,err) + Ts*z3;
    double nz3 = z3 + Ts*phi(3,err);
    
    z0 = nz0; z1 = nz1; z2 = nz2; z3 = nz3;

    // Enviar datos a Python (CSV format)
    // Orden: Tiempo, Ref, Planta, Z0, Z1, Z2, Z3
    Serial.print(t); Serial.print(",");
    Serial.print(ref); Serial.print(",");
    Serial.print(y_plant); Serial.print(",");
    Serial.print(z0); Serial.print(",");
    Serial.print(z1); Serial.print(",");
    Serial.print(z2); Serial.println(); // Fin de línea

    t += Ts;
  }
}