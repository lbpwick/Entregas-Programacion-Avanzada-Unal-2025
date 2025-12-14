# 🏗️ Diseño y Arquitectura – `punto_03.cpp`

Este documento describe la **arquitectura interna** del programa `punto_03`,
que implementa una RNA simple en C++ para clasificar números 0–9 en 4 clases.

---

## 1. Objetivo del Sistema

- Leer números en **binario** desde `digitos.txt`.
- Convertir cada línea a un entero \(n \in [0, 9]\).
- Construir un conjunto de entrenamiento \((X, Y)\).
- Entrenar una Red Neuronal **10‑8‑4** con backpropagation.
- Clasificar los números y mostrar su clase:

  - `0`: par.
  - `1`: impar.
  - `2`: primo.
  - `3`: compuesto.

---

## 2. Arquitectura General

### Diagrama de Flujo Alto Nivel
```
digitos.txt (binario por línea)
│
▼
Preprocesamiento
(limpiar + bin→int)
│
▼
Dataset (X,Y)
X: one-hot dígito 0-9
Y: vector clases (0-3)
│
▼
Red Neuronal 10-8-4
│
▼
Clasificación y salida
```

---

## 3. Componentes Principales

Todo está implementado en un único archivo `punto_03.cpp`, organizado en bloques:

1. **Utilidades numéricas**
   - Inicialización aleatoria de pesos.
   - Función de activación sigmoide y su derivada.

2. **Conversión y propiedades de números**
   - `binario_a_int`: convierte un string de bits a entero.
   - `esPrimo`, `esCompuesto`: para etiquetar los datos.

3. **Codificación de datos**
   - `encode_input(int)`: entero 0–9 → vector one‑hot de tamaño 10.
   - `encode_target(int)`: entero 0–9 → vector de tamaño 4 con clases.

4. **Clase `NeuralNet`**
   - Representa una red 10‑8‑4:
     - 10 neuronas de entrada.
     - 8 neuronas ocultas.
     - 4 neuronas de salida.
   - Métodos:
     - `forward`: propagación hacia adelante.
     - `train_example`: una iteración de backpropagation para un ejemplo.

5. **Entrada de datos**
   - `leer_digitos_binarios`: lee `digitos.txt`, limpia cada línea y convierte a enteros.

6. **Orquestación (`main`)**
   - Construye el dataset `X`, `Y`.
   - Crea la red y la entrena.
   - Clasifica los datos y muestra resultados.

---

## 4. Diseño de Datos

### 4.1 Representación de Entradas

Para un entero \(d \in \{0,1,\dots,9\}\):  encode_input(d) → vector<double> tamaño 10


Ejemplos:

- `d = 3` → `[0,0,0,1,0,0,0,0,0,0]`
- `d = 7` → `[0,0,0,0,0,0,0,1,0,0]`

Esta representación **one‑hot** hace que cada dígito sea una base canónica en \(\mathbb{R}^{10}\).

### 4.2 Representación de Salidas

Las clases se codifican en un vector de tamaño 4:

Orden: `[par, impar, primo, compuesto]`.

Ejemplos:

- `d = 2` (par y primo): `[1, 0, 1, 0]`.
- `d = 9` (impar y compuesto): `[0, 1, 0, 1]`.
- `d = 1` (impar, ni primo ni compuesto): `[0, 1, 0, 0]`.
- `d = 0` (par, ni primo ni compuesto): `[1, 0, 0, 0]`.

En la predicción se toma el índice con mayor activación como **clase dominante**.

---

## 5. Clase `NeuralNet`

### 5.1 Atributos
int n_input, n_hidden, n_output;

// input -> hidden
std::vector<std::vector<double>> w_ih; // [hidden][input]
std::vector<double> b_h;

// hidden -> output
std::vector<std::vector<double>> w_ho; // [output][hidden]
std::vector<double> b_o;

// activaciones
std::vector<double> a_in; // tamaño 10
std::vector<double> a_h; // tamaño 8
std::vector<double> a_out; // tamaño 4