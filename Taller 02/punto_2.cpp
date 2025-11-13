#include <iostream>
#include <random>
#include <stdexcept>
#include <limits> // numeric_limits
using namespace std;

class Matriz
{
private:
    int n;
    int **datos;

public:
    Matriz(int tam, int semilla) : n(tam)
    {
        std::mt19937 gen(semilla);
        std::uniform_int_distribution<> dis(0, 9);
        datos = new int *[n];
        for (int i = 0; i < n; i++)
        {
            datos[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                datos[i][j] = dis(gen);
            }
        }
    }

    ~Matriz()
    {
        for (int i = 0; i < n; i++)
            delete[] datos[i];
        delete[] datos;
    }

    int &operator()(int fila, int col)
    {
        if (fila >= 0 && fila < n && col >= 0 && col < n)
            return datos[fila][col];
        throw out_of_range("Índice fuera de rango");
    }

    void imprimir() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << datos[i][j] << " ";
            cout << endl;
        }
    }

    Matriz transpuesta() const
    {
        Matriz T(n, 12345);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                T.datos[j][i] = datos[i][j];
        return T;
    }

    Matriz multiplicar(const Matriz &otra) const
    {
        if (n != otra.n)
            throw invalid_argument("Las matrices deben tener la misma dimensión");
        Matriz R(n, 54321);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                R.datos[i][j] = 0;
                for (int k = 0; k < n; k++)
                    R.datos[i][j] += datos[i][k] * otra.datos[k][j];
            }
        }
        return R;
    }
};

// Lectura segura de enteros
int leerEntero(const string &prompt)
{
    int valor;
    while (true)
    {
        cout << prompt;
        if (cin >> valor)
        {
            return valor;
        }
        else
        {
            cout << "Entrada inválida. Por favor ingrese un número entero.\n";
            cin.clear();                                         // limpiar estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar entrada inválida
        }
    }
}

int main()
{
    int opcion;
    do
    {
        cout << "\n===== MENU MATRICES =====\n";
        cout << "1. Crear matriz y mostrarla\n";
        cout << "2. Multiplicar dos matrices\n";
        cout << "3. Calcular transpuesta\n";
        cout << "4. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion)
        {
        case 1:
        {
            int n = leerEntero("Ingrese dimension n: ");
            if (n <= 0)
            {
                cout << "n debe ser positivo.\n";
                break;
            }
            Matriz A(n, 42);
            cout << "Matriz A:\n";
            A.imprimir();
            break;
        }
        case 2:
        {
            int n = leerEntero("Ingrese dimension n: ");
            if (n <= 0)
            {
                cout << "n debe ser positivo.\n";
                break;
            }
            Matriz A(n, 42);
            Matriz B(n, 99);
            cout << "Matriz A:\n";
            A.imprimir();
            cout << "\nMatriz B:\n";
            B.imprimir();
            Matriz C = A.multiplicar(B);
            cout << "\nResultado A * B:\n";
            C.imprimir();
            break;
        }
        case 3:
        {
            int n = leerEntero("Ingrese dimension n: ");
            if (n <= 0)
            {
                cout << "n debe ser positivo.\n";
                break;
            }
            Matriz A(n, 42);
            cout << "Matriz A:\n";
            A.imprimir();
            Matriz T = A.transpuesta();
            cout << "\nTranspuesta de A:\n";
            T.imprimir();
            break;
        }
        case 4:
            cout << "Programa finalizado.\n";
            break;
        default:
            cout << "Opción no válida.\n";
            break;
        }

        // Limpieza de buffer por si quedan caracteres
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (opcion != 4);

    return 0;
}
