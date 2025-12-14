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


