#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Archivo donde se guardan las ventas
const string ARCHIVO = "ventas.txt";

//  Clase Venta
class Venta {
private:
    string producto;
    int    cantidad;
    double precio;
    double total;

public:
    // Constructor por defecto
    Venta() : producto(""), cantidad(0), precio(0.0), total(0.0) {}

    // Constructor con parámetros
    Venta(string _producto, int _cantidad, double _precio) {
        producto = _producto;
        cantidad = _cantidad;
        precio   = _precio;
        calcularTotal();
    }

    // Métodos GET
    string getProducto() const { return producto; }
    int    getCantidad() const { return cantidad;  }
    double getPrecio()   const { return precio;    }
    double getTotal()    const { return total;     }

    // Métodos SET
    void setProducto(string _producto) { producto = _producto; }
    void setCantidad(int    _cantidad) { cantidad = _cantidad; }
    void setPrecio(double   _precio)   { precio   = _precio;   }

    // Calcular total de la venta
    void calcularTotal() {
        total = cantidad * precio;
    }

    // Mostrar factura de la venta
    void mostrarFactura() const {
        cout << fixed << setprecision(2);
        cout << "  ----------------------------------------" << endl;
        cout << "  Producto  : " << producto           << endl;
        cout << "  Cantidad  : " << cantidad            << endl;
        cout << "  Precio u. : $" << precio             << endl;
        cout << "  TOTAL     : $" << total              << endl;
        cout << "  ----------------------------------------" << endl;
    }
};

//  Función: registrarVenta
//  Solicita datos y guarda la venta en el archivo
void registrarVenta() {
    string producto;
    int    cantidad;
    double precio;

    cout << "\n  -- Registrar Venta --" << endl;
    cout << "  Producto  : "; cin >> producto;

    do {
        cout << "  Cantidad  : "; cin >> cantidad;
        if (cantidad <= 0)
            cout << "  ERROR La cantidad debe ser mayor a 0." << endl;
    } while (cantidad <= 0);

    do {
        cout << "  Precio u. : "; cin >> precio;
        if (precio <= 0)
            cout << "  ERROR El precio debe ser mayor a 0." << endl;
    } while (precio <= 0);

    Venta v(producto, cantidad, precio);

    // Mostrar la factura generada
    cout << "\n  ======== FACTURA GENERADA ========" << endl;
    v.mostrarFactura();

    // Guardar en archivo (modo append)
    ofstream archivo(ARCHIVO, ios::app);
    if (!archivo.is_open()) {
        cout << "  ERROR No se pudo abrir el archivo de ventas." << endl;
        return;
    }

    archivo << fixed << setprecision(2);
    archivo << v.getProducto() << "|"
            << v.getCantidad() << "|"
            << v.getPrecio()   << "|"
            << v.getTotal()    << endl;

    archivo.close();
    cout << " Venta registrada correctamente." << endl;
}

//  Función: mostrarHistorial
//  Lee el archivo y muestra todas las ventas registradas
void mostrarHistorial() {
    ifstream archivo(ARCHIVO);
    if (!archivo.is_open()) {
        cout << "  No hay ventas registradas." << endl;
        return;
    }

    cout << "\n  ======== HISTORIAL DE VENTAS ========" << endl;

    string linea;
    int    contador = 0;
    double totalGeneral = 0.0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string producto, sCantidad, sPrecio, sTotal;
        getline(ss, producto,  '|');
        getline(ss, sCantidad, '|');
        getline(ss, sPrecio,   '|');
        getline(ss, sTotal,    '|');

        int    cantidad = stoi(sCantidad);
        double precio   = stod(sPrecio);
        double total    = stod(sTotal);

        Venta v(producto, cantidad, precio);
        v.mostrarFactura();

        totalGeneral += total;
        contador++;
    }

    archivo.close();

    if (contador == 0) {
        cout << " No hay ventas registradas." << endl;
    } else {
        cout << fixed << setprecision(2);
        cout << "  Total de ventas : " << contador       << endl;
        cout << "  Ingresos totales: $" << totalGeneral  << endl;
    }
}

//  Función principal – Menú interactivo
int main() {
    int opcion;

    cout << "============================================" << endl;
    cout << "   Sistema de Ventas C++ (APE05 Ej.9)    " << endl;
    cout << "============================================" << endl;

    do {
        cout << "\n  MENU PRINCIPAL" << endl;
        cout << "  1. Registrar venta"    << endl;
        cout << "  2. Historial de ventas" << endl;
        cout << "  3. Salir"              << endl;
        cout << "  Opcion: ";
        cin  >> opcion;

        switch (opcion) {
            case 1: registrarVenta();   break;
            case 2: mostrarHistorial(); break;
            case 3: cout << "  Hasta luego." << endl; break;
            default: cout << "  Opcion no valida." << endl;
        }

    } while (opcion != 3);

    return 0;
}
