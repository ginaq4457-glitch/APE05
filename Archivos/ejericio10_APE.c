// ============================================================
// APE 05 - Ejercicio 10: Mini Proyecto Integrador
// Sistema de Gestion de Productos (CRUD)
// Asignatura: Algoritmos y Logica de Programacion
// Docente: Jose Ruben Caiza
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Clase Producto - encapsula los atributos y comportamiento de cada producto
class Producto {
public:
    string codigo, nombre, categoria;
    double precio;
    int    stock;

    Producto(string c, string n, string cat, double p, int s)
        : codigo(c), nombre(n), categoria(cat), precio(p), stock(s) {}

    void mostrar() const {
        cout << "  Codigo    : " << codigo    << endl;
        cout << "  Nombre    : " << nombre    << endl;
        cout << "  Categoria : " << categoria << endl;
        cout << "  Precio    : $" << fixed << setprecision(2) << precio << endl;
        cout << "  Stock     : " << stock << " unidades" << endl;
    }

    string toLinea() const {
        stringstream ss;
        ss << fixed << setprecision(2) << precio;
        return codigo + "|" + nombre + "|" + categoria + "|" + ss.str() + "|" + to_string(stock);
    }
};

// Metodo auxiliar: divide una linea por delimitador
vector<string> dividir(const string& linea, char delim) {
    vector<string> partes; stringstream ss(linea); string tok;
    while (getline(ss, tok, delim)) partes.push_back(tok);
    return partes;
}

// Metodo: cargar productos desde el archivo
vector<Producto> cargarProductos(const string& archivo) {
    vector<Producto> lista; ifstream f(archivo);
    if (!f.is_open()) return lista;
    string linea;
    while (getline(f, linea)) {
        if (!linea.empty()) {
            auto d = dividir(linea, '|');
            if (d.size() == 5)
                lista.push_back(Producto(d[0], d[1], d[2], stod(d[3]), stoi(d[4])));
        }
    }
    f.close(); return lista;
}

// Metodo: guardar todos los productos en el archivo
void guardarProductos(const string& archivo, const vector<Producto>& lista) {
    ofstream f(archivo);
    for (const auto& p : lista) f << p.toLinea() << "\n";
}

// CRUD 1 - CREATE: agregar nuevo producto
void agregarProducto(const string& archivo, vector<Producto>& lista) {
    string cod, nom, cat; double precio; int stock;
    cout << "\n--- Agregar Producto ---\n";
    cout << "Codigo    : "; cin >> cod; cin.ignore();
    // Validar codigo unico
    for (const auto& p : lista)
        if (p.codigo == cod) { cout << "Error: el codigo ya existe.\n"; return; }
    cout << "Nombre    : "; getline(cin, nom);
    cout << "Categoria : "; getline(cin, cat);
    cout << "Precio    : "; cin >> precio;
    cout << "Stock     : "; cin >> stock;
    if (precio < 0 || stock < 0) { cout << "Error: precio y stock deben ser positivos.\n"; return; }
    lista.push_back(Producto(cod, nom, cat, precio, stock));
    guardarProductos(archivo, lista);
    cout << "Producto agregado correctamente.\n";
}

// CRUD 2 - READ: buscar producto
void buscarProducto(const vector<Producto>& lista) {
    cin.ignore();
    cout << "\nCriterio de busqueda: "; string b; getline(cin, b);
    string bl = b; transform(bl.begin(), bl.end(), bl.begin(), ::tolower);
    bool ok = false;
    for (const auto& p : lista) {
        string cl = p.codigo, nl = p.nombre;
        transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
        transform(nl.begin(), nl.end(), nl.begin(), ::tolower);
        if (cl.find(bl) != string::npos || nl.find(bl) != string::npos) {
            p.mostrar(); cout << "------------------------------\n"; ok = true;
        }
    }
    if (!ok) cout << "Sin resultados para: " << b << "\n";
}

// CRUD 3 - UPDATE: modificar producto
void modificarProducto(const string& archivo, vector<Producto>& lista) {
    cin.ignore();
    cout << "\n--- Modificar Producto ---\nCodigo a modificar: "; string cod; getline(cin, cod);
    for (auto& p : lista) {
        if (p.codigo == cod) {
            string nuevo; double np; int ns;
            cout << "Nuevo nombre    (Enter=mantener): "; getline(cin, nuevo);
            if (!nuevo.empty()) p.nombre = nuevo;
            cout << "Nueva categoria (Enter=mantener): "; getline(cin, nuevo);
            if (!nuevo.empty()) p.categoria = nuevo;
            cout << "Nuevo precio    (0=mantener): "; cin >> np; if (np > 0) p.precio = np;
            cout << "Nuevo stock     (-1=mantener): "; cin >> ns; if (ns >= 0) p.stock = ns;
            guardarProductos(archivo, lista);
            cout << "Producto modificado correctamente.\n"; return;
        }
    }
    cout << "Producto con codigo '" << cod << "' no encontrado.\n";
}

// CRUD 4 - DELETE: eliminar producto
void eliminarProducto(const string& archivo, vector<Producto>& lista) {
    cin.ignore();
    cout << "\n--- Eliminar Producto ---\nCodigo a eliminar: "; string cod; getline(cin, cod);
    for (int i = 0; i < (int)lista.size(); i++) {
        if (lista[i].codigo == cod) {
            cout << "Confirmar eliminacion de '" << lista[i].nombre << "'? (s/n): ";
            char conf; cin >> conf;
            if (conf == 's' || conf == 'S') {
                lista.erase(lista.begin() + i);
                guardarProductos(archivo, lista);
                cout << "Producto eliminado correctamente.\n";
            } else cout << "Eliminacion cancelada.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}

// CRUD 2 - READ: listar todos
void listarTodos(const vector<Producto>& lista) {
    if (lista.empty()) { cout << "No hay productos registrados.\n"; return; }
    cout << "\n====== TODOS LOS PRODUCTOS ======\n";
    for (int i = 0; i < (int)lista.size(); i++) {
        cout << "Producto #" << (i+1) << "\n";
        lista[i].mostrar();
        cout << "---\n";
    }
    cout << "Total: " << lista.size() << " producto(s).\n";
}

int main() {
    const string archivo = "productos.txt";
    vector<Producto> lista = cargarProductos(archivo);
    int op;
    do {
        cout << "\n===== SISTEMA DE PRODUCTOS =====\n";
        cout << "1. Agregar producto\n2. Buscar producto\n";
        cout << "3. Modificar producto\n4. Eliminar producto\n";
        cout << "5. Listar todos\n0. Salir\nOpcion: "; cin >> op;
        switch (op) {
            case 1: agregarProducto(archivo, lista);   break;
            case 2: buscarProducto(lista);             break;
            case 3: modificarProducto(archivo, lista); break;
            case 4: eliminarProducto(archivo, lista);  break;
            case 5: listarTodos(lista);                break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (op != 0);
    return 0;
}
