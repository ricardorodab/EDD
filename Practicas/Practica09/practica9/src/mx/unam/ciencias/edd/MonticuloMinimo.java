/* -------------------------------------------------------------------
 * MonticuloMinimo.java
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
import java.util.NoSuchElementException;

/**
 * @autor Jose Ricardo Rodriguez Abreu
 * @version 2.0
 * @since Abr 22 2014
 * Clase para montículos mínimos (<i>min heaps</i>). Podemos crear
 * un montículo mínimo con <em>n</em> elementos en tiempo
 * <em>O</em>(<em>n</em>), y podemos agregar y actualizar elementos
 * en tiempo <em>O</em>(log <em>n</em>). Eliminar el elemento mínimo
 * también nos toma tiempo <em>O</em>(log <em>n</em>).
 */
public class MonticuloMinimo<T extends ComparableIndexable<T>>
    implements Iterable<T> {

    /* Clase privada para iteradores de montículos. */
    private class Iterador<T extends ComparableIndexable<T>> implements Iterator<T> {

        /* Índice del iterador. */
        private int indice;
        private MonticuloMinimo<T> monticulo;

        /* Construye un nuevo iterador, auxiliándose del montículo
         * mínimo. */
        public Iterador(MonticuloMinimo<T> monticulo) {
            this.monticulo = monticulo;
	    this.indice = 0;
        }

        /* Nos dice si hay un siguiente elemento. */
        public boolean hasNext() {
	    return !(indice == monticulo.getElementos()); 
        }

        /* Regresa el siguiente elemento. */
        public T next() {
	    T g = monticulo.get(indice);
	    indice++;
	    return g;
        }

        /* No lo implementamos: siempre lanza una excepción. */
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    private int siguiente;
    /* Usamos un truco para poder utilizar arreglos genéricos. */
    private T[] arbol;

    /* Truco para crear arreglos genéricos. Es necesario hacerlo así
       por cómo Java implementa sus genéricos; de otra forma
       obtenemos advertencias del compilador. */
    @SuppressWarnings("unchecked") private T[] creaArregloGenerico(int n) {
        return (T[])(new ComparableIndexable[n]);
    }

    /**
     * Constructor sin parámetros. Es más eficiente usar {@link
     * #MonticuloMinimo(Lista)}, pero se ofrece este constructor por
     * completez.
     */
    public MonticuloMinimo() {
	this.siguiente = 0;
	this.arbol = creaArregloGenerico(0);
    }

    /**
     * Constructor para montículo mínimo que recibe una lista. Es
     * más barato construir un montículo con todos sus elementos de
     * antemano (tiempo <i>O</i>(<i>n</i>)), que el insertándolos
     * uno por uno (tiempo <i>O</i>(<i>n</i> log <i>n</i>)).
     */
    public MonticuloMinimo(Lista<T> lista) {
	this.siguiente = 0;
	this.arbol = creaArregloGenerico(lista.getLongitud()*2);
	for(int i = 0; i < lista.getLongitud(); i++){
	    arbol[i] = lista.get(i);
	    arbol[i].setIndice(i);
	    this.siguiente++;
	}
	int i = 0;
	while(i < siguiente){
	    for(int j = 0; j < siguiente; j++)
		reordena(arbol[j]);
	    i++;
	}
    }

    /**
     * Agrega un nuevo elemento en el montículo.
     * @param elemento el elemento a agregar en el montículo.
     */
    public void agrega(T elemento) {
        siguiente++;
	if(siguiente >= arbol.length-1 || arbol.length == 0){
	    T[] nuevo = creaArregloGenerico((arbol.length+1)*2);
	    for(int i = 0; i < siguiente-1; i++){
		nuevo[i] = arbol[i];
	    }
	    arbol = nuevo;
	}
	arbol[siguiente-1] = elemento;
	arbol[siguiente-1].setIndice(siguiente-1);
	reordena(arbol[elemento.getIndice()]);
	}

    /**
     * Elimina el elemento mínimo del montículo.
     * @return el elemento mínimo del montículo.
     * @throws IllegalStateException si el montículo es vacío.
     */
    public T elimina() {
	if(siguiente < 1)
	    throw new IllegalStateException();
	siguiente--;
	T elemento = arbol[0];
	if(siguiente == 0){	
	    arbol = creaArregloGenerico(0);
	    return elemento;
	}
	T ult = arbol[siguiente];
	arbol[0] = ult;
	arbol[arbol[0].getIndice()] = null;
	arbol[0].setIndice(0);
	reordena(arbol[0]);
	return elemento;
    }

    /**
     * Nos dice si el montículo es vacío.
     * @return <tt>true</tt> si ya no hay elementos en el montículo,
     *         <tt>false</tt> en otro caso.
     */
    public boolean esVacio() {
	return siguiente == 0;
    }

   /**
     * Reordena un elemento en el árbol.
     * @param elemento el elemento que hay que reordenar.
     */
    public void reordena(T elemento) {
	int k = elemento.getIndice();
	if(k == 0 && elemento != arbol[0])
	    return;
	while(arbol[k].compareTo(arbol[(k-1)/2]) < 0){
	    arbol[k].setIndice(arbol[(k-1)/2].getIndice());
	    arbol[(k-1)/2].setIndice(k);
		arbol[k] = arbol[(k-1)/2];
		arbol[(k-1)/2] = elemento;
		k = (k-1)/2;
	}
	while(tieneHijoDer(k) || tieneHijoIzq(k)){
	    if(tieneHijoDer(k) && tieneHijoIzq(k)){
		int c = arbol[(k*2)+1].compareTo(arbol[(k*2)+2]);
		if(c == -1 && arbol[k].compareTo(arbol[(k*2)+1]) > 0){
		    arbol[k].setIndice(arbol[(k*2)+1].getIndice());
		    arbol[(k*2)+1].setIndice(k);
		    arbol[k] = arbol[(k*2)+1];
		    arbol[(k*2)+1] = elemento;
		    k = (k*2)+1;
		}else if(c == 1 && arbol[k].compareTo(arbol[(k*2)+2]) > 0){
		    arbol[k].setIndice(arbol[(k*2)+2].getIndice());
		    arbol[(k*2)+2].setIndice(k);
		    arbol[k] = arbol[(k*2)+2];
		    arbol[(k*2)+2] = elemento;
		    k = (k*2)+2;
		}else{
		    break;
		}
	    }else if(tieneHijoIzq(k) && arbol[k].compareTo(arbol[(k*2)+1]) > 0){
		arbol[k].setIndice(arbol[(k*2)+1].getIndice());
		arbol[(k*2)+1].setIndice(k);
		arbol[k] = arbol[(k*2)+1];
		arbol[(k*2)+1] = elemento;
		k = (k*2)+1;
	    }else if(tieneHijoDer(k) && arbol[k].compareTo(arbol[(k*2)+2]) > 0){
		arbol[k].setIndice(arbol[(k*2)+2].getIndice());
		arbol[(k*2)+2].setIndice(k);
		arbol[k] = arbol[(k*2)+2];
		arbol[(k*2)+2] = elemento;
		k = (k*2)+2;
		
	    }else{
		break;
	    }
	}
    }

    /**
     * Regresa el número de elementos en el montículo mínimo.
     * @return el número de elementos en el montículo mínimo.
     */
    public int getElementos() {
	return siguiente;
    }

    /**
     * Regresa el <i>i</i>-ésimo elemento del árbol, por niveles.
     * @return el <i>i</i>-ésimo elemento del árbol, por niveles.
     * @throws NoSuchElementException si i es menor que cero, o
     *         mayor o igual que el número de elementos.
     */
    public T get(int i) {
	if(i < 0 || i >= siguiente)
	    throw new NoSuchElementException();
	return arbol[i];
    }

    /**
     * Regresa un iterador para iterar el montículo mínimo. El
     * montículo se itera en orden BFS.
     * @return un iterador para iterar el montículo mínimo.
     */
    public Iterator<T> iterator() {
        return new Iterador<T>(this);
    }

    /**
     * Metodo privado para saber si un elemento tiene hijo izquierdo.
     * @param El numero de indice del elemento.
     * @return true si lo tiene y false de lo contrario.
     */
    private boolean tieneHijoIzq(int i){
	int tamaño = siguiente;
	if((i*2)+1 >= tamaño)
	    return false;
    return true;
    }
    
    /**
     * Metodo privado para saber si un elemento tiene hijo derecho.
     * @param El numero de indice del elemento.
     * @return true si lo tiene y false de lo contrario.
     */
    private boolean tieneHijoDer(int i){
	int tamaño = siguiente;
	if((i*2)+2 >= tamaño)
	    return false;
    return true;
    }
} //Fin de MonticuloMinimo.java
