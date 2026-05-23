#include <iostream>
#include <string>
using namespace std;

int main() {
    // Arreglo de nombres de productos
    string productos[5] = {"Arroz", "Azucar", "Aceite", "Sal", "Harina"};

    // Arreglo paralelo de precios (en USD)
    double precios[5] = {1.50, 2.00, 3.75, 0.80, 1.20};

    string buscar;
    bool encontrado = false;

    cout << "=== Busqueda Lineal de Productos ===" << endl;
    cout << "Ingrese el nombre del producto a buscar: ";
    cin >> buscar;

    // Recorrer el arreglo usando busqueda lineal
    for (int i = 0; i < 5; i++) {
        if (productos[i] == buscar) {
            cout << "\nProducto encontrado: " << productos[i] << endl;
            cout << "Precio: $" << precios[i] << endl;
            encontrado = true;
            break; // Detener busqueda al encontrar el producto
        }
    }

    // Mensaje si el producto no existe
    if (!encontrado) {
        cout << "\nEl producto '" << buscar << "' no existe en el inventario." << endl;
    }

    return 0;
}
