# 🏗️ DISEÑO Y ARQUITECTURA - Juego de Dominó en C++

## Tabla de Contenidos
1. [Visión General](#visión-general)
2. [Arquitectura del Sistema](#arquitectura-del-sistema)
3. [Diseño de Clases](#diseño-de-clases)
4. [Patrones de Diseño](#patrones-de-diseño)
5. [Flujo de Datos](#flujo-de-datos)
6. [Estructura de la Lista Enlazada](#estructura-de-la-lista-enlazada)
7. [Decisiones de Diseño](#decisiones-de-diseño)
8. [Extensibilidad](#extensibilidad)

---

## 📊 Visión General

### Propósito
Implementar un juego de dominó completo con:
- **Programación Orientada a Objetos (POO)** pura
- **Estructura de datos dinámica** (lista enlazada) para historial
- **Sistema de puntuación** entre múltiples rondas
- **Interfaz de usuario** en consola

### Requisitos Clave
- ✅ 2-4 jugadores humanos
- ✅ 28 fichas doble-6 estándar
- ✅ Validación de movimientos
- ✅ Historial persistente en archivo
- ✅ Reinicio sin cerrar programa
- ✅ Manejo de excepciones

---

## 🏛️ Arquitectura del Sistema

### Diagrama de Capas

```
┌─────────────────────────────────────┐
│     CAPA DE PRESENTACIÓN            │
│  (Interfaz Consola - main.cpp)      │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│     CAPA DE LÓGICA DE JUEGO         │
│  (JuegoDomino - Controlador)        │
├──────────────────────────────────────┤
│ • Flujo de turnos                    │
│ • Validación de movimientos         │
│ • Cálculo de puntos                 │
│ • Gestión de estado                 │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│     CAPA DE MODELOS DE DATOS        │
├──────────────────────────────────────┤
│ • Ficha (entidad de juego)          │
│ • Jugador (participante)            │
│ • HistorialMovimientos (persistencia)│
└──────────────────────────────────────┘
```

### Dependencias Entre Módulos

```
main.cpp
  └─► JuegoDomino (controlador)
       ├─► Jugador (vector)
       │    └─► Ficha (vector)
       ├─► Ficha (deque mesa)
       ├─► HistorialMovimientos (lista enlazada)
       │    └─► NodoMovimiento (nodo)
       └─► std (STL containers)
```

---

## 🎯 Diseño de Clases

### Clase Ficha

**Responsabilidad**: Representar una ficha de dominó con dos extremos.

**Atributos Privados**:
```cpp
int izquierda;    // Valor 0-6
int derecha;      // Valor 0-6
```

**Métodos Públicos**:
- `getIzquierda()` : int const - Obtener extremo izquierdo
- `getDerecha()` : int const - Obtener extremo derecho
- `setIzquierda(int)` : void - Establecer con validación
- `setDerecha(int)` : void - Establecer con validación
- `voltear()` : void - Intercambiar extremos
- `operator==()` : bool - Comparación flexible
- `toString()` : string - Representación "[x|y]"

**Validación**:
- Constructor lanza `std::invalid_argument` si valores no están en [0,6]
- Setters validan antes de asignar

**Complejidad**:
- Espacio: O(1)
- Acceso: O(1)

---

### Clase Jugador

**Responsabilidad**: Gestionar fichas y puntuación de un jugador.

**Atributos Privados**:
```cpp
std::string nombre;
std::vector<Ficha> mano;      // Fichas en posesión
int puntuacion;               // Puntos acumulados
```

**Métodos Públicos Clave**:
- `agregarFicha(const Ficha&)` : void - O(1) amortizado
- `tomarFicha(size_t)` : Ficha - O(n) por erase
- `verFicha(size_t)` : const Ficha& - O(1)
- `cantidadFichas()` : size_t - O(1)
- `calcularPuntosMano()` : int - O(n)
- `tieneFichaCompatible(int)` : bool - O(n)
- `mostrarMano()` : void - O(n) visualización

**Invariantes**:
- Nombre nunca vacío
- Puntuación siempre >= 0
- Vector de fichas ordenado por índice

**Complejidad**:
- Espacio: O(n) donde n = número de fichas
- Búsqueda: O(n)

---

### Nodo de Lista Enlazada (NodoMovimiento)

**Responsabilidad**: Almacenar información de un movimiento.

**Estructura**:
```cpp
struct NodoMovimiento {
    std::string jugador;      // Nombre del jugador
    std::string ficha;        // "[x|y]"
    std::string estadoMesa;   // Representación mesa post-movimiento
    NodoMovimiento* siguiente; // Apuntador a siguiente nodo
};
```

**Propiedades**:
- Nodo simple (sin apuntador anterior)
- Inmutable después de construcción
- Reutilizable entre partidas
- Gestión de memoria en HistorialMovimientos

---

### Clase HistorialMovimientos

**Responsabilidad**: Mantener lista enlazada de movimientos.

**Atributos Privados**:
```cpp
NodoMovimiento* cabeza;  // Primer movimiento
NodoMovimiento* cola;    // Último movimiento (O(1) insert)
size_t tamano;           // Número de movimientos
```

**Métodos Públicos**:
- `registrarMovimiento(...)` : void - O(1) inserción
- `guardarEnArchivo(const string&)` : void - O(n) escritura
- `limpiar()` : void - O(n) liberación memoria
- `getTamano()` : size_t - O(1)

**Características de Diseño**:
- Cola apunta al último nodo → inserción O(1)
- Destructor llama a `limpiar()` → RAII
- Métodos privados desactivados (no hay removeFirst, etc.)

**Garantías**:
- No hay fugas de memoria (destructor completo)
- Coherencia: si cabeza es nulo, cola es nulo y tamano es 0

**Complejidad**:
```
Operación              | Complejidad
─────────────────────────────────────
Registrar movimiento   | O(1)
Guardar en archivo     | O(n)
Limpiar lista          | O(n)
Obtener tamaño         | O(1)
```

---

### Clase JuegoDomino (Controlador)

**Responsabilidad**: Gestionar flujo completo del juego.

**Atributos Privados**:
```cpp
std::vector<Jugador> jugadores;           // 2-4 jugadores
std::deque<Ficha> mesa;                   // Cadena de fichas
std::vector<Ficha> mazo;                  // Fichas para repartir
HistorialMovimientos historial;           // Historial liga enlazada
size_t jugadorActual;                     // Índice turno actual
bool partidaIniciada;                     // Flag estado
```

**Métodos Públicos**:
- `ejecutar()` : void - Bucle principal del juego

**Métodos Privados** (Responsabilidades):

#### Configuración Inicial
```cpp
void configurarJugadores()      // Entrada de datos
void inicializarMazo()          // Crear 28 fichas
void barajarMazo()              // Shuffle aleatorio
void repartirFichas(int)        // Distribuir a jugadores
```

#### Gestión de Partida
```cpp
void reiniciarPartida()         // Reset estado
void buclePrincipalPartida()    // Loop turnos → fin
```

#### Lógica de Juego
```cpp
bool puedeIniciarJuego() const              // Mesa vacía?
bool jugadorPuedeJugar(size_t) const        // Tiene movimiento?
bool todosBloqueados() const                // Nadie puede jugar?
bool procesarTurnoJugador(size_t)           // Input + validación + ejecución
```

#### Utilidades
```cpp
void mostrarEstadoJuego() const             // UI estado
std::string representacionMesa() const      // Visualizar mesa
int calcularGanadorBloqueo() const          // Min suma fichas
void asignarPuntosRonda(int)                // Actualizar puntuación
```

#### Movimientos
```cpp
bool esMovimientoValido(const Ficha&, bool) const  // Validar
void ejecutarMovimiento(Jugador&, size_t, bool)   // Ejecutar + registrar
```

#### Getters Privados
```cpp
int extremoIzquierdo() const                // Primer valor mesa
int extremoDerecho() const                  // Último valor mesa
```

**Complejidad**:
- Turno: O(n) validación + O(1) inserción
- Partida: O(m*n) donde m=turnos, n=fichas
- Fin: O(n) para guardar historial

---

## 🎭 Patrones de Diseño

### 1. **Patrón MVC (Model-View-Controller)**

```
Model: Ficha, Jugador, HistorialMovimientos
       (representan datos puros)
       
View: main.cpp (visualización en consola)
      (mostrarMano, mostrarEstadoJuego)
      
Control: JuegoDomino (lógica de negocio)
         (validaciones, turnos, puntuación)
```

### 2. **Patrón Singleton (Implicit)**

`JuegoDomino` actúa como singleton de facto:
- Una instancia por ejecución
- Control centralizado de estado

```cpp
int main() {
    JuegoDomino juego;  // Una única instancia
    juego.ejecutar();
}
```

### 3. **Encapsulación (Data Hiding)**

```
Privado (implementación interna):
├── Atributos de clases
├── Métodos auxiliares
└── Logica compleja

Público (interfaz):
├── Getters seguros
├── Métodos de negocio
└── Validaciones
```

### 4. **Patrón Iterator (Implícito)**

HistorialMovimientos itera internamente:
```cpp
for (NodoMovimiento* actual = cabeza; actual; actual = actual->siguiente) {
    // procesar nodo
}
```

---

## 🔄 Flujo de Datos

### Flujo Principal de Ejecución

```
main()
  │
  ├─► JuegoDomino.ejecutar()
  │    │
  │    ├─► configurarJugadores()
  │    │    └─► Lee nombre de cada jugador
  │    │
  │    └─► Loop rondas:
  │         │
  │         ├─► reiniciarPartida()
  │         │    ├─► Clear mesa
  │         │    ├─► Clear historial
  │         │    ├─► inicializarMazo()
  │         │    ├─► barajarMazo()
  │         │    └─► repartirFichas()
  │         │
  │         ├─► buclePrincipalPartida()
  │         │    │
  │         │    └─► Loop turnos:
  │         │         │
  │         │         ├─► mostrarEstadoJuego()
  │         │         │
  │         │         ├─► procesarTurnoJugador(actual)
  │         │         │    ├─► jugadorPuedeJugar()
  │         │         │    ├─► mostrarMano()
  │         │         │    ├─► Input usuario
  │         │         │    ├─► Validar movimiento
  │         │         │    └─► ejecutarMovimiento()
  │         │         │         └─► historial.registrarMovimiento()
  │         │         │
  │         │         └─► Fin: victoria o bloqueo?
  │         │
  │         ├─► historial.guardarEnArchivo()
  │         │    └─► Crear "historial_domino.txt"
  │         │
  │         └─► asignarPuntosRonda()
  │              └─► Actualizar puntuación jugadores
  │
  └─► return 0
```

### Flujo de Movimiento (Detallado)

```
procesarTurnoJugador(idxJugador)
  │
  ├─► jugadorPuedeJugar(idxJugador)?
  │    ├─► SI: Continuar
  │    └─► NO: Pasar turno → return false
  │
  ├─► Mostrar mano jugador
  │    └─► jugador.mostrarMano()
  │
  ├─► Pedir input usuario (índice ficha)
  │
  ├─► Validar índice
  │    ├─► < 0: pasar turno
  │    ├─► >= cantidadFichas(): error, reintentar
  │    └─► OK: Continuar
  │
  ├─► ¿Inicio de juego?
  │    ├─► SI: colocar ficha (inicio)
  │    └─► NO: Pedir lado (I/F)
  │         │
  │         ├─► Validar movimiento
  │         │    └─► esMovimientoValido(ficha, lado)
  │         │
  │         └─► Si válido:
  │              └─► ejecutarMovimiento()
  │
  ├─► ejecutarMovimiento(jugador, idxFicha, alInicio)
  │    ├─► Tomar ficha de mano
  │    ├─► ¿Necesita voltearse?
  │    │    └─► ficha.voltear()
  │    ├─► Colocar en mesa (push_front o push_back)
  │    └─► registrarMovimiento()
  │         └─► historial.registrarMovimiento(...)
  │
  └─► return (jugador sin fichas?)
       ├─► true: ¡Ganó!
       └─► false: Continúa juego
```

---

## 🔗 Estructura de la Lista Enlazada

### Visualización en Memoria

```
Estado inicial (vacío):
┌──────────────────────────┐
│ HistorialMovimientos     │
├──────────────────────────┤
│ cabeza: nullptr          │
│ cola:   nullptr          │
│ tamano: 0                │
└──────────────────────────┘


Después de 3 registros:
┌──────────────────────────┐
│ HistorialMovimientos     │
├──────────────────────────┤
│ cabeza: ──┐              │
│ cola:  ┐  │              │
│ tamano: 3 │              │
└──────────┬┼──────────────┘
           │└──────────────────────┐
           │                       │
    ┌──────▼──────┐         ┌──────▼──────┐
    │ Nodo #1     │         │ Nodo #2     │
    ├─────────────┤         ├─────────────┤
    │ jugador:    │         │ jugador:    │
    │ "Juan"      │         │ "Maria"     │
    ├─────────────┤         ├─────────────┤
    │ ficha:      │         │ ficha:      │
    │ "[6|6]"     │         │ "[6|3]"     │
    ├─────────────┤         ├─────────────┤
    │ estadoMesa: │         │ estadoMesa: │
    │ "[6|6]"     │         │ "[6|6]..."  │
    ├─────────────┤         ├─────────────┤
    │ siguiente:  │         │ siguiente:  │
    │    ──────────────────►│    ────────┐│
    └─────────────┘         └────────────┼┘
                                        │
                                  ┌─────▼──────┐
                                  │ Nodo #3    │
                                  ├────────────┤
                                  │ jugador:   │
                                  │ "Pedro"    │
                                  ├────────────┤
                                  │ ficha:     │
                                  │ "[3|5]"    │
                                  ├────────────┤
                                  │ estadoMesa:│
                                  │ "[6|6]..." │
                                  ├────────────┤
                                  │ siguiente: │
                                  │  nullptr   │
                                  └────────────┘
```

### Operaciones Clave

**Inserción O(1)**:
```cpp
// Siempre insertamos al final (en cola)
NodoMovimiento* nuevo = new NodoMovimiento(...);
if (!cabeza) {
    cabeza = cola = nuevo;  // Primer nodo
} else {
    cola->siguiente = nuevo; // Conectar
    cola = nuevo;             // Avanzar cola
}
```

**Traversal O(n)**:
```cpp
for (NodoMovimiento* actual = cabeza; actual; actual = actual->siguiente) {
    // Procesar nodo actual
}
```

**Liberación O(n)**:
```cpp
void limpiar() {
    for (NodoMovimiento* actual = cabeza; actual; ) {
        NodoMovimiento* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    cabeza = cola = nullptr;
    tamano = 0;
}
```

---

## 🎨 Decisiones de Diseño

### 1. **¿Por qué usar `std::deque` para la mesa?**

| Aspecto | vector | deque | list |
|---------|--------|-------|------|
| Insert frente | O(n) ❌ | O(1) ✅ | O(1) ✅ |
| Insert final | O(1) ✅ | O(1) ✅ | O(1) ✅ |
| Acceso aleatorio | O(1) ✅ | O(1) ✅ | O(n) ❌ |
| Cache friendly | Mejor | Bueno | Peor |

**Decisión**: `deque` es perfecto para mesa (inserciones en ambos extremos).

### 2. **¿Por qué lista enlazada para historial?**

**Alternativas**:
- `std::vector<Movimiento>`: Requiere espacio preasignado
- `std::list`: STL, pero ocultaría la implementación manual
- Lista enlazada manual: Enseña conceptos fundamentales

**Decisión**: Manual para demostrar POO y estructuras dinámicas.

### 3. **¿Por qué `std::vector<Ficha>` en mano?**

| Operación | Freq. | Complejidad |
|-----------|-------|------------|
| Agregar | Alto | O(1) amortizado |
| Ver | Alto | O(1) |
| Eliminar | Medio | O(n) |
| Buscar | Bajo | O(n) |

**Decisión**: Vector es adecuado (mostrar en orden es importante).

### 4. **¿Por qué Ficha es struct-like?**

- Simple: solo dos números
- Inmutable después de creación (validación en constructor)
- Operadores aritméticos innecesarios
- Cabe completamente en registros

### 5. **Manejo de Memoria: ¿RAII?**

```cpp
// ✅ RAII en HistorialMovimientos
class HistorialMovimientos {
public:
    ~HistorialMovimientos() { limpiar(); }  // Automático
};

// ✅ STL containers (vector, deque) auto-gestionan
std::vector<Ficha> mano;  // Sin new/delete

// ⚠️ Manual en NodoMovimiento (pero controlado en HistorialMovimientos)
NodoMovimiento* nuevo = new NodoMovimiento(...);
// Liberado en limpiar() → destructor
```

---

## 🚀 Extensibilidad

### 1. **Agregar IA (Jugador Computadora)**

```cpp
// Nueva clase
class JugadorIA : public Jugador {
private:
    EstrategiaJuego* estrategia;
public:
    int seleccionarMovimiento(...) const;
};

// Interface Strategy
class EstrategiaJuego {
public:
    virtual int elegirFicha(const Jugador&, int, int) = 0;
};

// Implementaciones
class EstrategiaAleatoria : public EstrategiaJuego { ... };
class EstrategiaOptima : public EstrategiaJuego { ... };
```

### 2. **Guardar/Cargar Partidas**

```cpp
// Serializacion en HistorialMovimientos
void HistorialMovimientos::cargarDesdeArchivo(const string& archivo);

// Persistencia de puntuaciones
void guardarPuntuaciones(const vector<Jugador>&);
vector<Jugador> cargarPuntuaciones();
```

### 3. **Modo Red (Multijugador)**

```cpp
// Socket wrapper
class ClienteRed {
    void enviarMovimiento(const NodoMovimiento&);
    NodoMovimiento recibirMovimiento();
};

// Reemplazar procesarTurnoJugador():
bool procesarTurnoJugadorRemoto(size_t idx, ClienteRed& cliente);
```

### 4. **Interfaz Gráfica**

```cpp
// Adapter para SDL2/SFML
class VisualizadorGrafico {
    void dibujarMesa(const deque<Ficha>&);
    void dibujarMano(const Jugador&);
    int obtenerSeleccionMouse();
};
```

### 5. **Estadísticas Avanzadas**

```cpp
class AnalizadorPartida {
public:
    int jugadoresQueHanPasado() const;
    Ficha fichasMasJugadas() const;
    double promedioFichasPorTurno() const;
};
```

---

## 📈 Análisis de Complejidad Total

### Partida Completa

```
n = número de fichas por jugador (7)
m = número de jugadores (2-4)
t = número de turnos hasta fin

Configuración: O(1)
Inicializar mazo: O(1)
Barajar: O(28 log 28) = O(1)
Repartir: O(28) = O(1)
─────────────────────────
Bucle partida: O(t * (n + m))
  • Validar jugador: O(n)
  • Mostrar estado: O(t) hist + O(m) jug
  • Insertar en lista: O(1)
─────────────────────────
Guardar historial: O(t)
Total: O(t * n)

Peor caso: t = 28*7 = 196 turnos
         n = 7 fichas
         O(196 * 7) ≈ O(1400) operaciones
```

### Espacio

```
Ficha: 2 * int = 8 bytes
Jugador: string + vector<Ficha> + int
       = 32 + (7 * 8) + 4 ≈ 100 bytes

NodoMovimiento: 3 * string + pointer
              = 96 + 8 ≈ 104 bytes

Partida:
  2-4 Jugadores: 2-4 * 100 = 200-400 bytes
  28 Fichas mesa: 28 * 8 = 224 bytes
  ~200 movimientos: 200 * 104 = 20,800 bytes
  Total: ~21 KB por partida

Razonable para consola.
```

---

## ✅ Criterios de Validación

### Antes de Compilar

- [ ] `#include` sin ciclos
- [ ] Headers con `#ifndef` guards
- [ ] Métodos const correctos
- [ ] No hay variables globales
- [ ] Validación en constructores

### Antes de Ejecutar

- [ ] `make clean && make` sin warnings
- [ ] Compilación con `-Wall -Wextra`
- [ ] Sin memory leaks (valgrind)
- [ ] Destructor ~HistorialMovimientos() se llama

### Durante Ejecución

- [ ] 2-4 jugadores aceptados
- [ ] Validación de índices
- [ ] Movimientos rechazados correctamente
- [ ] Bloqueo detectado
- [ ] Puntuación acumulada
- [ ] `historial_domino.txt` creado

---

## 📚 Referencias y Patrones Aplicados

### Libros/Estándares Aplicados

1. **Effective C++** (Scott Meyers)
   - RAII
   - Const-correctness
   - Exception safety

2. **Design Patterns** (Gang of Four)
   - MVC
   - Iterator (implícito)
   - Singleton (implícito)

3. **C++17 Standard**
   - `std::vector`, `std::deque`
   - Move semantics
   - Structured bindings

### Principios SOLID

| Principio | Aplicación |
|-----------|-----------|
| **S**RP | Cada clase: una responsabilidad |
| **O**CP | Extensible sin modificar (IA) |
| **L**SP | Sustitución en interfaces |
| **I**SP | Métodos específicos por clase |
| **D**IP | Bajo acoplamiento |

---