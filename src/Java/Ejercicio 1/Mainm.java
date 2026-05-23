import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.Scanner;

class Estudiante {
    private String cedula, nombre, carrera;
    private double promedio;

    public void capturarDatos() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Ingrese cedula: "); cedula = sc.nextLine();
        System.out.print("Ingrese nombre: "); nombre = sc.nextLine();
        System.out.print("Ingrese carrera: "); carrera = sc.nextLine();
        System.out.print("Ingrese promedio: "); promedio = sc.nextDouble();
    }

    public void guardarEnArchivo() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("estudiantes.txt", true))) {
            writer.println(cedula + " | " + nombre + " | " + carrera + " | " + promedio);
            System.out.println("Registro guardado exitosamente.");
        } catch (IOException e) {
            System.out.println("Error al escribir en el archivo: " + e.getMessage());
        }
    }
}

public class Mainm {
    public static void main(String[] args) {
        Estudiante e = new Estudiante();
        e.capturarDatos();
        e.guardarEnArchivo();
    }
}