# Taller #03 de Programacion Avanzada Unal. 2025

## Punto 1

###  Listado Estudiantil

Este ejercicio implementa un sistema de gestión de estudiantes utilizando listas enlazadas simples en C++.  
El programa permite insertar, eliminar, buscar, mostrar, invertir la lista y guardar los datos en un archivo.

---

###  Requisitos

Para compilar y ejecutar el programa necesitas:

- Un compilador compatible con **C++11** o superior (como `g++`)
- Sistema operativo **Windows**, **Linux** o **macOS**
- **Terminal / Consola**

---

### ▶️ Cómo compilar

Ejecutar en la terminal dentro de la carpeta del archivo:

```bash
g++ punto_1.cpp -o program
```
---
### 🧩 Descripción del Programa

El programa permite gestionar estudiantes mediante un menú interactivo con las opciones:

- Insertar estudiante.

- Eliminar estudiante por ID.

- Buscar estudiante por ID.

- Mostrar lista completa.

- Guardar lista en archivo `.txt`

- Invertir la lista enlazada.

- Acceder por índice usando `operator[]`

- Salir.

---

### 🛠️ Metodología del Código

A continuación se explica la estructura y funcionamiento interno del programa.

#### 🔹 1. Estructura Estudiante

Cada estudiante se almacena en una estructura que contiene:

- `nombreCompleto`

- `anioNacimiento`

- `id`

- `promedio`

- `email`

Representa la información básica del estudiante.

#### 🔹 2. Lista Enlazada Simple

El programa implementa manualmente una lista enlazada simple para almacenar estudiantes.

##### ✔ Estructura `Nodo`.

Cada nodo contiene:

- Un objeto `Estudiante`

- Un puntero al siguiente nodo (`Nodo* siguiente`)

##### ✔ Clase `ListadoEstudiantil`.

Centraliza todas las operaciones sobre la lista enlazada.

##### 🔸 `insertar(const Estudiante&)`

Inserta un estudiante al final de la lista.

- Si la lista está vacía, el nuevo nodo se convierte en la cabeza.

- Si no, se recorre la lista hasta encontrar el último nodo y se enlaza el nuevo.

##### 🔸 `eliminar(long id)`

Elimina al estudiante con el ID indicado.

Casos manejados:

- Lista vacía.

- El estudiante a eliminar es el primero.

- El estudiante está en cualquier otra posición.

Ajusta los punteros y libera memoria con `delete`.

##### 🔸 `buscar(long id)`

Busca un estudiante por ID.

- Recorre secuencialmente la lista.

- Retorna la posición `(0, 1, 2, …)`.

- Si no existe, devuelve `-1`.

##### 🔸 `operator[](int index)`

Sobrecarga del operador `[]` para acceder a un estudiante por índice como si fuera un arreglo.

Ejemplo:
```bash
Estudiante e = lista[2];
```

Si el índice es inválido, lanza la excepción:

```bash
std::out_of_range
```
##### 🔸 `invertir()`

Invierte el orden de la lista enlazada usando manipulación de punteros.

Utiliza tres punteros:

- `anterior`

- `actual`

- `siguiente`

Es un proceso in-place (sin usar memoria extra).

##### 🔸 `imprimirEnArchivo(const string&)`

Guarda todos los estudiantes en un archivo `.txt.`

Formato:
```bash
Nombre: Juan Pérez
Año de nacimiento: 2001
ID: 12345
Promedio: 17.8
Email: juan@gmail.com
-----------------------------
```
##### 🔸 `mostrar()`

Imprime en consola el contenido completo de la lista.

#### 🔹 3. `Función crearEstudiante()`

Solicita al usuario los datos requeridos y devuelve un objeto Estudiante.

El ingreso incluye:

- Nombre completo

- Año de nacimiento

- ID

- Promedio

- Email

#### 🔹 4. Menú en `main()`

Controlado con un do-while, permite al usuario seleccionar opciones.

También incluye:

- `setlocale()` para permitir caracteres en español.

- Manejo de excepciones al usar `operator[]`.

#### Ejemplo de uso
##### Insertar un estudiante
```bash
Nombre completo: Juan García
Año de nacimiento: 2001
ID: 123
Promedio: 17.5
Email: juan@gmail.com
```
##### Guardar en archivo
```bash
Nombre del archivo (ej: salida.txt): estudiantes.txt
Archivo guardado.
```
---
#### Recomendación de espacio de trabajo
Se recomienda que se tenga un archivo especificamente para este script.
```bash
📁 Code_1
 ├── Punto_1.cpp
 └── README.md
```
--- 
## Punto 2

### Procesamiento de Señal ECG 

Este ejercicio implementa un sistema en C++ para:

- Leer una señal ECG desde un archivo `.txt`.
- Calcular la frecuencia de muestreo.
- Filtrar la señal con dos métodos distintos (IIR simple y Butterworth con **filtfilt**).
- Detectar picos (complejos R) y calcular la frecuencia cardiaca.
- Guardar la señal filtrada en un nuevo archivo.

El proyecto está compuesto por **tres archivos de código y un archivo de datos en** `.txt` **iniciales de una señal**:

- `main.cpp` — Programa principal e interfaz por menú.  
- `SignalECG.h` — Definición de la clase `SignalECG` y la estructura `Node`.  
- `SignalECG.cpp` — Implementación de todos los métodos de procesamiento de la señal ECG.  
- `ECG.txt` — Archivo de datos que será filtrado. 

---

### 📂 Estructura del proyecto

Coloca los cuatro archivos en la misma carpeta:

```text
Punto_02/
├── main.cpp
├── SignalECG.cpp
├── SignalECG.h
└── ECG.txt   (archivo de entrada)
```
---

### ✅ Requisitos

Para compilar y ejecutar el programa necesitas:

- Compilador C++ compatible con C++11 o superior.

  - Ejemplo: `g++` (MinGW en Windows, o instalado en Linux / macOS).

- Sistema operativo:

  - Windows, Linux o macOS.

- Una terminal / consola para compilar y ejecutar.

### 🛠️ Cómo compilar

#### 🔹 Linux / macOS

Abre una terminal en la carpeta del proyecto y ejecuta:

```bash
g++ main.cpp SignalECG.cpp -o ecg_tool
```
Esto generará un ejecutable llamado:

- `ecg_tool` en Linux / macOS.

#### 🔹 Windows (con MinGW)

1. Asegúrate de tener instalado MinGW y que g++ esté en la variable PATH.

2. En la carpeta del proyecto, ejecuta en el terminal:
```bash
g++ -std=c++11 main.cpp SignalECG.cpp -o ecg_tool.exe
```

Esto generará el ejecutable:

- `ecg_tool.exe` en Windows.

### ▶️ Cómo ejecutar
**Linux / macOS**
```bash
./ecg_tool
```
**Windows**

En la terminal:
```bash
ecg_tool.exe
```

### 📄 Formato del archivo de entrada ECG

El programa espera un archivo de texto con dos columnas:
```bash
amplitud,tiempo
4.000566,0
7.391435,0.005
7.120300,0.010
...
```
- Separador: coma ,

- Sin encabezados (no uses títulos como "amp" o "time")

- `amplitud`: valor de la muestra de la señal ECG (en mV o unidades arbitrarias)

- `tiempo`: instante de tiempo correspondiente a cada muestra (en segundos)

### 💾 Formato del archivo de salida

Cuando elijas la opción “Guardar señal filtrada”, el programa creará un archivo .txt con el siguiente formato:
```bash
amplitud_filtrada,tiempo
0.10234,0
0.12098,0.005
...
```

Es decir, guarda la columna filtrada y el tiempo original.

### 🧩 Uso del menú (flujo básico)

Al ejecutar el programa verás un menú como este:

```bash
====== MENU ECG ======
1. Cargar archivo ECG
2. Calcular frecuencia de muestreo (Fs)
3. Filtrar simple (pasa bajos exponencial)
4. Filtrar Butterworth con filtfilt (RECOMENDADO)
5. Detectar picos y frecuencia cardiaca
6. Guardar señal filtrada
7. Salir
Seleccione una opcion:

```

#### Opción 1 — Cargar archivo ECG

Pide el nombre del archivo, por ejemplo:
```bash
Ingrese el nombre del archivo: datos_ecg.txt
(escribir nombre del archivo con su extensión)
```

#### Opción 2 — Calcular frecuencia de muestreo (Fs)

**1.** Calcula el período de muestreo promedio `Ts`:

<p align="center">

$$
T_s = \frac{1}{N - 1} \sum_{i=1}^{N-1} (t_{i+1} - t_i)
$$

</p>

**2.** Luego calcula la frecuencia de muestreo:

<p align="center">

$$
F_s = \frac{1}{T_s}
$$

</p>

**3.** Muestra el valor de `Fs` en Hz.

#### Opción 3 — Filtro pasa bajos simple (IIR de 1er orden)

Este filtro es un suavizado exponencial basado en una frecuencia de corte `Fc` elegida por el usuario.

**1.** El programa calcula el período de muestreo `Ts`.
**2.** A partir de `Fc` y `Ts`, calcula el coeficiente:

<p align="center">

$$
\alpha = 1 - e^{-2\pi F_c T_s}
$$

</p>

**3.** Aplica el filtro recursivo:
- Sea `x[n]` la amplitud original.
- Sea `y[n]` la señal filtrada.

<p align="center">

$$
y[n] = \alpha x[n] + (1 - \alpha)\, y[n-1] 
$$

</p>

**4.** El resultado se guarda en `Node::filtrada` para cada muestra.

#### Opción 4 — Filtro Butterworth con filtfilt (recomendado)
Este es el método principal y recomendado para señales ECG.

**Objetivo**: obtener un filtrado pasa bajos:

- Con frecuencia de corte `Fc` (típicamente 40–50 Hz para ECG)

- Con respuesta Butterworth (amplitud plana en banda pasante)

- Con fase casi cero usando filtrado bidireccional (filtfilt).

##### Pasos internos del método

**1. Leer parámetros del usuario**

- Frecuencia de corte Fc (Hz)

- Orden del filtro: 2 o 4

  - Si se ingresa otro valor, el código fuerza orden 4.

**2. Calcular la frecuencia de muestreo Fs usando el mismo método de la opción 2.**

**3. Normalizar frecuencia de corte:**
- Frecuencia de Nyquist:
<p align="center">

$$
F_N = \frac{F_s}{2}
$$

</p>

- Frecuencia normalizada:
<p align="center">

$$
W_n = \frac{F_c}{F_N}
$$

</p>

**4. Pre-warping** para la transformación bilineal:

<p align="center">

$$
w_p = \tan{(\frac{\pi * W_n}{2})}
$$

</p>

**5. Calcular coeficientes del filtro Butterworth** (`b` y `a`) según el orden:

- Para **orden 2**: se calculan directamente los coeficientes del filtro IIR de segundo orden.

- Para **orden 4**: se construye como cascada de dos secciones de orden 2 con factores de calidad `Q1` y `Q2`, y luego se combinan por convolución de coeficientes.

**6. Filtrado hacia adelante** (función `aplicarFiltroIIR`):
Implementa la ecuación general de un filtro IIR:
<p align="center">

$$
y[n] = \frac{1}{a_0}*( \sum_{k=0}^{M} b_{k}x[n-k] - \sum_{k=1}^{N}a_{k}y[n-k])  
$$

</p>

### 🧠 Metodología general del programa

Resumiendo, la metodología que sigue el sistema es:

#### 1. Adquisición de datos

- Lectura de un archivo .txt con muestras de ECG (amplitud,tiempo).

- Almacenamiento en una lista doblemente enlazada para facilitar recorridos y posible extensión futura (por ejemplo, eliminación/inserción de muestras).

#### 2. Caracterización de la señal

- Cálculo del período de muestreo promedio `Ts`.

- Obtención de la frecuencia de muestreo `Fs = 1/Ts`.

#### 3. Filtrado de ruido

- Opción 3: Filtro IIR de primer orden (suavizado exponencial), útil para pruebas rápidas pero con desfase.

- Opción 4 (metodología recomendada):

  - Diseño de un filtro Butterworth digital a partir de una frecuencia de corte Fc.

  - Uso de pre-warping y transformación bilineal en el cálculo de coeficientes.

  - Aplicación de filtrado bidireccional (filtfilt) para reducir el desfase y preservar la forma de la señal.

#### 4. Detección de picos (complejos R)

- Se explota la señal ya filtrada para evitar falsos picos por ruido.

- Umbral ajustable por el usuario para adaptarse a señales de distinta amplitud.

- Detección mediante máximos locales.

#### 5. Cálculo de frecuencia cardiaca

- Cálculo de intervalos R–R promedio.

- Conversión a bpm mediante `FC = 60 / RR_prom`.

#### 6. Exportación de resultados

Escritura de la señal filtrada en un nuevo archivo para análisis posterior (por ejemplo, graficarla en Python y entre otros).




---
## Punto 3

Abrir carpeta `03. Domino` para acceder a la información sobre los scripts del punto 03 y su `README.md` específico.

---










