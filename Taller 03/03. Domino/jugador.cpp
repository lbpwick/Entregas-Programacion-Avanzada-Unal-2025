#include "jugador.h"
#include <iostream>
#include <stdexcept>

Jugador::Jugador(const std::string& n) : nombre(n), puntuacion(0) {}

void Jugador::agregarFicha(const Ficha& f) {
    mano.push_back(f);
}

Ficha Jugador::tomarFicha(size_t indice) {
    if (indice >= mano.size()) {
        throw std::out_of_range("Indice de ficha fuera de rango");
    }
    Ficha f = mano[indice];
    mano.erase(mano.begin() + indice);
    return f;
}

const Ficha& Jugador::verFicha(size_t indice) const {
    if (indice >= mano.size()) {
        throw std::out_of_range("Indice de ficha fuera de rango");
    }
    return mano[indice];
}

int Jugador::calcularPuntosMano() const {
    int total = 0;
    for (const auto& f : mano) {
        total += f.getIzquierda() + f.getDerecha();
    }
    return total;
}

bool Jugador::tieneFichaCompatible(int numero) const {
    for (const auto& f : mano) {
        if (f.getIzquierda() == numero || f.getDerecha() == numero) {
            return true;
        }
    }
    return false;
}

void Jugador::mostrarMano() const {
    std::cout << "\n🂠 Fichas de " << nombre << " (" << mano.size() << " fichas):\n";
    for (size_t i = 0; i < mano.size(); ++i) {
        std::cout << "  " << i << ": " << mano[i].toString() << "\n";
    }
}