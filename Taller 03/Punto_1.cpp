#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
using namespace std;

struct Estudiante {
    string nombreCompleto;
    int anioNacimiento;
    long id;
    float promedio;
    string email;
};


struct Nodo {
    Estudiante dato;
    Nodo* siguiente;

    Nodo(const Estudiante& est) : dato(est), siguiente(nullptr) {}
};


class ListadoEstudiantil {
private:
    Nodo* cabeza;

public:
    
    ListadoEstudiantil() : cabeza(nullptr) {}

    
    ~ListadoEstudiantil() {
        Nodo* actual = cabeza;
        while (actual) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    
    void insertar(const Estudiante &est) {
        Nodo* nuevo = new Nodo(est);

        if (!cabeza) {
            cabeza = nuevo;
            return;
        }

        Nodo* actual = cabeza;
        while (actual->siguiente)
            actual = actual->siguiente;

        actual->siguiente = nuevo;
    }

    
    bool eliminar(long id) {
        if (!cabeza) return false;

        if (cabeza->dato.id == id) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return true;
        }

        Nodo* actual = cabeza;
        while (actual->siguiente && actual->siguiente->dato.id != id)
            actual = actual->siguiente;

        if (!actual->siguiente) return false;

        Nodo* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        return true;
    }

    
    int buscar(long id) const {
        Nodo* actual = cabeza;
        int pos = 0;

        while (actual) {
            if (actual->dato.id == id)
                return pos;
            actual = actual->siguiente;
            pos++;
        }
        return -1;
    }

    
    Estudiante& operator[](int index) {
        Nodo* actual = cabeza;
        int pos = 0;

        while (actual) {
            if (pos == index)
                return actual->dato;
            actual = actual->siguiente;
            pos++;
        }

        throw out_of_range("Indice fuera de rango");
    }

    
    void invertir() {
        Nodo* anterior = nullptr;
        Nodo* actual = cabeza;
        Nodo* siguiente = nullptr;

        while (actual) {
            siguiente = actual->siguiente;
            actual->siguiente = anterior;
            anterior = actual;
            actual = siguiente;
        }

        cabeza = anterior;
    }

    
    void imprimirEnArchivo(const string& archivoNombre) const {
        ofstream archivo(archivoNombre);

        if (!archivo) {
            cerr << "Error al abrir el archivo." << endl;
            return;
        }

        Nodo* actual = cabeza;

        while (actual) {
            archivo << "Nombre: " << actual->dato.nombreCompleto << endl;
            archivo << "Ano de nacimiento: " << actual->dato.anioNacimiento << endl;
            archivo << "ID: " << actual->dato.id << endl;
            archivo << "Promedio: " << actual->dato.promedio << endl;
            archivo << "Email: " << actual->dato.email << endl;
            archivo << "-----------------------------" << endl;

            actual = actual->siguiente;
        }

        archivo.close();
    }

    
    void mostrar() const {
        if (!cabeza) {
            cout << "La lista esta vacia.\n";
            return;
        }

        Nodo* actual = cabeza;

        while (actual) {
            cout << "Nombre: " << actual->dato.nombreCompleto << endl;
            cout << "Ano de nacimiento: " << actual->dato.anioNacimiento << endl;
            cout << "ID: " << actual->dato.id << endl;
            cout << "Promedio: " << actual->dato.promedio << endl;
            cout << "Email: " << actual->dato.email << endl;
            cout << "-----------------------------\n";

            actual = actual->siguiente;
        }
    }
};


Estudiante crearEstudiante() {
    Estudiante e;

    cin.ignore();
    cout << "\nNombre completo: ";
    getline(cin, e.nombreCompleto);

    cout << "Ano de nacimiento: ";
    cin >> e.anioNacimiento;

    cout << "Numero de identificacion: ";
    cin >> e.id;

    cout << "Promedio academico: ";
    cin >> e.promedio;

    cout << "Email: ";
    cin >> e.email;

    return e;
}


int main() {
    setlocale(LC_CTYPE, "Spanish");
    ListadoEstudiantil lista;
    int opcion;

    do {
        cout << "\n=========== MENU LISTADO ESTUDIANTIL ===========\n";
        cout << "1. Insertar estudiante\n";
        cout << "2. Eliminar estudiante por ID\n";
        cout << "3. Buscar estudiante por ID\n";
        cout << "4. Mostrar lista en pantalla\n";
        cout << "5. Guardar lista en archivo .txt\n";
        cout << "6. Invertir lista\n";
        cout << "7. Acceder por indice (operador [])\n";
        cout << "8. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Estudiante e = crearEstudiante();
            lista.insertar(e);
            cout << "Estudiante insertado correctamente.\n";
            break;
        }

        case 2: {
            long id;
            cout << "Ingrese ID a eliminar: ";
            cin >> id;

            if (lista.eliminar(id))
                cout << "Estudiante eliminado.\n";
            else
                cout << "ID no encontrado.\n";
            break;
        }

        case 3: {
            long id;
            cout << "Ingrese ID a buscar: ";
            cin >> id;

            int pos = lista.buscar(id);
            if (pos >= 0)
                cout << "Encontrado en la posicion: " << pos << endl;
            else
                cout << "No encontrado.\n";
            break;
        }

        case 4:
            lista.mostrar();
            break;

        case 5: {
            string nombreArchivo;
            cout << "Nombre del archivo (ej: salida.txt): ";
            cin >> nombreArchivo;

            lista.imprimirEnArchivo(nombreArchivo);
            cout << "Archivo guardado.\n";
            break;
        }

        case 6:
            lista.invertir();
            cout << "Lista invertida.\n";
            break;

        case 7: {
            int index;
            cout << "Indice a acceder: ";
            cin >> index;

            try {
                Estudiante& e = lista[index];
                cout << "Nombre: " << e.nombreCompleto << endl;
                cout << "ID: " << e.id << endl;
            } catch (exception& ex) {
                cout << "Error: " << ex.what() << endl;
            }
            break;
        }

        case 8:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 8);
    
    return 0;
}
