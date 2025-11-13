#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "ficha.h"

/**
 * @class Jugador
 * @brief Representa a un jugador en el juego de dominó
 * 
 * Cada jugador posee un nombre y una colección de fichas de dominó.
 * Encapsula las operaciones relacionadas con las fichas del jugador.
 */
class Jugador {
private:
    std::string nombre;              ///< Nombre del jugador
    std::vector<Ficha> fichas;       ///< Colección de fichas del jugador
    int puntosAcumulados = 0;        ///< Puntos acumulados en partidas anteriores

public:
    /**
     * @brief Constructor que inicializa un jugador con su nombre
     * @param n Nombre del jugador
     */
    explicit Jugador(const std::string& n) : nombre(n) {}

    /**
     * @brief Obtiene el nombre del jugador
     * @return Nombre del jugador
     */
    std::string getNombre() const { return nombre; }

    /**
     * @brief Obtiene la cantidad de fichas que posee el jugador
     * @return Número de fichas en la mano del jugador
     */
    int getNumeroFichas() const { return fichas.size(); }

    /**
     * @brief Obtiene los puntos acumulados del jugador
     * @return Total de puntos acumulados
     */
    int getPuntosAcumulados() const { return puntosAcumulados; }

    /**
     * @brief Agrega puntos al total acumulado
     * @param puntos Puntos a agregar
     */
    void agregarPuntos(int puntos) { puntosAcumulados += puntos; }

    /**
     * @brief Agrega una ficha al conjunto de fichas del jugador
     * @param ficha Ficha a agregar
     */
    void agregarFicha(const Ficha& ficha) { fichas.push_back(ficha); }

    /**
     * @brief Obtiene una ficha específica por índice
     * @param indice Índice de la ficha (0 basado)
     * @return Referencia constante a la ficha
     * @throws std::out_of_range si el índice es inválido
     */
    const Ficha& getFicha(int indice) const;

    /**
     * @brief Elimina una ficha por índice
     * @param indice Índice de la ficha a eliminar
     * @return La ficha que fue eliminada
     * @throws std::out_of_range si el índice es inválido
     */
    Ficha eliminarFicha(int indice);

    /**
     * @brief Obtiene el vector completo de fichas del jugador
     * @return Vector constante de fichas
     */
    const std::vector<Ficha>& getFichas() const { return fichas; }

    /**
     * @brief Verifica si el jugador puede jugar una ficha dado un valor
     * @param valorIzq Valor del extremo izquierdo de la mesa
     * @param valorDer Valor del extremo derecho de la mesa
     * @return true si el jugador tiene al menos una ficha que encaje
     */
    bool puedejugar(int valorIzq, int valorDer) const;

    /**
     * @brief Busca una ficha que pueda encajar en la mesa
     * @param valorIzq Valor del extremo izquierdo de la mesa
     * @param valorDer Valor del extremo derecho de la mesa
     * @return Índice de la ficha que encaja, o -1 si no hay ninguna
     */
    int encontrarFichaEncajable(int valorIzq, int valorDer) const;

    /**
     * @brief Calcula la puntuación total de las fichas que posee el jugador
     * @return Suma de los valores de ambos extremos de todas las fichas
     */
    int calcularPuntuacionFichas() const;

    /**
     * @brief Muestra todas las fichas del jugador en la consola
     */
    void mostrarFichas() const;

    /**
     * @brief Vacía la colección de fichas del jugador
     * Utilizada para reiniciar partidas
     */
    void limpiarFichas() { fichas.clear(); }

    /**
     * @brief Reinicia los puntos acumulados
     * Opcional, utilizada si se desea resetear toda la puntuación
     */
    void reiniciarPuntos() { puntosAcumulados = 0; }
};

#endif // JUGADOR_H
