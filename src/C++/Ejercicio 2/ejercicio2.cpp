#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
 
struct Estudiante { string cedula, nombre, carrera; double promedio; };
 
// Lee y parsea cada línea del archivo
vector<Estudiante> leerArchivo(const string& ruta) {
    vector<Estudiante> lista;
    ifstream f(ruta);
    string linea;
    while (getline(f, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        Estudiante e;
        string pro;
        getline(ss, e.cedula,  '|');
        getline(ss, e.nombre,  '|');
        getline(ss, e.carrera, '|');
        getline(ss, pro,       '|');
        e.promedio = stod(pro);
        lista.push_back(e);
    }
    return lista;
}
 
int main() {
    auto lista = leerArchivo("estudiantes.txt");
    if (lista.empty()) {
        cout << "No hay registros en el archivo." << endl;
        return 0;
    }
    cout << "=== Listado de Estudiantes ===" << endl;
    double suma = 0;
    for (auto& e : lista) {
        cout << "Cedula: "  << e.cedula  << " | Nombre: " << e.nombre
             << " | Carrera: " << e.carrera
             << " | Promedio: " << e.promedio << endl;
        suma += e.promedio;
    }
    cout << "\nTotal de estudiantes : " << lista.size() << endl;
    cout << "Promedio general     : " << suma / lista.size() << endl;
    return 0;
}
