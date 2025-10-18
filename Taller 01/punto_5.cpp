#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using Matriz = vector<vector<double>>;

// ---------- FUNCIONES AUXILIARES ----------
Matriz transpuesta(const Matriz& A) {
    int filas = A.size(), columnas = A[0].size();
    Matriz T(columnas, vector<double>(filas));
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            T[j][i] = A[i][j];
    return T;
}

Matriz multiplicar(const Matriz& A, const Matriz& B) {
    int filas = A.size(), columnas = B[0].size(), n = B.size();
    Matriz C(filas, vector<double>(columnas, 0.0));
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// ---------- INVERSA GAUSS-JORDAN ----------
bool invertirMatriz(Matriz& A, Matriz& inversa) {
    int n = A.size();
    inversa.assign(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        inversa[i][i] = 1.0;

    for (int i = 0; i < n; i++) {
        double pivote = A[i][i];
        if (fabs(pivote) < 1e-10) return false;

        for (int j = 0; j < n; j++) {
            A[i][j] /= pivote;
            inversa[i][j] /= pivote;
        }

        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = 0; j < n; j++) {
                A[k][j] -= factor * A[i][j];
                inversa[k][j] -= factor * inversa[i][j];
            }
        }
    }
    return true;
}

// ---------- PSEUDOINVERSA DE MOORE–PENROSE ----------
Matriz pseudoinversa(const Matriz& A) {
    int filas = A.size(), columnas = A[0].size();
    Matriz AT = transpuesta(A);

    // Caso 1: más filas que columnas (sobredeterminado)
    if (filas >= columnas) {
        Matriz ATA = multiplicar(AT, A);
        Matriz ATAinv;
        Matriz temp = ATA;
        if (!invertirMatriz(temp, ATAinv)) {
            cout << "No se puede calcular pseudoinversa: (A^T A) no es invertible." << endl;
            return {};
        }
        return multiplicar(ATAinv, AT);
    }
    // Caso 2: más columnas que filas (subdeterminada)
    else {
        Matriz AAT = multiplicar(A, AT);
        Matriz AATinv;
        Matriz temp = AAT;
        if (!invertirMatriz(temp, AATinv)) {
            cout << "No se puede calcular pseudoinversa: (A A^T) no es invertible." << endl;
            return {};
        }
        return multiplicar(AT, AATinv);
    }
}

// ---------- PRINCIPAL ----------
int main() {
    int filas, columnas;
    cout << "Ingrese número de filas: ";
    cin >> filas;
    cout << "Ingrese número de columnas: ";
    cin >> columnas;

    Matriz A(filas, vector<double>(columnas));
    cout << "Ingrese los elementos de la matriz A (por filas):\n";
    for (int i = 0; i < filas; i++)
        for (int j = 0; j < columnas; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> A[i][j];
        }

    cout << "\nMatriz ingresada:\n";
    for (auto& fila : A) {
        for (double val : fila) cout << val << "\t";
        cout << endl;
    }

    if (filas == columnas) {
        Matriz inversa;
        Matriz temp = A;
        if (invertirMatriz(temp, inversa)) {
            cout << "\nMatriz inversa:\n";
            for (auto& fila : inversa) {
                for (double val : fila) cout << val << "\t";
                cout << endl;
            }
        } else {
            cout << "\nLa matriz es cuadrada, pero no tiene inversa (determinante = 0 o filas/columnas dependientes)." << endl;
        }
    } else {
        cout << "\nLa matriz NO es cuadrada, por lo tanto **no tiene una inversa clásica**." << endl;
        cout << "Esto se debe a que la operación A^-1 sólo está definida para matrices cuadradas no singulares." << endl;

        char opcion;
        cout << "\n¿Desea calcular la pseudoinversa de Moore–Penrose como alternativa? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            Matriz pinv = pseudoinversa(A);
            if (!pinv.empty()) {
                cout << "\nPseudoinversa (Moore–Penrose):\n";
                for (auto& fila : pinv) {
                    for (double val : fila) cout << val << "\t";
                    cout << endl;
                }
            }
        } else {
            cout << "Operación finalizada sin calcular la pseudoinversa." << endl;
        }
    }

    return 0;
}
