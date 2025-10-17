#include <iostream>
#include <vector>
using namespace std;

// Estructura para devolver resultados
struct Resultados
{
    double maximo;
    int posMax;
    double minimo;
    int posMin;
};

// Función que encuentra máximo y mínimo con posiciones
Resultados encontrarMaxMin(const vector<double> &arr)
{
    Resultados res;
    if (arr.empty())
    {
        // Caso especial: arreglo vacío
        res.maximo = res.minimo = 0;
        res.posMax = res.posMin = -1;
        return res;
    }

    res.maximo = res.minimo = arr[0];
    res.posMax = res.posMin = 0;

    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] > res.maximo)
        {
            res.maximo = arr[i];
            res.posMax = i;
        }
        if (arr[i] < res.minimo)
        {
            res.minimo = arr[i];
            res.posMin = i;
        }
    }
    return res;
}

int main()
{
    int n;
    cout << "Ingrese el tamano del arreglo: ";
    cin >> n;

    vector<double> numeros(n);
    cout << "Ingrese " << n << " numeros decimales:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> numeros[i];
    }

    Resultados r = encontrarMaxMin(numeros);

    if (r.posMax == -1)
    {
        cout << "El arreglo esta vacio." << endl;
    }
    else
    {
        cout << "Valor maximo: " << r.maximo << " en la posicion " << r.posMax << endl;
        cout << "Valor minimo: " << r.minimo << " en la posicion " << r.posMin << endl;
    }

    return 0;
}
