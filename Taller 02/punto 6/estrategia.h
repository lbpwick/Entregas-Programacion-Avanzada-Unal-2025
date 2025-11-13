#ifndef ESTRATEGIA_JUEGO_H
#define ESTRATEGIA_JUEGO_H

#include "jugador.h"
#include <vector>

/**
 * @class EstrategiaJuego
 * @brief Clase abstracta para diferentes estrategias de juego
 * 
 * Implementa el patrón Strategy para permitir diferentes comportamientos
 * de juego sin modificar la clase JuegoDomino.
 * 
 * NOTA: Esta clase es un ejemplo de extensión futura usando polimorfismo.
 */
class EstrategiaJuego {
public:
    virtual ~EstrategiaJuego() = default;

    /**
     * @brief Selecciona una ficha para jugar
     * @param jugador El jugador que debe jugar
     * @param valorIzq Valor del extremo izquierdo de la mesa
     * @param valorDer Valor del extremo derecho de la mesa
     * @return Índice de la ficha a jugar, o -1 si no hay válida
     */
    virtual int seleccionarFicha(const Jugador& jugador, int valorIzq, int valorDer) = 0;

    /**
     * @brief Selecciona la posición donde jugar la ficha
     * @return 0 para izquierda, 1 para derecha
     */
    virtual int seleccionarPosicion() = 0;
};

/**
 * @class EstrategiaAleatoria
 * @brief Implementación de estrategia aleatoria
 * Selecciona fichas válidas de forma aleatoria
 */
class EstrategiaAleatoria : public EstrategiaJuego {
public:
    int seleccionarFicha(const Jugador& jugador, int valorIzq, int valorDer) override;
    int seleccionarPosicion() override;
};

/**
 * @class EstrategiaMaximaFicha
 * @brief Estrategia que intenta jugar la ficha con mayor valor
 * Maximiza los puntos potenciales en la mesa
 */
class EstrategiaMaximaFicha : public EstrategiaJuego {
public:
    int seleccionarFicha(const Jugador& jugador, int valorIzq, int valorDer) override;
    int seleccionarPosicion() override;
};

/**
 * @class EstrategiaMinimizaFichas
 * @brief Estrategia que intenta quedarse con fichas de bajo valor
 * Prioriza jugar fichas altas para minimizar puntos en mano
 */
class EstrategiaMinimizaFichas : public EstrategiaJuego {
public:
    int seleccionarFicha(const Jugador& jugador, int valorIzq, int valorDer) override;
    int seleccionarPosicion() override;
};

#endif // ESTRATEGIA_JUEGO_H
