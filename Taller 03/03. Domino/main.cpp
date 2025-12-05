#include "juego_domino.h"

/**
 * @brief Punto de entrada principal del programa.
 */
int main() {
    try {
        JuegoDomino juego;
        juego.ejecutar();
    } catch (const std::exception& e) {
        std::cerr << "❌ Error crítico: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}