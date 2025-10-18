# Taller #01 de Programacion Avanzada Unal. 2025 
---
# Punto 01

## Metodología del programa

El funcionamiento del código consiste en lo siguiente:

1. Se solicita al usuario que ingrese dos números enteros a través del teclado.
2. Se calculan y muestran los resultados de las operaciones de **suma**, **resta** y **multiplicación** directamente.
3. Para la **división**, se verifica primero que el segundo número no sea cero:
   - Si `b` es distinto de cero, se realiza la división utilizando conversión a `double` para obtener un resultado decimal preciso.
   - Si `b` es igual a cero, se muestra un mensaje de error indicando que no es posible dividir entre cero.
4. Finalmente, el programa muestra en pantalla todos los resultados obtenidos de manera ordenada.

---
# Punto 02

## Metodología del programa

El script ejecuta los pasos descritos a continuación para identificar el valor máximo y el valor mínimo dentro del conjunto de datos proporcionado por el usuario:

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
---
# Punto 04

## Metodología del programa

El programa implementa el cálculo de las **normas Euclidiana (L₂)** y **norma infinita (L∞)** tanto para **vectores** como para **matrices**.  
Para ello, se siguen los pasos descritos a continuación:

1. **Selección del tipo de dato:**
   - El programa solicita al usuario elegir si desea trabajar con un **vector (opción 1)** o con una **matriz (opción 2)**.

2. **Ingreso de datos:**
   - Si se elige **vector**, se pide el tamaño `n` y posteriormente los `n` elementos del vector.
   - Si se elige **matriz**, se piden las dimensiones (`filas` y `columnas`) y luego se ingresan los elementos fila por fila.
   - Los datos se almacenan en estructuras dinámicas de tipo `vector<double>` o `vector<vector<double>>` según el caso.

3. **Cálculo de la norma Euclidiana (L₂):**
   - Se suman los cuadrados de todos los elementos.
   - Luego, se obtiene la raíz cuadrada de esta suma utilizando `sqrt()`.
   - Matemáticamente:
     - Para un vector:  
       \[
       \|v\|_2 = \sqrt{\sum_{i=1}^{n} v_i^2}
       \]
     - Para una matriz:  
       \[
       \|M\|_2 = \sqrt{\sum_{i,j} M_{ij}^2}
       \]

4. **Cálculo de la norma infinita (L∞):**
   - En el caso del vector, se toma el **valor absoluto máximo** de todos los elementos.
   - En el caso de la matriz, se calcula la **máxima suma de valores absolutos por fila**.
   - Matemáticamente:
     - Para un vector:  
      $||v||_{\infty} = \max_i |v_i|$

     - Para una matriz:  
       \[
       \|M\|_\infty = \max_i \sum_j |M_{ij}|
       \]

5. **Visualización de resultados:**
   - Se muestran los datos ingresados en formato tabulado con cuatro cifras decimales (`setprecision(4)`).
   - Finalmente, se imprimen las normas L₂ y L∞ correspondientes, diferenciando entre vector o matriz.

6. **Manejo de errores:**
   - Si el usuario introduce una opción inválida al inicio, el programa muestra un mensaje de advertencia y termina la ejecución de forma segura.

---

De esta manera, el programa permite al usuario calcular y comparar dos tipos de normas ampliamente utilizadas en análisis numérico, álgebra lineal y evaluación de errores en vectores y matrices.

# Punto 05

## Metodología del programa

El programa permite calcular la **inversa** o **pseudoinversa de Moore–Penrose** de una matriz ingresada por el usuario.  
Sigue una metodología paso a paso basada en operaciones matriciales fundamentales:

1. **Lectura y almacenamiento de datos:**  
   El usuario ingresa el número de filas y columnas de la matriz, junto con sus elementos.  
   Estos se almacenan en una estructura `vector<vector<double>>` (alias `Matriz`).

2. **Visualización de la matriz:**  
   Se muestra la matriz ingresada en formato tabular para confirmar los datos.

3. **Determinación del tipo de matriz:**  
   - Si la matriz es **cuadrada**, se intenta calcular su **inversa clásica** mediante el método de **Gauss–Jordan**.  
   - Si no es cuadrada, el programa explica que **no posee una inversa convencional** y ofrece calcular la **pseudoinversa de Moore–Penrose**.

4. **Cálculo de la inversa (Gauss–Jordan):**  
   - Se forma una matriz identidad auxiliar.  
   - Se normaliza cada fila por su pivote y se eliminan los elementos fuera de la diagonal.  
   - Si un pivote es cero o muy pequeño, se determina que la matriz no es invertible.

5. **Cálculo de la pseudoinversa (Moore–Penrose):**  
   - Para matrices **sobredeterminadas** (más filas que columnas):  
     \[
     A^+ = (A^T A)^{-1} A^T
     \]
   - Para matrices **subdeterminadas** (más columnas que filas):  
     \[
     A^+ = A^T (A A^T)^{-1}
     \]
   - Se verifica que las matrices intermedias \((A^T A)\) o \((A A^T)\) sean invertibles antes de continuar.

6. **Resultados mostrados:**  
   - Si se obtiene una inversa o pseudoinversa válida, el resultado se imprime en formato matricial.  
   - En caso contrario, se notifica al usuario que la matriz no es invertible.

---

