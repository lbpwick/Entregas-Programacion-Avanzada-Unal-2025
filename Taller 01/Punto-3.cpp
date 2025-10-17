#include <iostream>
#include <string>
using namespace std;

// Función que cuenta vocales en una cadena
int contarVocales(const string &texto)
{
    int contador = 0;
    for (char c : texto)
    {
        char letra = tolower(c); // Convertir a minúscula para simplificar
        if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u')
        {
            contador++;
        }
    }
    return contador;
}

int main()
{
    string cadena;

    cout << "Ingrese una cadena de caracteres: ";
    getline(cin, cadena); // Permite leer espacios

    int numVocales = contarVocales(cadena);

    cout << "La cadena contiene " << numVocales << " vocal(es)." << endl;

    return 0;
}
