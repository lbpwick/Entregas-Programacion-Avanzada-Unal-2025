# Documento de Diseño Arquitectónico - Juego de Dominó

## 1. Visión General

El Juego de Dominó es una aplicación de consola que implementa completamente las reglas del dominó clásico con soporte para 2-4 jugadores humanos. El diseño utiliza principios sólidos de POO para crear una base extensible y mantenible.

## 2. Arquitectura del Sistema

```
┌─────────────────────────────────────────────────────┐
│                  InterfazJuego (main.cpp)           │
│        Maneja la interacción con el usuario          │
└──────────────────┬──────────────────────────────────┘
                   │
                   ▼
┌─────────────────────────────────────────────────────┐
│             JuegoDomino (Controlador)               │
│    Gestiona la lógica y flujo del juego             │
└──────────────────┬──────────────────────────────────┘
         ▲         │         ▲
         │         ▼         │
    ┌─────────────────────────────┐
    │                             │
    │   ┌────────────────────┐    │
    │   │   Jugador          │    │
    │   │  - nombre: string  │    │
    │   │  - fichas: []Ficha │    │
    │   │  - puntos: int     │    │
    │   └────────────────────┘    │
    │                             │
    │   ┌────────────────────┐    │
    │   │   Ficha            │    │
    │   │  - izquierda: int  │    │
    │   │  - derecha: int    │    │
    │   └────────────────────┘    │
    │                             │
    └─────────────────────────────┘
```

## 3. Clases y Responsabilidades

### 3.1 Clase Ficha

**Responsabilidad**: Representar una ficha individual de dominó

**Atributos Privados**:
- `izquierda: int` - Valor del extremo izquierdo (0-6)
- `derecha: int` - Valor del extremo derecho (0-6)

**Métodos Públicos**:
- `getIzquierda()` - Obtener valor izquierdo
- `getDerecha()` - Obtener valor derecho
- `voltear()` - Invertir posición de valores
- `encajaIzquierda(valor)` - Verificar encaje izquierdo
- `encajaDerecha(valor)` - Verificar encaje derecho
- `esDoble()` - Verificar si es ficha doble
- `operator==()` - Comparar fichas
- `mostrar()` - Mostrar ficha en consola

**Invariantes de Clase**:
- Los valores están siempre en rango [0, 6]
- izquierda ≤ derecha (después de construcción)

### 3.2 Clase Jugador

**Responsabilidad**: Gestionar las fichas y puntuación de un jugador

**Atributos Privados**:
- `nombre: string` - Nombre del jugador
- `fichas: vector<Ficha>` - Fichas en mano
- `puntosAcumulados: int` - Puntos totales acumulados

**Métodos Públicos**:
- `getNombre()` - Obtener nombre
- `getNumeroFichas()` - Cantidad de fichas actuales
- `getPuntosAcumulados()` - Total de puntos
- `agregarFicha(ficha)` - Agregar ficha a la mano
- `eliminarFicha(indice)` - Remover ficha específica
- `puedejugar(valorIzq, valorDer)` - Verificar si tiene movimiento válido
- `encontrarFichaEncajable()` - Buscar ficha válida
- `calcularPuntuacionFichas()` - Puntos de fichas actuales
- `mostrarFichas()` - Mostrar fichas en consola
- `agregarPuntos(cantidad)` - Sumar puntos acumulados

**Invariantes**:
- El número de fichas está entre 0 y 28
- Los puntos acumulados no pueden ser negativos

### 3.3 Clase JuegoDomino

**Responsabilidad**: Controlar el flujo completo del juego

**Atributos Privados**:
- `jugadores: vector<Jugador>` - Todos los jugadores
- `fichasEnMesa: deque<Ficha>` - Fichas colocadas (orden lineal)
- `almacen: vector<Ficha>` - Fichas disponibles
- `indiceJugadorActual: int` - Turno actual
- `jugadoresConsecutivosQuePasan: int` - Contador de pasos
- `juegoEnCurso: bool` - Estado del juego

**Métodos Privados**:
- `inicializarFichas()` - Crear las 28 fichas
- `mezclarFichas()` - Barajar aleatoriamente
- `distribuirFichasIniciales()` - Dar 7 fichas a cada uno
- `encontrarJugadorInicial()` - Determinar quién inicia
- `robarFicha()` - Tomar ficha del almacén
- `puedeJugarOrobar()` - Verificar si puede continuar
- `pasoturno()` - Cambiar jugador activo
- `estaBloqueado()` - Detectar condición de bloqueo
- `determinarGanadorPorBloqueo()` - Ganador en bloqueo

**Métodos Públicos**:
- `getNumJugadores()` - Cantidad de jugadores
- `getJugador(indice)` - Acceso a jugador específico
- `getJugadorActual()` - Jugador que juega
- `iniciarPartida()` - Comenzar nueva ronda
- `jugarFicha(indice, posicion)` - Colocar ficha
- `getExtremosActuales()` - Valores en extremos de mesa
- `ejecutarturno()` - Procesar turno
- `partida_terminada()` - Verificar fin de partida
- `getGanador()` - Obtener ganador
- `mostrarEstado()` - Información del juego
- `mostrarMesa()` - Fichas en mesa
- `mostrarPuntuacion()` - Puntuación acumulada
- `limpiarPartida()` - Reset para nueva partida

### 3.4 Clase InterfazJuego

**Responsabilidad**: Interactuar con el usuario

**Métodos**:
- `mostrarMenuPrincipal()` - Menú inicial
- `mostrarMenuturno()` - Opciones de turno
- `limpiarPantalla()` - Borrar consola
- `manejarturno()` - Ejecutar turno del jugador
- `mostrarResultado()` - Mostrar fin de partida
- `ejecutar()` - Loop principal

## 4. Patrones de Diseño Utilizados

### 4.1 Patrón MVC (Modelo-Vista-Controlador)

- **Modelo**: Ficha, Jugador (datos)
- **Controlador**: JuegoDomino (lógica)
- **Vista**: InterfazJuego (presentación)

### 4.2 Patrón Singleton (Potencial)

`JuegoDomino` podría ser singleton para asegurar una única instancia del juego.

### 4.3 Patrón Strategy (Extensión Futura)

La clase `EstrategiaJuego` permite diferentes comportamientos de IA sin modificar la lógica central.

### 4.4 Patrón Observer (Extensión Futura)

Notificar cambios de estado a múltiples observadores (GUI, estadísticas, etc.).

## 5. Flujo de Ejecución

### 5.1 Inicialización del Juego

```
1. Usuario selecciona número de jugadores (2-4)
   └─> Validar entrada

2. Crear instancia de JuegoDomino
   └─> Crear vector de jugadores

3. Crear InterfazJuego
   └─> Mostrar menú principal
```

### 5.2 Inicio de Partida

```
1. iniciarPartida()
   ├─> limpiarPartida()
   │   └─> Resetear estado
   ├─> inicializarFichas()
   │   └─> Crear 28 fichas [0|0] a [6|6]
   ├─> mezclarFichas()
   │   └─> Randomizar con std::shuffle
   ├─> distribuirFichasIniciales()
   │   └─> Dar 7 fichas a cada jugador
   ├─> encontrarJugadorInicial()
   │   └─> Buscar ficha doble más alta
   └─> juegoEnCurso = true
```

### 5.3 Turno de Juego

```
1. manejarturno()
   ├─> mostrarEstado()
   ├─> Usuario selecciona acción:
   │   ├─ Jugar ficha
   │   │  └─> jugarFicha(indice, posicion)
   │   │      ├─> Validar movimiento
   │   │      ├─> Colocar ficha
   │   │      └─> pasoturno()
   │   ├─ Robar ficha
   │   │  └─> ejecutarturno()
   │   ├─ Ver fichas
   │   ├─ Ver estado
   │   └─ Pasar turno
   └─> Retornar estado
```

### 5.4 Fin de Partida

```
1. Verificar partida_terminada()
   ├─> ¿Jugador tiene 0 fichas?
   │   └─> Victoria por juego limpio
   └─> ¿Juego bloqueado?
       └─> Victoria por bloqueo (menor puntuación)

2. getGanador()
   └─> Retornar ganador

3. Actualizar puntuación acumulada
   └─> Ganador recibe puntos de otros jugadores

4. Mostrar resultado
   └─> Opción de nueva partida
```

## 6. Gestión de Memoria

### Características de Seguridad

- **RAII** (Resource Acquisition Is Initialization): Uso de contenedores STL
- **Sin punteros desnudos**: Solo se usan referencias
- **Validación de índices**: Uso de excepciones std::out_of_range
- **Limpieza automática**: Destructores implícitos suficientes

### Ciclo de Vida de Objetos

```
Inicio
  │
  ├─> JuegoDomino creado (stack)
  │   │
  │   ├─> vector<Jugador> creado
  │   │   │
  │   │   └─> Cada Jugador crea vector<Ficha>
  │   │
  │   └─> vector<Ficha> del almacén creado
  │
  └─> InterfazJuego creado (stack)

Fin
  │
  └─> Destructores automáticos liberan memoria
      (Contenedores STL)
```

## 7. Manejo de Errores

### Excepciones Implementadas

| Tipo | Condición | Dónde |
|------|-----------|-------|
| `std::invalid_argument` | Valores fuera de rango 0-6 | Ficha::constructor |
| `std::invalid_argument` | Jugadores no están en 2-4 | JuegoDomino::constructor |
| `std::out_of_range` | Índice de ficha inválido | Jugador::getFicha() |
| `std::out_of_range` | Índice de ficha a eliminar | Jugador::eliminarFicha() |

### Estrategia de Validación

```
Usuario Input
     │
     ▼
Validar formato (int, rango)
     │
     ├─ NO ──> Mostrar error, repetir
     │
     ▼ SÍ
Validar lógica (movimiento válido)
     │
     ├─ NO ──> Mostrar razón, permitir reintento
     │
     ▼ SÍ
Ejecutar acción
```

## 8. Principios SOLID Aplicados

### S - Single Responsibility
- **Ficha**: Solo representar una ficha
- **Jugador**: Solo gestionar fichas de un jugador
- **JuegoDomino**: Solo controlar el flujo
- **InterfazJuego**: Solo interactuar con usuario

### O - Open/Closed
- Diseño abierto a extensiones (estrategias de IA)
- Cerrado a modificaciones (núcleo del juego estable)

### L - Liskov Substitution
- Las subclases de EstrategiaJuego pueden reemplazarse sin efectos

### I - Interface Segregation
- Cada clase expone solo métodos relevantes
- Métodos privados para implementación interna

### D - Dependency Inversion
- Las clases dependen de abstracciones
- Uso de interfaces cuando es necesario

## 9. Pruebas Sugeridas

### Pruebas Unitarias

```cpp
// Prueba: Crear ficha válida
TEST(FichaTest, CreacionValida) {
    Ficha f(3, 5);
    ASSERT_EQ(f.getIzquierda(), 3);
    ASSERT_EQ(f.getDerecha(), 5);
}

// Prueba: Ficha inválida lanza excepción
TEST(FichaTest, CreacionInvalida) {
    ASSERT_THROW(Ficha(3, 7), std::invalid_argument);
}

// Prueba: Encaje correcto
TEST(FichaTest, Encaje) {
    Ficha f(3, 5);
    ASSERT_TRUE(f.encajaIzquierda(3));
    ASSERT_TRUE(f.encajaDerecha(5));
}
```

### Pruebas de Integración

- Partida completa con 2 jugadores
- Partida con bloqueo
- Múltiples partidas consecutivas
- Validación de puntuación

## 10. Métricas de Código

| Métrica | Valor |
|---------|-------|
| Líneas de código | ~1200 |
| Clases | 4 principales + 1 interfaz |
| Métodos | ~50 |
| Complejidad ciclomática | Baja (métodos pequeños) |
| Cobertura potencial | >90% |

## 11. Consideraciones de Rendimiento

- **Complejidad**: O(n) por turno (n = fichas del jugador)
- **Memoria**: O(J + F) (J jugadores, F fichas)
- **Tiempo de inicio**: < 100ms
- **Tiempo por turno**: Instantáneo (dominado por entrada de usuario)

## 12. Extensiones Posibles

### Corto Plazo
- [ ] Validación de entrada mejorada
- [ ] Estadísticas por partida
- [ ] Historial de movimientos

### Mediano Plazo
- [ ] Implementar IA con estrategias
- [ ] Sistema de dificultad
- [ ] Guardado de partidas

### Largo Plazo
- [ ] Interfaz gráfica (SDL2, SFML)
- [ ] Multijugador en red
- [ ] Variantes del dominó
- [ ] Base de datos para estadísticas

---

**Documento versión**: 1.0  
**Fecha**: 2025  
**Autor**: Luis Borrero
