# Clasificación de Dígitos 0–9 con Redes Neuronales en C++

Este proyecto implementa una **Red Neuronal Artificial (RNA) feed‑forward simple en C++**
para clasificar números naturales del 0 al 9 en las siguientes clases:

- **Clase 0**: Números pares (0, 2, 4, 6, 8).
- **Clase 1**: Números impares (1, 3, 5, 7, 9).
- **Clase 2**: Números primos (2, 3, 5, 7).
- **Clase 3**: Números compuestos (4, 6, 8, 9).

La entrada proviene del archivo `digitos.txt`, donde **cada línea es un número en binario**
(por ejemplo `0001`, `0010`, `0101`), que se convierte a un entero de 0 a 9 y se clasifica.

El código principal está en `punto_03.cpp`.

---

## 📂 Estructura del Proyecto
```
.
├── punto_03.cpp    # Código fuente principal (RNA + lectura binaria)
├── digitos.txt     # Datos de entrada (líneas en binario)
├── README.md       # Guía de instalación y uso
└── DESIGN.md       # Diseño y arquitectura de la solución
```
---

## ⚙️ Requisitos

- Compilador C++ con soporte para **C++17**:
  - `g++`, `clang++` o MinGW en Windows.
- Sistema operativo:
  - Linux, macOS o Windows.

No se usan librerías externas: solo **STL** (`<vector>`, `<string>`, `<random>`, etc.).

---

## 🚀 Compilación y Ejecución

El archivo fuente se llama **`punto_03.cpp`**:

### Linux / macOS
```
g++ -std=c++17 -O2 -Wall punto_03.cpp -o punto_03
./punto_03
```
### Windows (MinGW)
```
g++ -std=c++17 -O2 -Wall punto_03.cpp -o punto_03.exe
punto_03.exe
```
---
## 🧾 Formato de `digitos.txt`

- Cada **línea** representa un número natural en **binario**.
- Se consideran solo los caracteres `0` y `1`; otros caracteres se ignoran.
- El valor decimal final debe estar en el rango **0 a 9**; si es mayor, se descarta.

Ejemplo de `digitos.txt`:
```
0000
0001
0010
0011
0100
0101
0110
0111
1000
1001
```
Equivalente a:
```
0
1
2
3
4
5
6
7
8
9
```

También se admiten espacios entre bits:
```
0 0 0 0
0 0 0 1
0 0 1 0
0 1 0 0
1 0 0 1
```
El programa limpia cada línea y conserva solo `0` y `1`.
---

## 🧮 Qué Hace el Programa (`punto_03.cpp`)

1. **Lee** cada línea de `digitos.txt`.
2. **Limpia** la línea, dejando solo bits (`0` y `1`).
3. **Convierte** la cadena binaria a entero `n` en base 2.
4. **Descarta** valores fuera de `[0, 9]`.
5. **Construye** un conjunto de entrenamiento:
   - Entrada: vector one‑hot de tamaño 10 (posición `n` en 1).
   - Salida: vector de tamaño 4 según las clases (0–3).
6. **Crea y entrena** una RNA 10‑8‑4 (10 entrada, 8 oculta, 4 salida) con backpropagation.
7. **Clasifica** cada número y muestra por pantalla:
   - Número decimal.
   - Clase predicha (0–3).
   - Etiqueta textual (par, impar, primo, compuesto).

---

## 🧪 Ejemplo de Salida

Ejemplo típico de ejecución:
```
Epoch 0 MSE=0.24
Epoch 500 MSE=0.03
Epoch 1000 MSE=0.01
Epoch 1500 MSE=0.005
```
Resultados sobre los datos del archivo:
```
Numero: 0 -> clase 0 (par)
Numero: 1 -> clase 1 (impar)
Numero: 2 -> clase 2 (primo)
Numero: 3 -> clase 2 (primo)
Numero: 4 -> clase 3 (compuesto)
Numero: 5 -> clase 2 (primo)
Numero: 6 -> clase 3 (compuesto)
Numero: 7 -> clase 2 (primo)
Numero: 8 -> clase 3 (compuesto)
Numero: 9 -> clase 3 (compuesto)
```


---

