// ============================================================
// APE 05 - Ejercicio 8: Biblioteca Virtual
// Asignatura: Algoritmos y Logica de Programacion
// Docente: Jose Ruben Caiza
// ============================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// Clase que representa un libro de la biblioteca
class Libro {
public:
    string codigo;
    string titulo;
    string autor;
    string estado; // "disponible" o "prestado"

    // Constructor
    Libro(string cod, string tit, string aut, string est) {
        codigo = cod;
        titulo = tit;
        autor  = aut;
        estado = est;
    }

    // Metodo para mostrar los datos del libro
    void mostrar() {
        cout << "  Codigo : " << codigo << endl;
        cout << "  Titulo : " << titulo << endl;
        cout << "  Autor  : " << autor  << endl;
        cout << "  Estado : " << estado << endl;
    }

    // Metodo para convertir el libro a linea de archivo
    string toLinea() {
        return codigo + "|" + titulo + "|" + autor + "|" + estado;
    }
};

// Metodo auxiliar: divide un string por delimitador
vector<string> dividir(string linea, char delimitador) {
    vector<string> partes;
    stringstream ss(linea);
    string token;
    while (getline(ss, token, delimitador)) {
        partes.push_back(token);
    }
    return partes;
}

// Metodo para leer todos los libros desde el archivo
vector<Libro> leerLibros(string nombreArchivo) {
    vector<Libro> libros;
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return libros; // Si no existe aun, se retorna vacio

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            // Formato: codigo|titulo|autor|estado
            vector<string> datos = dividir(linea, '|');
            if (datos.size() == 4) {
                libros.push_back(Libro(datos[0], datos[1], datos[2], datos[3]));
            }
        }
    }
    archivo.close();
    return libros;
}

// Metodo para guardar todos los libros en el archivo
void guardarLibros(string nombreArchivo, vector<Libro>& libros) {
    ofstream archivo(nombreArchivo);
    for (int i = 0; i < (int)libros.size(); i++) {
        archivo << libros[i].toLinea() << "\n";
    }
    archivo.close();
}

// Metodo para registrar un nuevo libro
void registrarLibro(string nombreArchivo, vector<Libro>& libros) {
    string codigo, titulo, autor, estado;

    cout << "\n--- Registrar Nuevo Libro ---" << endl;
    cout << "Codigo : "; cin >> codigo;
    cin.ignore();
    cout << "Titulo : "; getline(cin, titulo);
    cout << "Autor  : "; getline(cin, autor);

    // Validar estado
    do {
        cout << "Estado (disponible / prestado): ";
        getline(cin, estado);
        if (estado != "disponible" && estado != "prestado") {
            cout << "Estado invalido. Ingrese 'disponible' o 'prestado'." << endl;
        }
    } while (estado != "disponible" && estado != "prestado");

    libros.push_back(Libro(codigo, titulo, autor, estado));
    guardarLibros(nombreArchivo, libros);
    cout << "Libro registrado y guardado correctamente." << endl;
}

// Metodo para buscar libros por codigo o titulo
void buscarLibro(vector<Libro>& libros) {
    cin.ignore();
    cout << "\nIngrese codigo o titulo a buscar: ";
    string busqueda;
    getline(cin, busqueda);

    // Convertir busqueda a minusculas para comparacion sin distincion
    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    bool encontrado = false;
    cout << "\n--- Resultados de Busqueda ---" << endl;

    for (int i = 0; i < (int)libros.size(); i++) {
        string codigoLower = libros[i].codigo;
        string tituloLower = libros[i].titulo;

        transform(codigoLower.begin(), codigoLower.end(), codigoLower.begin(), ::tolower);
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        if (codigoLower.find(busquedaLower) != string::npos ||
            tituloLower.find(busquedaLower) != string::npos) {
            libros[i].mostrar();
            cout << "------------------------------" << endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron libros con ese criterio." << endl;
    }
}

// Metodo para mostrar libros segun su estado
void mostrarPorEstado(vector<Libro>& libros) {
    cout << "\n====== LIBROS DISPONIBLES ======" << endl;
    int contDisponibles = 0;
    for (int i = 0; i < (int)libros.size(); i++) {
        if (libros[i].estado == "disponible") {
            libros[i].mostrar();
            cout << "--------------------------------" << endl;
            contDisponibles++;
        }
    }
    if (contDisponibles == 0) cout << "No hay libros disponibles." << endl;

    cout << "\n====== LIBROS PRESTADOS ========" << endl;
    int contPrestados = 0;
    for (int i = 0; i < (int)libros.size(); i++) {
        if (libros[i].estado == "prestado") {
            libros[i].mostrar();
            cout << "--------------------------------" << endl;
            contPrestados++;
        }
    }
    if (contPrestados == 0) cout << "No hay libros prestados." << endl;

    cout << "\nResumen: " << contDisponibles << " disponible(s), "
         << contPrestados << " prestado(s)." << endl;
}

// Metodo para mostrar todos los libros registrados
void mostrarTodos(vector<Libro>& libros) {
    if (libros.empty()) {
        cout << "No hay libros registrados." << endl;
        return;
    }
    cout << "\n====== CATALOGO COMPLETO ======" << endl;
    for (int i = 0; i < (int)libros.size(); i++) {
        cout << "Libro #" << (i + 1) << endl;
        libros[i].mostrar();
        cout << "-------------------------------" << endl;
    }
    cout << "Total: " << libros.size() << " libro(s)." << endl;
}

int main() {
    string nombreArchivo = "libros.txt";

    // Cargar libros existentes desde el archivo
    vector<Libro> libros = leerLibros(nombreArchivo);

    int opcion;
    do {
        cout << "\n===== BIBLIOTECA VIRTUAL =====" << endl;
        cout << "1. Registrar libro"              << endl;
        cout << "2. Buscar libro"                  << endl;
        cout << "3. Ver disponibles y prestados"   << endl;
        cout << "4. Ver catalogo completo"         << endl;
        cout << "0. Salir"                         << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarLibro(nombreArchivo, libros); break;
            case 2: buscarLibro(libros);                   break;
            case 3: mostrarPorEstado(libros);              break;
            case 4: mostrarTodos(libros);                  break;
            case 0: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}
