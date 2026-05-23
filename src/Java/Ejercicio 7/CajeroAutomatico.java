import java.io.*;
import java.util.Scanner;

class CuentaBancaria {
    private String usuario;
    private double saldo;
    
    // Constructor
    public CuentaBancaria(String usuario, double saldo) {
        this.usuario = usuario;
        this.saldo = saldo;
    }
    
    // Carga saldo desde el archivo
    public static CuentaBancaria cargar(String user) {
        String archivo = "cajero.txt";
        
        try (BufferedReader br = new BufferedReader(new FileReader(archivo))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                String[] partes = linea.split("\\|");
                if (partes.length == 2 && partes[0].equals(user)) {
                    double saldo = Double.parseDouble(partes[1]);
                    return new CuentaBancaria(user, saldo);
                }
            }
        } catch (FileNotFoundException e) {
            // Archivo no existe, se creará nuevo
        } catch (IOException e) {
            System.err.println("Error al leer archivo: " + e.getMessage());
        } 
        return new CuentaBancaria(user, 0.0); // Cuenta nueva
    }
    // Guarda el saldo actual en el archivo
    public void guardar() {
        try (PrintWriter pw = new PrintWriter(new FileWriter("cajero.txt"))) {
            pw.println(usuario + "|" + saldo);
        } catch (IOException e) {
            System.err.println("Error al guardar: " + e.getMessage());
        }
    }
    // Consulta saldo
    public void consultarSaldo() {
        System.out.printf("Saldo actual: $%.2f%n", saldo);
    }
    
    // Depositar
    public void depositar(double monto) {
        if (monto <= 0) {
            System.out.println("Monto invalido.");
            return;
        }
        saldo += monto;
        guardar();
        System.out.printf("Deposito exitoso. Saldo: $%.2f%n", saldo);
    }   
    // Retirar
    public void retirar(double monto) {
        if (monto <= 0 || monto > saldo) {
            System.out.println("Fondos insuficientes o monto invalido.");
            return;
        }
        saldo -= monto;
        guardar();
        System.out.printf("Retiro exitoso. Saldo: $%.2f%n", saldo);
    }
}
public class CajeroAutomatico {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.println("=== Cajero Automatico ===");
        System.out.print("Usuario: ");
        String user = sc.nextLine();
        
        CuentaBancaria cuenta = CuentaBancaria.cargar(user);
        
        int opcion;
        double monto;
        
        do {
            System.out.println("\n1. Consultar saldo");
            System.out.println("2. Depositar");
            System.out.println("3. Retirar");
            System.out.println("0. Salir");
            System.out.print("Opcion: ");
            opcion = sc.nextInt();
            
            switch (opcion) {
                case 1:
                    cuenta.consultarSaldo();
                    break;
                case 2:
                    System.out.print("Monto: ");
                    monto = sc.nextDouble();
                    cuenta.depositar(monto);
                    break;
                case 3:
                    System.out.print("Monto: ");
                    monto = sc.nextDouble();
                    cuenta.retirar(monto);
                    break;
                case 0:
                    System.out.println("Gracias por usar el cajero");
                    break;
                default:
                    System.out.println("Opcion invalida");
            }
        } while (opcion != 0);
        
        sc.close();
    }
}
