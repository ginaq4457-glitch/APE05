// ============================================================
// APE 05 - Ejercicio 8: Biblioteca Virtual
// Asignatura: Algoritmos y Logica de Programacion
// Docente: Jose Ruben Caiza
// ============================================================

import java.io.*;
import java.util.*;

// Clase que representa un libro de la biblioteca
class Libro {
    private String codigo;
    private String titulo;
    private String autor;
    private String estado; // "disponible" o "prestado"

    // Constructor
    public Libro(String codigo, String titulo, String autor, String estado) {
        this.codigo = codigo;
        this.titulo = titulo;
        this.autor  = autor;
        this.estado = estado;
    }

    // Getters y Setter de estado
    public String getCodigo() { return codigo; }
    public String getTitulo() { return titulo; }
    public String getAutor()  { return autor;  }
    public String getEstado() { return estado; }
    public void setEstado(String estado) { this.estado = estado; }

    // Metodo para mostrar los datos del libro
    public void mostrar() {
        System.out.println("  Codigo : " + codigo);
        System.out.println("  Titulo : " + titulo);
        System.out.println("  Autor  : " + autor);
        System.out.println("  Estado : " + estado);
    }

    // Metodo para convertir el libro a linea de archivo
    public String toLinea() {
        return codigo + "|" + titulo + "|" + autor + "|" + estado;
    }
}

public class Ejercicio8 {

    static final String NOMBRE_ARCHIVO = "libros.txt";
    static List<Libro> libros = new ArrayList<>();
    static Scanner sc = new Scanner(System.in);

    // Metodo para leer todos los libros desde el archivo
    public static void leerLibros() {
        libros.clear();
        try (BufferedReader br = new BufferedReader(new FileReader(NOMBRE_ARCHIVO))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                if (!linea.isEmpty()) {
                    // Formato: codigo|titulo|autor|estado
                    String[] datos = linea.split("\\|");
                    if (datos.length == 4) {
                        libros.add(new Libro(datos[0], datos[1], datos[2], datos[3]));
                    }
                }
            }
        } catch (FileNotFoundException e) {
            // El archivo aun no existe, es normal al primer uso
        } catch (IOException e) {
            System.out.println("Error al leer el archivo: " + e.getMessage());
        }
    }

    // Metodo para guardar todos los libros en el archivo
    public static void guardarLibros() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(NOMBRE_ARCHIVO))) {
            for (Libro l : libros) {
                bw.write(l.toLinea());
                bw.newLine();
            }
        } catch (IOException e) {
            System.out.println("Error al guardar en el archivo: " + e.getMessage());
        }
    }

    // Metodo para registrar un nuevo libro
    public static void registrarLibro() {
        System.out.println("\n--- Registrar Nuevo Libro ---");
        System.out.print("Codigo : ");
        String codigo = sc.nextLine();
        System.out.print("Titulo : ");
        String titulo = sc.nextLine();
        System.out.print("Autor  : ");
        String autor = sc.nextLine();

        // Validar estado ingresado
        String estado;
        do {
            System.out.print("Estado (disponible / prestado): ");
            estado = sc.nextLine();
            if (!estado.equals("disponible") && !estado.equals("prestado")) {
                System.out.println("Estado invalido. Ingrese 'disponible' o 'prestado'.");
            }
        } while (!estado.equals("disponible") && !estado.equals("prestado"));

        libros.add(new Libro(codigo, titulo, autor, estado));
        guardarLibros();
        System.out.println("Libro registrado y guardado correctamente.");
    }

    // Metodo para buscar libros por codigo o titulo
    public static void buscarLibro() {
        System.out.print("\nIngrese codigo o titulo a buscar: ");
        String busqueda = sc.nextLine().toLowerCase();

        boolean encontrado = false;
        System.out.println("\n--- Resultados de Busqueda ---");

        for (Libro l : libros) {
            if (l.getCodigo().toLowerCase().contains(busqueda) ||
                l.getTitulo().toLowerCase().contains(busqueda)) {
                l.mostrar();
                System.out.println("------------------------------");
                encontrado = true;
            }
        }

        if (!encontrado) {
            System.out.println("No se encontraron libros con ese criterio.");
        }
    }

    // Metodo para mostrar libros segun su estado
    public static void mostrarPorEstado() {
        System.out.println("\n====== LIBROS DISPONIBLES ======");
        int contDisponibles = 0;
        for (Libro l : libros) {
            if (l.getEstado().equals("disponible")) {
                l.mostrar();
                System.out.println("--------------------------------");
                contDisponibles++;
            }
        }
        if (contDisponibles == 0) System.out.println("No hay libros disponibles.");

        System.out.println("\n====== LIBROS PRESTADOS ========");
        int contPrestados = 0;
        for (Libro l : libros) {
            if (l.getEstado().equals("prestado")) {
                l.mostrar();
                System.out.println("--------------------------------");
                contPrestados++;
            }
        }
        if (contPrestados == 0) System.out.println("No hay libros prestados.");

        System.out.println("\nResumen: " + contDisponibles +
                           " disponible(s), " + contPrestados + " prestado(s).");
    }

    // Metodo para mostrar todos los libros registrados
    public static void mostrarTodos() {
        if (libros.isEmpty()) {
            System.out.println("No hay libros registrados.");
            return;
        }
        System.out.println("\n====== CATALOGO COMPLETO ======");
        for (int i = 0; i < libros.size(); i++) {
            System.out.println("Libro #" + (i + 1));
            libros.get(i).mostrar();
            System.out.println("-------------------------------");
        }
        System.out.println("Total: " + libros.size() + " libro(s).");
    }

    public static void main(String[] args) {
        // Cargar libros existentes desde el archivo
        leerLibros();

        int opcion;
        do {
            System.out.println("\n===== BIBLIOTECA VIRTUAL =====");
            System.out.println("1. Registrar libro");
            System.out.println("2. Buscar libro");
            System.out.println("3. Ver disponibles y prestados");
            System.out.println("4. Ver catalogo completo");
            System.out.println("0. Salir");
            System.out.print("Opcion: ");

            try {
                opcion = Integer.parseInt(sc.nextLine());
            } catch (NumberFormatException e) {
                opcion = -1; // Forzar opcion invalida
            }

            switch (opcion) {
                case 1: registrarLibro();    break;
                case 2: buscarLibro();       break;
                case 3: mostrarPorEstado();  break;
                case 4: mostrarTodos();      break;
                case 0: System.out.println("Saliendo del sistema..."); break;
                default: System.out.println("Opcion invalida. Intente de nuevo.");
            }

        } while (opcion != 0);

        sc.close();
    }
}
