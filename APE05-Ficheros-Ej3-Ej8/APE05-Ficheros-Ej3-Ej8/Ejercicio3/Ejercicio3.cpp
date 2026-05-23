// ============================================================
// APE 05 - Ejercicio 3: Sistema de Inventario Basico
// Asignatura: Algoritmos y Logica de Programacion
// Docente: Jose Ruben Caiza
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// Clase que representa un producto del inventario
class Producto {
public:
    string codigo;
    string nombre;
    int    cantidad;
    double precio;

    // Constructor
    Producto(string cod, string nom, int cant, double prec) {
        codigo   = cod;
        nombre   = nom;
        cantidad = cant;
        precio   = prec;
    }

    // Metodo para mostrar los datos del producto
    void mostrar() {
        cout << "  Codigo  : " << codigo  << endl;
        cout << "  Nombre  : " << nombre  << endl;
        cout << "  Cantidad: " << cantidad << endl;
        cout << "  Precio  : $" << fixed << setprecision(2) << precio  << endl;
        cout << "  Subtotal: $" << fixed << setprecision(2) << (precio * cantidad) << endl;
    }

    // Metodo que calcula el subtotal del producto (precio * cantidad)
    double subtotal() {
        return precio * cantidad;
    }

    // Convertir el producto a linea de archivo
    string toLinea() {
        stringstream ss;
        ss << fixed << setprecision(2) << precio;
        return codigo + "|" + nombre + "|" + to_string(cantidad) + "|" + ss.str();
    }
};

// Metodo auxiliar: divide un string por un delimitador
vector<string> dividir(string linea, char delimitador) {
    vector<string> partes;
    stringstream ss(linea);
    string token;
    while (getline(ss, token, delimitador)) {
        partes.push_back(token);
    }
    return partes;
}

// Metodo para guardar un producto en el archivo (modo agregar)
void guardarProducto(string nombreArchivo, Producto& p) {
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << p.toLinea() << "\n";
        archivo.close();
    } else {
        cout << "Error: no se pudo abrir el archivo." << endl;
    }
}

// Metodo para registrar un nuevo producto
void registrarProducto(string nombreArchivo, vector<Producto>& inventario) {
    string codigo, nombre;
    int    cantidad;
    double precio;

    cout << "\n--- Registrar Nuevo Producto ---" << endl;
    cout << "Codigo  : "; cin >> codigo; cin.ignore();
    cout << "Nombre  : "; getline(cin, nombre);
    cout << "Cantidad: "; cin >> cantidad;
    cout << "Precio  : "; cin >> precio;

    // Validar que cantidad y precio no sean negativos
    if (cantidad < 0 || precio < 0) {
        cout << "Error: cantidad y precio deben ser valores positivos." << endl;
        return;
    }

    Producto p(codigo, nombre, cantidad, precio);
    inventario.push_back(p);
    guardarProducto(nombreArchivo, p);

    cout << "Producto registrado correctamente en " << nombreArchivo << "." << endl;
}

// Metodo para leer todos los productos desde el archivo
vector<Producto> leerInventario(string nombreArchivo) {
    vector<Producto> inventario;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        return inventario;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            vector<string> datos = dividir(linea, '|');
            if (datos.size() == 4) {
                Producto p(datos[0], datos[1], stoi(datos[2]), stod(datos[3]));
                inventario.push_back(p);
            }
        }
    }
    archivo.close();
    return inventario;
}

// Metodo para mostrar el inventario completo
void mostrarInventario(vector<Producto>& inventario) {
    if (inventario.empty()) {
        cout << "El inventario esta vacio." << endl;
        return;
    }

    cout << "\n=========================================" << endl;
    cout << "       INVENTARIO COMPLETO" << endl;
    cout << "  Total de productos: " << inventario.size() << endl;
    cout << "=========================================" << endl;

    for (int i = 0; i < (int)inventario.size(); i++) {
        cout << "Producto #" << (i + 1) << endl;
        inventario[i].mostrar();
        cout << "-----------------------------------------" << endl;
    }
}

// Metodo para calcular el valor total del inventario
double calcularValorTotal(vector<Producto>& inventario) {
    double total = 0.0;
    for (int i = 0; i < (int)inventario.size(); i++) {
        total += inventario[i].subtotal();
    }
    return total;
}

int main() {
    string nombreArchivo = "inventario.txt";

    // Cargar inventario existente desde el archivo
    vector<Producto> inventario = leerInventario(nombreArchivo);

    int opcion;
    do {
        cout << "\n===== SISTEMA DE INVENTARIO =====" << endl;
        cout << "1. Registrar producto"               << endl;
        cout << "2. Mostrar inventario"               << endl;
        cout << "3. Calcular valor total"             << endl;
        cout << "0. Salir"                            << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarProducto(nombreArchivo, inventario);
                break;
            case 2:
                mostrarInventario(inventario);
                break;
            case 3: {
                double total = calcularValorTotal(inventario);
                cout << "\nValor total del inventario: $"
                     << fixed << setprecision(2) << total << endl;
                break;
            }
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}
