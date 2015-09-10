package mx.unam.ciencias.edd;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Clase para gráficas. Una gráfica es un conjunto de vértices y
 * aristas, tales que las aristas son un subconjunto del producto
 * cruz de los vértices.
 */
public class Grafica<T> implements Iterable<T> {

    /* Clase privada para iteradores de gráficas. */
    private class Iterador<T> implements Iterator<T> {

        /* Iterador auxiliar. */
        private Iterator<Grafica<T>.Vertice<T>> iterador;

        /* Construye un nuevo iterador, auxiliándose de la lista de
         * vértices. */
        public Iterador(Grafica<T> grafica) {
	    this.iterador = grafica.vertices.iterator();
        }

        /* Nos dice si hay un siguiente elemento. */
        public boolean hasNext() {
	    return iterador.hasNext();
        }

        /* Regresa el siguiente elemento. */
        public T next() {
	    return iterador.next().elemento;
        }

        /* No lo implementamos: siempre lanza una excepción. */
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    /* Vertices para gráficas; implementan la interfaz
     * VerticeGrafica */
    private class Vertice<T> implements VerticeGrafica<T> {

        public T elemento;
        public Color color;
        public Lista<Grafica<T>.Vertice<T>> vecinos;
        public IteradorLista<Grafica<T>.Vertice<T>> iterador;

        /* Crea un nuevo vértice a partir de un elemento. */
        public Vertice(T elemento) {
	    this.elemento = elemento;
	    this.color = Color.NINGUNO;
	    vecinos = new Lista<Grafica<T>.Vertice<T>>();
	    iterador = vecinos.iteradorLista(); 
        }

        /* Crea un nuevo iterador para los vecinos, si no existe, o
         * lo mueve al inico. */
        public void inicio() {
		iterador = vecinos.iteradorLista();
        }

        /* Hay un vecino si el iterador tiene un siguiente. */
        public boolean hayVecino() {
	    if(iterador == null || iterador.hasNext() == false)
		return false;
	    return true;
        }

        /* Regresa el siguiente vecino. */
        public VerticeGrafica<T> vecino() {
	    return iterador.next();
        }

        /* Regresa el elemento del vértice. */
        public T getElemento() {
	    return this.elemento;
        }

        /* Regresa el grado del vértice. */
        public int getGrado() { 
	    return vecinos.getLongitud();
       }

        /* Regresa el color del vértice. */
        public Color getColor() {
	    return this.color;
        }

        /* Define el color del vértice. */
        public void setColor(Color color) {
            this.color = color;
        }
    }

    /* Vértices. */
    private Lista<Vertice<T>> vertices;
    /* Número de aristas. */
    private int aristas;

    /**
     * Constructor único.
     */
    public Grafica() {
	this.vertices = new Lista<Vertice<T>>();
	this.aristas = 0;
    }

    /**
     *
     */
    protected Lista<Vertice<T>> listaVertices(){
	return this.vertices;
    }
    /**
     * Regresa el número de vértices.
     * @return el número de vértices.
     */
    public int getVertices() {
	return vertices.getLongitud();
    }

    /**
     * Regresa el número de aristas.
     * @return el número de aristas.
     */
    public int getAristas() {
	return aristas;
    }

    /* Método auxiliar para buscar vértices. */
    private Vertice<T> buscaVertice(T elemento) {
	for(int i = 0; i < vertices.getLongitud(); i++){
	    Vertice<T> buscaVer = vertices.get(i);
	    if(buscaVer.elemento.equals(elemento))
		return buscaVer;
	}
	return null;
    }

    /**
     * Agrega un nuevo elemento a la gráfica.
     * @param elemento el elemento a agregar.
     * @throws IllegalArgumentException si el elemento ya había sido
     *         agregado a la gráfica.
     */
    public void agrega(T elemento) {
	Vertice<T> vert = buscaVertice(elemento);
	if(vert == null)
	    vertices.agregaFinal(new Vertice<T>(elemento));
	else
	    throw new IllegalArgumentException();	
    }

    /**
     * Conecta dos elementos de la gráfica. Los elementos deben
     * estar en la gráfica.
     * @param a el primer elemento a conectar.
     * @param b el segundo elemento a conectar.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     * @throws IllegalArgumentException si a o b ya están
     *         conectados, o si a es igual a b.
     */
    public void conecta(T a, T b) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else if((verticeA.vecinos.contiene(verticeB) && verticeB.vecinos.contiene(verticeA))
		|| verticeA == verticeB)
	    throw new IllegalArgumentException();
	else{
	    verticeA.vecinos.agregaFinal(verticeB);
	    verticeB.vecinos.agregaFinal(verticeA);
	    verticeA.inicio();
	    verticeB.inicio();
	    aristas++;
	}
    }

    /**
     * Desconecta dos elementos de la gráfica. Los elementos deben
     * estar en la gráfica y estar conectados entre ellos.
     * @param a el primer elemento a desconectar.
     * @param b el segundo elemento a desconectar.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     * @throws IllegalArgumentException si a o b no están
     *         conectados.
     */
    public void desconecta(T a, T b) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else if(!(verticeA.vecinos.contiene(verticeB) && verticeB.vecinos.contiene(verticeA)))
	    throw new IllegalArgumentException();
	else{
	    verticeA.vecinos.elimina(verticeB);
	    verticeB.vecinos.elimina(verticeA);
	    verticeA.inicio();
	    verticeB.inicio();
	    aristas--;
	}
    }

    /**
     * Nos dice si el elemento está contenido en la gráfica.
     * @return <tt>true</tt> si el elemento está contenido en la
     *         gráfica, <tt>false</tt> en otro caso.
     */
    public boolean contiene(T elemento) {
	for(int i = 0; i < vertices.getLongitud(); i++){
	    Vertice<T> verticeC = vertices.get(i);
	    if(verticeC.elemento.equals(elemento))
		return true;
	}
	return false;
    }

    /**
     * Elimina un elemento de la gráfica. El elemento tiene que
     * estar contenido en la gráfica.
     * @param elemento el elemento a eliminar.
     * @throws NoSuchElementException si el elemento no está
     *         contenido en la gráfica.
     */
    public void elimina(T elemento) {
	Vertice<T> vertice = buscaVertice(elemento);        
	if(vertice == null)
	    throw new NoSuchElementException();
	else{
	    for(Vertice<T> ver : vertice.vecinos){
		ver.vecinos.elimina(vertice);
		ver.inicio();
		aristas--;
	    }
	    vertices.elimina(vertice);
	}
    }

    /**
     * Nos dice si dos elementos de la gráfica están conectados. Los
     * elementos deben estar en la gráfica.
     * @param a el primer elemento.
     * @param b el segundo elemento.
     * @return <tt>true</tt> si a y b son vecinos, <tt>false</tt> en
     *         otro caso.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     */
    public boolean sonVecinos(T a, T b) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else{
	    if(verticeA.vecinos.contiene(verticeB) && verticeB.vecinos.contiene(verticeA))
		return true;
	    return false;
	}
    }
    
    /**
     * Regresa el vértice correspondiente el elemento recibido.
     * @throws NoSuchElementException si elemento no es elemento de
     *         la gráfica.
     * @return el vértice correspondiente el elemento recibido.
     */
    public VerticeGrafica<T> vertice(T elemento) {
	return buscaVertice(elemento);
    }

    /**
     * Realiza la acción recibida en cada uno de los vértices de la
     * gráfica, en el orden en que fueron agregados.
     * @param accion la acción a realizar.
     */
    public void paraCadaVertice(AccionVerticeGrafica<T> accion) {
	for(Vertice<T> ver : vertices){
	    accion.actua(ver);
	}
    }


    /**
     * Realiza la acción recibida en todos los vértices de la
     * gráfica, en el orden determinado por BFS, comenzando por el
     * vértice correspondiente al elemento recibido. Al terminar el
     * método, todos los vértices tendrán color {@link
     * Color#NINGUNO}.
     * @param elemento el elemento sobre cuyo vértice queremos
     *        comenzar el recorrido.
     * @param accion la acción a realizar.
     * @throws NoSuchElementException si el elemento no está en la
     *         gráfica.
     */
    public void bfs(T elemento, AccionVerticeGrafica<T> accion) {
	Vertice<T> raiz = buscaVertice(elemento);       
	if(raiz == null)
	    throw new NoSuchElementException();
	else{
	    Cola<Grafica<T>.Vertice<T>> cola = new Cola<Grafica<T>.Vertice<T>>();
	    raiz.setColor(Color.ROJO);
	    cola.mete(raiz);
	    while(!cola.esVacia()){
		Vertice<T> temp = cola.saca();
		accion.actua(temp);
		for(Vertice<T> ver : temp.vecinos){
		    if(ver.color != Color.ROJO){
			ver.color = Color.ROJO;
			cola.mete(ver);
		    }	
		}
		if(cola.esVacia()){
		    for(int i = 0; i < vertices.getLongitud(); i++){
			temp = vertices.get(i);
			if(temp.color != Color.ROJO){
			    for(Vertice<T> ver : temp.vecinos){
				if(ver.color != Color.ROJO){
				    ver.color = Color.ROJO;
				    cola.mete(ver);
				}	
			    }   
			}
		    }
		}
	    }
	    for(Vertice<T> ver : vertices){
		ver.setColor(Color.NINGUNO);
		ver.inicio(); 
	    }
	    raiz.inicio();
	}
	// Aquí va su código.
    }

    /**
     * Realiza la acción recibida en todos los vértices de la
     * gráfica, en el orden determinado por DFS, comenzando por el
     * vértice correspondiente al elemento recibido. Al terminar el
     * método, todos los vértices tendrán color {@link
     * Color#NINGUNO}.
     * @param elemento el elemento sobre cuyo vértice queremos
     *        comenzar el recorrido.
     * @param accion la acción a realizar.
     * @throws NoSuchElementException si el elemento no está en la
     *         gráfica.
     */
    public void dfs(T elemento, AccionVerticeGrafica<T> accion) {
	Vertice<T> raiz = buscaVertice(elemento);       
	if(raiz == null)
	    throw new NoSuchElementException();
	else{
	    Pila<Grafica<T>.Vertice<T>> pila = new Pila<Grafica<T>.Vertice<T>>();
	    raiz.setColor(Color.ROJO);
	    pila.mete(raiz);
	    while(!pila.esVacia()){
		Vertice<T> temp = pila.saca();
		accion.actua(temp);
		for(Vertice<T> ver : temp.vecinos){
		    if(ver.color != Color.ROJO){
			ver.color = Color.ROJO;
			pila.mete(ver);
		    }	
		}
		if(pila.esVacia()){
		    for(int i = 0; i < vertices.getLongitud(); i++){
			temp = vertices.get(i);
			if(temp.color != Color.ROJO){
			    for(Vertice<T> ver : temp.vecinos){
				if(ver.color != Color.ROJO){
				    ver.color = Color.ROJO;
				    pila.mete(ver);
				}	
			    }   
			}
		    }
		}
	    }
	    for(Vertice<T> ver : vertices){
		ver.setColor(Color.NINGUNO);
		ver.inicio();
	    }
	    raiz.inicio();
	}
    }

    /**
     * Regresa un iterador para iterar la gráfica. La gráfica se
     * itera en el orden en que fueron agregados sus elementos.
     * @return un iterador para iterar el árbol.
     */
    @Override public Iterator<T> iterator() {
	Iterator<T> i = new Iterador<T>(this);
	return i;
    }
}
