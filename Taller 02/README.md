# Taller #02 de Programacion Avanzada Unal. 2025 

## Librerías necesarias para 5 de los 6 códigos

### Punto 1 

* `<iostream>`
* `<vector>`
* `<cmath>`

### Punto 2 

* `<iostream>`
* `<random>`
* `<stdexcept>`
* `<limits>`

###  Punto 3 

* `<iostream>`
* `<cmath>`
* `<iomanip>`
* `<typeinfo>`

### Punto 4 

* `<iostream>`
* `<cmath>`
* `<vector>`
* `<typeinfo>`

### Punto 5 

* `<iostream>`
* `<vector>`
* `<string>`
* `<sstream>`
* `<algorithm>`
* `<cmath>`
---
## Cómo compilar y ejecutar programas en C++ usando Visual Studio Code

Esta guía resume los pasos generales necesarios para compilar y ejecutar cualquiera de los programas en C++ dentro de Visual Studio Code.

### 1. Instalar requisitos

#### a) Compilador C++

Instala un compilador compatible con C++17 o superior:

* **Windows**: MinGW-w64 o MSYS2
* **Linux**: `sudo apt install g++`
* **macOS**: instalar Xcode Command Line Tools (`xcode-select --install`)

Verifica la instalación ejecutando en la terminal:
```bash
g++ --version
```

### 2. Instalar extensiones en VS Code

Desde el Marketplace de VS Code instala:

* **C/C++** (de Microsoft) → soporte de IntelliSense y depuración
* **C/C++ Compile Run** (opcional) → permite ejecutar con un clic
* **Code Runner** (opcional)

### 3. Abrir el proyecto en VS Code

1. Crea una carpeta para tus programas.
2. Copia dentro de ella cualquiera de los archivos de código (`.cpp`).
3. En VS Code, abre esa carpeta: **File → Open Folder**

### 4. Compilar manualmente desde la terminal integrada

1. Abre la terminal: **View → Terminal**
2. Compila cualquier archivo con:
```bash
g++ archivo.cpp -o programa
```

Ejemplo:
```bash
g++ matrices.cpp -o matrices
```

3. Ejecuta:

**En Linux / macOS:**
```bash
./programa
```

**En Windows:**
```bash
programa.exe
```

### 5. Compilar y ejecutar usando C/C++ Compile Run (opcional)

Si instalaste la extensión:

* Simplemente presiona **F6**
* VS Code compilará y ejecutará automáticamente el archivo actual.

### 6. Crear una tarea personalizada (opcional)

Para automatizar la compilación:

1. Ve a **Terminal → Configure Tasks… → C++: g++ build active file**
2. VS Code generará `.vscode/tasks.json`.

Para compilar con esa tarea, usa:
```
Ctrl + Shift + B
```

### 7. Entrada por teclado

Si el programa requiere datos del usuario, asegúrate de ejecutarlo desde la terminal, no desde Code Runner, para evitar problemas con `cin`.

---

### Resumen rápido

* Instala un compilador y la extensión C/C++.
* Abre el archivo en VS Code.
* Compila con:
```bash
g++ archivo.cpp -o ejecutable
```

* Ejecuta con `./ejecutable` (Linux/macOS) o `ejecutable.exe` (Windows)

---
# Punto 01

## Metodología del programa

El objetivo del programa es demostrar cómo manipular vectores tridimensionales mediante una clase orientada a objetos.
La metodología utilizada se basa en los siguientes pasos:

1. Definición de la clase Vector3D

  Contiene tres atributos privados: `x`, `y`, `z`, que representan las componentes del vector. Incluye métodos y operadores sobrecargados para operar con objetos de esta clase.

2. Sobrecarga de operadores

  `operator+` → realiza la suma de dos vectores.

  `operator-` → realiza la resta de dos vectores.

  `operator*` → implementa el producto escalar (retorna un número real).

3. Funciones matemáticas

  `magnitud()` → calcula la longitud del vector usando la raíz cuadrada de la suma de los cuadrados de sus componentes.

  `normalizado()` → devuelve un nuevo vector con la misma dirección pero con magnitud igual a 1.

4. Interacción con el usuario

  La función `leerVector()` solicita al usuario las componentes `x`, `y`, `z` de dos vectores.

  En `main()`, el usuario ingresa ambos vectores y el programa muestra:

  -- Los resultados de la suma, resta y producto escalar.

  -- La magnitud y el vector normalizado de cada uno.

5. Salida formateada

Se emplea la función `mostrar()` para imprimir los vectores en un formato legible.

---
# Punto 02

## Metodología del programa

Características implementadas
1. **Constructor**: inicializa con valores aleatorios entre 0 y 9.
2. **Destructor**: libera memoria dinámica correctamente.
3. **Encapsulación**: atributos privados (`n, datos`).
4. Sobrecarga de operador (): acceso estilo `A(i,j)`.
5. Método `transpuesta()`: devuelve una nueva matriz transpuesta.
6. Método `multiplicar()`: realiza la multiplicación matricial clásica.
7. Método `imprimir()`: muestra la matriz en consola.
8. Se usa `random` con `std::mt19937` y `std::uniform_int_distribution` para generar números aleatorios.
9. Esto garantiza que A y B tengan valores diferentes en cada ejecución, incluso si se crean en el mismo instante.
10. En métodos como `transpuesta()` y `multiplicar()`, se usan semillas fijas para inicializar matrices auxiliares, evitando que aparezcan valores aleatorios no deseados.

---

# Punto 03

Este programa implementa una clase Polinomio en C++ que permite crear y operar polinomios de manera dinámica usando programación orientada a objetos. Cada polinomio almacena su grado y un arreglo dinámico de coeficientes, lo que permite manejar funciones de cualquier orden.

## Metodología del programa

Clase `Polinomio`: 

- Contiene el grado y los coeficientes del polinomio.

- Usa memoria dinámica (`new` y `delete[]`) para adaptarse al tamaño del polinomio.

- Incluye constructor por defecto, constructor copia, operador de asignación y destructor.

`Operaciones implementadas`:

- Suma (`operator+`): combina coeficientes de ambos polinomios.

- Multiplicación (`operator*`): aplica convolución de coeficientes.

- Evaluación (`evaluar(x)`): calcula el valor numérico del polinomio.

- Derivación (`derivar()`): genera un nuevo polinomio con la derivada.

- Impresión formateada (`imprimir()`): muestra el polinomio con signos y potencias.

`Interacción con el usuario`:

- El método `leer()` permite ingresar el grado y coeficientes.


Un menú en `main()` permite:

- Leer dos polinomios.

- Mostrarlos.

- Sumarlos.

- Multiplicarlos.

- Evaluar uno de ellos.

- Derivarlo.

---
# Punto 04

Este programa implementa dos clases (`complex` y `polar`) que permiten trabajar de forma flexible con números complejos tanto en su forma binomial ($$a + bi$$) como en su forma polar ($$r·e^{iθ}$$). Además, integra operaciones básicas, conversiones entre ambas representaciones y funciones de acumulación usando plantillas variádicas.

## Metodología

1. Clase `complex` (forma binomial)

Representa un número complejo del tipo $$a + bi$$, e incluye:

- Operadores definidos:

  - Suma, resta, multiplicación y división.

  - Conjugado.

- Conversiones:

  - Constructor que recibe un número polar.

  - Método `toPolar()` para convertir a coordenadas polares.

- Visualización:

  - print() muestra el número en formato ($$a ± bi$$).


2. Clase polar (forma polar)

Representa números complejos como $$r · e^{iθ}$$, con:

- Operadores definidos:

  - Suma y resta (conversión temporal a binomial).

  - Multiplicación y división mediante propiedades polares.

  - Conjugado.

- Conversiones:

  - Constructor que recibe un número complejo.

  - toComplex() para convertir a forma binomial.

- Visualización:

  - `print()` imprime $$r * e^{iθ}$$.


## Relación entre complex y polar

Ambas clases están diseñadas para ser compatibles mediante:

- Constructores cruzados.

- Métodos de conversión (`toPolar()` y `toComplex()`).

- Operadores que permiten realizar operaciones sin importar la forma en la que fueron ingresados.

## Funciones plantilla (Templates variádicas)

El programa implementa dos funciones para sumar múltiples valores:

- `acumula(args...)` → recibe varios números complejos y retorna su suma.

- `acumulaPolar(args...)` → recibe varios valores polares, los convierte a binomial y acumula sus sumas.

Esto permite sumar una cantidad arbitraria de números usando una sola llamada.

## Interfaz por menú

El `main()` incluye un menú interactivo que permite:

- Crear y mostrar un número complejo.

- Crear y mostrar un número en formato polar.

- Convertir entre ambas representaciones.

- Realizar operaciones (`+`, `−`, `×`, `÷`, conjugado) entre dos complejos.

- Sumar múltiples números complejos ingresados por el usuario.

---
# Punto 05
Este programa implementa una calculadora de polinomios en C++ usando Programación Orientada a Objetos. Permite ingresar dos polinomios, mostrarlos en formato algebraico y calcular su suma y multiplicación.

## Metodología

**Clase** `CTermino`

Representa un término de la forma 𝑐𝑥𝑒cxe.

- Atributos: coeficiente (coef) y exponente (exp).

- Funciones clave:

  - `getCoef()` y `getExp()`: obtienen coeficiente y exponente.

  - `toString()`: convierte el término a formato algebraico (por ejemplo, $$+3x^2$$).

**Clase** `CPolinomio`

Gestiona un polinomio como un vector de términos.

- insertar(CTermino)
Añade un término manteniendo:

  - suma de coeficientes si ya existe ese exponente,

  - eliminación si queda coeficiente 0,

  - orden ascendente por exponente.

- sumar(CPolinomio)
Suma dos polinomios insertando sus términos en uno nuevo.

- multiplicar(CPolinomio)
Aplica multiplicación clásica: combina todos los términos entre ambos polinomios.

- toString()
Devuelve la representación algebraica completa (ej. $$4x^{3}+2x-1$$).

- **Entrada del usuario**

La función `leerPolinomioUsuario()` pide:

  - Grado del polinomio.

  - Coeficientes desde $$x^{n}$$ hasta $$x^{0}$$.

Cada término se inserta en el polinomio automáticamente.

- `main()`

  - Solicita P(x) y Q(x) al usuario.

  - Calcula:

    - Suma: `P + Q`

    - Producto: `P * Q`

  - Muestra todos los resultados en formato algebraico.

---
# Punto 06 

Abrir carpeta `Punto 6` y leer el `README` correspondiente a este punto.


