package mx.unam.ciencias.edd;

/**
 * Interfaz para vértices de gráfica. Un vértice de gráfica puede
 * darnos el elemento en el vértice, recorrer sus vecinos, decirnos
 * el grado del vértice, y obtener o cambiar su color.
 */
public interface VerticeGrafica<T> {

    /**
     * Regresa al inicio de todos los vecinos del vértice. Después
     * de llamar este método, el método {@link VerticeGrafica#vecino} siempre
     * regresa el primer vecino, si el vértice tiene vecinos.
     */
    public void inicio();

    /**
     * Nos dice si todavía hay un vecino para recorrer.
     * @return <tt>true</tt> si todavía hay vecinos del vértice,
     *         <tt>false</tt> en otro caso.
     */
    public boolean hayVecino();

    /**
     * Regresa el siguiente vecino del vértice.
     * @return el siguiente vecino del vértice.
     * @throws NoSuchElementException si ya no hay vecinos por
     *         recorrer.
     */
    public VerticeGrafica<T> vecino();

    /**
     * Regresa el elemento del vértice.
     * @return el elemento del vértice.
     */
    public T getElemento();

    /**
     * Regresa el grado del vértice.
     * @return el grado del vértice.
     */
    public int getGrado();

    /**
     * Regresa el color del vértice.
     * @return el color del vértice.
     */
    public Color getColor();

    /**
     * Define el color del vértice.
     * @param color el nuevo color del vértice.
     */
    public void setColor(Color color);
}
