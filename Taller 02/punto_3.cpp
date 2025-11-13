#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Polinomio {
private:
    int grado;
    double* coef; 

public:
    Polinomio(int grado = 0, const double* coeficientes = nullptr) {
        this->grado = grado;
        coef = new double[grado + 1];
        if (coeficientes) {
            for (int i = 0; i <= grado; i++)
                coef[i] = coeficientes[i];
        } else {
            for (int i = 0; i <= grado; i++)
                coef[i] = 0;
        }
    }

    Polinomio(const Polinomio& p) {
        grado = p.grado;
        coef = new double[grado + 1];
        for (int i = 0; i <= grado; i++)
            coef[i] = p.coef[i];
    }

    ~Polinomio() {
        delete[] coef;
    }

    Polinomio& operator=(const Polinomio& p) {
        if (this == &p) return *this;
        delete[] coef;
        grado = p.grado;
        coef = new double[grado + 1];
        for (int i = 0; i <= grado; i++)
            coef[i] = p.coef[i];
        return *this;
    }

    void leer() {
        cout << "Ingrese el grado del polinomio: ";
        cin >> grado;
        delete[] coef;
        coef = new double[grado + 1];
        cout << "Ingrese los coeficientes desde el termino constante hasta x^" << grado << ":\n";
        for (int i = 0; i <= grado; i++) {
            cout << "Coeficiente de x^" << i << ": ";
            cin >> coef[i];
        }
    }

    double evaluar(double x) const {
        double resultado = 0.0;
        for (int i = 0; i <= grado; i++) {
            resultado += coef[i] * pow(x, i);
        }
        return resultado;
    }

    Polinomio operator+(const Polinomio& otro) const {
        int nuevoGrado = max(grado, otro.grado);
        double* nuevosCoef = new double[nuevoGrado + 1]{0};

        for (int i = 0; i <= grado; i++)
            nuevosCoef[i] += coef[i];
        for (int i = 0; i <= otro.grado; i++)
            nuevosCoef[i] += otro.coef[i];

        Polinomio resultado(nuevoGrado, nuevosCoef);
        delete[] nuevosCoef;
        return resultado;
    }

    Polinomio operator*(const Polinomio& otro) const {
        int nuevoGrado = grado + otro.grado;
        double* nuevosCoef = new double[nuevoGrado + 1]{0};

        for (int i = 0; i <= grado; i++) {
            for (int j = 0; j <= otro.grado; j++) {
                nuevosCoef[i + j] += coef[i] * otro.coef[j];
            }
        }

        Polinomio resultado(nuevoGrado, nuevosCoef);
        delete[] nuevosCoef;
        return resultado;
    }

    Polinomio derivar() const {
        if (grado == 0) {
            double cero = 0;
            return Polinomio(0, &cero);
        }

        double* nuevosCoef = new double[grado];
        for (int i = 1; i <= grado; i++) {
            nuevosCoef[i - 1] = coef[i] * i;
        }

        Polinomio derivada(grado - 1, nuevosCoef);
        delete[] nuevosCoef;
        return derivada;
    }

    void imprimir() const {
        bool primero = true;
        for (int i = grado; i >= 0; i--) {
            if (fabs(coef[i]) < 1e-9) continue; 

            if (!primero)
                cout << (coef[i] >= 0 ? " + " : " - ");
            else if (coef[i] < 0)
                cout << "-";

            cout << fixed << setprecision(2) << fabs(coef[i]);

            if (i > 0)
                cout << "x";
            if (i > 1)
                cout << "^" << i;

            primero = false;
        }
        if (primero)
            cout << "0";
        cout << endl;
    }
};

int main() {
    Polinomio p1, p2, resultado;
    int opcion;
    double x;

    do {
        cout << "\n=== MENU DE POLINOMIOS ===\n";
        cout << "1. Ingresar Polinomio 1\n";
        cout << "2. Ingresar Polinomio 2\n";
        cout << "3. Mostrar Polinomios\n";
        cout << "4. Sumar P1 + P2\n";
        cout << "5. Multiplicar P1 * P2\n";
        cout << "6. Evaluar Polinomio 1 en un valor de x\n";
        cout << "7. Derivar Polinomio 1\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n--- Ingresar Polinomio 1 ---\n";
                p1.leer();
                break;
            case 2:
                cout << "\n--- Ingresar Polinomio 2 ---\n";
                p2.leer();
                break;
            case 3:
                cout << "\nP1(x) = "; p1.imprimir();
                cout << "P2(x) = "; p2.imprimir();
                break;
            case 4:
                resultado = p1 + p2;
                cout << "\nP1(x) + P2(x) = ";
                resultado.imprimir();
                break;
            case 5:
                resultado = p1 * p2;
                cout << "\nP1(x) * P2(x) = ";
                resultado.imprimir();
                break;
            case 6:
                cout << "Ingrese el valor de x: ";
                cin >> x;
                cout << "P1(" << x << ") = " << p1.evaluar(x) << endl;
                break;
            case 7:
                resultado = p1.derivar();
                cout << "\nP1'(x) = ";
                resultado.imprimir();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);

    return 0;
}
