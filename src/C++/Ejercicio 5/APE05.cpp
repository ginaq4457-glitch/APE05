// ============================================================
// APE 05 - Ejercicio 5: Sistema de Calificaciones
// Sistema de Gestion de Notas (POO, Metodos y Archivos)
// Asignatura: Algoritmos y Logica de Programacion
// Docente: Jose Ruben Caiza
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Estudiante {
public:
    string nombre;
    double nota1, nota2, nota3; // Atributos de las notas
    double promedio;
    string condicion;

    // CONSTRUCTOR CORREGIDO: Ahora sí inicializa todas las variables numéricas en 0.0
    Estudiante() {
        nombre = "";
        nota1 = 0.0;
        nota2 = 0.0;
        nota3 = 0.0;
        promedio = 0.0;
        condicion = "";
    }

    // MÉTODO CORREGIDO: Se agregaron las líneas para que sí te pida las notas por teclado
    void registrarDatos() {
        cout << "=== Registrar Estudiante ===" << endl;
        cout << "Nombre del estudiante: ";
        getline(cin, nombre);
        cout << "Nota 1: ";
        cin >> nota1;
        cout << "Nota 2: ";
        cin >> nota2;
        cout << "Nota 3: ";
        cin >> nota3;
    }

    void calcularPromedio() {
        promedio = (nota1 + nota2 + nota3) / 3.0;
    }

    void evaluarCondicion() {
        if (promedio >= 7.0) {
            condicion = "Aprobado";
        } else {
            condicion = "Reprobado";
        }
    }

    void mostrarReporte() const {
        cout << "\n======= REPORTE =======" << endl;
        cout << " Estudiante: " << nombre << endl;
        cout << " Nota 1    : " << nota1 << endl;
        cout << " Nota 2    : " << nota2 << endl;
        cout << " Nota 3    : " << nota3 << endl;
        cout << " Promedio  : " << fixed << setprecision(2) << promedio << endl;
        cout << " Estado    : " << condicion << endl;
        cout << "-----------------------" << endl;
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo;
        archivo.open(nombreArchivo, ios::app);

        if (archivo.is_open()) {
            archivo << nombre << "|" << nota1 << "|" << nota2 << "|" << nota3 << "|"
                    << fixed << setprecision(2) << promedio << "|" << condicion << "\n";
            archivo.close();
            cout << "[!] Registro guardado exitosamente en '" << nombreArchivo << "'." << endl;
        } else {
            cout << "Error: No se pudo acceder al archivo de persistencia." << endl;
        }
    }
};

int main() {
    const string archivo = "notas.txt";
    Estudiante est;

    // Ejecución secuencial sin saltos
    est.registrarDatos();
    est.calcularPromedio();
    est.evaluarCondicion();
    est.mostrarReporte();
    est.guardarEnArchivo(archivo);

    return 0;
}

