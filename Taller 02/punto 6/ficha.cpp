#include "ficha.h"

/**
 * Constructor de la clase Ficha
 * Valida que los valores estén en el rango válido (0-6)
 */
Ficha::Ficha(int izq, int der) : izquierda(izq), derecha(der) {
    if (izq < 0 || izq > 6 || der < 0 || der > 6) {
        throw std::invalid_argument("Los valores de las fichas deben estar entre 0 y 6");
    }
}

/**
 * Voltea la ficha intercambiando sus valores
 */
void Ficha::voltear() {
    std::swap(izquierda, derecha);
}

/**
 * Sobrecarga del operador de igualdad
 * Dos fichas son iguales si tienen los mismos valores en los extremos
 * (considerando que una ficha volteada es igual a su original)
 */
bool Ficha::operator==(const Ficha& otra) const {
    return (izquierda == otra.izquierda && derecha == otra.derecha) ||
           (izquierda == otra.derecha && derecha == otra.izquierda);
}

/**
 * Imprime la ficha en formato visual
 * Ejemplo: [3|5] representa una ficha con valores 3 y 5
 */
void Ficha::mostrar() const {
    std::cout << "[" << izquierda << "|" << derecha << "]";
}
