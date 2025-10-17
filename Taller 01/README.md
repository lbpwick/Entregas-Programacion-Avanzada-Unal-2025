# Taller #01 de Programacion Avanzada Unal. 2025 
---
# Punto 01
* Se usa cin y cout para entrada/salida estándar.
* La división convierte explícitamente a double para mostrar resultados con decimales.
* Se valida que el divisor no sea cero antes de realizar la operación.
---
# Punto 02

## Metodología del programa

El código sigue los siguientes pasos para determinar el valor máximo y mínimo dentro de un conjunto de números ingresados por el usuario:

1. Se solicita al usuario el tamaño del arreglo y luego los valores numéricos que se almacenan en un `vector<double>`.
2. Se inicializa una estructura `Resultados` que contiene los valores máximo, mínimo y sus respectivas posiciones.
3. Si el arreglo no contiene elementos, se devuelve un resultado con valores nulos y posiciones en `-1` para indicar que no hay datos.
4. En caso contrario, se recorren los elementos del vector con un bucle `for`:
   - Si un elemento es mayor que el máximo actual, se actualizan el valor máximo y su posición.
   - Si un elemento es menor que el mínimo actual, se actualizan el valor mínimo y su posición.
5. Finalmente, se muestran en pantalla el valor máximo, el valor mínimo y las posiciones que ocupan dentro del arreglo.

---
# Punto 03

## Metodología del programa

El programa sigue los siguientes pasos para contar las vocales en una cadena:

1. Se utiliza `getline(cin, cadena)` para leer toda la línea de texto ingresada, incluyendo los espacios.
2. La función `tolower()` convierte cada carácter a minúscula, garantizando que el conteo sea insensible a mayúsculas o minúsculas.
3. Luego, mediante un bucle *for-each*, se recorre la cadena y se incrementa un contador cada vez que el carácter analizado es una vocal.
4. Finalmente, el programa muestra en pantalla el número total de vocales encontradas.
