# Juego de Dominó en C++ con Programación Orientada a Objetos

## 📋 Descripción

Implementación completa de un juego de dominó en C++ utilizando principios sólidos de Programación Orientada a Objetos (POO). El juego soporta entre 2 y 4 jugadores humanos, con un sistema de puntuación acumulativa y una interfaz de consola intuitiva.

## 🎮 Características Principales

### Clases Implementadas

#### **Ficha (ficha.h, ficha.cpp)**
- Representa una ficha de dominó con dos valores (0-6) en sus extremos
- Métodos para validar encaje, voltear fichas y verificar fichas dobles
- Sobrecarga del operador de igualdad

#### **Jugador (jugador.h, jugador.cpp)**
- Gestiona las fichas de un jugador
- Mantiene registro de puntos acumulados
- Implementa búsqueda de fichas válidas y cálculo de puntuaciones

#### **JuegoDomino (juego_domino.h, juego_domino.cpp)**
- Controla el flujo completo del juego
- Maneja la creación de las 28 fichas estándar
- Distribuye fichas aleatoriamente a jugadores
- Verifica reglas y validez de movimientos
- Gestiona turnos y detecta bloqueos

#### **InterfazJuego (main.cpp)**
- Interfaz de usuario en consola
- Menú principal para iniciar partidas
- Menú de turno para acciones del jugador
- Muestra estado del juego y puntuación acumulada

## 🏗️ Estructura de Programación Orientada a Objetos

### **Encapsulación**
- Datos privados (fichas, nombre, puntos) con acceso controlado mediante getters
- Métodos privados para operaciones internas del juego

### **Herencia y Polimorfismo**
Aunque el diseño actual es composición, es extensible para agregar:
- Clase base `Jugador` con variantes como `JugadorIA`
- Polimorfismo para diferentes estrategias de juego

### **Principios SOLID Aplicados**
- **Single Responsibility**: Cada clase tiene una responsabilidad clara
- **Open/Closed**: Diseño fácil de extender (agregar IA, nuevas reglas)
- **Liskov Substitution**: Interfaces consistentes
- **Interface Segregation**: Métodos específicos en cada clase
- **Dependency Inversion**: Bajo acoplamiento entre clases

## 📁 Archivos del Proyecto

```
.
├── ficha.h              # Definición de la clase Ficha
├── ficha.cpp            # Implementación de Ficha
├── jugador.h            # Definición de la clase Jugador
├── jugador.cpp          # Implementación de Jugador
├── juego_domino.h       # Definición de la clase JuegoDomino
├── juego_domino.cpp     # Implementación de JuegoDomino
├── main.cpp             # Interfaz de usuario y función main
├── Makefile             # Configuración de compilación
└── README.md            # Este archivo
```

## 🔧 Compilación y Ejecución

### En Linux/macOS

```bash
# Compilar el proyecto
make

# Ejecutar el juego
make run

# Limpiar archivos compilados
make clean
```

### En Windows (con MinGW)

```bash
# Compilar
mingw32-make

# Ejecutar
mingw32-make run

# Limpiar
mingw32-make clean
```

### Compilación Manual

```bash
g++ -Wall -Wextra -std=c++17 -O2 -c ficha.cpp
g++ -Wall -Wextra -std=c++17 -O2 -c jugador.cpp
g++ -Wall -Wextra -std=c++17 -O2 -c juego_domino.cpp
g++ -Wall -Wextra -std=c++17 -O2 -c main.cpp
g++ -Wall -Wextra -std=c++17 -O2 -o domino ficha.o jugador.o juego_domino.o main.o
./domino
```

## 📖 Reglas del Dominó

### Objetivo
Ser el primer jugador en colocar todas sus fichas en la mesa, o tener la menor puntuación cuando el juego se bloquea.

### Inicio
- Cada jugador recibe 7 fichas al azar
- El jugador con la ficha doble más alta comienza
- Si no hay dobles, comienza el primer jugador

### Turno
1. **Colocar Ficha**: Coloca una ficha cuyos extremos coincidan con los valores en los extremos de la mesa
2. **Robar**: Si no puede jugar, roba del almacén
3. **Pasar**: Si roba y aún no puede jugar, pasa el turno

### Fin de Partida
- **Victoria**: Un jugador coloca todas sus fichas
- **Bloqueo**: Cuando todos los jugadores pasan consecutivamente
  - En bloqueo, gana quien tenga menos puntos en sus fichas restantes

### Puntuación
- En cada partida, el ganador recibe puntos iguales a la suma de los puntajes de los demás jugadores
- Los puntos se acumulan a través de múltiples partidas

## 🎯 Características Implementadas

✅ Clase Ficha con validación de valores  
✅ Clase Jugador con gestión de fichas  
✅ Clase JuegoDomino con lógica completa  
✅ Distribución aleatoria de fichas (28 fichas)  
✅ Validación de movimientos según reglas  
✅ Soporte para 2-4 jugadores  
✅ Sistema de puntuación acumulativa  
✅ Interfaz de consola interactiva  
✅ Manejo de excepciones  
✅ Código comentado y documentado  
✅ Reinicio de partidas sin reiniciar el programa  
✅ Detección de bloqueos  
✅ Principios POO (Encapsulación, Herencia, Polimorfismo)  

## 🎮 Uso del Juego

### Menú Principal
```
1. Iniciar nueva partida   - Comienza una nueva ronda
2. Ver puntuación acumulada - Muestra puntos totales
3. Salir                    - Cierra el programa
```

### Menú de Turno
```
1. Jugar ficha      - Coloca una ficha en la mesa
2. Robar ficha      - Toma una ficha del almacén
3. Ver fichas       - Muestra tus fichas disponibles
4. Ver estado       - Muestra información del juego
5. Pasar turno      - Pasa al siguiente jugador
```

## 💡 Ejemplos de Uso

### Jugar una Ficha
1. Selecciona opción 1 en el menú de turno
2. Ingresa el índice de la ficha (mostrado en paréntesis)
3. Elige posición: 0 para izquierda, 1 para derecha
4. Sistema valida automáticamente

### Ver Fichas
```
Fichas de Jugador 1: (0) [2|5] (1) [3|4] (2) [1|1] (3) [6|2]
```

## 🔄 Flujo del Juego

```
Inicio
  ↓
Crear jugadores
  ↓
Inicializar y mezclar fichas
  ↓
Distribuir fichas
  ↓
Determinar primer jugador
  ↓
BUCLE: Mientras juego no termine
  ├─ Mostrar estado del juego
  ├─ Turno del jugador actual
  │  ├─ Intentar jugar ficha
  │  ├─ Robar si es necesario
  │  └─ Pasar turno al siguiente
  ├─ Verificar condición de victoria
  └─ Verificar bloqueo
  ↓
Mostrar ganador y puntuación
  ↓
¿Nueva partida? → Ir a "Inicializar fichas"
  ↓
Fin
```

## 🛠️ Extensiones Futuras

### Posibles Mejoras
- Implementar Jugador IA con estrategia
- Agregar dificultad de IA (fácil, medio, difícil)
- Sistema de deshacer movimientos
- Guardado y carga de partidas
- Variantes del dominó (mexicano, all-fives, etc.)
- Interfaz gráfica (SDL2, SFML)
- Multijugador en red
- Estadísticas detalladas

### Patrón de Diseño Extensible
```cpp
// Estructura para fácil extensión
class Jugador { /* base */ };
class JugadorHumano : public Jugador { /* implementación actual */ };
class JugadorIA : public Jugador { /* estrategia de IA */ };
```

## 📝 Notas Técnicas

### Dependencias
- C++17 o superior
- Compilador: g++, clang, MSVC
- Librerías estándar de C++ (STL)

### Complejidad
- **Complejidad Espacial**: O(J + F) donde J es número de jugadores, F es fichas
- **Complejidad Temporal**: O(n) por turno, donde n es número de fichas del jugador

### Manejo de Errores
- Validación de rangos en Ficha (0-6)
- Índices válidos en búsqueda de fichas
- Detección de condiciones de juego
- Excepciones std::invalid_argument y std::out_of_range

