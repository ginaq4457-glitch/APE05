import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

class Estudiante {
    String cedula;
    String nombre;
    String carrera;
    double promedio;
    
    Estudiante(String cedula, String nombre, String carrera, double promedio) {
        this.cedula = cedula;
        this.nombre = nombre;
        this.carrera = carrera;
        this.promedio = promedio;
    }
}

public class LecturaEstudiantes {
    
    public static List<Estudiante> leerArchivo(String ruta) {
        List<Estudiante> lista = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(ruta))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                if (linea.trim().isEmpty()) continue;
                String[] partes = linea.split("\\|");
                if (partes.length == 4) {
                    String cedula = partes[0];
                    String nombre = partes[1];
                    String carrera = partes[2];
                    double promedio = Double.parseDouble(partes[3]);
                    lista.add(new Estudiante(cedula, nombre, carrera, promedio));
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo: " + e.getMessage());
        }
        return lista;
    }
    
    public static void main(String[] args) {
        List<Estudiante> lista = leerArchivo("estudiantes.txt");
        
        if (lista.isEmpty()) {
            System.out.println("No hay registros en el archivo.");
            return;
        }
        
        System.out.println("=== Listado de Estudiantes ===");
        double suma = 0;
        for (Estudiante e : lista) {
            System.out.printf("Cedula: %s | Nombre: %s | Carrera: %s | Promedio: %.2f%n",
                              e.cedula, e.nombre, e.carrera, e.promedio);
            suma += e.promedio;
        }
        System.out.println("\nTotal de estudiantes : " + lista.size());
        System.out.printf("Promedio general     : %.2f%n", suma / lista.size());
    }
}