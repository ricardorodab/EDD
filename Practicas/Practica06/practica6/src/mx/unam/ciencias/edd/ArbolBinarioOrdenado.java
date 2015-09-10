package mx.unam.ciencias.edd;

import java.util.Iterator;

/**
 * <p>Clase para árboles binarios ordenados. Los árboles son
 * genéricos, pero acotados a la interfaz {@link Comparable}.</p>
 *
 * <p>Un árbol instancia de esta clase siempre cumple que:</p>
 * <ul>
 *   <li>Cualquier elemento en el árbol es mayor o igual que todos
 *       sus descendientes por la izquierda.</li>
 *   <li>Cualquier elemento en el árbol es menor o igual que todos
 *       sus descendientes por la derecha.</li>
 * </ul>
 */
public class ArbolBinarioOrdenado<T extends Comparable<T>>
    extends ArbolBinario<T> {

    /* Clase privada para iteradores de árboles binarios
     * ordenados. */
    private class Iterador<T> implements Iterator<T> {

        /* Pila para emular la pila de ejecución. */
        private Pila<ArbolBinario<T>.Vertice<T>> pila;

        /* Construye un iterador con el vértice recibido. */
        public Iterador(ArbolBinario<T>.Vertice<T> vertice) {
	    this.pila = new Pila<ArbolBinario<T>.Vertice<T>>();
	    Pila<ArbolBinario<T>.Vertice<T>> metedora = new Pila<ArbolBinario<T>.Vertice<T>>();
	    ArbolBinario<T>.Vertice<T> actual = vertice;
	    while(!metedora.esVacia() || actual != null){
		if(actual != null){
		    metedora.mete(actual);
		    actual = actual.derecho;		
		}else{
		    actual = metedora.saca();
		    pila.mete(actual);
		    actual = actual.izquierdo;
		}
	    }
        }

        /* Nos dice si hay un siguiente elemento. */
        @Override public boolean hasNext() {
            return !pila.esVacia();
        }

        /* Regresa el siguiente elemento del árbol en orden. */
        @Override public T next() {
            if(this.hasNext()){
		return pila.saca().get();
	    }
	    return null;
        }

        /* No lo implementamos: siempre lanza una excepción. */
        @Override public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    /**
     * Constructor sin parámetros. Sencillamente ejecuta el
     * constructor sin parámetros de {@link ArbolBinario}.
     */
    public ArbolBinarioOrdenado() { super(); }

    /**
     * Construye un árbol binario ordenado a partir de un árbol
     * binario. El árbol binario ordenado tiene los mismos elementos
     * que el árbol recibido, pero ordenados.
     * @param arbol el árbol binario a partir del cuál creamos el
     *        árbol binario ordenado.
     */
    public ArbolBinarioOrdenado(ArbolBinario<T> arbol) {
        Cola<Vertice<T>> metedora = new Cola<Vertice<T>>();
	metedora.mete(arbol.raiz);
	Vertice<T> actual;
	while(!metedora.esVacia()){
	    actual = metedora.saca();
	    this.agrega(actual.get());
	    if(actual.hayIzquierdo())
		metedora.mete(actual.izquierdo);
	    if(actual.hayDerecho())
		metedora.mete(actual.derecho);
	}
    }
    
    /**
     * Agrega un nuevo elemento al árbol. El árbol conserva su orden
     * in-order.
     * @param elemento el elemento a agregar.
     * @return un iterador que apunta al vértice del nuevo elemento.
     */
    @Override public VerticeArbolBinario<T> agrega(T elemento) {
	Vertice<T> agregado = new Vertice<T>(elemento);
	Vertice<T> actual = this.raiz;
	if(this.getElementos()==0){
	    this.raiz = agregado;
	    this.elementos++;
	    return agregado;
	}else{
	    this.elementos++;
	    while(actual != null){
		//System.out.println(actual.elemento != null);
		if(elemento.compareTo(actual.elemento)<=0){
		    if(!actual.hayIzquierdo()){
			actual.izquierdo = agregado;
			agregado.padre= actual;
			return agregado;
		    }else{
			actual = actual.izquierdo;
		    }
		}else{
		    if(!actual.hayDerecho()){
			actual.derecho = agregado;
			agregado.padre = actual;
			return agregado;
		    }else{
			actual = actual.derecho;
		    }
		}
	    }
	}	
	return agregado;
    }
    
    /**
     * Elimina un elemento. Si el elemento no está en el árbol, no
     * hace nada; si está varias veces, elimina el primero que
     * encuentre (in-order). El árbol conserva su orden in-order.
     * @param elemento el elemento a eliminar.
     */
        @Override public void elimina(T elemento) {
	    if(this.getElementos() == 1){
		if(this.raiz.get().equals(elemento)){
		    this.raiz = null;
		    this.elementos--;
		}	
		return;
	    }
	    if(this.getElementos() == 0)
		return;
	    VerticeArbolBinario<T> e = this.busca(elemento);
	    if(e != null){
		Vertice<T> eliminado = this.vertice(e);
		if(eliminado.hayIzquierdo()){
		    Vertice<T> anterior = this.buscaVerticeAnterior(eliminado);
		    eliminado.elemento = anterior.get();
		    if(anterior.equals(anterior.padre.derecho)){
			anterior.padre.derecho= anterior.izquierdo;
		    }else{
			anterior.padre.izquierdo = anterior.izquierdo;
		    }
		    if(anterior.hayIzquierdo()){
			anterior.izquierdo.padre = anterior.padre;
		    }
		    this.elementos--;
		}else if(eliminado.hayDerecho()){
		    if(eliminado.equals(this.raiz)){
			eliminado.derecho.padre = null;
			this.raiz = eliminado.derecho;
			this.elementos--;
		    }else{
			if(eliminado.equals(eliminado.padre.derecho)){
			    eliminado.padre.derecho = eliminado.derecho;
			    eliminado.derecho.padre = eliminado.padre;
			    this.elementos--;
			}else{
			    eliminado.padre.izquierdo = eliminado.derecho;
			    eliminado.derecho.padre = eliminado.padre;
			    this.elementos--;
			}
		    }
		}else{
		    if(eliminado.equals(eliminado.padre.izquierdo)){
			eliminado.padre.izquierdo = null;
			this.elementos--;
		    }else{
			eliminado.padre.derecho = null;
			this.elementos--;
		    }
		}
	    }    
	}
	
     /**
     * Busca un elemento en el árbol recorriéndolo in-order. Si lo
     * encuentra, regresa un iterador que apunta a dicho elemento;
     * si no, regresa <tt>null</tt>.
     * @param elemento el elemento a buscar.
     * @return un iterador que apunta al elemento buscado si lo
     *         encuentra; <tt>null</tt> en otro caso.
     */
    @Override public VerticeArbolBinario<T> busca(T elemento) {
	if(this.getElementos() < 1){
	    return null;
	}
	Vertice<T> actual = this.raiz;
	T eleactual;
	while(actual != null){
	    eleactual = actual.elemento;
	    if(elemento.compareTo(eleactual)<0){
		actual = actual.izquierdo;
	    }else if(elemento.equals(eleactual)){
		return actual;
	    }else{
		actual = actual.derecho;
	    }
	}
	return null;
    }
    
    
    /**
     * Regresa el vertice anterior (en in-order) al vertice que recibe.
     * @param vertice el vertice del que queremos encontrar el anterior.
     * @return el vertice anterior (en in-order) al vertice que recibe.
     */
    protected Vertice<T> buscaVerticeAnterior(Vertice<T> vertice) {
	if(vertice.hayIzquierdo()){
	    Vertice<T> actual = vertice.izquierdo;
	    while(actual != null){
		if(!actual.hayDerecho())
		    return actual;
		actual = actual.derecho;
	    }
	}
	return null;	   
    }
	
    /**
     * Regresa un iterador para iterar el árbol. El árbol se itera
     * en orden.
     * @return un iterador para iterar el árbol.
     */
    @Override public Iterator<T> iterator() {
	if(this.getElementos() > 0){
        return new Iterador<T>(raiz);
	}else{
	    return null;
	}
    }
    
    /**
     * Gira el árbol a la derecha sobre el vértice recibido. Si el
     * vértice no tiene hijo izquierdo, el método no hace nada.
     * @param vertice el vértice sobre el que vamos a girar.
     */
    public void giraDerecha(VerticeArbolBinario<T> vertice) {
        Vertice<T> v = vertice(vertice);
        giraDerecha(v);
    }

    /**
     * Gira el árbol a la derecha sobre el vértice recibido. Si el
     * vértice no tiene hijo izquierdo, el método no hace nada.
     * @param vertice el vértice sobre el que vamos a girar.
     */
    protected void giraDerecha(Vertice<T> vertice) {
       if(!vertice.hayIzquierdo())
	    return;
	Vertice<T> q = vertice.izquierdo;
	if(vertice.hayPadre()){
	    q.padre = vertice.padre;
	    if(vertice.padre.derecho == vertice)
		vertice.padre.derecho = q;
	    else
		vertice.padre.izquierdo = q;
	}else{
	    this.raiz = q;
	    q.padre = null;
	}
	vertice.izquierdo = q.derecho;
	if(q.hayDerecho())
	    q.derecho.padre = vertice;
	q.derecho = vertice;
	vertice.padre = q;
    }
    
    /**
     * Gira el árbol a la izquierda sobre el vértice recibido. Si el
     * vértice no tiene hijo derecho, el método no hace nada.
     * @param vertice el vértice sobre el que vamos a girar.
     */
    public void giraIzquierda(VerticeArbolBinario<T> vertice) {
        Vertice<T> v = vertice(vertice);
        giraIzquierda(v);
    }

    /**
     * Gira el árbol a la izquierda sobre el vértice recibido. Si el
     * vértice no tiene hijo derecho, el método no hace nada.
     * @param vertice el vértice sobre el que vamos a girar.
     */
    protected void giraIzquierda(Vertice<T> vertice) {
	if(!vertice.hayDerecho())
	    return;
	Vertice<T> q = vertice.derecho;
	q.padre = vertice.padre;
	if(vertice.hayPadre()){
	    if(vertice.padre.izquierdo == vertice)
		vertice.padre.izquierdo = q;
	    else
		vertice.padre.derecho = q;
	}else{
	    this.raiz = q;
	}
	vertice.derecho = q.izquierdo;
	if(q.hayIzquierdo())
	    q.izquierdo.padre = vertice;
	q.izquierdo = vertice;
	vertice.padre = q; 
    }
}
