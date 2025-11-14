#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

// =======================================================
//                Clase CTermino
// Representa un término c*x^e de un polinomio.
// =======================================================
class CTermino {
private:
    double coef;   // Coeficiente del término
    int exp;       // Exponente del término

public:
    // Constructor con valores por defecto
    CTermino(double c = 0, int e = 0) : coef(c), exp(e) {}

    // Métodos de acceso
    double getCoef() const { return coef; }
    int getExp() const { return exp; }

    // Convierte el término a un string en formato algebraico
    string toString() const {
        if (coef == 0) return ""; // No mostrar términos nulos

        stringstream ss;
        
        // Signo del término (+ o -)
        ss << (coef > 0 ? "+" : "-");

        // Mostrar coeficiente solo si no es 1 o si el exponente es 0
        if (fabs(coef) != 1 || exp == 0)
            ss << fabs(coef);

        // Mostrar variable y exponente
        if (exp > 0) {
            ss << "x";
            if (exp > 1)
                ss << "^" << exp;
        }

        return ss.str();
    }
};

// =======================================================
//                Clase CPolinomio
// Gestiona un polinomio compuesto por varios términos.
// =======================================================
class CPolinomio {
private:
    vector<CTermino> polinomio;  // Lista de términos

public:
    CPolinomio() {}

    int getNumTerminos() const { return polinomio.size(); }

    // Inserta un término ordenando y combinando exponentes repetidos
    void insertar(const CTermino &t) {
        double c = t.getCoef();
        int e = t.getExp();

        // Ignorar términos con coeficiente 0
        if (c == 0) return;

        // Buscar si el exponente ya existe
        for (auto &term : polinomio) {
            if (term.getExp() == e) {
                double nuevo = term.getCoef() + c;

                // Si el coeficiente resultante es 0, eliminar término
                if (nuevo == 0) {
                    polinomio.erase(
                        remove_if(polinomio.begin(), polinomio.end(),
                        [&](const CTermino &tt){ return tt.getExp() == e; }),
                        polinomio.end()
                    );
                } else {
                    // Actualizar coeficiente existente
                    term = CTermino(nuevo, e);
                }
                return;
            }
        }

        // Si no existe, añadir término y ordenar
        polinomio.push_back(t);

        sort(polinomio.begin(), polinomio.end(),
            [](const CTermino &a, const CTermino &b) {
                return a.getExp() < b.getExp();  // Orden por exponente
            });
    }

    // Suma dos polinomios
    CPolinomio sumar(const CPolinomio &p) const {
        CPolinomio r;

        // Insertar todos los términos de ambos polinomios
        for (auto &t : polinomio) r.insertar(t);
        for (auto &t : p.polinomio) r.insertar(t);

        return r;
    }

    // Multiplica dos polinomios
    CPolinomio multiplicar(const CPolinomio &p) const {
        CPolinomio r;

        // Producto cruzado de todos los términos
        for (auto &a : polinomio) {
            for (auto &b : p.polinomio) {
                r.insertar(CTermino(
                    a.getCoef() * b.getCoef(),   // Multiplica coeficientes
                    a.getExp() + b.getExp()      // Suma exponentes
                ));
            }
        }
        return r;
    }

    // Convierte el polinomio completo a string
    string toString() const {
        if (polinomio.empty()) return "0";

        string s = "";
        for (auto &t : polinomio) s += t.toString();

        // Quitar signo inicial si es '+'
        if (!s.empty() && s[0] == '+') s.erase(0, 1);

        return s;
    }
};

// =======================================================
//         Función que lee un polinomio desde teclado
// =======================================================
CPolinomio leerPolinomioUsuario() {
    CPolinomio P;
    int grado;

    cout << "\nIngrese el grado del polinomio: ";
    cin >> grado;

    cout << "Ingrese los coeficientes desde x^" << grado << " hasta x^0\n";

    // Leer coeficientes en orden descendente
    for (int e = grado; e >= 0; e--) {
        double c;
        cout << "Coeficiente para x^" << e << ": ";
        cin >> c;

        P.insertar(CTermino(c, e));
    }

    return P;
}

// =======================================================
//                   Ejemplo de uso en main()
// =======================================================
int main() {
    cout << "=== Ingreso de P(x) ===\n";
    CPolinomio P = leerPolinomioUsuario();

    cout << "\n=== Ingreso de Q(x) ===\n";
    CPolinomio Q = leerPolinomioUsuario();

    // Calcular suma y producto
    CPolinomio S = P.sumar(Q);
    CPolinomio M = P.multiplicar(Q);

    // Mostrar resultados
    cout << "\nP(x) = " << P.toString() << endl;
    cout << "Q(x) = " << Q.toString() << endl;

    cout << "\nP(x) + Q(x) = " << S.toString() << endl;
    cout << "P(x) * Q(x) = " << M.toString() << endl;

    return 0;
}
