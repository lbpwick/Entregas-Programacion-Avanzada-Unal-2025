#include "SignalECG.h"
#include <iostream>

using namespace std;

int main() {
    SignalECG ecg;
    int opcion;

    do {
        ecg.imprimirMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string filename;
                cout << "Ingrese el nombre del archivo: ";
                cin >> filename;
                ecg.cargarArchivo(filename);
                break;
            }

            case 2: {
                double fs = ecg.calcularFrecuenciaMuestreo();
                if (fs > 0) {
                    cout << "Frecuencia de muestreo: " << fs << " Hz" << endl;
                } else {
                    cout << "No se puede calcular. Cargue primero un archivo." << endl;
                }
                break;
            }

            case 3: {
                double fc;
                cout << "Ingrese frecuencia de corte (Fc) en Hz: ";
                cin >> fc;
                ecg.filtrarLowPassFc(fc);
                break;
            }

            case 4: {
                double fc;
                int orden;
                cout << "\n=== FILTRO BUTTERWORTH CON FILTFILT ===" << endl;
                cout << "Para señales ECG se recomienda:" << endl;
                cout << "  - Fc = 40-50 Hz (preserva complejo QRS)" << endl;
                cout << "  - Orden = 2 o 4 (orden efectivo será el doble)" << endl;
                cout << "\nIngrese frecuencia de corte (Fc) en Hz [recomendado 40]: ";
                cin >> fc;
                cout << "Ingrese orden del filtro (2 o 4) [recomendado 4]: ";
                cin >> orden;
                
                if (orden != 2 && orden != 4) {
                    cout << "ADVERTENCIA: Solo se soporta orden 2 o 4. Usando orden 4." << endl;
                    orden = 4;
                }
                
                ecg.filtrarButterworthFiltfilt(fc, orden);
                break;
            }

            case 5: {
                double umbral;
                cout << "Ingrese el umbral para deteccion de picos: ";
                cin >> umbral;

                int cantidadPicos = 0;
                double promedioRR = 0;

                ecg.detectarPicos(umbral, cantidadPicos, promedioRR);

                if (cantidadPicos > 0) {
                    double fc = ecg.calcularFrecuenciaCardiaca(promedioRR);
                    cout << "Promedio R-R: " << promedioRR << " s" << endl;
                    cout << "Frecuencia cardiaca: " << fc << " bpm" << endl;
                }
                break;
            }

            case 6: {
                string filename;
                cout << "Ingrese el nombre del archivo de salida: ";
                cin >> filename;
                ecg.guardarArchivo(filename);
                break;
            }

            case 7:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 7);

    return 0;
}