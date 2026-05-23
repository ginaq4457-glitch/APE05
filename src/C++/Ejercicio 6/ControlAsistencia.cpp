#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void registrar() {
    string nombre, fecha, estado;
    ofstream archivo("asistencia.txt", ios::app);
    cout << "Nombre: "; cin >> nombre;
    cout << "Fecha (DD/MM/AAAA): "; cin >> fecha;
    do {
        cout << "Estado (Presente/Ausente): "; cin >> estado;
    } while (estado != "Presente" && estado != "Ausente");
    archivo << nombre << " " << fecha << " " << estado << endl;
    archivo.close();
}

void historial() {
    string n, f, e;
    int faltas = 0;
    ifstream archivo("asistencia.txt");
    while (archivo >> n >> f >> e) {
        cout << n << " | " << f << " | " << e << endl;
        if (e == "Ausente") faltas++;
    }
    cout << "Total faltas: " << faltas << endl;
    archivo.close();
}

int main() {
    int op;
    do {
        cout << "\n1. Registrar | 2. Ver historial | 3. Salir: "; cin >> op;
        if (op == 1) registrar();
        else if (op == 2) historial();
    } while (op != 3);
    return 0;
}