#ifndef FICHA_H
#define FICHA_H

#include <iostream>
#include <stdexcept>

/**
 * @class Ficha
 * @brief Representa una ficha de dominó con dos valores en sus extremos
 * 
 * Una ficha de dominó contiene dos números (0-6) que definen sus extremos.
 * Proporciona métodos para acceder a los valores y verificar compatibilidad.
 */
class Ficha {
private:
    int izquierda;  ///< Valor del extremo izquierdo (0-6)
    int derecha;    ///< Valor del extremo derecho (0-6)

public:
    /**
     * @brief Constructor por defecto
     * @param izq Valor del extremo izquierdo (por defecto 0)
     * @param der Valor del extremo derecho (por defecto 0)
     * @throws std::invalid_argument si los valores están fuera del rango 0-6
     */
    Ficha(int izq = 0, int der = 0);

    /**
     * @brief Obtiene el valor del extremo izquierdo
     * @return Valor entero del extremo izquierdo
     */
    int getIzquierda() const { return izquierda; }

    /**
     * @brief Obtiene el valor del extremo derecho
     * @return Valor entero del extremo derecho
     */
    int getDerecha() const { return derecha; }

    /**
     * @brief Voltea la ficha invirtiendo sus valores
     * Intercambia los valores de izquierda y derecha
     */
    void voltear();

    /**
     * @brief Verifica si la ficha puede conectarse por la izquierda
     * @param valor Valor a comparar con el extremo izquierdo
     * @return true si los valores coinciden, false en caso contrario
     */
    bool encajaIzquierda(int valor) const { return izquierda == valor; }

    /**
     * @brief Verifica si la ficha puede conectarse por la derecha
     * @param valor Valor a comparar con el extremo derecho
     * @return true si los valores coinciden, false en caso contrario
     */
    bool encajaDerecha(int valor) const { return derecha == valor; }

    /**
     * @brief Verifica si la ficha es doble (ambos extremos tienen el mismo valor)
     * @return true si es doble, false en caso contrario
     */
    bool esDoble() const { return izquierda == derecha; }

    /**
     * @brief Sobrecarga del operador de igualdad
     * @param otra Ficha a comparar
     * @return true si ambas fichas tienen los mismos valores
     */
    bool operator==(const Ficha& otra) const;

    /**
     * @brief Imprime la ficha en formato visual
     */
    void mostrar() const;
};

#endif // FICHA_H
