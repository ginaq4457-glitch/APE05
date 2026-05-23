// ============================================================
// APE 05 - Ejercicio 3: Sistema de Inventario Basico
// Asignatura: Algoritmos y Logica de Programacion
// Docente: Jose Ruben Caiza
// ============================================================

import java.io.*;
import java.util.*;

// Clase que representa un producto del inventario
class Producto {
    private String codigo;
    private String nombre;
    private int    cantidad;
    private double precio;

    // Constructor
    public Producto(String codigo, String nombre, int cantidad, double precio) {
        this.codigo   = codigo;
        this.nombre   = nombre;
        this.cantidad = cantidad;
        this.precio   = precio;
    }

    // Getters
    public String getCodigo()   { return codigo;   }
    public String getNombre()   { return nombre;   }
    public int    getCantidad() { return cantidad; }
    public double getPrecio()   { return precio;   }

    // Metodo para mostrar los datos del producto
    public void mostrar() {
        System.out.println("  Codigo  : " + codigo);
        System.out.println("  Nombre  : " + nombre);
        System.out.println("  Cantidad: " + cantidad);
        System.out.printf ("  Precio  : $%.2f%n", precio);
        System.out.printf ("  Subtotal: $%.2f%n", subtotal());
    }

    // Metodo que calcula el subtotal del producto (precio * cantidad)
    public double subtotal() {
        return precio * cantidad;
    }

    // Convertir el producto a linea de archivo
    public String toLinea() {
        return codigo + "|" + nombre + "|" + cantidad + "|" + String.format("%.2f", precio);
    }
}

public class Ejercicio3 {

    static final String NOMBRE_ARCHIVO = "inventario.txt";
    static List<Producto> inventario = new ArrayList<>();
    static Scanner sc = new Scanner(System.in);

    // Metodo para guardar un producto en el archivo (modo agregar)
    public static void guardarProducto(Producto p) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(NOMBRE_ARCHIVO, true))) {
            bw.write(p.toLinea());
            bw.newLine();
        } catch (IOException e) {
            System.out.println("Error al guardar: " + e.getMessage());
        }
    }

    // Metodo para registrar un nuevo producto
    public static void registrarProducto() {
        System.out.println("\n--- Registrar Nuevo Producto ---");
        System.out.print("Codigo  : ");
        String codigo = sc.nextLine();
        System.out.print("Nombre  : ");
        String nombre = sc.nextLine();
        System.out.print("Cantidad: ");
        int cantidad = Integer.parseInt(sc.nextLine());
        System.out.print("Precio  : ");
        double precio = Double.parseDouble(sc.nextLine());

        // Validar que cantidad y precio no sean negativos
        if (cantidad < 0 || precio < 0) {
            System.out.println("Error: cantidad y precio deben ser valores positivos.");
            return;
        }

        Producto p = new Producto(codigo, nombre, cantidad, precio);
        inventario.add(p);
        guardarProducto(p);

        System.out.println("Producto registrado correctamente en " + NOMBRE_ARCHIVO + ".");
    }

    // Metodo para leer todos los productos desde el archivo
    public static void leerInventario() {
        inventario.clear();
        try (BufferedReader br = new BufferedReader(new FileReader(NOMBRE_ARCHIVO))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                if (!linea.isEmpty()) {
                    // Formato: codigo|nombre|cantidad|precio
                    String[] datos = linea.split("\\|");
                    if (datos.length == 4) {
                        inventario.add(new Producto(
                            datos[0],
                            datos[1],
                            Integer.parseInt(datos[2]),
                            Double.parseDouble(datos[3])
                        ));
                    }
                }
            }
        } catch (FileNotFoundException e) {
            // Primer uso, el archivo aun no existe
        } catch (IOException e) {
            System.out.println("Error al leer el archivo: " + e.getMessage());
        }
    }

    // Metodo para mostrar el inventario completo
    public static void mostrarInventario() {
        if (inventario.isEmpty()) {
            System.out.println("El inventario esta vacio.");
            return;
        }

        System.out.println("\n=========================================");
        System.out.println("       INVENTARIO COMPLETO");
        System.out.println("  Total de productos: " + inventario.size());
        System.out.println("=========================================");

        for (int i = 0; i < inventario.size(); i++) {
            System.out.println("Producto #" + (i + 1));
            inventario.get(i).mostrar();
            System.out.println("-----------------------------------------");
        }
    }

    // Metodo para calcular el valor total del inventario
    public static double calcularValorTotal() {
        double total = 0.0;
        for (Producto p : inventario) {
            total += p.subtotal();
        }
        return total;
    }

    public static void main(String[] args) {
        // Cargar inventario existente
        leerInventario();

        int opcion;
        do {
            System.out.println("\n===== SISTEMA DE INVENTARIO =====");
            System.out.println("1. Registrar producto");
            System.out.println("2. Mostrar inventario");
            System.out.println("3. Calcular valor total");
            System.out.println("0. Salir");
            System.out.print("Opcion: ");

            try {
                opcion = Integer.parseInt(sc.nextLine());
            } catch (NumberFormatException e) {
                opcion = -1;
            }

            switch (opcion) {
                case 1:
                    registrarProducto();
                    break;
                case 2:
                    mostrarInventario();
                    break;
                case 3:
                    double total = calcularValorTotal();
                    System.out.printf("%nValor total del inventario: $%.2f%n", total);
                    break;
                case 0:
                    System.out.println("Saliendo del sistema...");
                    break;
                default:
                    System.out.println("Opcion invalida. Intente de nuevo.");
            }
        } while (opcion != 0);

        sc.close();
    }
}
