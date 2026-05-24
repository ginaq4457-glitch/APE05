import java.io.*;
import java.util.Scanner;

public class Ej4main {

    // Nombre del archivo donde se guardan los contactos
    private static final String ARCHIVO = "agenda.txt";
    private static Scanner sc = new Scanner(System.in);

    //  Método: agregarContacto
    //  Solicita datos y los guarda en el archivo (append)
    public static void agregarContacto() throws IOException {
        System.out.println("\n  -- Agregar Contacto --");
        sc.nextLine(); // Limpiar el buffer del scanner antes de leer Strings
        
        System.out.print(" Nombre : "); 
        String nombre = sc.nextLine();

        System.out.print(" Telefono : "); 
        String telefono = sc.nextLine();

        System.out.print(" Correo : "); 
        String correo = sc.nextLine();

        Ej4Contacto c = new Ej4Contacto(nombre, telefono, correo);

        // Abrir en modo append (true = agregar sin borrar contenido)
        FileWriter fw = new FileWriter(ARCHIVO, true);
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(c.toArchivo());
        bw.newLine();
        bw.close();
        fw.close();

        System.out.println("  [OK] Contacto guardado correctamente.");
    }

    //  Método: mostrarContactos
    //  Lee el archivo y muestra todos los contactos
    public static void mostrarContactos() throws IOException {
        File f = new File(ARCHIVO);
        if (!f.exists()) {
            System.out.println("  [INFO] No hay contactos registrados.");
            return;
        }

        System.out.println("\n  ======== LISTA DE CONTACTOS ========");

        BufferedReader br = new BufferedReader(new FileReader(ARCHIVO));
        String linea;
        int contador = 0;

        while ((linea = br.readLine()) != null) {
            if (linea.trim().isEmpty()) continue;
            Ej4Contacto c = Ej4Contacto.fromArchivo(linea);
            c.mostrarContacto();
            contador++;
        }
        br.close();

        if (contador == 0) {
            System.out.println("  [INFO] No hay contactos registrados.");
        } else {
            System.out.println("  Total de contactos: " + contador);
        }
    }

    //  Método: buscarContacto
    //  Busca contactos por nombre (búsqueda parcial)
    public static void buscarContacto() throws IOException {
        System.out.println("\n  -- Buscar Contacto --");
        sc.nextLine(); // Limpiar el buffer del scanner antes de leer Strings
        System.out.print("  Ingrese nombre a buscar: ");
        String busqueda = sc.nextLine();

        File f = new File(ARCHIVO);
        if (!f.exists()) {
            System.out.println("  [INFO] No hay contactos registrados.");
            return;
        }

        BufferedReader br = new BufferedReader(new FileReader(ARCHIVO));
        String linea;
        boolean encontrado = false;

        System.out.println("\n  ======== RESULTADOS ========");

        while ((linea = br.readLine()) != null) {
            if (linea.trim().isEmpty()) continue;
            Ej4Contacto c = Ej4Contacto.fromArchivo(linea);
            if (c.getNombre().toLowerCase().contains(busqueda.toLowerCase())) {
                c.mostrarContacto();
                encontrado = true;
            }
        }
        br.close();

        if (!encontrado) {
            System.out.println("  [INFO] No se encontró ningún contacto con ese nombre.");
        }
    }

    //  Método principal – Menú interactivo
    public static void main(String[] args) {
        System.out.println("============================================");
        System.out.println("   Agenda Telefonica Java (APE05 Ej.4)   ");
        System.out.println("============================================");

        int opcion;
        do {
            System.out.println("\n  MENU PRINCIPAL");
            System.out.println("  1. Agregar contacto");
            System.out.println("  2. Mostrar contactos");
            System.out.println("  3. Buscar contacto");
            System.out.println("  4. Salir");
            System.out.print("  Opcion: ");
            
            while (!sc.hasNextInt()) {
                System.out.println("  [ERROR] Debe ingresar un numero.");
                System.out.print("  Opcion: ");
                sc.next();
            }
            opcion = sc.nextInt();

            try {
                switch (opcion) {
                    case 1: agregarContacto(); break;
                    case 2: mostrarContactos(); break;
                    case 3: buscarContacto();   break;
                    case 4: System.out.println("  Hasta luego."); break;
                    default: System.out.println("  [ERROR] Opción no valida.");
                }
            } catch (IOException e) {
                System.out.println("  [ERROR] Problema con el archivo: " + e.getMessage());
            }

        } while (opcion != 4);

        sc.close();
    }
}
