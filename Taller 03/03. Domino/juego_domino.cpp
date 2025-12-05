#include "juego_domino.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>

JuegoDomino::JuegoDomino() : jugadorActual(0), partidaIniciada(false) {}

void JuegoDomino::ejecutar() {
    std::cout << "\n🎮 === JUEGO DE DOMINÓ DOBLE 6 === 🎮\n";
    configurarJugadores();
    
    char continuar;
    do {
        reiniciarPartida();
        buclePrincipalPartida();
        
        std::cout << "\n🤔 ¿Jugar otra ronda? (s/n): ";
        std::cin >> continuar;
    } while (continuar == 's' || continuar == 'S');
    
    std::cout << "\n🏆 ¡Gracias por jugar!\n";
}

void JuegoDomino::configurarJugadores() {
    int numJugadores;
    do {
        std::cout << "Número de jugadores (2-4): ";
        std::cin >> numJugadores;
    } while (numJugadores < 2 || numJugadores > 4);
    
    jugadores.clear();
    std::string nombre;
    for (int i = 0; i < numJugadores; ++i) {
        std::cout << "Nombre jugador " << (i+1) << ": ";
        std::cin >> nombre;
        jugadores.emplace_back(nombre);
    }
    std::cout << "✅ Jugadores configurados.\n";
}

void JuegoDomino::inicializarMazo() {
    mazo.clear();
    // Genera las 28 fichas del doble 6 (incluyendo dobles)
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            mazo.emplace_back(i, j);
        }
    }
}

void JuegoDomino::barajarMazo() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(mazo.begin(), mazo.end(), std::mt19937(seed));
}

void JuegoDomino::repartirFichas(int fichasPorJugador) {
    size_t idxMazo = 0;
    for (auto& jugador : jugadores) {
        for (int i = 0; i < fichasPorJugador && idxMazo < mazo.size(); ++i) {
            jugador.agregarFicha(mazo[idxMazo++]);
        }
    }
}

void JuegoDomino::reiniciarPartida() {
    mesa.clear();
    historial.limpiar();
    inicializarMazo();
    barajarMazo();
    repartirFichas();
    jugadorActual = 0;
    partidaIniciada = false;
    std::cout << "\n🔄 Nueva partida iniciada.\n";
}

bool JuegoDomino::puedeIniciarJuego() const {
    return mesa.empty();
}

int JuegoDomino::extremoIzquierdo() const {
    return mesa.empty() ? -1 : mesa.front().getIzquierda();
}

int JuegoDomino::extremoDerecho() const {
    return mesa.empty() ? -1 : mesa.back().getDerecha();
}

bool JuegoDomino::jugadorPuedeJugar(size_t idxJugador) const {
    if (puedeIniciarJuego()) return true;
    
    const Jugador& jugador = jugadores[idxJugador];
    int izq = extremoIzquierdo();
    int der = extremoDerecho();
    
    return jugador.tieneFichaCompatible(izq) || jugador.tieneFichaCompatible(der);
}

bool JuegoDomino::todosBloqueados() const {
    for (size_t i = 0; i < jugadores.size(); ++i) {
        if (jugadorPuedeJugar(i)) return false;
    }
    return true;
}

std::string JuegoDomino::representacionMesa() const {
    if (mesa.empty()) return "(Mesa vacía)";
    
    std::string resultado;
    for (const auto& f : mesa) {
        resultado += f.toString() + " ";
    }
    return resultado;
}

void JuegoDomino::mostrarEstadoJuego() const {
    std::cout << "\n📊 === ESTADO DEL JUEGO ===\n";
    std::cout << "Mesa: " << representacionMesa() << "\n";
    std::cout << "Extremos: " 
              << (mesa.empty() ? "N/A" : std::to_string(extremoIzquierdo()))
              << " | " 
              << (mesa.empty() ? "N/A" : std::to_string(extremoDerecho())) << "\n";
    
    for (size_t i = 0; i < jugadores.size(); ++i) {
        std::cout << "J" << (i+1) << " " << jugadores[i].getNombre() 
                  << ": " << jugadores[i].cantidadFichas() << " fichas ("
                  << jugadores[i].getPuntuacion() << " pts)\n";
    }
    std::cout << "Turno: " << jugadores[jugadorActual].getNombre() << "\n";
    std::cout << "=======================\n";
}

bool JuegoDomino::esMovimientoValido(const Ficha& ficha, bool alInicio) const {
    if (puedeIniciarJuego()) return true;
    
    int extremo = alInicio ? extremoIzquierdo() : extremoDerecho();
    return ficha.getIzquierda() == extremo || ficha.getDerecha() == extremo;
}

void JuegoDomino::ejecutarMovimiento(Jugador& jugador, size_t idxFicha, bool alInicio) {
    Ficha ficha = jugador.tomarFicha(idxFicha);
    
    // Rotar si es necesario
    if (!puedeIniciarJuego()) {
        int extremo = alInicio ? extremoIzquierdo() : extremoDerecho();
        if (ficha.getIzquierda() != extremo) {
            ficha.voltear();
        }
    }
    
    // Colocar en mesa
    if (alInicio) {
        mesa.push_front(ficha);
    } else {
        mesa.push_back(ficha);
    }
    
    // Registrar en historial
    historial.registrarMovimiento(jugador.getNombre(), 
                                  ficha.toString(), 
                                  representacionMesa());
}

bool JuegoDomino::procesarTurnoJugador(size_t idxJugador) {
    Jugador& jugador = jugadores[idxJugador];
    
    if (!jugadorPuedeJugar(idxJugador)) {
        std::cout << jugador.getNombre() << " pasa (no tiene movimientos).\n";
        return false;
    }
    
    jugador.mostrarMano();
    std::cout << "\nMesa: " << representacionMesa() << "\n";
    
    if (puedeIniciarJuego()) {
        std::cout << "🎯 Selecciona ficha para INICIAR (0-" 
                  << (jugador.cantidadFichas()-1) << "): ";
    } else {
        std::cout << "🎯 Ficha (-1=pasar, 0-" << (jugador.cantidadFichas()-1) << "): ";
    }
    
    int opcion;
    std::cin >> opcion;
    
    if (opcion < 0) {
        std::cout << "Pasando turno...\n";
        return false;
    }
    
    if (opcion >= static_cast<int>(jugador.cantidadFichas())) {
        std::cout << "❌ Índice inválido.\n";
        return false;
    }
    
    char lado;
    if (!puedeIniciarJuego()) {
        std::cout << "Lado: [I]nicio o [F]inal? ";
        std::cin >> lado;
        bool alInicio = (lado == 'I' || lado == 'i');
        
        if (!esMovimientoValido(jugador.verFicha(opcion), alInicio)) {
            std::cout << "❌ Ficha no compatible con ese extremo.\n";
            return false;
        }
        
        ejecutarMovimiento(jugador, opcion, alInicio);
    } else {
        ejecutarMovimiento(jugador, opcion, false);
    }
    
    std::cout << "✅ " << jugador.getNombre() << " juega " 
              << jugador.verFicha(opcion).toString() << "\n";
    
    partidaIniciada = true;
    return jugador.cantidadFichas() == 0; // Ganó?
}

int JuegoDomino::calcularGanadorBloqueo() const {
    int mejorIdx = -1;
    int menorPuntos = INT_MAX;
    
    for (size_t i = 0; i < jugadores.size(); ++i) {
        int puntos = jugadores[i].calcularPuntosMano();
        if (puntos < menorPuntos) {
            menorPuntos = puntos;
            mejorIdx = static_cast<int>(i);
        }
    }
    return mejorIdx;
}

void JuegoDomino::asignarPuntosRonda(int idxGanador) {
    int puntosTotales = 0;
    
    for (size_t i = 0; i < jugadores.size(); ++i) {
        if (static_cast<int>(i) != idxGanador) {
            puntosTotales += jugadores[i].calcularPuntosMano();
        }
    }
    
    jugadores[idxGanador].agregarPuntos(puntosTotales);
}

void JuegoDomino::buclePrincipalPartida() {
    bool finPartida = false;
    int idxGanador = -1;
    
    while (!finPartida) {
        mostrarEstadoJuego();
        
        bool gano = procesarTurnoJugador(jugadorActual);
        if (gano) {
            idxGanador = static_cast<int>(jugadorActual);
            finPartida = true;
            std::cout << "\n🎉 " << jugadores[idxGanador].getNombre() 
                      << " GANA LA RONDA!\n";
        } else if (todosBloqueados()) {
            idxGanador = calcularGanadorBloqueo();
            finPartida = true;
            std::cout << "\n⚠️  RONDA BLOQUEADA!\n";
        }
        
        jugadorActual = (jugadorActual + 1) % jugadores.size();
    }
    
    // Finalizar ronda
    historial.guardarEnArchivo();
    asignarPuntosRonda(idxGanador);
    
    std::cout << "\n🏅 PUNTUACIONES ACUMULADAS:\n";
    for (const auto& j : jugadores) {
        std::cout << j.getNombre() << ": " << j.getPuntuacion() << " pts\n";
    }
}