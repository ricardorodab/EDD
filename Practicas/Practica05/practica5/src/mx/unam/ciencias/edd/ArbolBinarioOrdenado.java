/* -------------------------------------------------------------------
 * ArbolBinarioOrdenado.java
 * versión 2.0
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
 * @version 2.0
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
	    return pila.saca().get();
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
	ArbolBinario<T>.Vertice<T> v = this.raiz;
	Pila<ArbolBinario<T>.Vertice<T>> pila = new Pila<ArbolBinario<T>.Vertice<T>>();
	boolean esto = false;
	while(!esto){
	    if(v != null){
		pila.mete(v);
		v = v.izquierdo;
	    }else{
		if(pila.esVacia()){
		    esto = true;
		}else{
		    v = pila.saca();
		    if(v.elemento.compareTo(elemento) == 0)
			break;
		    v = v.derecho;
		}
	    }
	}
	if(v.elemento.compareTo(elemento) == 0){
	    ArbolBinario<T>.Vertice<T> temp = v;
	    while(true){
		if(temp.hayIzquierdo()){
		    temp = temp.izquierdo;
		    if(!temp.hayDerecho()){
			if(temp.hayIzquierdo()){
			    v.elemento = temp.get();
			    temp.elemento = elemento;
			    v = temp;
			    continue;
			}
	    		v.elemento = temp.get();
			temp.elemento = elemento;
			temp.padre.izquierdo = null;
			temp.padre = null;
			elementos--;
			break;
		    }else{
			while(temp.derecho != null){
			    temp = temp.derecho;
			}
			v.elemento = temp.get();
			temp.elemento = elemento;
			temp.padre.derecho = null;
			if(temp.hayIzquierdo()){
			    temp.izquierdo.padre = temp.padre;
			    temp.padre.derecho = temp.izquierdo;
			    temp.izquierdo = null;
			}
			temp.padre = null;
			elementos--;
			break;
		    }
		} else if(temp.hayDerecho()){
		    temp = temp.derecho;
		    if(!temp.hayIzquierdo()){
			if(temp.hayDerecho()){
			    v.elemento = temp.get();
			    temp.elemento = elemento;
			    v = temp;
			    continue;
			}
			v.elemento = temp.get();
			temp.elemento = elemento;
			temp.padre.derecho = null;
			temp.padre = null;
			elementos--;
			break;
		    }else{
			while(temp.izquierdo != null){
			    temp = temp.izquierdo;
			}
			v.elemento = temp.get();
			temp.elemento = elemento;
			temp.padre.izquierdo = null;
			if(temp.hayDerecho()){
			    temp.derecho.padre = temp.padre;
			    temp.padre.izquierdo = temp.derecho;
			    temp.derecho = null;
			}
			temp.padre = null;
			elementos--;
			break;
		    }
		}else{
		    if(temp == this.raiz){
			this.raiz = null;
			elementos--;		    
			break;
		    }else{
			if(v.padre.izquierdo == v){
			    v.padre.izquierdo = null;
			    v.padre = null;
			    elementos--;
			    break;
			}else{
			    v.padre.derecho = null;
			    v.padre = null;
			    elementos--;
			    break;
			}
		    }
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
	ArbolBinario<T>.Vertice<T> temp = this.raiz;	 
	Pila<ArbolBinario<T>.Vertice<T>> pila2 = new Pila<ArbolBinario<T>.Vertice<T>>();
	boolean esto = false;
	while(!esto){
	    if(temp != null){
		pila2.mete(temp);
		temp = temp.izquierdo;
	    }else{
		if(pila2.esVacia()){
		    esto = true;
		}else{
		    temp = pila2.saca();
		    if(temp.elemento.compareTo(elemento) == 0)
			return temp;
		    temp = temp.derecho;
		}
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
	Pila<ArbolBinario<T>.Vertice<T>> pila = new Pila<ArbolBinario<T>.Vertice<T>>();
	ArbolBinario<T>.Vertice<T> temp = this.raiz;	 
	Pila<ArbolBinario<T>.Vertice<T>> pila2 = new Pila<ArbolBinario<T>.Vertice<T>>();
	Pila<ArbolBinario<T>.Vertice<T>> pilat = new Pila<ArbolBinario<T>.Vertice<T>>();
	boolean listo = false;
	while(!listo){
	    if(temp != null){
		pila2.mete(temp);
		temp = temp.izquierdo;
	    }else{
		if(pila2.esVacia()){
		    listo = true;
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
	while(!pila.esVacia()){
	    temp = pila.saca();
	    if(temp.get().compareTo(vertice.elemento) <= 0 && 
	       pila.mira() == vertice)
		return temp;
	}
	return null;
    }
    
    /**
     * Regresa un iterador para iterar el árbol. El árbol se itera
     * en orden.
     * @return un iterador para iterar el árbol.
     */
    @Override public Iterator<T> iterator() {
        return new Iterador<T>(this.raiz);
    }
} //Fin de ArbolBinarioOrdenado.java
