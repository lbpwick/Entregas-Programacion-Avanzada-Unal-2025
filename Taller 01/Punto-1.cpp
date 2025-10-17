#include <iostream>
using namespace std;

int main()
{
    int a, b;

    cout << "Ingrese el primer numero entero: ";
    cin >> a;

    cout << "Ingrese el segundo numero entero: ";
    cin >> b;

    // Operaciones básicas
    cout << "Suma: " << (a + b) << endl;
    cout << "Resta: " << (a - b) << endl;
    cout << "Multiplicacion: " << (a * b) << endl;

    // Manejo de la división por cero
    if (b != 0)
    {
        cout << "Division: " << (static_cast<double>(a) / b) << endl;
    }
    else
    {
        cout << "Division: Error, no se puede dividir entre cero." << endl;
    }

    return 0;
}
