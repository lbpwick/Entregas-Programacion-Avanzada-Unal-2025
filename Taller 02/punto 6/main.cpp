#include <iostream>
#include <string>
#include <limits>
#include "juego_domino.h"

/**
 * @class InterfazJuego
 * @brief Interfaz de usuario en consola para el juego de dominó
 * Maneja la interacción con el usuario y muestra el estado del juego
 */
class InterfazJuego {
private:
    JuegoDomino& juego;
    bool juegoActivo = true;

public:
    /**
     * @brief Constructor que recibe una referencia al juego
     * @param j Referencia a la instancia del juego de dominó
     */
    explicit InterfazJuego(JuegoDomino& j) : juego(j) {}

    /**
     * @brief Muestra el menú principal
     */
    void mostrarMenuPrincipal() const {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║     JUEGO DE DOMINÓ - MENÚ PRINCIPAL║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "1. Iniciar nueva partida" << std::endl;
        std::cout << "2. Ver puntuación acumulada" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
    }

    /**
     * @brief Muestra el menú de acciones durante el turno
     */
    void mostrarMenuturno() const {
        std::cout << "\n╔════════════════════════════════════╗" << std::endl;
        std::cout << "║         MENÚ DE TURNO              ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
        std::cout << "1. Jugar ficha" << std::endl;
        std::cout << "2. Robar ficha" << std::endl;
        std::cout << "3. Ver fichas" << std::endl;
        std::cout << "4. Ver estado del juego" << std::endl;
        std::cout << "5. Pasar turno" << std::endl;
        std::cout << "Seleccione una opción: ";
    }

    /**
     * @brief Limpia la pantalla (compatible con Windows y Linux)
     */
    void limpiarPantalla() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    /**
     * @brief Imprime un encabezado centrado
     * @param texto Texto a mostrar
     */
    void imprimirEncabezado(const std::string& texto) const {
        std::cout << "\n╔";
        for (size_t i = 0; i < 36; ++i) std::cout << "═";
        std::cout << "╗" << std::endl;
        std::cout << "║ " << texto << std::string(33 - texto.length(), ' ') << "║" << std::endl;
        std::cout << "╚";
        for (size_t i = 0; i < 36; ++i) std::cout << "═";
        std::cout << "╝" << std::endl;
    }

    /**
     * @brief Maneja un turno completo del juego
     * @return true si el turno se realizó exitosamente, false si el juego terminó
     */
    bool manejarturno() {
        limpiarPantalla();
        
        Jugador& jugadorActual = juego.getJugadorActual();
        imprimirEncabezado("TURNO DE " + jugadorActual.getNombre());

        juego.mostrarMesa();
        jugadorActual.mostrarFichas();

        int opcion;
        while (true) {
            mostrarMenuturno();
            std::cin >> opcion;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada inválida. Intente de nuevo." << std::endl;
                continue;
            }

            switch (opcion) {
                case 1: {
                    // Jugar ficha
                    std::cout << "\nIngrese el índice de la ficha: ";
                    int indice;
                    std::cin >> indice;

                    std::cout << "Ingrese la posición (0=izquierda, 1=derecha): ";
                    int posicion;
                    std::cin >> posicion;

                    if (juego.jugarFicha(indice, posicion)) {
                        std::cout << "¡Ficha colocada exitosamente!" << std::endl;
                        juego.pasoturno();
                        return true;
                    } else {
                        std::cout << "Movimiento inválido. Intente de nuevo." << std::endl;
                    }
                    break;
                }
                case 2: {
                    // Robar ficha
                    int valorIzq, valorDer;
                    juego.getExtremosActuales(valorIzq, valorDer);

                    if (!jugadorActual.puedejugar(valorIzq, valorDer)) {
                        std::cout << "Robando ficha del almacén..." << std::endl;
                        juego.ejecutarturno();
                        juego.pasoturno();
                        return true;
                    } else {
                        std::cout << "Aún puede jugar una ficha válida." << std::endl;
                    }
                    break;
                }
                case 3: {
                    // Ver fichas
                    jugadorActual.mostrarFichas();
                    break;
                }
                case 4: {
                    // Ver estado del juego
                    juego.mostrarEstado();
                    break;
                }
                case 5: {
                    // Pasar turno
                    std::cout << "Pasando turno..." << std::endl;
                    juego.pasoturno();
                    juego.ejecutarturno();
                    return true;
                }
                default:
                    std::cout << "Opción no válida." << std::endl;
            }
        }
    }

    /**
     * @brief Muestra el resultado final de una partida
     */
    void mostrarResultado() {
        limpiarPantalla();
        Jugador* ganador = juego.getGanador();

        if (ganador) {
            imprimirEncabezado("¡FIN DE LA PARTIDA!");
            std::cout << "\n¡Felicidades! " << ganador->getNombre() << " ha ganado la partida." << std::endl;
            int puntosGanados = 0;
            for (int i = 0; i < juego.getNumJugadores(); ++i) {
                Jugador& j = juego.getJugador(i);
                if (&j != ganador) {
                    puntosGanados += j.calcularPuntuacionFichas();
                }
            }
            ganador->agregarPuntos(puntosGanados);
            std::cout << "Puntos ganados en esta partida: " << puntosGanados << std::endl;
        }

        juego.mostrarPuntuacion();
    }

    /**
     * @brief Ejecuta el flujo principal del juego
     */
    void ejecutar() {
        while (juegoActivo) {
            limpiarPantalla();
            mostrarMenuPrincipal();

            int opcion;
            std::cin >> opcion;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            switch (opcion) {
                case 1: {
                    juego.iniciarPartida();
                    juego.mostrarEstado();
                    std::cout << "\nPresione Enter para comenzar...";
                    std::cin.ignore();
                    std::cin.get();

                    while (!juego.partida_terminada()) {
                        if (!manejarturno()) break;
                    }

                    mostrarResultado();
                    std::cout << "\nPresione Enter para continuar...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                }
                case 2:
                    limpiarPantalla();
                    juego.mostrarPuntuacion();
                    std::cout << "\nPresione Enter para continuar...";
                    std::cin.ignore();
                    std::cin.get();
                    break;
                case 3:
                    juegoActivo = false;
                    std::cout << "\n¡Gracias por jugar! Adiós." << std::endl;
                    break;
                default:
                    std::cout << "Opción no válida." << std::endl;
            }
        }
    }
};

/**
 * @brief Función principal
 * Punto de entrada del programa
 */
int main() {
    try {
        std::cout << "¿Cuántos jugadores desea? (2-4): ";
        int numJugadores;
        std::cin >> numJugadores;

        JuegoDomino juego(numJugadores);
        InterfazJuego interfaz(juego);
        interfaz.ejecutar();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
