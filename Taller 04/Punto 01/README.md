# 🧩 Solucionador del 8-Puzzle usando A*

## Descripción del programa

Este programa implementa el algoritmo A* para resolver el clásico **8-Puzzle**, un rompecabezas deslizante de una cuadrícula 3×3 con ocho fichas numeradas y un espacio vacío.

El objetivo es transformar una configuración inicial en la configuración final ordenada, **usando el menor número posible de movimientos**.
---
## 🎯 Objetivo del programa

Dada una configuración inicial del tablero:

- Verifica si el problema tiene solución

- Aplica el algoritmo A* con heurística de distancia Manhattan

- Encuentra la secuencia óptima de movimientos

- Muestra:

    - Número de movimientos

    - Secuencia de pasos para resolver el puzzle
---
## 🕹️ ¿Cómo interactúa el usuario con el programa?

**1.** Al ejecutar el programa, se solicita al usuario ingresar la configuración inicial del tablero.

**2** Se deben ingresar 9 números, separados por espacios:

  - Los números del 1 al 8 representan las fichas

  - El número 0 representa el espacio vacío

**3** El programa analiza la configuración:

  - Si no tiene solución, se notifica y el programa termina

  - Si tiene solución, se ejecuta el algoritmo A* y se muestra el resultado

---
## 🧭 Interpretación de los movimientos

La solución se expresa como una cadena de caracteres, donde cada letra indica el movimiento del espacio vacío:

| Letra | Movimiento |
| ----- | ---------- |
| W     | Arriba     |
| S     | Abajo      |
| A     | Izquierda  |
| D     | Derecha    |

Estas secuencias se observarán en el terminal de la siguiente manera:

```bash
Secuencia: DAWS
```
---
## 🧠 ¿Cómo funciona el algoritmo?

El programa utiliza el algoritmo A*, que combina:

- **Costo real** `(g)`**:** número de movimientos realizados

- **Heurística** `(h)`**:** estimación de cuántos movimientos faltan

**Función de evaluación:**

$$f(n) = g(n) + h(n)$$

Se expande siempre el estado con el menor valor de `f`, garantizando una solución óptima.

---
## 🧩 Estructura del código
### 📦 Inclusión de librerías
```cpp
#include <bits/stdc++.h>
using namespace std;
```
Incluye todas las librerías estándar necesarias para:

- Vectores

- Colas de prioridad

- Conjuntos

- Algoritmos

- Entrada y salida

### 🏗️ Estructura State
```cpp
struct State {
    vector<int> board;
    int g;
    int h;
    string path;

    int f() const { return g + h; }
};

```
Representa un estado del puzzle:

| Atributo | Descripción               |
| -------- | ------------------------- |
| `board`  | Estado actual del tablero |
| `g`      | Movimientos realizados    |
| `h`      | Heurística (Manhattan)    |
| `path`   | Secuencia de movimientos  |
| `f()`    | Costo total estimado      |


### 🔀 Comparador para la cola de prioridad

```cpp
struct Compare {
    bool operator()(const State& a, const State& b) const {
        return a.f() > b.f();
    }
};

```
Permite que la cola de prioridad siempre seleccione el estado con menor valor de `f`, como exige A*.

### 📏 Heurística: Distancia Manhattan
```cpp
int manhattan(const vector<int>& board)
```

Calcula cuántos movimientos faltan aproximadamente para llegar al objetivo:

- Para cada ficha:

  - Se calcula la distancia horizontal y vertical desde su posición actual hasta su posición final

- El espacio vacío (0) no se considera

✔️ Esta heurística es admisible, por lo que A* garantiza la mejor solución.

### 🔍 Verificación de solucionabilidad
```cpp
bool isSolvable(const vector<int>& board)
```
Antes de ejecutar A*, el programa verifica si el puzzle tiene solución, usando el concepto de **inversiones**:

- Cuenta pares de fichas fuera de orden

- Si el número de inversiones es par, el puzzle es resoluble

- Si es impar, no existe solución

Esto evita búsquedas innecesarias.

### 🚀 Función `main()` 
#### 1️⃣ Entrada del usuario
```cpp
vector<int> start(9);
```
Se lee el tablero inicial desde consola.

#### 2️⃣ Estado objetivo
```cpp
vector<int> goal = {1,2,3,4,5,6,7,8,0};
```
Representa el tablero ordenado.

#### 3️⃣ Inicialización de estructuras
```cpp
priority_queue<State, vector<State>, Compare> pq;
unordered_set<string> visited;
```
- `pq`: estados pendientes por explorar

- `visited`: evita repetir estados ya evaluados

#### 4️⃣ Estado inicial
```cpp
State init{start, 0, manhattan(start), ""};
```
- `g` = 0 → ningún movimiento

- `h` → heurística inicial

- `path` vacío

#### 5️⃣ Movimientos posibles
```cpp
dx, dy, moveChar
```
Define:

- Cambios de posición

- Letra asociada a cada movimiento

#### 6️⃣ Bucle principal A*
```cpp
while (!pq.empty())
```
Para cada estado:

**1.** Se extrae el mejor candidato

**2.** Se ignora si ya fue visitado

**3.** Se verifica si es el objetivo

**4.** Se generan nuevos estados moviendo el espacio vacío

**5.** Se agregan a la cola de prioridad

#### 7️⃣ Solución encontrada

Cuando el estado actual coincide con el objetivo:

- Se imprime:

    - Número de movimientos

    - Secuencia de pasos

    - Leyenda de controles

#### 8️⃣ Caso sin solución

Si la cola se vacía sin alcanzar el objetivo:

```cpp
No se encontro solucion.
```

---
## 📌 Ejemplo de entrada
Al iniciar el programa se observa lo siguiente
```bash
Ingrese la configuracion inicial (use 0 para el espacio vacio):
```
Se ingresan los números para la configuracion inicial:
```bash
Ingrese la configuracion inicial (use 0 para el espacio vacio):
1 2 3 4 5 6 0 7 8   <---- Se ingresa los valores en una linea separados por espacio cada uno
```
Se pulsa enter para enviar y se obtiene la siguiente respuesta:
```bash
Solucion encontrada en 2 movimientos.
Secuencia: DD
W:Arriba, S:Abajo, A:Izquierda, D:Derecha
```


