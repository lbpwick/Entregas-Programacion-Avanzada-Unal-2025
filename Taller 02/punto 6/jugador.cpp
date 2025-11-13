#include "jugador.h"
#include <algorithm>

/**
 * Obtiene una ficha específica por su índice
 * Valida que el índice esté dentro del rango válido
 */
const Ficha& Jugador::getFicha(int indice) const {
    if (indice < 0 || indice >= static_cast<int>(fichas.size())) {
        throw std::out_of_range("Índice de ficha inválido");
    }
    return fichas[indice];
}

/**
 * Elimina una ficha del jugador por su índice
 * Retorna la ficha que fue eliminada
 */
Ficha Jugador::eliminarFicha(int indice) {
    if (indice < 0 || indice >= static_cast<int>(fichas.size())) {
        throw std::out_of_range("Índice de ficha inválido");
    }
    Ficha ficha = fichas[indice];
    fichas.erase(fichas.begin() + indice);
    return ficha;
}

/**
 * Verifica si el jugador puede jugar una ficha dado los valores en los extremos de la mesa
 */
bool Jugador::puedejugar(int valorIzq, int valorDer) const {
    return encontrarFichaEncajable(valorIzq, valorDer) != -1;
}

/**
 * Busca una ficha que encaje en la mesa
 * Retorna el índice de la primera ficha que encaja, o -1 si no hay ninguna
 */
int Jugador::encontrarFichaEncajable(int valorIzq, int valorDer) const {
    for (int i = 0; i < static_cast<int>(fichas.size()); ++i) {
        if (fichas[i].encajaIzquierda(valorIzq) || fichas[i].encajaDerecha(valorIzq) ||
            fichas[i].encajaIzquierda(valorDer) || fichas[i].encajaDerecha(valorDer)) {
            return i;
        }
    }
    return -1;
}

/**
 * Calcula la puntuación total de las fichas del jugador
 * La puntuación es la suma de todos los números en las fichas
 */
int Jugador::calcularPuntuacionFichas() const {
    int puntuacion = 0;
    for (const auto& ficha : fichas) {
        puntuacion += ficha.getIzquierda() + ficha.getDerecha();
    }
    return puntuacion;
}

/**
 * Muestra todas las fichas del jugador en la consola
 */
void Jugador::mostrarFichas() const {
    std::cout << "Fichas de " << nombre << ": ";
    for (int i = 0; i < static_cast<int>(fichas.size()); ++i) {
        std::cout << "(" << i << ") ";
        fichas[i].mostrar();
        std::cout << " ";
    }
    std::cout << std::endl;
}
