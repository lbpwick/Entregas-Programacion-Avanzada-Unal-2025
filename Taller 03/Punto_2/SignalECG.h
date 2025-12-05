#ifndef SIGNALECG_H
#define SIGNALECG_H

#include <string>
#include <vector>

struct Node {
    double tiempo;
    double amplitud;
    double filtrada;
    Node* next;
    Node* prev;

    Node(double t, double a) : tiempo(t), amplitud(a), filtrada(a), next(nullptr), prev(nullptr) {}
};

class SignalECG {
private:
    Node* head;
    Node* tail;
    int size;

    // Métodos auxiliares para el filtro Butterworth
    void calcularCoeficientesButterworth(double fc, double fs, int orden,
                                         std::vector<double>& b, std::vector<double>& a);
    
    void aplicarFiltroIIR(const std::vector<double>& entrada,
                          std::vector<double>& salida,
                          const std::vector<double>& b,
                          const std::vector<double>& a);

public:
    SignalECG();
    ~SignalECG();

    void limpiar();
    bool cargarArchivo(const std::string& filename);
    double calcularPeriodoMuestreo();
    double calcularFrecuenciaMuestreo();
    
    // Filtros
    void filtrarLowPassFc(double fc_hz);  // Filtro simple (antiguo)
    void filtrarButterworthFiltfilt(double fc_hz, int orden = 4);  // NUEVO: Filtro Butterworth
    
    void detectarPicos(double umbral, int& cantidadPicos, double& promedioRR);
    void guardarArchivo(const std::string& filename);
    double calcularFrecuenciaCardiaca(double promedioRR);
    void imprimirMenu();
};

#endif