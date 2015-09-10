/* -------------------------------------------------------------------
 * ArbolBinarioOrdenado.java
 * versión 5.0
 * Copyright (C) 2014  José Ricardo Rodríguez Abreu.
 * Facultad de Ciencias,
 * Universidad Nacional Autónoma de México, Mexico.
 *
 * Este programa es software libre; se puede redistribuir
 * y/o modificar en los términos establecidos por la
 * Licencia Pública General de GNU tal como fue publicada
 * por la Free Software Foundation en la versión 2 o
 * superior.
 *
 * Este programa es distribuido con la esperanza de que
 * resulte de utilidad, pero SIN GARANTÍA ALGUNA; de hecho
 * sin la garantía implícita de COMERCIALIZACIÓN o
 * ADECUACIÓN PARA PROPÓSITOS PARTICULARES. Véase la
 * Licencia Pública General de GNU para mayores detalles.
 *
 * Con este programa se debe haber recibido una copia de la
 * Licencia Pública General de GNU, de no ser así, visite el
 * siguiente URL:
 * http://www.gnu.org/licenses/gpl.html
 * o escriba a la Free Software Foundation Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * -------------------------------------------------------------------
 */
package mx.unam.ciencias.edd;

import java.util.Iterator;

/**
 * @autor Jose Ricardo Rodriguez Abreu
 * @version 3.0
 * @since Mar 11 2014
 
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
	    pila = new Pila<ArbolBinario<T>.Vertice<T>>();
	    ArbolBinario<T>.Vertice<T> temp = vertice;	 
	    Pila<ArbolBinario<T>.Vertice<T>> pila2 = new Pila<ArbolBinario<T>.Vertice<T>>();
	    Pila<ArbolBinario<T>.Vertice<T>> pilat = new Pila<ArbolBinario<T>.Vertice<T>>();
	    boolean done = false;
	    while(!done){
		if(temp != null){
		    pila2.mete(temp);
		    temp = temp.izquierdo;
		}else{
		    if(pila2.esVacia()){
			done = true;
		    }else{
			temp = pila2.saca();
			pilat.mete(temp);
			temp = temp.derecho;
		    }
		}
	    }
	    while(!pilat.esVacia()){
		pila.mete(pilat.saca());
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
	if(arbol.raiz != null){
	    Pila<ArbolBinario<T>.Vertice<T>> pila = new Pila<ArbolBinario<T>.Vertice<T>>();
	    Cola<ArbolBinario<T>.Vertice<T>> cola = new Cola<ArbolBinario<T>.Vertice<T>>();
	    cola.mete(arbol.raiz);
	    while(!cola.esVacia()){
		ArbolBinario<T>.Vertice<T> temp = cola.saca();
		pila.mete(temp);
		if(temp.hayIzquierdo())
		    cola.mete(temp.izquierdo);
		if(temp.hayDerecho())
		    cola.mete(temp.derecho);
	    }
	    while(!pila.esVacia()){
		ArbolBinario<T>.Vertice<T> compara = arbol.raiz;
		ArbolBinario<T>.Vertice<T> v = pila.saca();
		if(v == compara)
		    break;
		while(true){
		    if(v.get().compareTo(compara.get()) <= 0){
			if(compara.hayIzquierdo()){
			    compara = compara.izquierdo;
			} else { 
			    compara.izquierdo = v;
			    v.padre = compara;
			    break;
			}
		    } else if(v.get().compareTo(compara.get()) > 0) {
			if(compara.hayDerecho()){
			    compara = compara.derecho;
			}else{
			    compara.derecho = v;
			    v.padre = compara;
			    break;
			}
		    }
		}
	    }
	}    
    }
    
    /**
     * Agrega un nuevo elemento al árbol. El árbol conserva su orden
     * in-order.
     * @param elemento el elemento a agregar.
     * @return un iterador que apunta al vértice del nuevo elemento.
     */
    @Override public VerticeArbolBinario<T> agrega(T elemento) {
	ArbolBinario<T>.Vertice<T> v = new ArbolBinario<T>.Vertice<T>(elemento);
	if(this.raiz == null){
	    this.raiz = v;
	    this.elementos++;
	    return this.raiz;
	}else{
	    ArbolBinario<T>.Vertice<T> compara = this.raiz; 
	    while(true){
		if(v.get().compareTo(compara.get()) <= 0){
		    if(compara.hayIzquierdo()){
			compara = compara.izquierdo;
		    } else { 
			compara.izquierdo = v;
			v.padre = compara;
			this.elementos++;
			return v;
		    }
		} else if(v.get().compareTo(compara.get()) > 0) {
		    if(compara.hayDerecho()){
			compara = compara.derecho;
		    }else{
			compara.derecho = v;
			v.padre = compara;
			this.elementos++;
			return v;
		    }
		}
	    }
	}
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
	Vertice<T> v1 = this.raiz;
	T t1;
	while(v1 != null){
	    t1 = v1.elemento;
	    if(elemento.compareTo(t1)<0){
		v1 = v1.izquierdo;
	    }else if(elemento.equals(t1)){
		return v1;
	    }else{
		v1 = v1.derecho;
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
	    Vertice<T> v1 = vertice.izquierdo;
	    while(v1 != null){
		if(!v1.hayDerecho())
		    return v1;
		v1 = v1.derecho;
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
	if(vertice.izquierdo != null){
	    if(vertice.padre != null){
		if(vertice.padre.izquierdo == vertice)
		    vertice.padre.izquierdo = vertice.izquierdo;
		else
		    vertice.padre.derecho = vertice.izquierdo;
	    
	    vertice.izquierdo.padre = vertice.padre;
	    }else{
		this.raiz = vertice.izquierdo;
		vertice.izquierdo.padre = null;
	    }
	    vertice.padre = vertice.izquierdo;
	    if(vertice.izquierdo.derecho != null){
		vertice.izquierdo = vertice.padre.derecho;
		vertice.izquierdo.padre = vertice;
	    }else
		vertice.izquierdo = null;	    
	    
	    vertice.padre.derecho = vertice;
	}
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
	if(vertice.derecho != null){
	    if(vertice.padre != null){
		if(vertice.padre.izquierdo == vertice)
		    vertice.padre.izquierdo = vertice.derecho;
		else
		    vertice.padre.derecho = vertice.derecho;
	    vertice.derecho.padre = vertice.padre;
	    }else{
		this.raiz = vertice.derecho;
		vertice.derecho.padre = null;
	    }
	    vertice.padre = vertice.derecho;
	    if(vertice.derecho.izquierdo != null){
		vertice.derecho = vertice.padre.izquierdo;
		vertice.derecho.padre = vertice;
	    }else
		vertice.derecho = null;
	    vertice.padre.izquierdo = vertice;
	}
    }
} //Fin de ArbolBinarioOrdenado.java
