# Ejemplos Prácticos y Casos de Uso - Juego de Dominó

## 1. Ejemplo Básico: Crear y Jugar una Partida

### Flujo de Usuario

```
┌─────────────────────────────────────┐
│   BIENVENIDA AL JUEGO DE DOMINÓ     │
└─────────────────────────────────────┘

¿Cuántos jugadores desea? (2-4): 3

┌─────────────────────────────────────┐
│   MENÚ PRINCIPAL                    │
├─────────────────────────────────────┤
│ 1. Iniciar nueva partida            │
│ 2. Ver puntuación acumulada         │
│ 3. Salir                            │
└─────────────────────────────────────┘

Seleccione una opción: 1

[Distribuyendo fichas...]
[Iniciando partida...]

TURNO DE JUGADOR 1
Mesa: [6|4]
Fichas de Jugador 1: (0) [2|5] (1) [3|4] (2) [1|1] (3) [6|2] (4) [4|6]

MENÚ DE TURNO
├─ 1. Jugar ficha
├─ 2. Robar ficha
├─ 3. Ver fichas
├─ 4. Ver estado del juego
└─ 5. Pasar turno

Seleccione una opción: 1

Ingrese el índice de la ficha: 3
Ingrese la posición (0=izquierda, 1=derecha): 1

¡Ficha colocada exitosamente!

Mesa: [6|4][6|2]
```

## 2. Implementación Detallada: Flujo de un Turno

### 2.1 Escenario: Jugador con Movimiento Válido

```cpp
// Estado actual
Mesa: [5|3]
Jugador 2 - Fichas: [3|6], [2|2], [5|1], [4|3]

// El jugador puede jugar porque:
// - [3|6]: extremo 3 encaja con valor 3 de la mesa
// - [4|3]: extremo 3 encaja con valor 3 de la mesa

// Usuario selecciona colocar ficha 0 (3|6) a la derecha
juego.jugarFicha(0, 1);

// Internamente:
// 1. Valida que fichasEnMesa no esté vacía ✓
// 2. Obtiene la ficha [3|6]
// 3. Verifica encaje a la derecha:
//    - valorDerecha = 3 (extremo derecho de mesa)
//    - ficha.encajaIzquierda(3)? [3|6].encajaIzquierda(3)? ✓
// 4. Coloca la ficha: fichasEnMesa.push_back([3|6])
// 5. Elimina de la mano del jugador
// 6. Nuevo estado mesa: [5|3][3|6]

// Resultado: true, movimiento exitoso
```

### 2.2 Escenario: Jugador sin Movimiento Válido

```cpp
// Estado actual
Mesa: [2|4]
Jugador 1 - Fichas: [1|1], [5|5], [3|6], [0|0]

// Validación de movimientos:
// - [1|1]: ¿encaja con 2 o 4? NO
// - [5|5]: ¿encaja con 2 o 4? NO
// - [3|6]: ¿encaja con 2 o 4? NO
// - [0|0]: ¿encaja con 2 o 4? NO

// El jugador debe robar del almacén
ejecutarturno(); // Intenta robar

// Si almacén tiene fichas:
//   - Jugador recibe ficha al azar
//   - Si ahora puede jugar: retorna true (es su turno aún)
//   - Si aún no puede: pasa a siguiente jugador

// Si almacén está vacío:
//   - Jugador pasa turno
//   - Se incrementa jugadoresConsecutivosQuePasan
//   - Si todos pasaron: BLOQUEO
```

## 3. Validación de Movimientos: Casos Específicos

### 3.1 Caso: Ficha Doble

```cpp
// Mesa: [3|2]
// Jugador tiene: [3|3]

// Análisis:
// - Extremo izquierdo: 3
// - Extremo derecho: 2
// - Ficha: [3|3] es doble

// Posición 0 (izquierda):
//   - ¿[3|3].encajaIzquierda(3)? ✓
//   - Se coloca sin voltear
//   - Nueva mesa: [3|3][3|2]

// Posición 1 (derecha):
//   - ¿[3|3].encajaDerecha(2)? NO
//   - ¿[3|3].encajaIzquierda(2)? NO
//   - Movimiento INVÁLIDO en posición derecha
```

### 3.2 Caso: Ficha que Necesita Voltearse

```cpp
// Mesa: [4|1]
// Jugador tiene: [2|1]

// Posición 1 (derecha):
//   - Extremo derecha de mesa: 1
//   - ¿[2|1].encajaDerecha(1)? ✓
//   - Se coloca sin voltear: [4|1][2|1]

// Posición 0 (izquierda) con otra ficha:
// Mesa: [1|4]
// Jugador tiene: [2|1]

//   - Extremo izquierda de mesa: 1
//   - ¿[2|1].encajaIzquierda(1)? NO
//   - ¿[2|1].encajaDerecha(1)? ✓
//   - Se VOLTEA la ficha
//   - Se coloca volteada: [1|2][1|4]
```

## 4. Sistema de Puntuación

### 4.1 Cálculo de Puntos

```cpp
// Fin de partida:
// Ganador: Jugador 1 (jugó todas sus fichas)
// Jugador 2 - Fichas restantes: [3|5], [2|2], [6|4]
//   Puntos: 3+5 + 2+2 + 6+4 = 22
// Jugador 3 - Fichas restantes: [1|1], [4|5]
//   Puntos: 1+1 + 4+5 = 11

// Puntos para el ganador:
// Jugador 1 recibe: 22 + 11 = 33 puntos

// Puntuación acumulada:
// Jugador 1: 33
// Jugador 2: 0
// Jugador 3: 0

// Nueva partida (similar):
// Ganador: Jugador 3 (con 28 puntos)

// Puntuación acumulada final:
// Jugador 1: 33 (33 + 0)
// Jugador 2: 0  (0 + 0)
// Jugador 3: 28 (0 + 28)
```

### 4.2 Caso de Bloqueo

```cpp
// Ningún jugador puede jugar
// Fichas en mesa terminan en: [5|6]

// Fichas restantes:
// Jugador 1: [0|0], [1|1], [2|2] → Puntos: 0 + 2 + 4 = 6 ✓ GANA
// Jugador 2: [3|3], [4|4]        → Puntos: 6 + 8 = 14
// Jugador 3: [5|5], [6|6]        → Puntos: 10 + 12 = 22

// Ganador por bloqueo: Jugador 1 (menor puntuación)
// Puntos: 14 + 22 = 36
```

## 5. Flujo Completo de Una Sesión de Juego

### Estado Inicial

```
Jugadores: 3 (Jugador 1, Jugador 2, Jugador 3)

PARTIDA 1:
├─ Distribución: Cada uno recibe 7 fichas
├─ Jugador inicial: El que tiene [6|6]
├─ Turnos:
│  ├─ Jugador 1: Juega [6|6]
│  ├─ Jugador 2: Juega [6|2]
│  ├─ Jugador 3: Juega [6|4]
│  ├─ Jugador 1: Juega [2|5]
│  ├─ ... (múltiples turnos)
│  └─ Jugador 2: ¡Juega última ficha! VICTORIA
├─ Puntuación: Jugador 2 gana 45 puntos
└─ Puntuación acumulada: J1: 0, J2: 45, J3: 0

PARTIDA 2:
├─ Nueva distribución de fichas
├─ Jugador inicial calculado
├─ Turnos...
├─ Bloqueo en turno 23
├─ Ganador por bloqueo: Jugador 3 (12 puntos)
├─ Puntuación: Jugador 3 gana 38 puntos
└─ Puntuación acumulada: J1: 0, J2: 45, J3: 38

MENÚ PRINCIPAL:
┌─────────────────────────────┐
│ PUNTUACIÓN ACUMULADA        │
├─────────────────────────────┤
│ Jugador 1: 0 puntos         │
│ Jugador 2: 45 puntos        │
│ Jugador 3: 38 puntos        │
└─────────────────────────────┘

Usuario selecciona: 1 (Nueva partida)
```

## 6. Manejo de Errores: Escenarios Comunes

### 6.1 Entrada de Usuario Inválida

```
Sistema: Seleccione una opción (1-5): 
Usuario: abc

Resultado:
✗ Entrada inválida. Intente de nuevo.
Sistema: Seleccione una opción (1-5): 
```

### 6.2 Índice de Ficha Inválido

```
Sistema: Ingrese el índice de la ficha: 
Usuario: 10
(Jugador tiene solo 7 fichas)

Resultado:
✗ Movimiento inválido. Intente de nuevo.
Sistema: Ingrese el índice de la ficha: 
```

### 6.3 Número de Jugadores Inválido

```
Sistema: ¿Cuántos jugadores desea? (2-4): 
Usuario: 5

Resultado:
Error: El número de jugadores debe estar entre 2 y 4
(Programa termina)
```

## 7. Extensión: Implementar Jugador IA

### Estructura Sugerida

```cpp
class JugadorIA : public Jugador {
private:
    EstrategiaJuego* estrategia;
    
public:
    JugadorIA(const std::string& nombre, EstrategiaJuego* est)
        : Jugador(nombre), estrategia(est) {}
    
    int jugarTurnoIA(int valorIzq, int valorDer) {
        return estrategia->seleccionarFicha(*this, valorIzq, valorDer);
    }
};

// En main.cpp:
// if (esIA) {
//     JugadorIA jugador("IA " + to_string(i+1), new EstrategiaAleatoria());
// } else {
//     Jugador jugador("Jugador " + to_string(i+1));
// }
```

### Estrategias Posibles

1. **EstrategiaAleatoria**: Juega ficha válida aleatoria
2. **EstrategiaMaximaFicha**: Juega la ficha con mayor valor
3. **EstrategiaMinimizaFichas**: Juega fichas altas para reducir puntos
4. **EstrategiaDefensiva**: Intenta bloquear al oponente

## 8. Depuración: Métodos Útiles

### Visualizar Estado Completo

```cpp
// Agregar en InterfazJuego:
void mostrarEstadoCompleto() {
    std::cout << "=== ESTADO COMPLETO DEL JUEGO ===" << std::endl;
    
    // Mesa
    std::cout << "Mesa: ";
    juego.mostrarMesa();
    
    // Fichas en almacén
    std::cout << "Fichas en almacén: " << almacen.size() << std::endl;
    
    // Estado de cada jugador
    for (int i = 0; i < juego.getNumJugadores(); ++i) {
        Jugador& j = juego.getJugador(i);
        std::cout << j.getNombre() << ": " 
                  << j.getNumeroFichas() << " fichas, "
                  << j.getPuntosAcumulados() << " puntos acumulados"
                  << std::endl;
    }
    
    // Jugador actual
    std::cout << "Jugador actual: " 
              << juego.getJugadorActual().getNombre() << std::endl;
}
```

### Log de Movimientos

```cpp
// Agregar en JuegoDomino:
void registrarMovimiento(const std::string& descripcion) {
    std::ofstream log("juego_log.txt", std::ios::app);
    log << "[" << indiceJugadorActual << "] " 
        << descripcion << std::endl;
    log.close();
}

// Uso:
bool jugarFicha(int indice, int posicion) {
    // ... validación ...
    registrarMovimiento("Jugó ficha en posición " + to_string(posicion));
    // ... resto de la lógica ...
}
```

## 9. Optimización: Mejoras Posibles

### Rendimiento

```cpp
// Usar unordered_map para fichas por valor
std::unordered_map<int, std::vector<Ficha>> fichasXValor;

// En lugar de búsqueda lineal O(n):
int encontrarFichaEncajable(int valorIzq, int valorDer) {
    auto it = fichasXValor.find(valorIzq);
    if (it != fichasXValor.end() && !it->second.empty()) {
        return indiceDeLaPrimeraFicha;
    }
    // ... similar para valorDer ...
}
```

### Memoria

```cpp
// Usar std::move para trasferencia eficiente
Ficha Jugador::eliminarFicha(int indice) {
    Ficha temp = std::move(fichas[indice]);
    fichas.erase(fichas.begin() + indice);
    return temp;
}
```

---

**Documento versión**: 1.0  
**Propósito**: Guía práctica para entender y usar el juego
