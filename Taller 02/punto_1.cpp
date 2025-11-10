#include <iostream>
#include <cmath>

class Vector3D {
    float x{}, y{}, z{};
public:
    // Constructor que inicializa los componentes del vector
    Vector3D(float x_val = 0, float y_val = 0, float z_val = 0)
        : x(x_val), y(y_val), z(z_val) {}

    // Operadores sobrecargados (suma, resta, escalado)
    Vector3D operator+(const Vector3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3D operator-(const Vector3D& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    float operator*(const Vector3D& other) const {
        return (x * other.x + y * other.y + z * other.z);
    }

    // Magnitud del vector
    float magnitud() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalización (devuelve el vector normalizado)
    Vector3D normalizado() const {
        float mag = magnitud();
        return (mag > 0) ? Vector3D(x / mag, y / mag, z / mag) : *this;
    }

    // Mostrar vector
    void mostrar() const {
        std::cout << "Vector(" << x << ", " << y << ", " << z << ")";
    }
};

// Función auxiliar para leer un vector del usuario
Vector3D leerVector(const std::string& nombre) {
    float x, y, z;
    std::cout << "Ingrese el valor de x para " << nombre << ": ";
    std::cin >> x;
    std::cout << "Ingrese el valor de y para " << nombre << ": ";
    std::cin >> y;
    std::cout << "Ingrese el valor de z para " << nombre << ": ";
    std::cin >> z;
    return {x, y, z};
}

int main() {
    Vector3D vec1 = leerVector("el primer vector");
    Vector3D vec2 = leerVector("el segundo vector");

    Vector3D suma = vec1 + vec2;
    Vector3D resta = vec1 - vec2;
    float producto_escalar = vec1 * vec2;

    std::cout << "\nResultado de la suma: ";
    suma.mostrar();
    std::cout << "\nResultado de la resta: ";
    resta.mostrar();
    std::cout << "\nResultado del producto escalar: " << producto_escalar;

    std::cout << "\n\nMagnitud del primer vector: " << vec1.magnitud();
    std::cout << "\nVector normalizado: ";
    vec1.normalizado().mostrar();

    std::cout << "\n\nMagnitud del segundo vector: " << vec2.magnitud();
    std::cout << "\nVector normalizado: ";
    vec2.normalizado().mostrar();

    std::cout << std::endl;
    return 0;
}
