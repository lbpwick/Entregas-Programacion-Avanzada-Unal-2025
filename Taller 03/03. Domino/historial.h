#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>

/**
 * @brief Nodo de lista enlazada simple para almacenar movimientos del juego.
 */
struct NodoMovimiento {
    std::string jugador;
    std::string ficha;
    std::string estadoMesa;
    NodoMovimiento* siguiente;

    /**
     * @brief Constructor del nodo.
     */
    NodoMovimiento(const std::string& j, const std::string& f, const std::string& e)
        : jugador(j), ficha(f), estadoMesa(e), siguiente(nullptr) {}
};

/**
 * @brief Lista enlazada dinámica que registra historial completo de movimientos.
 * Utiliza RAII para gestión automática de memoria.
 */
class HistorialMovimientos {
private:
    NodoMovimiento* cabeza;
    NodoMovimiento* cola;
    size_t tamano;

public:
    HistorialMovimientos();
    ~HistorialMovimientos();

    /**
     * @brief Agrega movimiento al final de la lista (O(1)).
     */
    void registrarMovimiento(const std::string& jugador,
                            const std::string& ficha,
                            const std::string& estadoMesa);

    /**
     * @brief Guarda historial completo en archivo de texto.
     * @param nombreArchivo Ruta del archivo destino
     */
    void guardarEnArchivo(const std::string& nombreArchivo = "historial_domino.txt") const;

    /**
     * @brief Limpia la lista liberando memoria.
     */
    void limpiar();

    size_t getTamano() const { return tamano; }
};

#endif