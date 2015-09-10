/* -------------------------------------------------------------------
 * ArbolBinarioCompleto.java
 * versión 2.5
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
import java.util.NoSuchElementException;

/**
 * @autor Jose Ricardo Rodriguez Abreu
 * @version 2.5
 * @since Mar 5 2014
 * <p>Clase para árboles binarios completos.</p>
 *
 * <p>Un árbol binario completo agrega y elimina elementos de tal
 * forma que el árbol siempre es lo más cercano posible a estar
 * lleno.<p>
 */
public class ArbolBinarioCompleto<T> extends ArbolBinario<T> {

    /* Clase privada para iteradores de árboles binarios
     * completos. */
    private class Iterador<T> implements Iterator<T> {

	Cola<ArbolBinario<T>.Vertice<T>> cola;

        /* Constructor que recibe la raíz del árbol. */
        public Iterador(ArbolBinario<T>.Vertice<T> raiz) {
	    cola = new Cola<ArbolBinario<T>.Vertice<T>>();
	    cola.mete(raiz);
        }

        /* Nos dice si hay un elemento siguiente. */
        @Override public boolean hasNext() {
            return !cola.esVacia();
        }

        /* Regresa el elemento siguiente. */
        @Override public T next() {
            ArbolBinario<T>.Vertice<T> v = cola.saca();
	    if(v.hayIzquierdo())
		cola.mete(v.izquierdo);
	    if(v.hayDerecho())
		cola.mete(v.derecho);
	    return v.elemento;
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
    public ArbolBinarioCompleto() { super(); }

    /**
     * Agrega un elemento al árbol binario completo. El nuevo
     * elemento se coloca a la derecha del último nivel, o a la
     * izquierda de un nuevo nivel.
     * @param elemento el elemento a agregar al árbol.
     * @return un iterador que apunta al vértice del árbol que
     *         contiene el elemento.
     */
    @Override public VerticeArbolBinario<T> agrega(T elemento) {
	ArbolBinario<T>.Vertice<T> temp = new ArbolBinario<T>.Vertice<T>(elemento);
	ArbolBinario<T>.Vertice<T> temp2;
	if(this.raiz == null){
	    this.raiz = temp;
	    elementos++;
	    return this.raiz;
	}else{
	    Cola<ArbolBinario<T>.Vertice<T>> cola = new Cola<ArbolBinario<T>.Vertice<T>>();
	    cola.mete(this.raiz);
	    while(!cola.esVacia()){
		temp2 = cola.saca();
		if(temp2.hayIzquierdo()){
		    cola.mete(temp2.izquierdo);
		}else{
		    temp2.izquierdo = temp;
		    temp.padre = temp2;
		    elementos++;
		    return temp;
		}
		if(temp2.hayDerecho()){
		    cola.mete(temp2.derecho);
		}else{
		    temp2.derecho = temp;
		    temp.padre = temp2;
		    elementos++;
		    return temp;
		}
	    }
	    return temp;
	}
    }


    /**
     * Elimina un elemento del árbol. El elemento a eliminar cambia
     * lugares con el último elemento del árbol al recorrerlo por
     * BFS, y entonces es eliminado.
     * @param elemento el elemento a eliminar.
     */
    @Override public void elimina(T elemento) {
	if(raiz == null){}
	else if(raiz != null){
	    if(!raiz.hayDerecho() && !raiz.hayIzquierdo()){
		if(raiz.elemento.equals(elemento))
		    raiz = null;
	    }else{
		Cola<ArbolBinario<T>.Vertice<T>> colaFin = new Cola<ArbolBinario<T>.Vertice<T>>();
		Cola<ArbolBinario<T>.Vertice<T>> cola = new Cola<ArbolBinario<T>.Vertice<T>>();
		ArbolBinario<T>.Vertice<T> tempFin = null;
		ArbolBinario<T>.Vertice<T> temp = null;
		cola.mete(this.raiz);
		colaFin.mete(this.raiz);
		while(!colaFin.esVacia()){
		    tempFin = colaFin.saca();
		    if(tempFin.hayIzquierdo())
			colaFin.mete(tempFin.izquierdo);
		    if(tempFin.hayDerecho())
			colaFin.mete(tempFin.derecho);
		}
		while(!cola.esVacia()){
		    temp = cola.saca();
		    if(temp.elemento.equals(elemento)){
			temp.elemento = tempFin.elemento;
			tempFin.elemento = elemento;
			if(tempFin.padre.izquierdo.equals(tempFin)){
			    tempFin.padre.izquierdo = null;
			}else{
			    tempFin.padre.derecho = null;
			}
			tempFin.padre = null;
			elementos--;
			break;
		    }else{
			if(temp.hayIzquierdo())
			    cola.mete(temp.izquierdo);
			if(temp.hayDerecho())
			    cola.mete(temp.derecho);
		    }
		}	      
	    }
	}
    }

    /**
     * Regresa un iterador para iterar el árbol. El árbol se itera
     * en orden BFS.
     * @return un iterador para iterar el árbol.
     */
    @Override public Iterator<T> iterator() {
        Iterador<T> i = new Iterador<T>(this.raiz);
	return i;
    }
} //Fin de ArbolBinarioCompleto.java
