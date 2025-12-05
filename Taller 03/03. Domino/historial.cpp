#include "historial.h"
#include <fstream>
#include <iostream>

HistorialMovimientos::HistorialMovimientos() 
    : cabeza(nullptr), cola(nullptr), tamano(0) {}

HistorialMovimientos::~HistorialMovimientos() {
    limpiar();
}

void HistorialMovimientos::registrarMovimiento(const std::string& jugador,
                                              const std::string& ficha,
                                              const std::string& estadoMesa) {
    NodoMovimiento* nuevo = new NodoMovimiento(jugador, ficha, estadoMesa);
    
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    tamano++;
}

void HistorialMovimientos::guardarEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "❌ Error: No se pudo crear " << nombreArchivo << std::endl;
        return;
    }

    archivo << "📜 HISTORIAL COMPLETO DE MOVIMIENTOS\n";
    archivo << "=====================================\n\n";

    const NodoMovimiento* actual = cabeza;
    int numero = 1;
    
    while (actual) {
        archivo << "MOVIMIENTO #" << numero++ << ":\n";
        archivo << "├── Jugador: " << actual->jugador << "\n";
        archivo << "├── Ficha:   " << actual->ficha << "\n";
        archivo << "└── Mesa:    " << actual->estadoMesa << "\n";
        archivo << "─────────────────────────────────────\n\n";
        actual = actual->siguiente;
    }
    
    archivo << "Total movimientos: " << tamano << "\n";
    std::cout << "✅ Historial guardado en " << nombreArchivo << std::endl;
}

void HistorialMovimientos::limpiar() {
    NodoMovimiento* actual = cabeza;
    while (actual) {
        NodoMovimiento* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    cabeza = cola = nullptr;
    tamano = 0;
}