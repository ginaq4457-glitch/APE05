#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
 
class CuentaBancaria {
private:
    string usuario; double saldo;
public:
    CuentaBancaria(string u, double s) : usuario(u), saldo(s) {}
 
    // Carga saldo desde el archivo
    static CuentaBancaria cargar(const string& user) {
        ifstream f("cajero.txt"); string linea;
        while (getline(f,linea)) {
            stringstream ss(linea); string u,s;
            getline(ss,u,'|'); getline(ss,s,'|');
            if (u == user) return CuentaBancaria(u, stod(s));
        }
        return CuentaBancaria(user, 0.0); // cuenta nueva
    }
    void guardar() {
        ofstream f("cajero.txt"); // sobreescribe
        f << usuario << "|" << saldo << "\n";
    }
    void consultarSaldo() {
        cout << "Saldo actual: $" << saldo << endl;
    }
    void depositar(double monto) {
        if (monto <= 0) { cout << "Monto invalido." << endl; return; }
        saldo += monto;
        guardar();
        cout << "Deposito exitoso. Saldo: $" << saldo << endl;
    }
    void retirar(double monto) {
        if (monto <= 0 || monto > saldo) {
            cout << "Fondos insuficientes o monto invalido." << endl;
            return;
        }
        saldo -= monto;
        guardar();
        cout << "Retiro exitoso. Saldo: $" << saldo << endl;
    }
};
 
int main() {
    string user;
    cout << "=== Cajero Automatico ===" << endl;
    cout << "Usuario: "; cin >> user;
    CuentaBancaria cuenta = CuentaBancaria::cargar(user);
    int op; double monto;
    do {
        cout << "\n1. Consultar saldo\n2. Depositar"
             << "\n3. Retirar\n0. Salir\nOpcion: ";
        cin >> op;
        if      (op == 1) cuenta.consultarSaldo();
        else if (op == 2) { cout << "Monto: "; cin >> monto; cuenta.depositar(monto); }
        else if (op == 3) { cout << "Monto: "; cin >> monto; cuenta.retirar(monto); }
    } while (op != 0);
    return 0;
}
