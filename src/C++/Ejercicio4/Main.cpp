#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Nombre del archivo donde se guardan los contactos
const string ARCHIVO = "agenda.txt";

//  Clase Contacto
class Contacto {
private:
    string nombre;
    string telefono;
    string correo;

public:
    // Constructor por defecto
    Contacto() : nombre(""), telefono(""), correo("") {}

    // Constructor con parámetros
    Contacto(string _nombre, string _telefono, string _correo) {
        nombre   = _nombre;
        telefono = _telefono;
        correo   = _correo;
    }

    // Métodos GET
    string getNombre()   const { return nombre;   }
    string getTelefono() const { return telefono; }
    string getCorreo()   const { return correo;   }

    // Métodos SET
    void setNombre(string _nombre)     { nombre   = _nombre;   }
    void setTelefono(string _telefono) { telefono = _telefono; }
    void setCorreo(string _correo)     { correo   = _correo;   }

    // Mostrar información del contacto
    void mostrarContacto() const {
        cout << "  ----------------------------------------" << endl;
        cout << "  Nombre   : " << nombre   << endl;
        cout << "  Telefono : " << telefono << endl;
        cout << "  Correo   : " << correo   << endl;
        cout << "  ----------------------------------------" << endl;
    }
};

//  Función: agregarContacto
//  Guarda un contacto al final del archivo (modo append)
void agregarContacto() {
    string nombre, telefono, correo;

    cout << "\n  -- Agregar Contacto --" << endl;
    cout << "  Nombre   : "; cin >> nombre;
    cout << "  Telefono : "; cin >> telefono;
    cout << "  Correo   : "; cin >> correo;

    Contacto c(nombre, telefono, correo);

    // Abrir archivo en modo agregar (ios::app)
    ofstream archivo(ARCHIVO, ios::app);
    if (!archivo.is_open()) {
        cout << "  [ERROR] No se pudo abrir el archivo." << endl;
        return;
    }

    // Guardar en formato: nombre|telefono|correo
    archivo << c.getNombre()   << "|"
            << c.getTelefono() << "|"
            << c.getCorreo()   << endl;

    archivo.close();
    cout << "  [OK] Contacto guardado correctamente." << endl;
}

//  Función: mostrarContactos
//  Lee y muestra todos los contactos del archivo
void mostrarContactos() {
    ifstream archivo(ARCHIVO);
    if (!archivo.is_open()) {
        cout << "  [INFO] No hay contactos registrados." << endl;
        return;
    }

    cout << "\n  ======== LISTA DE CONTACTOS ========" << endl;

    string linea;
    int contador = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        // Separar los campos por el delimitador '|'
        stringstream ss(linea);
        string nombre, telefono, correo;
        getline(ss, nombre,   '|');
        getline(ss, telefono, '|');
        getline(ss, correo,   '|');

        Contacto c(nombre, telefono, correo);
        c.mostrarContacto();
        contador++;
    }

    archivo.close();

    if (contador == 0) {
        cout << "  [INFO] No hay contactos registrados." << endl;
    } else {
        cout << "  Total de contactos: " << contador << endl;
    }
}

//  Función: buscarContacto
//  Busca un contacto por nombre (búsqueda parcial)
void buscarContacto() {
    string busqueda;
    cout << "\n  -- Buscar Contacto --" << endl;
    cout << "  Ingrese nombre a buscar: "; cin >> busqueda;

    ifstream archivo(ARCHIVO);
    if (!archivo.is_open()) {
        cout << "  [INFO] No hay contactos registrados." << endl;
        return;
    }

    string linea;
    bool encontrado = false;

    cout << "\n  ======== RESULTADOS ========" << endl;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string nombre, telefono, correo;
        getline(ss, nombre,   '|');
        getline(ss, telefono, '|');
        getline(ss, correo,   '|');

        // Búsqueda insensible a mayúsculas no es requerida; búsqueda exacta
        if (nombre.find(busqueda) != string::npos) {
            Contacto c(nombre, telefono, correo);
            c.mostrarContacto();
            encontrado = true;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "  [INFO] No se encontro ningun contacto con ese nombre." << endl;
    }
}

//Menú interactivo
int main() {
    int opcion;

    cout << "============================================" << endl;
    cout << "    Agenda Telefonica (Ej.4)   " << endl;
    cout << "============================================" << endl;

    do {
        cout << "\n  MENU PRINCIPAL" << endl;
        cout << "  1. Agregar contacto"  << endl;
        cout << "  2. Mostrar contactos" << endl;
        cout << "  3. Buscar contacto"   << endl;
        cout << "  4. Salir"             << endl;
        cout << "  Opcion: ";
        cin  >> opcion;

        switch (opcion) {
            case 1: agregarContacto(); break;
            case 2: mostrarContactos(); break;
            case 3: buscarContacto();   break;
            case 4: cout << "  Hasta luego." << endl; break;
            default: cout << " Opción no valida." << endl;
        }

    } while (opcion != 4);

    return 0;
}
