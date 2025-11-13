#ifndef JUEGO_DOMINO_H
#define JUEGO_DOMINO_H

#include <vector>
#include <deque>
#include <memory>
#include "ficha.h"
#include "jugador.h"

/**
 * @class JuegoDomino
 * @brief Gestiona el flujo completo del juego de dominó
 * 
 * Esta clase encapsula toda la lógica del juego, incluyendo:
 * - Creación del conjunto de fichas
 * - Distribución de fichas a jugadores
 * - Control del turno de juego
 * - Verificación de reglas y movimientos válidos
 * - Gestión de rondas y puntuaciones
 */
class JuegoDomino {
private:
    std::vector<Jugador> jugadores;     ///< Vector de jugadores
    std::deque<Ficha> fichasEnMesa;     ///< Fichas colocadas en la mesa (orden lineal)
    std::vector<Ficha> almacen;         ///< Fichas disponibles para robar
    int indiceJugadorActual = 0;        ///< Índice del jugador que juega actualmente
    int jugadoresConsecutivosQuePasan = 0; ///< Contador de jugadores que pasan consecutivamente
    bool juegoEnCurso = false;          ///< Estado del juego

    /**
     * @brief Inicializa el conjunto completo de fichas de dominó (28 fichas)
     * Las fichas van desde [0|0] hasta [6|6]
     */
    void inicializarFichas();

    /**
     * @brief Mezcla aleatoriamente el almacén de fichas
     */
    void mezclarFichas();

    /**
     * @brief Distribuye fichas iniciales a los jugadores (7 fichas cada uno)
     */
    void distribuirFichasIniciales();

    /**
     * @brief Busca al jugador con la ficha doble más alta para que comience
     * @return Índice del jugador que debe comenzar, o 0 si no hay dobles
     */
    int encontrarJugadorInicial();

    /**
     * @brief Intenta que el jugador actual tome una ficha del almacén
     * @return true si tomó una ficha, false si el almacén está vacío
     */
    bool robarFicha();

    /**
     * @brief Verifica si el jugador actual puede realizar algún movimiento válido
     * @return true si puede jugar o hay fichas para robar
     */
    bool puedeJugarOrobar();

    /**
     * @brief Pasa el turno al siguiente jugador
     */
    void pasoturno();

    /**
     * @brief Verifica si el juego está en estado de bloqueo
     * @return true si ningún jugador puede jugar
     */
    bool estaBloqueado() const;

    /**
     * @brief Determina el ganador cuando hay bloqueo
     * El ganador es quien tiene menos puntos en sus fichas
     */
    Jugador* determinarGanadorPorBloqueo();

public:
    /**
     * @brief Constructor que inicializa el juego con un número específico de jugadores
     * @param numJugadores Número de jugadores (entre 2 y 4)
     * @throws std::invalid_argument si el número de jugadores no está en el rango válido
     */
    explicit JuegoDomino(int numJugadores);

    /**
     * @brief Obtiene el número de jugadores en el juego
     * @return Cantidad de jugadores
     */
    int getNumJugadores() const { return jugadores.size(); }

    /**
     * @brief Obtiene un jugador por su índice
     * @param indice Índice del jugador
     * @return Referencia al jugador
     */
    Jugador& getJugador(int indice) { return jugadores[indice]; }

    /**
     * @brief Obtiene el jugador actual (el que está jugando)
     * @return Referencia al jugador actual
     */
    Jugador& getJugadorActual() { return jugadores[indiceJugadorActual]; }

    /**
     * @brief Obtiene el índice del jugador actual
     * @return Índice del jugador que juega en este momento
     */
    int getIndiceJugadorActual() const { return indiceJugadorActual; }

    /**
     * @brief Inicia una nueva partida
     * Limpia fichas previas, baraja, distribuye y determina el primer jugador
     */
    void iniciarPartida();

    /**
     * @brief Realiza el movimiento de colocar una ficha en la mesa
     * @param indice Índice de la ficha en la mano del jugador actual
     * @param posicion Posición donde colocar (0 = izquierda, 1 = derecha)
     * @return true si el movimiento fue válido y se realizó, false en caso contrario
     */
    bool jugarFicha(int indice, int posicion);

    /**
     * @brief Obtiene los valores en los extremos de las fichas en la mesa
     * @param valorIzq Referencia donde se almacena el valor izquierdo
     * @param valorDer Referencia donde se almacena el valor derecho
     */
    void getExtremosActuales(int& valorIzq, int& valorDer) const;

    /**
     * @brief Ejecuta el turno del jugador actual
     * Retorna si el juego continúa o termina
     * @return true si el juego debe continuar, false si ha terminado
     */
    bool ejecutarturno();

    /**
     * @brief Verifica si la partida ha terminado
     * @return true si alguien ha ganado
     */
    bool partida_terminada() const;

    /**
     * @brief Obtiene el ganador actual
     * @return Puntero al jugador ganador, nullptr si no hay ganador aún
     */
    Jugador* getGanador();

    /**
     * @brief Muestra el estado actual del juego en la consola
     */
    void mostrarEstado() const;

    /**
     * @brief Muestra las fichas en la mesa
     */
    void mostrarMesa() const;

    /**
     * @brief Muestra la puntuación acumulada de todos los jugadores
     */
    void mostrarPuntuacion() const;

    /**
     * @brief Limpia todas las fichas para iniciar una nueva partida
     */
    void limpiarPartida();
};

#endif // JUEGO_DOMINO_H
