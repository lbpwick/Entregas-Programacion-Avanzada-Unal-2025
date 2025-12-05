#include "ficha.h"
#include <stdexcept>
#include <algorithm>

Ficha::Ficha(int izq, int der) : izquierda(izq), derecha(der) {
    if (izq < 0 || izq > 6 || der < 0 || der > 6) {
        throw std::invalid_argument("Ficha: valores deben estar entre 0-6");
    }
}

void Ficha::setIzquierda(int v) {
    if (v < 0 || v > 6) throw std::invalid_argument("Izquierda: 0-6");
    izquierda = v;
}

void Ficha::setDerecha(int v) {
    if (v < 0 || v > 6) throw std::invalid_argument("Derecha: 0-6");
    derecha = v;
}

void Ficha::voltear() {
    std::swap(izquierda, derecha);
}

bool Ficha::operator==(const Ficha& otra) const {
    return (izquierda == otra.izquierda && derecha == otra.derecha) ||
           (izquierda == otra.derecha && derecha == otra.izquierda);
}

std::string Ficha::toString() const {
    return "[" + std::to_string(izquierda) + "|" + std::to_string(derecha) + "]";
}