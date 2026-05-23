#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Estudiante {
private:
    string cedula, nombre, carrera;
    float promedio;
public:
    void capturarDatos() {
        cout << "Ingrese cedula: "; cin >> cedula;
        cout << "Ingrese nombre: "; cin >> nombre;
        cout << "Ingrese carrera: "; cin >> carrera;
        cout << "Ingrese promedio: "; cin >> promedio;
    }
    void guardarEnArchivo() {
        ofstream archivo("estudiantes.txt", ios::app);
        if (archivo.is_open()) {
            archivo << cedula << " | " << nombre << " | " << carrera << " | " << promedio << endl;
            archivo.close();
            cout << "Registro guardado exitosamente." << endl;
        } else {
            cout << "Error al abrir el archivo." << endl;
        }
    }
};
int main() {
    Estudiante e;
    e.capturarDatos();
    e.guardarEnArchivo();
    return 0;
}