#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>  // Para setprecision
using namespace std;

// Calcula normas L2 y L_inf para vectores
void calcularNormasVector(const vector<double>& v) {
    double norma2 = 0.0;
    double normainf = 0.0;

    for (double val : v) {
        norma2 += val * val;
        if (fabs(val) > normainf)
            normainf = fabs(val);
    }

    norma2 = sqrt(norma2);

    cout << fixed << setprecision(4);
    cout << "\n--- Resultados (Vector) ---" << endl;
    cout << "Norma L2 (Euclidiana): " << norma2 << endl;
    cout << "Norma L_inf (Infinita): " << normainf << endl;
}

// Calcula normas L2 y L_inf para matrices
void calcularNormasMatriz(const vector<vector<double>>& M) {
    double norma2 = 0.0;
    double normainf = 0.0;

    for (size_t i = 0; i < M.size(); ++i) {
        double sumaFila = 0.0;
        for (size_t j = 0; j < M[i].size(); ++j) {
            norma2 += M[i][j] * M[i][j];
            sumaFila += fabs(M[i][j]);
        }
        if (sumaFila > normainf)
            normainf = sumaFila;
    }

    norma2 = sqrt(norma2);

    cout << fixed << setprecision(4);
    cout << "\n--- Resultados (Matriz) ---" << endl;
    cout << "Norma L2 (Euclidiana): " << norma2 << endl;
    cout << "Norma L_inf (Infinita): " << normainf << endl;
}

int main() {
    int tipo;
    cout << "Seleccione tipo de arreglo (1 = vector, 2 = matriz): ";
    cin >> tipo;

    if (tipo == 1) {
        int n;
        cout << "\nIngrese tamaño del vector: ";
        cin >> n;

        vector<double> v(n);
        cout << "\nIngrese los elementos del vector:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "  v[" << i + 1 << "] = ";
            cin >> v[i];
        }

        cout << "\nVector ingresado: [ ";
        cout << fixed << setprecision(4);
        for (double val : v)
            cout << val << " ";
        cout << "]" << endl;

        calcularNormasVector(v);
    }
    else if (tipo == 2) {
        int filas, columnas;
        cout << "\nIngrese número de filas: ";
        cin >> filas;
        cout << "Ingrese número de columnas: ";
        cin >> columnas;

        vector<vector<double>> M(filas, vector<double>(columnas));
        cout << "\nIngrese los elementos de la matriz (fila por fila):\n";
        for (int i = 0; i < filas; ++i) {
            cout << "Fila " << i + 1 << ":" << endl;
            for (int j = 0; j < columnas; ++j) {
                cout << "  M[" << i + 1 << "][" << j + 1 << "] = ";
                cin >> M[i][j];
            }
        }

        cout << "\nMatriz ingresada:" << endl;
        cout << fixed << setprecision(4);
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j)
                cout << setw(8) << M[i][j];
            cout << endl;
        }

        calcularNormasMatriz(M);
    }
    else {
        cout << "\nOpción inválida." << endl;
    }

    return 0;
}
