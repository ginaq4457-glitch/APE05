public class Ej4Contacto {

    // Atributos privados
    private String nombre;
    private String telefono;
    private String correo;

    // Constructor por defecto
    public Ej4Contacto() {
        this.nombre   = "";
        this.telefono = "";
        this.correo   = "";
    }

    // Constructor con parámetros
    public Ej4Contacto(String nombre, String telefono, String correo) {
        this.nombre   = nombre;
        this.telefono = telefono;
        this.correo   = correo;
    }

    // Métodos GET
    public String getNombre()   { return nombre;   }
    public String getTelefono() { return telefono; }
    public String getCorreo()   { return correo;   }

    // Métodos SET
    public void setNombre(String nombre)     { this.nombre   = nombre;   }
    public void setTelefono(String telefono) { this.telefono = telefono; }
    public void setCorreo(String correo)     { this.correo   = correo;   }

    // Mostrar información del contacto
    public void mostrarContacto() {
        System.out.println("  ----------------------------------------");
        System.out.printf("  Nombre   : %s%n", nombre);
        System.out.printf("  Telefono : %s%n", telefono);
        System.out.printf("  Correo   : %s%n", correo);
        System.out.println("  ----------------------------------------");
    }

    // Convertir a cadena para guardar en archivo (separador '|')
    public String toArchivo() {
        return nombre + "|" + telefono + "|" + correo;
    }

    // Crear un Contacto desde una línea del archivo
    public static Ej4Contacto fromArchivo(String linea) {
        String[] partes = linea.split("\\|");
        if (partes.length == 3) {
            return new Ej4Contacto(partes[0], partes[1], partes[2]);
        }
        return new Ej4Contacto();
    }
}