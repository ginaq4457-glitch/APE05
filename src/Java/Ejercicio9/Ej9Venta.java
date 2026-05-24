public class Ej9Venta {

    // Atributos privados
    private String producto;
    private int    cantidad;
    private double precio;
    private double total;

    // Constructor por defecto
    public Ej9Venta() {
        this.producto = "";
        this.cantidad = 0;
        this.precio   = 0.0;
        this.total    = 0.0;
    }

    // Constructor con parámetros
    public Ej9Venta(String producto, int cantidad, double precio) {
        this.producto = producto;
        this.cantidad = cantidad;
        this.precio   = precio;
        calcularTotal();
    }

    // Métodos GET
    public String getProducto() { return producto; }
    public int    getCantidad() { return cantidad; }
    public double getPrecio()   { return precio;   }
    public double getTotal()    { return total;    }

    // Métodos SET
    public void setProducto(String producto) { this.producto = producto; }
    public void setCantidad(int    cantidad) { this.cantidad = cantidad; }
    public void setPrecio(double   precio)   { this.precio   = precio;   }

    // Calcular total de la venta
    public void calcularTotal() {
        this.total = this.cantidad * this.precio;
    }

    // Mostrar factura de la venta
    public void mostrarFactura() {
        System.out.println("  ----------------------------------------");
        System.out.printf("  Producto  : %s%n",   producto);
        System.out.printf("  Cantidad  : %d%n",   cantidad);
        System.out.printf("  Precio u. : $%.2f%n", precio);
        System.out.printf("  TOTAL     : $%.2f%n", total);
        System.out.println("  ----------------------------------------");
    }

    // Convertir a cadena para guardar en archivo (siempre con punto decimal)
    public String toArchivo() {
        return String.format(java.util.Locale.US, "%s|%d|%.2f|%.2f", producto, cantidad, precio, total);
    }

    // Crear una Venta desde una línea del archivo
    public static Ej9Venta fromArchivo(String linea) {
        String[] partes = linea.split("\\|");
        if (partes.length == 4) {
            String producto = partes[0];
            int    cantidad = Integer.parseInt(partes[1].trim());
            // Reemplazar coma por punto por compatibilidad con Windows
            double precio   = Double.parseDouble(partes[2].trim().replace(",", "."));
            return new Ej9Venta(producto, cantidad, precio);
        }
        return new Ej9Venta();
    }
}