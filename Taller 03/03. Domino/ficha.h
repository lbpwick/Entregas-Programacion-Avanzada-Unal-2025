#ifndef FICHA_H
#define FICHA_H

#include <iostream>
#include <string>

/**
 * @brief Clase que representa una ficha de dominó con dos valores (0-6).
 * Implementa encapsulación con datos privados y métodos públicos controlados.
 */
class Ficha {
private:
    int izquierda;  ///< Valor del extremo izquierdo (0-6)
    int derecha;    ///< Valor del extremo derecho (0-6)

public:
    /**
     * @brief Constructor que valida rangos 0-6.
     * @param izq Valor izquierdo
     * @param der Valor derecho
     * @throws std::invalid_argument si valores fuera de rango
     */
    Ficha(int izq = 0, int der = 0);

    /// @name Getters (const-correctos)
    int getIzquierda() const { return izquierda; }
    int getDerecha() const { return derecha; }

    /// @name Setters con validación
    void setIzquierda(int v);
    void setDerecha(int v);

    /**
     * @brief Voltea la ficha intercambiando extremos.
     */
    void voltear();

    /**
     * @brief Sobrecarga para comparación de igualdad.
     */
    bool operator==(const Ficha& otra) const;

    /**
     * @brief Representación textual: "[6|3]"
     */
    std::string toString() const;
};

#endif