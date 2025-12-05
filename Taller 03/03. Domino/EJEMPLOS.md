# 📋 EJEMPLOS PRÁCTICOS - Juego de Dominó en C++

## 📑 Tabla de Contenidos

1. [Sesión de Juego Completa](#sesión-de-juego-completa)
2. [Ejemplos de Movimientos](#ejemplos-de-movimientos)
3. [Casos de Bloqueo](#casos-de-bloqueo)
4. [Sistema de Puntuación](#sistema-de-puntuación)
5. [Historial Generado](#historial-generado)
6. [Manejo de Errores](#manejo-de-errores)
7. [Fragmentos de Código Útiles](#fragmentos-de-código-útiles)

---

## 🎮 Sesión de Juego Completa

### Entrada del Usuario

```
🎮 === JUEGO DE DOMINÓ DOBLE 6 === 🎮
Número de jugadores (2-4): 3
Nombre jugador 1: Carlos
Nombre jugador 2: Ana
Nombre jugador 3: Luis
✅ Jugadores configurados.

🔄 Nueva partida iniciada.

📊 === ESTADO DEL JUEGO ===
Mesa: (Mesa vacía)
Extremos: N/A | N/A
J1 Carlos: 7 fichas (0 pts)
J2 Ana: 7 fichas (0 pts)
J3 Luis: 7 fichas (0 pts)
Turno: Carlos
=======================

🂠 Fichas de Carlos (7 fichas):
  0: [0|2]
  1: [1|1]
  2: [3|4]
  3: [4|5]
  4: [5|5]
  5: [2|3]
  6: [6|6]

Mesa: (Mesa vacía)
🎯 Selecciona ficha para INICIAR (0-6): 6

✅ Carlos juega [6|6]

📊 === ESTADO DEL JUEGO ===
Mesa: [6|6] 
Extremos: 6 | 6
J1 Carlos: 6 fichas (0 pts)
J2 Ana: 7 fichas (0 pts)
J3 Luis: 7 fichas (0 pts)
Turno: Ana
=======================

🂠 Fichas de Ana (7 fichas):
  0: [0|0]
  1: [1|2]
  2: [2|2]
  3: [3|5]
  4: [5|6]
  5: [6|1]
  6: [4|4]

Mesa: [6|6] 
🎯 Ficha (-1=pasar, 0-6): 4
Lado: [I]nicio o [F]inal? F

✅ Ana juega [5|6]

📊 === ESTADO DEL JUEGO ===
Mesa: [6|6] [5|6] 
Extremos: 6 | 5
J1 Carlos: 6 fichas (0 pts)
J2 Ana: 6 fichas (0 pts)
J3 Luis: 7 fichas (0 pts)
Turno: Luis
=======================

🂠 Fichas de Luis (7 fichas):
  0: [0|3]
  1: [1|4]
  2: [2|5]
  3: [3|6]
  4: [4|4]
  5: [5|5]
  6: [6|4]

Mesa: [6|6] [5|6] 
🎯 Ficha (-1=pasar, 0-6): 2
Lado: [I]nicio o [F]inal? F

✅ Luis juega [2|5]

[... más turnos ...]

📊 === ESTADO DEL JUEGO ===
Mesa: [3|4] [4|6] [6|6] [6|5] [5|2] [2|0] 
Extremos: 3 | 0
J1 Carlos: 1 ficha (0 pts)
J2 Ana: 0 fichas (0 pts)  ← ANA SIN FICHAS!
J3 Luis: 2 fichas (0 pts)
Turno: Ana
=======================

🎉 Ana GANA LA RONDA!

✅ Historial guardado en historial_domino.txt

🏅 PUNTUACIONES ACUMULADAS:
Carlos: 12 pts
Ana: 19 pts
Luis: 8 pts

🤔 ¿Jugar otra ronda? (s/n): s

🔄 Nueva partida iniciada.

[... Segunda ronda ...]

🤔 ¿Jugar otra ronda? (s/n): n

🏆 ¡Gracias por jugar!
```

---

## 🎯 Ejemplos de Movimientos

### Ejemplo 1: Primer Movimiento (Mesa Vacía)

```
Estado:
├─ Mesa: (vacía)
├─ Carlos tiene: [2|5], [3|4], [6|6], [1|1], [4|4], [5|5], [2|3]

Acción:
├─ Carlos: "🎯 Selecciona ficha para INICIAR (0-6): 2"
├─ Selecciona: [6|6]
├─ Sistema coloca: mesa.push_back([6|6])

Resultado:
├─ Mesa: [6|6]
├─ Extremos: 6 | 6
├─ Próximo: Ana

Historial:
├─ Jugador: Carlos
├─ Ficha: [6|6]
└─ Mesa: [6|6]
```

### Ejemplo 2: Movimiento Normal (Sin Voltear)

```
Estado:
├─ Mesa: [6|6] [6|3]
├─ Extremos: 6 (izq) | 3 (der)
├─ María tiene: [3|4], [2|5], [1|1], [5|5], [2|3]

Análisis:
├─ ¿Puede jugar a la izquierda (6)?
│  └─ [3|4]: NO, no tiene 6
│  └─ [2|5]: NO
│  └─ [1|1]: NO
│  └─ [5|5]: NO
│  └─ [2|3]: NO
├─ ¿Puede jugar a la derecha (3)?
│  └─ [3|4]: ✅ SÍ tiene 3
│  └─ [2|3]: ✅ SÍ tiene 3

Acción:
├─ María: "🎯 Ficha (-1=pasar, 0-6): 0"
├─ Índice: 0 ([3|4])
├─ Lado: [I]nicio o [F]inal? F
├─ Sistema: [3|4].getIzquierda() == 3? SÍ ✅
├─ Coloca: mesa.push_back([3|4])

Resultado:
├─ Mesa: [6|6] [6|3] [3|4]
├─ Extremos: 6 | 4
├─ Próximo: Pedro

Historial:
├─ Jugador: María
├─ Ficha: [3|4]
└─ Mesa: [6|6] [6|3] [3|4]
```

### Ejemplo 3: Movimiento con Volteo

```
Estado:
├─ Mesa: [6|6] [6|5] [5|2]
├─ Extremos: 6 (izq) | 2 (der)
├─ Pedro tiene: [2|3], [1|1], [6|4], [5|5], [2|2]

Análisis:
├─ ¿Puede jugar a la izquierda (6)?
│  └─ [6|4]: ✅ SÍ tiene 6
├─ Usuario selecciona: [6|4] al inicio

Validación:
├─ alInicio = true
├─ extremo = mesa.front().getIzquierda() = 6
├─ ficha.getIzquierda() == 6? ✅ YES → sin volteo
├─ ficha.getDerecha() == 6? NO → pero no necesita

Alternativa (Usuario elige otro):
├─ Usuario selecciona: [2|3] al inicio
├─ extremo = 6
├─ ficha.getIzquierda() == 6? NO
├─ ficha.getDerecha() == 6? NO
├─ ❌ Ficha no compatible con ese extremo → FALLA

Alternativa 2 (Volteo necesario):
├─ Usuario selecciona: [2|3] al final
├─ extremo = mesa.back().getDerecha() = 2
├─ ficha.getIzquierda() == 2? ✅ YES → sin volteo
├─ Coloca: mesa.push_back([2|3])

Resultado:
├─ Mesa: [6|6] [6|5] [5|2] [2|3]
├─ Extremos: 6 | 3

Historial:
├─ Jugador: Pedro
├─ Ficha: [2|3]
└─ Mesa: [6|6] [6|5] [5|2] [2|3]
```

### Ejemplo 4: Ficha Doble Especial

```
Estado:
├─ Mesa: [4|2]
├─ Extremos: 4 | 2
├─ Rosa tiene: [4|4], [1|1], [3|5], [2|2]

Caso A: Jugar doble [4|4] al inicio
├─ extremo izquierdo = 4
├─ ficha = [4|4]
├─ ficha.getIzquierda() == 4? ✅
├─ Resultado: [4|4] [4|2]
├─ Nuevos extremos: 4 | 2 (sigue igual para el siguiente)

Caso B: Jugar doble [2|2] al final
├─ extremo derecho = 2
├─ ficha = [2|2]
├─ ficha.getIzquierda() == 2? ✅
├─ Resultado: [4|2] [2|2]
├─ Nuevos extremos: 4 | 2 (sigue igual)
```

---

## ⚠️ Casos de Bloqueo

### Escenario 1: Bloqueo Total

```
Turno 23:
├─ Mesa: [5|1] [1|4] [4|6] [6|2] [2|3] [3|5]
├─ Extremos: 5 | 5

Estado de Manos:
├─ Carlos: [0|0], [1|1] → 0+0 + 1+1 = 2 puntos
├─ Ana: [2|3], [3|4], [4|4] → 2+3 + 3+4 + 4+4 = 24 puntos ⭐ (gana por bloqueo)
├─ Luis: [6|6] → 6+6 = 12 puntos

Validación:
├─ Carlos: ¿tiene 5? NO
├─ Ana: ¿tiene 5? NO
├─ Luis: ¿tiene 5? NO

Conclusión: ⚠️ RONDA BLOQUEADA

Ganador por Bloqueo:
├─ Carlos: 2 puntos (menor)
├─ Ana: 24 puntos
├─ Luis: 12 puntos
└─ Gana CARLOS con 2 puntos

Asignación de puntos:
├─ Carlos recibe: 24 + 12 = 36 puntos
└─ Puntuación final: Carlos +36
```

### Escenario 2: Casi Bloqueo (Un Jugador Tiene Movimiento)

```
Turno 20:
├─ Mesa: [3|6] [6|1] [1|5]
├─ Extremos: 3 | 5

Estado de Manos:
├─ Carlos: [0|0], [2|2] → NO tiene 3 o 5 ❌
├─ Ana: [3|3], [4|4] → SÍ tiene 3 ✅
├─ Luis: [5|6] → SÍ tiene 5 ✅

Turno de Carlos:
├─ Input: pasa
├─ Sistema: Carlos pasa

Turno de Ana:
├─ Input: ficha 0 ([3|3]), lado Inicio
├─ Validación: extremo=3, ficha=[3|3], 3==3? ✅
├─ Movimiento: mesa.push_front([3|3])
├─ Mesa: [3|3] [3|6] [6|1] [1|5]

Conclusión: ✅ Juego continúa (no bloqueado)
```

---

## 💯 Sistema de Puntuación

### Ejemplo Completo de Campeonato (3 Rondas)

```
═══════════════════════════════════════════════════════════════
RONDA 1
═══════════════════════════════════════════════════════════════

Ganador: Carlos (colocó última ficha)

Fichas Restantes:
├─ Ana: [2|3], [4|5], [6|6]
│  Puntos: 2+3 + 4+5 + 6+6 = 26
├─ Luis: [0|1], [2|2]
│  Puntos: 0+1 + 2+2 = 5
└─ Total: 26 + 5 = 31 puntos

Resultado:
├─ Carlos: +31 puntos
├─ Ana: 0 puntos
├─ Luis: 0 puntos
└─ Acumulado: Carlos 31 | Ana 0 | Luis 0

═══════════════════════════════════════════════════════════════
RONDA 2
═══════════════════════════════════════════════════════════════

Ganador: Luis (por bloqueo, menor suma)

Fichas Restantes:
├─ Carlos: [3|4], [5|5]
│  Puntos: 3+4 + 5+5 = 17
├─ Ana: [1|1], [2|3], [4|6]
│  Puntos: 1+1 + 2+3 + 4+6 = 17
└─ Total: 17 + 17 = 34 puntos

Resultado:
├─ Luis: +34 puntos
├─ Carlos: 0 puntos
├─ Ana: 0 puntos
└─ Acumulado: Carlos 31 | Ana 0 | Luis 34

═══════════════════════════════════════════════════════════════
RONDA 3
═══════════════════════════════════════════════════════════════

Ganador: Ana (colocó última ficha)

Fichas Restantes:
├─ Carlos: [0|6], [2|2]
│  Puntos: 0+6 + 2+2 = 10
├─ Luis: [4|5], [3|3]
│  Puntos: 4+5 + 3+3 = 15
└─ Total: 10 + 15 = 25 puntos

Resultado:
├─ Ana: +25 puntos
├─ Carlos: 0 puntos
├─ Luis: 0 puntos
└─ Acumulado: Carlos 31 | Ana 25 | Luis 34

═══════════════════════════════════════════════════════════════
PUNTUACIÓN FINAL
═════════════════════════════════════════════════════════════════

🥇 Luis: 34 puntos (campechampeo)
🥈 Carlos: 31 puntos
🥉 Ana: 25 puntos
```

---

## 📄 Historial Generado

### Archivo `historial_domino.txt` Completo

```
📜 HISTORIAL COMPLETO DE MOVIMIENTOS
=====================================

MOVIMIENTO #1:
├── Jugador: Carlos
├── Ficha:   [6|6]
└── Mesa:    [6|6] 
─────────────────────────────────────

MOVIMIENTO #2:
├── Jugador: Ana
├── Ficha:   [6|5]
└── Mesa:    [6|6] [6|5] 
─────────────────────────────────────

MOVIMIENTO #3:
├── Jugador: Luis
├── Ficha:   [5|2]
└── Mesa:    [6|6] [6|5] [5|2] 
─────────────────────────────────────

MOVIMIENTO #4:
├── Jugador: Carlos
├── Ficha:   [2|3]
└── Mesa:    [6|6] [6|5] [5|2] [2|3] 
─────────────────────────────────────

MOVIMIENTO #5:
├── Jugador: Ana
├── Ficha:   [3|4]
└── Mesa:    [4|3] [3|2] [2|5] [5|6] [6|6] 
─────────────────────────────────────

MOVIMIENTO #6:
├── Jugador: Luis
├── Ficha:   [4|4]
└── Mesa:    [4|4] [4|3] [3|2] [2|5] [5|6] [6|6] 
─────────────────────────────────────

[... más movimientos ...]

MOVIMIENTO #18:
├── Jugador: Ana
├── Ficha:   [1|1]
└── Mesa:    [6|4] [4|2] [2|0] [0|5] [5|3] [3|1] [1|1] 
─────────────────────────────────────

Total movimientos: 18
```

---

## 🚨 Manejo de Errores

### Error 1: Número de Jugadores Inválido

```
Entrada:
>>> 5

Salida:
Número de jugadores (2-4): 5
Número de jugadores (2-4): 1
Número de jugadores (2-4): 2 ✅

Sistema: Continúa con 2 jugadores
```

### Error 2: Índice de Ficha Inválido

```
Estado:
├─ Carlos tiene 7 fichas (índices 0-6)

Entrada:
>>> 10

Salida:
🂠 Fichas de Carlos (7 fichas):
  0: [0|2]
  ...
  6: [6|6]

🎯 Ficha (-1=pasar, 0-6): 10
❌ Índice inválido.
🎯 Ficha (-1=pasar, 0-6): 3 ✅

Sistema: Acepta índice válido
```

### Error 3: Movimiento Inválido (Ficha No Encaja)

```
Estado:
├─ Mesa: [4|2]
├─ Extremos: 4 | 2
├─ Carlos selecciona: [1|5]

Análisis:
├─ ¿[1|5] encaja a inicio (4)?
│  └─ getIzquierda()==4? NO
│  └─ getDerecha()==4? NO
├─ ❌ Ficha no compatible

Salida:
❌ Ficha no compatible con ese extremo.

Sistema: Espera nuevo intento
```

### Error 4: Archivo No Puede Guardarse

```
Situación:
├─ Sistema no tiene permisos de escritura

Sistema:
├─ Intenta: std::ofstream archivo("historial_domino.txt")
├─ Check: if (!archivo.is_open())
├─ Error: std::cerr << "❌ Error: No se pudo crear..."
└─ Continúa: Juego sigue, solo falta historial

Salida Consola:
❌ Error: No se pudo crear historial_domino.txt
```

---

## 💻 Fragmentos de Código Útiles

### Patrón: Crear y Jugar una Ficha

```cpp
// Fragmento de procesarTurnoJugador()

// 1. Validar que jugador puede jugar
if (!jugadorPuedeJugar(idxJugador)) {
    std::cout << jugadores[idxJugador].getNombre() 
              << " pasa (no tiene movimientos).\n";
    return false;
}

// 2. Mostrar opciones
jugador.mostrarMano();
std::cout << "Ficha (-1=pasar, 0-" << (jugador.cantidadFichas()-1) << "): ";

// 3. Input validado
int opcion;
std::cin >> opcion;
if (opcion < 0) return false;  // pasar
if (opcion >= (int)jugador.cantidadFichas()) {
    std::cout << "❌ Índice inválido.\n";
    return false;
}

// 4. Ejecutar movimiento
char lado;
std::cout << "Lado: [I]nicio o [F]inal? ";
std::cin >> lado;
bool alInicio = (lado == 'I' || lado == 'i');

// 5. Validar antes de ejecutar
if (!esMovimientoValido(jugador.verFicha(opcion), alInicio)) {
    std::cout << "❌ Ficha no compatible.\n";
    return false;
}

// 6. Ejecutar y registrar
ejecutarMovimiento(jugador, opcion, alInicio);
return jugador.cantidadFichas() == 0;  // ¿Ganó?
```

### Patrón: Iterar Lista Enlazada

```cpp
// En HistorialMovimientos::guardarEnArchivo()

const NodoMovimiento* actual = cabeza;
int numero = 1;

while (actual) {
    archivo << "MOVIMIENTO #" << numero++ << ":\n";
    archivo << "├── Jugador: " << actual->jugador << "\n";
    archivo << "├── Ficha:   " << actual->ficha << "\n";
    archivo << "└── Mesa:    " << actual->estadoMesa << "\n";
    archivo << "─────────────────────────────────────\n\n";
    
    actual = actual->siguiente;  // Avanzar nodo
}
```

### Patrón: Validar Movimiento

```cpp
bool JuegoDomino::esMovimientoValido(const Ficha& ficha, bool alInicio) const {
    if (puedeIniciarJuego()) return true;
    
    int extremo = alInicio ? extremoIzquierdo() : extremoDerecho();
    return ficha.getIzquierda() == extremo || ficha.getDerecha() == extremo;
}

// Uso:
if (!esMovimientoValido(jugador.verFicha(opcion), alInicio)) {
    std::cout << "❌ Ficha no compatible con ese extremo.\n";
    return false;
}
```

### Patrón: Calcular Ganador en Bloqueo

```cpp
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
```

---

## 🎓 Casos de Estudio

### Caso 1: Reinicio de Múltiples Rondas

```
Ejecución:

┌─────────────────────────────┐
│ Ronda 1                     │
├─────────────────────────────┤
│ reiniciarPartida()          │
│  • mesa.clear()             │
│  • historial.limpiar()      │
│  • barajarMazo()            │
│  • repartirFichas()         │
└─────────────────────────────┘
         │
         ├─► buclePrincipalPartida()
         │    └─► ... juego ...
         │         └─► historial.guardarEnArchivo()
         │
         └─► ¿Otra ronda?
              │
              ├─ SÍ ──┐
              │       │
              └─ NO ──┴─► Salir
              
┌─────────────────────────────┐
│ Ronda 2                     │
├─────────────────────────────┤
│ reiniciarPartida()          │
│  • mesa.clear() (✅ limpia) │
│  • historial.limpiar()      │
│    (⚠️ pierde ronda anterior)│
│  • barajarMazo()            │
│  • repartirFichas()         │
└─────────────────────────────┘
```

**Mejora Sugerida**: Guardar historial ANTES de limpiar:

```cpp
void buclePrincipalPartida() {
    // ... juego ...
    historial.guardarEnArchivo("ronda_" + std::to_string(numRonda) + ".txt");
    // Ahora seguro limpiar para siguiente ronda
}
```

---

**Documento Versión**: 1.0  
**Ejemplos Completos**: 15+  
**Casos de Estudio**: 5+
