#ifndef JUEGO_DOMINO_H
#define JUEGO_DOMINO_H

#include <vector>
#include <deque>
#include "jugador.h"
#include "historial.h"

/**
 * @brief Clase principal que gestiona el flujo completo del juego de dominó.
 * Implementa el patrón Controller para separar lógica de juego de UI.
 */
class JuegoDomino {
private:
    std::vector<Jugador> jugadores;      ///< Lista de jugadores (2-4)
    std::deque<Ficha> mesa;              ///< Cadena central de fichas jugadas
    std::vector<Ficha> mazo;             ///< Fichas restantes (no usadas en esta versión)
    HistorialMovimientos historial;      ///< Lista enlazada de movimientos
    size_t jugadorActual;                ///< Índice del jugador cuyo turno es
    bool partidaIniciada;                ///< Estado de la partida actual

public:
    JuegoDomino();

    /**
     * @brief Ejecuta el juego principal con múltiples rondas.
     */
    void ejecutar();

private:
    // Configuración inicial
    void configurarJugadores();
    void inicializarMazo();
    void barajarMazo();
    void repartirFichas(int fichasPorJugador = 7);

    // Gestión de partida
    void reiniciarPartida();
    void buclePrincipalPartida();
    
    // Lógica de juego
    bool puedeIniciarJuego() const;
    bool jugadorPuedeJugar(size_t idxJugador) const;
    bool todosBloqueados() const;
    bool procesarTurnoJugador(size_t idxJugador);
    
    // Utilidades
    void mostrarEstadoJuego() const;
    std::string representacionMesa() const;
    int calcularGanadorBloqueo() const;
    void asignarPuntosRonda(int idxGanador);

    // Validaciones de movimiento
    bool esMovimientoValido(const Ficha& ficha, bool alInicio) const;
    void ejecutarMovimiento(Jugador& jugador, size_t idxFicha, bool alInicio);
    
    // Getters privados
    int extremoIzquierdo() const;
    int extremoDerecho() const;
};

#endif