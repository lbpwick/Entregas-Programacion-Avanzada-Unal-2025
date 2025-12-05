#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "ficha.h"

/**
 * @brief Clase que representa un jugador con nombre, mano de fichas y puntuación.
 * Encapsula la lógica de gestión de fichas del jugador.
 */
class Jugador {
private:
    std::string nombre;
    std::vector<Ficha> mano;     ///< Fichas en posesión del jugador
    int puntuacion;              ///< Puntos acumulados en múltiples rondas

public:
    /**
     * @brief Constructor con nombre opcional.
     */
    Jugador(const std::string& n = "Anonimo");

    /// @name Acceso a propiedades
    const std::string& getNombre() const { return nombre; }
    void setNombre(const std::string& n) { nombre = n; }
    int getPuntuacion() const { return puntuacion; }
    void agregarPuntos(int p) { puntuacion += p; }

    /// @name Gestión de fichas
    void agregarFicha(const Ficha& f);
    Ficha tomarFicha(size_t indice);
    const Ficha& verFicha(size_t indice) const;
    size_t cantidadFichas() const { return mano.size(); }
    int calcularPuntosMano() const;

    /**
     * @brief Verifica si el jugador tiene ficha compatible con un número.
     */
    bool tieneFichaCompatible(int numero) const;

    /**
     * @brief Muestra las fichas del jugador numeradas.
     */
    void mostrarMano() const;
};

#endif