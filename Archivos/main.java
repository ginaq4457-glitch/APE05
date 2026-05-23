/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.estsudiante;
import java.util.ArrayList;
import java.util.Scanner;
/**
 *
 * @author GT ECUADOR
 */
public class main {

    public static void main(String[] args) {

        ArrayList<Estsudiante> listaEstudiantes = new ArrayList<>();
        int totalEstudiantes = 5;

        System.out.println("==================================================");
        System.out.println(" SISTEMA DE REGISTRO DE CALIFICACIONES (JAVA)     ");
        System.out.println("==================================================");

        for (int i = 0; i < totalEstudiantes; i++) {

            System.out.println("\n--- Registro del Estudiante " + (i + 1) + " ---");

            String cedula = SistemaControl.leerCedula();
            SistemaControl.entrada.nextLine();

            System.out.print("  Nombre: ");
            String nombre = SistemaControl.entrada.nextLine();

            System.out.print("  Apellido: ");
            String apellido = SistemaControl.entrada.nextLine();

            double n1 = SistemaControl.leerNota("Nota 1");
            double n2 = SistemaControl.leerNota("Nota 2");
            double n3 = SistemaControl.leerNota("Nota 3");

            listaEstudiantes.add(new Estsudiante(cedula, nombre, apellido, n1, n2, n3));
        }

        int aprobados = 0, reprobados = 0;

        System.out.println("\n================================================================================");
        System.out.println("                         LISTADO COMPLETO DE ESTUDIANTES                        ");
        System.out.println("================================================================================");

        System.out.printf("%-15s %-25s %-8s %-8s %-8s %-10s %-10s%n",
                "Cedula", "Estudiante", "N1", "N2", "N3", "Prom", "Estado");

        System.out.println("--------------------------------------------------------------------------------");

        for (Estsudiante est : listaEstudiantes) {

            est.mostrarInformacion();

            if (est.getEstado().equals("Aprobado")) {
                aprobados++;
            } else {
                reprobados++;
            }
        }

        System.out.println("--------------------------------------------------------------------------------");
        System.out.println(" REPORTE ESTADISTICO:");
        System.out.println("   Estudiantes Aprobados : " + aprobados);
        System.out.println("   Estudiantes Reprobados: " + reprobados);
        System.out.println("================================================================================");
    }
}

class SistemaControl {

    public static Scanner entrada = new Scanner(System.in);
    public static String leerCedula() {

        String ced;

        while (true) {

            System.out.print("  Cedula (10 digitos): ");

            ced = entrada.next();

            if (ced.length() == 10) {
                return ced;
            }

            System.out.println("  [Error] La cedula debe tener exactamente 10 digitos. Intente de nuevo.");
        }
    }
    public static double leerNota(String numeroNota) {

        double nota;

        while (true) {

            System.out.print("  Ingrese " + numeroNota + " (0 - 10): ");

            if (entrada.hasNextDouble()) {

                nota = entrada.nextDouble();

                if (nota >= 0 && nota <= 10) {
                    return nota;
                }

            } else {
                entrada.next();
            }

            System.out.println("  [Error] La nota debe estar entre 0 y 10. Intente de nuevo.");
        }
    }
}

