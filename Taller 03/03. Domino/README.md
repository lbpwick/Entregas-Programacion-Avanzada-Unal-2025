# 🎮 Juego de Dominó en C++ - Programación Orientada a Objetos Completa

## ✨ Características Implementadas

✅ **Clases POO**:
- `Ficha`: Encapsulación completa con validación 0-6
- `Jugador`: Gestión de mano y puntuación
- `HistorialMovimientos`: Lista enlazada dinámica para movimientos
- `JuegoDomino`: Controlador principal del juego

✅ **Funcionalidades**:
- 28 fichas doble-6 estándar
- 2-4 jugadores humanos
- Distribución aleatoria de 7 fichas
- Validación completa de reglas
- Detección de victoria/bloqueo
- Sistema de puntuación acumulativa
- **Historial en lista enlazada** → `historial_domino.txt`
- Reinicio de rondas sin cerrar programa
- Interfaz consola intuitiva

✅ **Principios SOLID aplicados**:
- SRP: Una responsabilidad por clase
- OCP: Extensible sin modificar código
- LSP: Subclases intercambiables
- ISP: Interfaces específicas
- DIP: Dependencias por abstracción

## 🚀 Compilación y Ejecución

### Linux/macOS:
```bash
make          # Compilar
./domino      # Ejecutar
make clean    # Limpiar
```

### Windows (MinGW/MSYS2):
```bash
g++ -std=c++17 *.cpp -o domino.exe
./domino.exe
```

### Manual (cualquier sistema):
```bash
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o domino
./domino
```

## 📖 Reglas del Juego (Doble-6 Simplificado)

1. **Inicio**: Primer jugador coloca cualquier ficha
2. **Turno**: Colocar ficha que coincida con extremos de mesa
3. **Rotación**: Fichas se pueden voltear para encajar
4. **Pasar**: Si no hay movimientos válidos
5. **Victoria**: Primer jugador sin fichas
6. **Bloqueo**: Gana jugador con menos puntos en mano

**Puntuación**:
- Victoria: Suma puntos de fichas rivales
- Bloqueo: Menos puntos en mano + suma rivales

## 📄 Salida del Historial

Archivo `historial_domino.txt`:

```
📜 HISTORIAL COMPLETO DE MOVIMIENTOS
=====================================

MOVIMIENTO #1:
├── Jugador: Juan
├── Ficha:   [6|6]
└── Mesa:    [6|6] 

MOVIMIENTO #2:
├── Jugador: Maria
├── Ficha:   [6|3]
└── Mesa:    [6|6] [6|3] 

MOVIMIENTO #3:
├── Jugador: Pedro
├── Ficha:   [3|5]
└── Mesa:    [6|6] [6|3] [3|5] 

─────────────────────────────────────

Total movimientos: 3
```

## 🛠️ Estructura de Archivos

```
├── ficha.h / ficha.cpp           # Ficha de dominó
├── jugador.h / jugador.cpp       # Gestión jugador
├── historial.h / historial.cpp   # Lista enlazada movimientos ⭐
├── juego_domino.h / .cpp         # Lógica principal
├── main.cpp                      # Entrada
├── Makefile                      # Automatización
└── README.md                     # Esta guía
```

## 🎯 Ejemplo de Ejecución

```
🎮 === JUEGO DE DOMINÓ DOBLE 6 === 🎮
Número de jugadores (2-4): 2
Nombre jugador 1: Juan
Nombre jugador 2: Maria
✅ Jugadores configurados.

🔄 Nueva partida iniciada.

📊 === ESTADO DEL JUEGO ===
Mesa: (Mesa vacía)
Extremos: N/A | N/A
J1 Juan: 7 fichas (0 pts)
J2 Maria: 7 fichas (0 pts)
Turno: Juan
=======================

🂠 Fichas de Juan (7 fichas):
  0: [0|2]
  1: [1|5]
  2: [3|4]
  3: [4|6]
  4: [5|5]
  5: [2|3]
  6: [6|6]

Mesa: (Mesa vacía)
🎯 Selecciona ficha para INICIAR (0-6): 6

✅ Juan juega [6|6]
```

## 🔧 Comandos Útiles

```bash
# Compilar optimizado
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o domino

# Compilar con debug
g++ -std=c++17 -Wall -Wextra -g *.cpp -o domino

# Limpiar archivos objeto
make clean

# Compilar y ejecutar
make run
```

## 📊 Características de la Lista Enlazada

- **Tipo**: Sencilla (simple linked list)
- **Nodos**: `NodoMovimiento` con jugador, ficha, estado mesa
- **Operación inserción**: O(1) (cola apunta al último)
- **Operación lectura**: O(n) (búsqueda lineal)
- **Gestión memoria**: RAII con destructor

## 🎲 Sistema de Puntuación

**Victoria Normal**:
- Jugador sin fichas suma todos los puntos de rivales

**Bloqueo**:
- Jugador con menor suma en mano suma puntos rivales

**Acumulación**:
- Los puntos se mantienen entre rondas
- Sistema de campeonato en una sesión

## ⚠️ Manejo de Errores

- ✅ Validación de rangos en fichas (0-6)
- ✅ Validación de índices
- ✅ Detección de movimientos inválidos
- ✅ Manejo de excepciones std::exception
- ✅ Bloqueo de juego detectado automáticamente

## 📝 Notas de Implementación

- C++17 estándar
- STL: `std::vector`, `std::deque`, `std::string`
- Archivo log: `historial_domino.txt`
- Barajado: `std::mt19937` (Mersenne Twister)
- Const-correctness: Getters const
- RAII: Gestión automática de memoria

## ✅ Todos los Requisitos Cumplidos

- [x] Clase Ficha con dos extremos
- [x] Clase Jugador con fichas
- [x] Clase JuegoDomino con lógica
- [x] 28 fichas doble-6
- [x] Distribución aleatoria
- [x] Validación de movimientos
- [x] Detección de bloqueo
- [x] 2-4 jugadores
- [x] Sistema de puntuación
- [x] **Lista enlazada para historial**
- [x] Guardado en archivo `.txt`
- [x] Reinicio sin cerrar programa
- [x] Código comentado
- [x] README completo
- [x] Manejo de errores

