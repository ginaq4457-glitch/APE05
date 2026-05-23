import java.io.*;
import java.util.Scanner;

public class ControlAsistencia {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int op;
        do {
            System.out.print("\n1. Registrar | 2. Historial | 3. Salir: ");
            op = sc.nextInt();
            if (op == 1) {
                try (PrintWriter w = new PrintWriter(new FileWriter("asistencia.txt", true))) {
                    System.out.print("Nombre: "); String n = sc.next();
                    System.out.print("Fecha: "); String f = sc.next();
                    String e;
                    do { System.out.print("Estado (Presente/Ausente): "); e = sc.next(); } 
                    while (!e.equals("Presente") && !e.equals("Ausente"));
                    w.println(n + " " + f + " " + e);
                }
            } else if (op == 2) {
                try (Scanner fs = new Scanner(new File("asistencia.txt"))) {
                    int faltas = 0;
                    while (fs.hasNext()) {
                        String n = fs.next(), f = fs.next(), e = fs.next();
                        System.out.println(n + " | " + f + " | " + e);
                        if (e.equals("Ausente")) faltas++;
                    }
                    System.out.println("Total faltas: " + faltas);
                } catch (FileNotFoundException ex) { System.out.println("No hay registros."); }
            }
        } while (op != 3);
    }
}