# Taller #02 de Programacion Avanzada Unal. 2025 
---
# Punto 01

## Metodología del programa

El objetivo del programa es demostrar cómo manipular vectores tridimensionales mediante una clase orientada a objetos.
La metodología utilizada se basa en los siguientes pasos:

1. Definición de la clase Vector3D

Contiene tres atributos privados: x, y, z, que representan las componentes del vector.

Incluye métodos y operadores sobrecargados para operar con objetos de esta clase.

2. Sobrecarga de operadores

`operator+` → realiza la suma de dos vectores.

`operator-` → realiza la resta de dos vectores.

`operator*` → implementa el producto escalar (retorna un número real).

3. Funciones matemáticas

`magnitud()` → calcula la longitud del vector usando la raíz cuadrada de la suma de los cuadrados de sus componentes.

`normalizado()` → devuelve un nuevo vector con la misma dirección pero con magnitud igual a 1.

4. Interacción con el usuario

La función `leerVector()` solicita al usuario las componentes x, y, z de dos vectores.

En `main()`, el usuario ingresa ambos vectores y el programa muestra:

Los resultados de la suma, resta y producto escalar.

La magnitud y el vector normalizado de cada uno.

5. Salida formateada

Se emplea la función `mostrar()` para imprimir los vectores en un formato legible.

### Estructura del código
Vector3D.cpp
├── Clase `Vector3D`
│   ├── Constructor
│   ├── Operadores sobrecargados (`+`, `-`, `*`)
│   ├── Métodos: `magnitud()`, `normalizado()`, `mostrar()`
├── Función auxiliar `leerVector()`
└── Función principal `main()`


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



## Metodología del programa
