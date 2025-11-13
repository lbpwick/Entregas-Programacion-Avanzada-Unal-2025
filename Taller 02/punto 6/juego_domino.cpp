#include "juego_domino.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <ctime>

/**
 * Constructor: Inicializa el juego con el número especificado de jugadores
 */
JuegoDomino::JuegoDomino(int numJugadores) {
    if (numJugadores < 2 || numJugadores > 4) {
        throw std::invalid_argument("El número de jugadores debe estar entre 2 y 4");
    }

    for (int i = 0; i < numJugadores; ++i) {
        jugadores.emplace_back("Jugador " + std::to_string(i + 1));
    }
}

/**
 * Inicializa todas las fichas de dominó (28 fichas totales)
 * Las fichas son: [0|0], [0|1], ..., [0|6], [1|1], ..., [6|6]
 */
void JuegoDomino::inicializarFichas() {
    almacen.clear();
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            almacen.emplace_back(i, j);
        }
    }
}

/**
 * Mezcla aleatoriamente las fichas en el almacén
 */
void JuegoDomino::mezclarFichas() {
    std::mt19937 gen(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(almacen.begin(), almacen.end(), gen);
}

/**
 * Distribuye 7 fichas a cada jugador
 */
void JuegoDomino::distribuirFichasIniciales() {
    const int fichasXJugador = 7;
    for (int i = 0; i < fichasXJugador; ++i) {
        for (auto& jugador : jugadores) {
            if (!almacen.empty()) {
                jugador.agregarFicha(almacen.back());
                almacen.pop_back();
            }
        }
    }
}

/**
 * Encuentra al jugador que tiene la ficha doble más alta para comenzar
 * Si no hay dobles, comienza el primer jugador
 */
int JuegoDomino::encontrarJugadorInicial() {
    int mejorDoble = -1;
    int indiceJugador = 0;
    int mejorIndice = 0;

    for (auto& jugador : jugadores) {
        const auto& fichas = jugador.getFichas();
        for (size_t i = 0; i < fichas.size(); ++i) {
            if (fichas[i].esDoble() && fichas[i].getIzquierda() > mejorDoble) {
                mejorDoble = fichas[i].getIzquierda();
                mejorIndice = indiceJugador;
            }
        }
        indiceJugador++;
    }

    return mejorIndice;
}

/**
 * Intenta que el jugador actual robe una ficha del almacén
 */
bool JuegoDomino::robarFicha() {
    if (!almacen.empty()) {
        jugadores[indiceJugadorActual].agregarFicha(almacen.back());
        almacen.pop_back();
        return true;
    }
    return false;
}

/**
 * Verifica si el jugador actual puede jugar o robar fichas
 */
bool JuegoDomino::puedeJugarOrobar() {
    int valorIzq, valorDer;
    getExtremosActuales(valorIzq, valorDer);

    // Si la mesa está vacía, siempre puede jugar
    if (fichasEnMesa.empty()) {
        return true;
    }

    // Verifica si puede jugar una ficha
    if (jugadores[indiceJugadorActual].puedejugar(valorIzq, valorDer)) {
        return true;
    }

    // Intenta robar del almacén
    return robarFicha();
}

/**
 * Pasa el turno al siguiente jugador
 */
void JuegoDomino::pasoturno() {
    indiceJugadorActual = (indiceJugadorActual + 1) % jugadores.size();
    jugadoresConsecutivosQuePasan++;
}

/**
 * Verifica si el juego está en estado de bloqueo
 * Sucede cuando todos los jugadores han pasado consecutivamente
 */
bool JuegoDomino::estaBloqueado() const {
    return jugadoresConsecutivosQuePasan >= static_cast<int>(jugadores.size());
}

/**
 * Cuando hay bloqueo, determina el ganador
 * El ganador es quien tiene menos puntos en sus fichas restantes
 */
Jugador* JuegoDomino::determinarGanadorPorBloqueo() {
    Jugador* ganador = nullptr;
    int puntajeMinimo = INT_MAX;

    for (auto& jugador : jugadores) {
        int puntos = jugador.calcularPuntuacionFichas();
        if (puntos < puntajeMinimo) {
            puntajeMinimo = puntos;
            ganador = &jugador;
        }
    }

    return ganador;
}

/**
 * Inicializa una nueva partida
 */
void JuegoDomino::iniciarPartida() {
    limpiarPartida();
    inicializarFichas();
    mezclarFichas();
    distribuirFichasIniciales();
    indiceJugadorActual = encontrarJugadorInicial();
    juegoEnCurso = true;
    jugadoresConsecutivosQuePasan = 0;
}

/**
 * Coloca una ficha en la mesa desde la mano del jugador actual
 */
bool JuegoDomino::jugarFicha(int indice, int posicion) {
    if (!juegoEnCurso || indice < 0 || posicion < 0 || posicion > 1) {
        return false;
    }

    Jugador& jugador = jugadores[indiceJugadorActual];

    try {
        const Ficha& ficha = jugador.getFicha(indice);
        int valorIzq, valorDer;
        getExtremosActuales(valorIzq, valorDer);

        // Verifica si la ficha encaja en los extremos de la mesa
        bool encajaIzq = fichasEnMesa.empty() || ficha.encajaIzquierda(valorIzq) || ficha.encajaDerecha(valorIzq);
        bool encajaDer = fichasEnMesa.empty() || ficha.encajaIzquierda(valorDer) || ficha.encajaDerecha(valorDer);

        if (!encajaIzq && !encajaDer) {
            return false;
        }

        // Si la mesa está vacía, coloca la primera ficha
        if (fichasEnMesa.empty()) {
            fichasEnMesa.push_back(ficha);
            jugador.eliminarFicha(indice);
            jugadoresConsecutivosQuePasan = 0;
            return true;
        }

        // Coloca la ficha en la posición especificada
        Ficha fichaAColocar = ficha;

        if (posicion == 0) { // Izquierda
            if (fichaAColocar.encajaDerecha(valorIzq)) {
                fichaAColocar.voltear();
            } else if (!fichaAColocar.encajaIzquierda(valorIzq)) {
                return false;
            }
            fichasEnMesa.push_front(fichaAColocar);
        } else { // Derecha
            if (fichaAColocar.encajaIzquierda(valorDer)) {
                fichaAColocar.voltear();
            } else if (!fichaAColocar.encajaDerecha(valorDer)) {
                return false;
            }
            fichasEnMesa.push_back(fichaAColocar);
        }

        jugador.eliminarFicha(indice);
        jugadoresConsecutivosQuePasan = 0;
        return true;

    } catch (const std::out_of_range&) {
        return false;
    }
}

/**
 * Obtiene los valores en los extremos de las fichas en la mesa
 */
void JuegoDomino::getExtremosActuales(int& valorIzq, int& valorDer) const {
    if (fichasEnMesa.empty()) {
        valorIzq = -1;
        valorDer = -1;
    } else {
        valorIzq = fichasEnMesa.front().getIzquierda();
        valorDer = fichasEnMesa.back().getDerecha();
    }
}

/**
 * Ejecuta el turno del jugador actual
 */
bool JuegoDomino::ejecutarturno() {
    if (!puedeJugarOrobar()) {
        pasoturno();
        if (estaBloqueado()) {
            juegoEnCurso = false;
            return false;
        }
        return true;
    }
    return true;
}

/**
 * Verifica si la partida ha terminado
 */
bool JuegoDomino::partida_terminada() const {
    return !juegoEnCurso || jugadores[indiceJugadorActual].getNumeroFichas() == 0;
}

/**
 * Obtiene el ganador de la partida
 */
Jugador* JuegoDomino::getGanador() {
    if (jugadores[indiceJugadorActual].getNumeroFichas() == 0) {
        return &jugadores[indiceJugadorActual];
    }

    if (estaBloqueado()) {
        return determinarGanadorPorBloqueo();
    }

    return nullptr;
}

/**
 * Muestra el estado actual del juego
 */
void JuegoDomino::mostrarEstado() const {
    std::cout << "\n=== ESTADO DEL JUEGO ===" << std::endl;
    std::cout << "Jugador actual: " << jugadores[indiceJugadorActual].getNombre() << std::endl;
    std::cout << "Fichas en almacén: " << almacen.size() << std::endl;
    std::cout << "\nFichas de cada jugador:" << std::endl;
    for (const auto& jugador : jugadores) {
        std::cout << "  " << jugador.getNombre() << ": " << jugador.getNumeroFichas() << " fichas" << std::endl;
    }
}

/**
 * Muestra las fichas en la mesa
 */
void JuegoDomino::mostrarMesa() const {
    std::cout << "Mesa: ";
    for (const auto& ficha : fichasEnMesa) {
        ficha.mostrar();
        std::cout << " ";
    }
    std::cout << std::endl;
}

/**
 * Muestra la puntuación acumulada
 */
void JuegoDomino::mostrarPuntuacion() const {
    std::cout << "\n=== PUNTUACIÓN ACUMULADA ===" << std::endl;
    for (const auto& jugador : jugadores) {
        std::cout << jugador.getNombre() << ": " << jugador.getPuntosAcumulados() << " puntos" << std::endl;
    }
}

/**
 * Limpia el estado del juego para una nueva partida
 */
void JuegoDomino::limpiarPartida() {
    for (auto& jugador : jugadores) {
        jugador.limpiarFichas();
    }
    fichasEnMesa.clear();
    almacen.clear();
    indiceJugadorActual = 0;
    jugadoresConsecutivosQuePasan = 0;
    juegoEnCurso = false;
}
