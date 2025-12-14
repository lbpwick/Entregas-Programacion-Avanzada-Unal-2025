#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <string>

// -------- utilidades numéricas --------

double randWeight() {
    static std::mt19937 gen{std::random_device{}()};
    static std::uniform_real_distribution<double> dist(-1.0, 1.0);
    return dist(gen);
}

double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double sigmoid_deriv(double y) {
    return y * (1.0 - y);
}

// binario (solo 0 y 1) -> int
int binario_a_int(const std::string& s) {
    int valor = 0;
    for (char c : s) {
        valor <<= 1;
        if (c == '1') valor |= 1;
    }
    return valor;
}

bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

bool esCompuesto(int n) {
    return (n > 1 && !esPrimo(n));
}

// -------- codificaciones --------

// entrada: entero 0-9 -> one-hot 10
std::vector<double> encode_input(int d) {
    std::vector<double> v(10, 0.0);
    if (d >= 0 && d <= 9) v[d] = 1.0;
    return v;
}

// salida: clases 0..3
// Clase 0: pares
// Clase 1: impares
// Clase 2: primos
// Clase 3: compuestos
std::vector<double> encode_target(int d) {
    std::vector<double> t(4, 0.0);

    if (d % 2 == 0) t[0] = 1.0;     // par
    else t[1] = 1.0;                // impar

    if (esPrimo(d))       t[2] = 1.0;
    else if (esCompuesto(d)) t[3] = 1.0;

    return t;
}

int argmax(const std::vector<double>& v) {
    int idx = 0;
    double best = v[0];
    for (int i = 1; i < (int)v.size(); ++i)
        if (v[i] > best) { best = v[i]; idx = i; }
    return idx;
}

// -------- Red neuronal simple 10-8-4 --------

class NeuralNet {
public:
    int n_input, n_hidden, n_output;
    std::vector<std::vector<double>> w_ih;
    std::vector<double> b_h;
    std::vector<std::vector<double>> w_ho;
    std::vector<double> b_o;
    std::vector<double> a_in, a_h, a_out;

    NeuralNet(int in, int hid, int out)
        : n_input(in), n_hidden(hid), n_output(out),
          w_ih(hid, std::vector<double>(in)),
          b_h(hid),
          w_ho(out, std::vector<double>(hid)),
          b_o(out),
          a_in(in), a_h(hid), a_out(out)
    {
        for (int j = 0; j < n_hidden; ++j) {
            for (int i = 0; i < n_input; ++i)
                w_ih[j][i] = randWeight();
            b_h[j] = randWeight();
        }
        for (int k = 0; k < n_output; ++k) {
            for (int j = 0; j < n_hidden; ++j)
                w_ho[k][j] = randWeight();
            b_o[k] = randWeight();
        }
    }

    const std::vector<double>& forward(const std::vector<double>& input) {
        a_in = input;

        for (int j = 0; j < n_hidden; ++j) {
            double sum = b_h[j];
            for (int i = 0; i < n_input; ++i)
                sum += w_ih[j][i] * a_in[i];
            a_h[j] = sigmoid(sum);
        }

        for (int k = 0; k < n_output; ++k) {
            double sum = b_o[k];
            for (int j = 0; j < n_hidden; ++j)
                sum += w_ho[k][j] * a_h[j];
            a_out[k] = sigmoid(sum);
        }
        return a_out;
    }

    void train_example(const std::vector<double>& input,
                       const std::vector<double>& target,
                       double lr) {
        forward(input);

        std::vector<double> delta_o(n_output);
        for (int k = 0; k < n_output; ++k) {
            double error = target[k] - a_out[k];
            delta_o[k] = error * sigmoid_deriv(a_out[k]);
        }

        std::vector<double> delta_h(n_hidden);
        for (int j = 0; j < n_hidden; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n_output; ++k)
                sum += w_ho[k][j] * delta_o[k];
            delta_h[j] = sum * sigmoid_deriv(a_h[j]);
        }

        for (int k = 0; k < n_output; ++k) {
            for (int j = 0; j < n_hidden; ++j)
                w_ho[k][j] += lr * delta_o[k] * a_h[j];
            b_o[k] += lr * delta_o[k];
        }

        for (int j = 0; j < n_hidden; ++j) {
            for (int i = 0; i < n_input; ++i)
                w_ih[j][i] += lr * delta_h[j] * a_in[i];
            b_h[j] += lr * delta_h[j];
        }
    }
};

// -------- Lectura de binarios --------

std::vector<int> leer_digitos_binarios(const std::string& archivo) {
    std::vector<int> datos;
    std::ifstream in(archivo);
    if (!in) {
        std::cerr << "No se pudo abrir " << archivo << "\n";
        return datos;
    }
    std::string linea;
    while (std::getline(in, linea)) {
        std::string limpio;
        for (char c : linea)
            if (c == '0' || c == '1') limpio.push_back(c);
        if (limpio.empty()) continue;

        int valor = binario_a_int(limpio);
        if (valor >= 0 && valor <= 9)  // solo dígitos 0-9
            datos.push_back(valor);
    }
    return datos;
}

// -------- main --------

int main() {
    // 1) leer archivo binario -> enteros 0-9
    std::vector<int> digitos = leer_digitos_binarios("digitos.txt");
    if (digitos.empty()) {
        std::cout << "No hay datos válidos en digitos.txt\n";
        return 0;
    }

    // 2) construir dataset para RNA
    std::vector<std::vector<double>> X, Y;
    for (int d : digitos) {
        X.push_back(encode_input(d));
        Y.push_back(encode_target(d));
    }

    // 3) crear red 10-8-4
    NeuralNet net(10, 8, 4);
    int epochs = 3000;
    double lr = 0.5;

    for (int e = 0; e < epochs; ++e) {
        double mse = 0.0;
        for (size_t i = 0; i < X.size(); ++i) {
            net.train_example(X[i], Y[i], lr);
            const auto& out = net.forward(X[i]);
            for (int k = 0; k < net.n_output; ++k) {
                double err = Y[i][k] - out[k];
                mse += err * err;
            }
        }
        mse /= (X.size() * net.n_output);
        if (e % 500 == 0)
            std::cout << "Epoch " << e << "  MSE=" << mse << "\n";
    }

    // 4) clasificar e imprimir: número y categoría
    std::cout << "\nResultados sobre los datos del archivo:\n";
    for (int d : digitos) {
        auto inp = encode_input(d);
        const auto& out = net.forward(inp);
        int c = argmax(out);

        std::cout << "Numero: " << d << " -> clase " << c << " (";
        if (c == 0) std::cout << "par";
        else if (c == 1) std::cout << "impar";
        else if (c == 2) std::cout << "primo";
        else if (c == 3) std::cout << "compuesto";
        std::cout << ")\n";
    }

    return 0;
}
