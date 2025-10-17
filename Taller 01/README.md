# Taller #01 de Programacion Avanzada Unal. 2025 
---
# Punto 01
* Se usa cin y cout para entrada/salida estándar.
* La división convierte explícitamente a double para mostrar resultados con decimales.
* Se valida que el divisor no sea cero antes de realizar la operación.
---
# Punto 02
* Uso de una estructura Resultados para devolver múltiples valores (máximo, mínimo y posiciones).
* La función encontrarMaxMin recorre el arreglo una sola vez (O(n)).
* Se maneja el caso de arreglo vacío devolviendo posiciones -1.
---
## Punto 03
## Metodología del programa

El programa sigue los siguientes pasos para contar las vocales en una cadena:

1. Se utiliza `getline(cin, cadena)` para leer toda la línea de texto ingresada, incluyendo los espacios.
2. La función `tolower()` convierte cada carácter a minúscula, garantizando que el conteo sea insensible a mayúsculas o minúsculas.
3. Luego, mediante un bucle *for-each*, se recorre la cadena y se incrementa un contador cada vez que el carácter analizado es una vocal.
4. Finalmente, el programa muestra en pantalla el número total de vocales encontradas.
