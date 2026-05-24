import java.io.*;
import java.util.Scanner;

public class Ej9main {

// Archivo donde se guardan las ventas
private static final String ARCHIVO = "ventas.txt";
private static Scanner sc = new Scanner(System.in);

//  Método: registrarVenta
//  Solicita datos, genera factura y guarda en archivo
public static void registrarVenta() throws IOException {
System.out.println("\n  -- Registrar Venta --");

System.out.print("  Producto  : ");
String producto = sc.next();

int cantidad;
do {
System.out.print("  Cantidad  : ");
cantidad = sc.nextInt();
if (cantidad <= 0)
System.out.println("  La cantidad debe ser mayor a 0.");
} while (cantidad <= 0);

double precio;
do {
System.out.print("  Precio u. : ");
precio = sc.nextDouble();
if (precio <= 0)
System.out.println("  El precio debe ser mayor a 0.");
} while (precio <= 0);

Ej9Venta v = new Ej9Venta(producto, cantidad, precio);

// Mostrar factura generada
System.out.println("\n  ======== FACTURA GENERADA ========");
v.mostrarFactura();

// Guardar en archivo (modo append)
FileWriter fw   = new FileWriter(ARCHIVO, true);
BufferedWriter bw = new BufferedWriter(fw);
bw.write(v.toArchivo());
bw.newLine();
bw.close();
fw.close();

System.out.println(" Venta registrada correctamente.");
}

//  Método: mostrarHistorial
//  Lee el archivo y muestra todas las ventas
public static void mostrarHistorial() throws IOException {
File f = new File(ARCHIVO);
if (!f.exists()) {
System.out.println(" No hay ventas registradas.");
return;
}

System.out.println("\n  ======== HISTORIAL DE VENTAS ========");

BufferedReader br = new BufferedReader(new FileReader(ARCHIVO));
String linea;
int    contador     = 0;
double totalGeneral = 0.0;

while ((linea = br.readLine()) != null) {
if (linea.trim().isEmpty()) continue;
Ej9Venta v = Ej9Venta.fromArchivo(linea);
v.mostrarFactura();
totalGeneral += v.getTotal();
contador++;
}
br.close();

if (contador == 0) {
System.out.println("  [INFO] No hay ventas registradas.");
} else {
System.out.printf("  Total de ventas  : %d%n",    contador);
System.out.printf("  Ingresos totales : $%.2f%n", totalGeneral);
}
}

//  Método principal – Menú interactivo
public static void main(String[] args) {
System.out.println("============================================");
System.out.println("   Sistema de Ventas Java (APE05 Ej.9)   ");
System.out.println("============================================");

int opcion;
do {
System.out.println("\n  MENU PRINCIPAL");
System.out.println("  1. Registrar venta");
System.out.println("  2. Historial de ventas");
System.out.println("  3. Salir");
System.out.print("  Opcion: ");
opcion = sc.nextInt();

try {
switch (opcion) {
case 1: registrarVenta();   break;
case 2: mostrarHistorial(); break;
case 3: System.out.println("  Hasta luego."); break;
default: System.out.println("  Opcion no valida.");
}
} catch (IOException e) {
System.out.println("  Problema con el archivo: " + e.getMessage());
}

} while (opcion != 3);

sc.close();
}
}
