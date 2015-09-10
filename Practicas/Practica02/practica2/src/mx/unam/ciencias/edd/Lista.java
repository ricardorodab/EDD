/* -------------------------------------------------------------------
 * Lista.java
 * versión 1.5
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
 * @version 1.5
 * @since Feb 9 2014
 * <p>Clase genérica para listas doblemente ligadas.</p>
 *
 * <p>Las listas nos permiten agregar elementos al inicio o final de
 * la lista, eliminar elementos de la lista, comprobar si un
 * elemento está o no en la lista, y otras operaciones básicas.</p>
 *
 * <p>Las instancias de la clase Lista implementan la interfaz
 * {@link Iterator}, por lo que el recorrerlas es muy sencillo:</p>
 *
<pre>
    for (String s : l)
        System.out.println(s);
</pre>
 *
 * <p>Además, se le puede pedir a una lista una instancia de {@link
 * IteradorLista} para recorrerla en ambas direcciones.</p>
 */
public class Lista<T> implements Iterable<T> {

    /* Clase Nodo privada para uso interno de la clase Lista. */
    private class Nodo<T> {
        public T elemento;
        public Nodo<T> anterior;
        public Nodo<T> siguiente;

        public Nodo(T elemento) {
            this.elemento = elemento;
        }
    }

    /* Clase Iterador privada para iteradores. */
    private class Iterador<T> implements IteradorLista<T> {

        /* La lista a iterar. */
        Lista<T> lista;
        /* Elemento anterior. */
        private Lista<T>.Nodo<T> anterior;
        /* Elemento siguiente. */
        private Lista<T>.Nodo<T> siguiente;
	
        /* El constructor recibe una lista para inicializar su
         * siguiente con la cabeza. */
        public Iterador(Lista<T> lista) {
            this.lista = lista;
	    this.siguiente = lista.cabeza;
	    this.anterior = null;
        }

        /* Existe un siguiente elemento, si el siguiente no es
         * nulo. */
        @Override public boolean hasNext() {
            if(this.siguiente == null){
		return false;
	    }else{
		return true;
	    }
        }

        /* Regresa el elemento del siguiente, a menos que sea nulo,
         * en cuyo caso lanza la excepción
         * NoSuchElementException. */
        @Override public T next() {
            if(this.siguiente == null){
		throw new NoSuchElementException();
	    }else{
		Lista<T>.Nodo<T> n = this.siguiente;
		this.anterior = n;
		this.siguiente = n.siguiente;
		return n.elemento;
	    }
        }

        /* Existe un elemento anterior, si el anterior no es
         * nulo. */
        @Override public boolean hasPrevious() {
            if(this.anterior == null){
		return false;
	    }else{
		return true;
	    }
	}

        /* Regresa el elemento del anterior, a menos que sea nulo,
         * en cuyo caso lanza la excepción
         * NoSuchElementException. */
        @Override public T previous() {
            if(!this.hasPrevious()){
		throw new NoSuchElementException();
	    }else{
		Lista<T>.Nodo<T> n = anterior;
		this.anterior = n.anterior;
		this.siguiente = n;
		return n.elemento;
	    }
        }

        /* No implementamos el método remove(); sencillamente
         * lanzamos la excepción UnsupportedOperationException. */
        @Override public void remove() {
            throw new UnsupportedOperationException();
        }

        /* Mueve el iterador al inicio de la lista; después de
         * llamar este método, y si la lista no es vacía, hasNext()
         * regresa verdadero y next() regresa el primer elemento. */
        @Override public void start() {
	    this.siguiente = lista.cabeza;
	    this.anterior = null;
        }

        /* Mueve el iterador al final de la lista; después de llamar
         * este método, y si la lista no es vacía, hasPrevious()
         * regresa verdadero y previous() regresa el último
         * elemento. */
        @Override public void end() {
	    this.anterior = lista.rabo;
	    this.siguiente = null;
        }
    }

    /* Primer elemento de la lista. */
    private Nodo<T> cabeza;
    /* Último elemento de la lista. */
    private Nodo<T> rabo;
    /* Número de elementos en la lista. */
    private int longitud;

    /**
     * Regresa la longitud de la lista.
     * @return la longitud de la lista, el número de elementos que
     * contiene.
     */
    public int getLongitud() {
        return longitud;
    }

    /**
     * Agrega un elemento al final de la lista. Si la lista no
     * tiene elementos, el elemento a agregar será el primero y
     * último.
     * @param elemento el elemento a agregar.
     */
    public void agregaFinal(T elemento) {
        Nodo<T> nodo1 = new Nodo<T>(elemento);
	if(getLongitud() == 0){
	    this.cabeza = nodo1;
	    this.rabo = nodo1;
	    this.rabo.siguiente = null;
	    this.cabeza.anterior = null;
	}else{
	    this.rabo.siguiente = nodo1;
	    nodo1.anterior = rabo;
	    this.rabo = nodo1;
	    this.rabo.siguiente = null;
	}
	this.longitud++;
    }

    /**
     * Agrega un elemento al inicio de la lista. Si la lista no
     * tiene elementos, el elemento a agregar será el primero y
     * último.
     * @param elemento el elemento a agregar.
     */
    public void agregaInicio(T elemento) {
        Nodo<T> nodo2 = new Nodo<T>(elemento);
	if(getLongitud() == 0){
	    this.cabeza = nodo2;
	    this.rabo = nodo2;
	    this.rabo.siguiente = null;
	    this.cabeza.anterior = null;
	}else{
	    this.cabeza.anterior = nodo2;
	    nodo2.siguiente = cabeza;
	    this.cabeza = nodo2;
	    this.cabeza.anterior = null;
	}
	this.longitud++;
    }
    
    
    /**
     * Busca el nodo en una lista dado un elemento.
     * @param elemento - es el elemento que tiene el nodo.
     * @return - regresa el nodo que contiene al elemento. 
     * En caso de no existir el elemento regresa un nodo null.
     */
    public Nodo<T> buscaNodo(T elemento){
	Nodo<T> n = this.cabeza;
	Nodo<T> l = this.rabo;
	if(n.elemento.equals(elemento)){
	    return n;
	}else if(l.elemento.equals(elemento)){
		return l;
	    }else{
	    while(n.siguiente != null){
		if(n.elemento.equals(elemento)){
		    return n;
		}else{
		    n = n.siguiente;
		}	
	    }
	    return null;
	}
    }
    
    /**
     * Elimina un elemento de la lista. Si el elemento no está
     * contenido en la lista, el método no la modifica.
     * @param elemento el elemento a eliminar.
     */
    public void elimina(T elemento) {
	Nodo<T> n = this.buscaNodo(elemento);
	if(this.cabeza.elemento.equals(elemento)){
	    eliminaPrimero();
	} else if(this.rabo.elemento.equals(elemento)){
	    eliminaUltimo();
	}else if(this.getLongitud() > 0 && n != null){
	    Nodo<T> m = n;
	    n.siguiente.anterior = m.anterior;
	    n.anterior.siguiente = m.siguiente;
	    this.longitud--;
	}
    }

    /**
     * Elimina el primer elemento de la lista y lo regresa.
     * @return el primer elemento de la lista.
     * @throws NoSuchElementException si la lista es vacía.
     */
    public T eliminaPrimero() {
	if(this.getLongitud() == 0){
	    throw new NoSuchElementException();
	}else{
	    Nodo<T> ca = this.cabeza;
	    this.cabeza = ca.siguiente;  
	    this.longitud--;
	    return ca.elemento;
	}
    }

    /**
     * Elimina el último elemento de la lista y lo regresa.
     * @return el último elemento de la lista.
     * @throws NoSuchElementException si la lista es vacía.
     */
    public T eliminaUltimo() {
	if(this.getLongitud() == 0 || this.cabeza == null){
	    throw new NoSuchElementException();
	}else{
	    Nodo<T> ca = this.rabo;
	    this.rabo = ca.anterior;
	    this.longitud--;
	    return ca.elemento;
	}    
    }
    /**
     * Nos dice si un elemento está en la lista.
     * @param elemento el elemento que queremos saber si está en la
     * lista.
     * @return <tt>true</tt> si <tt>elemento</tt> está en la lista,
     *         <tt>false</tt> en otro caso.
     */
    public boolean contiene(T elemento) {
	if(getLongitud() == 0){
	    return false;
	}else{
	    Nodo <T> igual = buscaNodo(elemento);
	    if(igual != null){
		return true;
	    }else{
		return false;
	    }
	}
    }
    /**
     * Regresa la reversa de la lista.
     * @return una nueva lista que es la reversa la que manda llamar
     *         el método.
     */
    public Lista<T> reversa() {
	Lista<T> nueva = new Lista<T>();
	Nodo<T> nodo7 = this.cabeza;
	nueva.longitud = 0;
	while(nodo7 != null){
	    nueva.agregaInicio(nodo7.elemento);
	    nodo7 = nodo7.siguiente;
	}
	return nueva;
    }

    /**
     * Regresa una copia de la lista. La copia tiene los mismos
     * elementos que la lista que manda llamar el método, en el
     * mismo orden.
     * @return una copiad de la lista.
     */
    public Lista<T> copia() {
	Lista<T> nueva1 = new Lista<T>();
	nueva1.longitud = 0;
	Nodo<T> nodo8 = this.cabeza;
	while(nodo8 != null){
	    nueva1.agregaFinal(nodo8.elemento);
	    nodo8 = nodo8.siguiente;
	}
	return nueva1;
    }   

    /**
     * Limpia la lista de elementos. El llamar este método es
     * equivalente a eliminar todos los elementos de la lista.
     */
    public void limpia() {
	this.cabeza.siguiente.anterior = null;
	this.rabo.anterior.siguiente = null;
	this.cabeza = null;
	this.rabo = null;
	this.longitud = 0;
    }

    /**
     * Regresa el primer elemento de la lista.
     * @return el primer elemento de la lista.
     * @throws NoSuchElementException si la lista es vacía.
     */
    public T getPrimero() {
	if(this.cabeza == null || this.getLongitud() == 0){
	    throw new NoSuchElementException();
	}else{
	    return this.cabeza.elemento;
	}
    }

    /**
     * Regresa el último elemento de la lista.
     * @return el último elemento de la lista.
     * @throws NoSuchElementException si la lista es vacía.
     */
    public T getUltimo() {
        if(this.cabeza == null || this.getLongitud() == 0){
	    throw new NoSuchElementException();
	}else{
	    return this.rabo.elemento;
	}
    }

    /**
     * Regresa el <em>i</em>-ésimo elemento de la lista.
     * @param i el índice del elemento que queremos.
     * @return el <em>i</em>-ésimo elemento de la lista, si
     *         <em>i</em> es mayor o igual que cero y menor que el
     *         número de elementos en la lista.
     * @throws ExcepcionIndiceInvalido si el índice recibido es
     *         menor que cero, o mayor que el número de elementos en
     *         la lista menos uno.
     */
    public T get(int i) {
	if(i > getLongitud() -1 || i < 0){
	    throw new ExcepcionIndiceInvalido();
	}else{
	    Nodo<T> nodo9 = this.cabeza;
	    int l = 0;
	    while(l < i){
		nodo9 = nodo9.siguiente;
		l++;
	}
	    return nodo9.elemento;
	}
    }
    /**
     * Regresa el índice del elemento recibido en la lista.
     * @param elemento el elemento del que se busca el índice.
     * @return el índice del elemento recibido en la lista, o -1 si
     *         el elemento no está contenido en la lista.
     */
    public int indiceDe(T elemento) {
	int l = 0;
	Nodo<T> nodo10 = this.cabeza;
	while(l < getLongitud()){ 
	    if(nodo10.elemento.equals(elemento)){
		return l;
	    }else{
		nodo10 = nodo10.siguiente;
	    }
	    l++;
	}
	return -1;
    }

    /**
     * Nos dice si la lista es igual al objeto recibido.
     * @param o el objeto con el que hay que comparar.
     * @return <tt>true</tt> si la lista es igual al objeto
     *         recibido; <tt>false</tt> en otro caso.
     */
    @Override public boolean equals(Object o) {
	boolean r = true;
	Nodo<T> nodo11 = this.cabeza;
        if(o == null){
	    return false;
	} if(o.getClass() != getClass()){
	    return false;
	}
	@SuppressWarnings("unchecked") Lista<T> l = (Lista<T>)o;
	Nodo<T> nodoL = l.cabeza;
	if(l.getLongitud() != this.getLongitud()){
	    return false;
	}
	while(nodo11 != null){
	    r = nodo11.elemento.equals(nodoL.elemento);
	    nodo11 = nodo11.siguiente;
	    nodoL = nodoL.siguiente;
	    if(r == false){
		return false;
	    }
	}
	return true;
    }
    
    /**
     * Regresa una representación en cadena de la lista.
     * @return una representación en cadena de la lista.
     */
    @Override public String toString() {
        Nodo<T> l = this.cabeza;
	String cadena = "[";
	if(this.cabeza == null){
	    cadena.concat("]");
	}else{
	    while(l.siguiente != null){
		cadena = cadena.concat(l.elemento.toString());
		if(l.siguiente.siguiente != null){
		    cadena = cadena.concat(", ");
		}else{
		    cadena = cadena.concat(", "+l.siguiente.elemento.toString()+"]");
		    break;
		}
		l = l.siguiente;
	    }	
	}
	return cadena;
    }

    /**
     * Regresa un iterador para recorrer la lista.
     * @return un iterador para recorrer la lista.
     */
    @Override public Iterator<T> iterator() {
	Iterator<T> i = new Iterador<T>(this);
       return i;
    }

    /**
     * Regresa un iterador para recorrer la lista en ambas
     * direcciones.
     * @return un iterador para recorrer la lista en ambas
     * direcciones.
     */
    public IteradorLista<T> iteradorLista() {
	Iterator<T> i = new Iterador<T>(this);
	return (IteradorLista<T>)i;
    }
} // Fin de la clase Lista.java