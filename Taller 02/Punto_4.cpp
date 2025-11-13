#include <iostream>
#include <cmath>
#include <vector>
#include <typeinfo>
using namespace std;


class complex {
public:
    double re, im;

    complex(double r = 0, double i = 0) : re(r), im(i) {}
    complex(class polar p);

    complex operator+(const complex& c) const { return complex(re + c.re, im + c.im); }
    complex operator-(const complex& c) const { return complex(re - c.re, im - c.im); }
    complex operator*(const complex& c) const {
        return complex(re * c.re - im * c.im, re * c.im + im * c.re);
    }
    complex operator/(const complex& c) const {
        double denom = c.re * c.re + c.im * c.im;
        return complex((re * c.re + im * c.im) / denom,
                       (im * c.re - re * c.im) / denom);
    }

    complex conj() const { return complex(re, -im); }

    class polar toPolar() const;

    void print() const {
        cout << "(" << re << (im >= 0 ? " + " : " - ") << fabs(im) << "i)";
    }
};


class polar {
public:
    double r, theta;

    polar(double mod = 0, double ang = 0) : r(mod), theta(ang) {}
    polar(complex c) {
        r = sqrt(c.re * c.re + c.im * c.im);
        theta = atan2(c.im, c.re);
    }

    polar operator+(const polar& p) const {
        complex a = *this, b = p;
        return polar(a + b);
    }
    polar operator-(const polar& p) const {
        complex a = *this, b = p;
        return polar(a - b);
    }
    polar operator*(const polar& p) const {
        return polar(r * p.r, theta + p.theta);
    }
    polar operator/(const polar& p) const {
        return polar(r / p.r, theta - p.theta);
    }

    polar conj() const { return polar(r, -theta); }

    complex toComplex() const {
        return complex(r * cos(theta), r * sin(theta));
    }

    void print() const {
        cout << r << " * e^(i" << theta << ")";
    }
};


complex::complex(polar p) {
    re = p.r * cos(p.theta);
    im = p.r * sin(p.theta);
}

polar complex::toPolar() const {
    return polar(sqrt(re * re + im * im), atan2(im, re));
}


template <typename... Args>
complex acumula(Args... args) {
    vector<complex> lista = { args... };
    complex suma(0, 0);
    for (auto& c : lista)
        suma = suma + c;
    return suma;
}

template <typename... Args>
complex acumulaPolar(Args... args) {
    vector<complex> lista = { args.toComplex()... };
    complex suma(0, 0);
    for (auto& c : lista)
        suma = suma + c;
    return suma;
}


int main() {
    int opcion;
    do {
        cout << "\n========== MENU DE OPERACIONES COMPLEJAS ==========\n";
        cout << "1. Crear y mostrar un numero complejo (a + ib)\n";
        cout << "2. Crear y mostrar un numero polar (a * e^(b))\n";
        cout << "3. Convertir complejo a polar\n";
        cout << "4. Operaciones (+, -, *, /, conj)\n";
        cout << "5. Acumular varios numeros\n";
        cout << "0. Salir\n";
        cout << "--------------------------------------------------\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            double a, b;
            cout << "Ingrese parte real: ";
            cin >> a;
            cout << "Ingrese parte imaginaria: ";
            cin >> b;
            complex c(a, b);
            cout << "Numero complejo: ";
            c.print();
            cout << endl;
            break;
        }
        case 2: {
            double r, t;
            cout << "Ingrese modulo r: ";
            cin >> r;
            cout << "Ingrese argumento θ (radianes): ";
            cin >> t;
            polar p(r, t);
            cout << "Numero polar: ";
            p.print();
            cout << endl;
            break;
        }
        case 3: {
            int tipo;
            cout << "1. De complejo a polar\n2. De polar a complejo\nOpcion: ";
            cin >> tipo;
            if (tipo == 1) {
                double a, b;
                cout << "Ingrese parte real: ";
                cin >> a;
                cout << "Ingrese parte imaginaria: ";
                cin >> b;
                complex c(a, b);
                polar p = c.toPolar();
                cout << "Forma polar: ";
                p.print();
                cout << endl;
            } else {
                double r, t;
                cout << "Ingrese modulo r: ";
                cin >> r;
                cout << "Ingrese argumento θ: ";
                cin >> t;
                polar p(r, t);
                complex c = p.toComplex();
                cout << "Forma binomial: ";
                c.print();
                cout << endl;
            }
            break;
        }
        case 4: {
            double a1, b1, a2, b2;
            cout << "Ingrese parte real e imaginaria del primer numero: ";
            cin >> a1 >> b1;
            cout << "Ingrese parte real e imaginaria del segundo numero: ";
            cin >> a2 >> b2;
            complex c1(a1, b1), c2(a2, b2);

            cout << "\nResultados:\n";
            cout << "Suma: "; (c1 + c2).print(); cout << endl;
            cout << "Resta: "; (c1 - c2).print(); cout << endl;
            cout << "Producto: "; (c1 * c2).print(); cout << endl;
            cout << "Division: "; (c1 / c2).print(); cout << endl;
            cout << "Conjugado del primero: "; c1.conj().print(); cout << endl;
            break;
        }
        case 5: {
            int n;
            cout << "Cuantos numeros desea sumar?: ";
            cin >> n;
            vector<complex> lista;
            for (int i = 0; i < n; i++) {
                double a, b;
                cout << "Numero " << i + 1 << " - parte real: ";
                cin >> a;
                cout << "parte imaginaria: ";
                cin >> b;
                lista.push_back(complex(a, b));
            }
            complex suma(0, 0);
            for (auto& c : lista) suma = suma + c;
            cout << "Suma total: ";
            suma.print();
            cout << endl;
            break;
        }
        case 0:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
