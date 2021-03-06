/* -------------------------------------------------------------------
 * ArbolBinario.java
 * versión 3.0
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

import java.util.NoSuchElementException;

/**
*  @autor Jose Ricardo Rodriguez Abreu
 * @version 3.0
 * @since Mar 5 2014
 * <p>Clase abstracta para árboles binarios genéricos.</p>
 *
 * <p>La clase proporciona las operaciones básicas para árboles
 * binarios, pero deja la implementación de varios en manos de las
 * clases concretas.</p>
 */
public abstract class ArbolBinario<T> implements Iterable<T> {

    /**
     * Clase interna protegida para vértices.
     */
    protected class Vertice<T> implements VerticeArbolBinario<T> {
        /** El elemento del vértice. */
        public T elemento;
        /** El padre del vértice. */
        public Vertice<T> padre;
        /** El izquierdo del vértice. */
        public Vertice<T> izquierdo;
        /** El derecho del vértice. */
        public Vertice<T> derecho;
	/** El color del nodo. */
	public Color color;
        /**
         * Constructor único que recibe un elemento.
         * @param elemento el elemento del vértice.
         */
        public Vertice(T elemento) {
            this.elemento = elemento;
        }

        /**
         * Regresa una representación en cadena del vértice.
         * @return una representación en cadena del vértice.
         */
        public String toString() {
            return this.elemento.toString();
        }

        /**
         * Nos dice si el vértice tiene un padre.
         * @return <tt>true</tt> si el vértice tiene padre,
         *         <tt>false</tt> en otro caso.
         */
        @Override public boolean hayPadre() {
            return this.padre != null;
        }

        /**
         * Nos dice si el vértice tiene un izquierdo.
         * @return <tt>true</tt> si el vértice tiene izquierdo,
         *         <tt>false</tt> en otro caso.
         */
        @Override public boolean hayIzquierdo() {
            return this.izquierdo != null;
        }

        /**
         * Nos dice si el vértice tiene un derecho.
         * @return <tt>true</tt> si el vértice tiene derecho,
         *         <tt>false</tt> en otro caso.
         */
        @Override public boolean hayDerecho() {
            return this.derecho != null;
        }

        /**
         * Regresa el padre del vértice.
         * @return el padre del vértice.
         * @throws NoSuchElementException si el vértice no tiene padre.
         */
        @Override public VerticeArbolBinario<T> getPadre() {
            return this.padre;
        }

        /**
         * Regresa el izquierdo del vértice.
         * @return el izquierdo del vértice.
         * @throws NoSuchElementException si el vértice no tiene izquierdo.
         */
        @Override public VerticeArbolBinario<T> getIzquierdo() {
            return this.izquierdo;
        }

        /**
         * Regresa el derecho del vértice.
         * @return el derecho del vértice.
         * @throws NoSuchElementException si el vértice no tiene derecho.
         */
        @Override public VerticeArbolBinario<T> getDerecho() {
            return this.derecho;
        }

        /**
         * Regresa el elemento al que apunta el vértice.
         * @return el elemento al que apunta el vértice.
         */
        @Override public T get() {
            return this.elemento;
        }

	/**
	 * Regresa el color del vértice.
	 * @return el color del vértice.
	 */
	@Override public Color getColor() {
	    return this.color;
	}
    }

    /** La raíz del árbol. */
    protected Vertice<T> raiz;
    /** El número de elementos */
    protected int elementos;

    /**
     * Construye un árbol con cero elementos.
     */
    public ArbolBinario() {
        raiz = null;
	elementos = 0;
    }

    /**
     *
     *
     */
    private int profundidad(Vertice<T> v, int l){
	int i, j;
	i = j = l;
	if(v.hayIzquierdo())
	    i = profundidad(v.izquierdo, l+1);
	if(v.hayDerecho())
	    j = profundidad(v.derecho, l+1);
	if(i >= j)
	    return i;
	else
	    return j;
    }


    /**
     * Regresa la profundidad del árbol. La profundidad de un árbol
     * es la longitud de la ruta más larga entre la raíz y una hoja.
     * @return la profundidad del árbol.
     */
    public int profundidad() {
        return profundidad(this.raiz, 0);
    }

    /**
     * Regresa el número de elementos en el árbol. El número de
     * elementos es el número de elementos que se han agregado al
     * árbol.
     * @return el número de elementos en el árbol.
     */
    public int getElementos() {
	/*if(this.raiz == null){
	    return 0;
	}else{
        Cola<Vertice<T>> cola = new Cola<Vertice<T>>();
	cola.mete(this.raiz);
	int i = 0;
	while(!cola.esVacia()){
	    Vertice<T> v = cola.saca();
	    if(v.hayIzquierdo())
		cola.mete(v.izquierdo);
	    if(v.hayDerecho())
		cola.mete(v.derecho);
	    i++;
	}
	return i;
	}*/
return elementos;
    }
    
    
    /**
     * Agrega un elemento al árbol.
     * @param elemento el elemento a agregar al árbol.
     * @return el vértice agregado al árbol que contiene el
     *         elemento.
     */
    public abstract VerticeArbolBinario<T> agrega(T elemento);

    /**
     * Elimina un elemento del árbol.
     * @param elemento el elemento a eliminar.
     */
    public abstract void elimina(T elemento);

    /**
     * Busca un elemento en el árbol. Si lo encuentra, regresa el
     * vértice que lo contiene; si no, regresa <tt>null</tt>.
     * @param elemento el elemento a buscar.
     * @return un vértice que contiene el elemento buscado si lo
     *         encuentra; <tt>null</tt> en otro caso.
     */
    public VerticeArbolBinario<T> busca(T elemento) {
	if(this.raiz == null){
	    return null;
	}else{
	    Cola<Vertice<T>> cola = new Cola<Vertice<T>>();
	    cola.mete(this.raiz);
	    while(!cola.esVacia()){
		Vertice<T> v = cola.saca();
		if(v.elemento.equals(elemento)){
		    return v;
		}else{
		    if(v.hayIzquierdo())
			cola.mete(v.izquierdo);
		    if(v.hayDerecho())
			cola.mete(v.derecho);
		}
	    }
	    return null;
	}
    }
    
    /**
     * Regresa el vértice que contiene la raíz del árbol.
     * @return el vértice que contiene la raíz del árbol.
     * @throws NoSuchElementException si el árbol es vacío.
     */
    public VerticeArbolBinario<T> raiz() {
        return this.raiz;
    }

    /**
     * Regresa una representación en cadena del árbol.
     * @return una representación en cadena del árbol.
     */
    @Override public String toString() {
        /* Necesitamos la profundidad para saber cuántas ramas puede
           haber. */
        if (elementos == 0)
            return "";
        int p = profundidad() + 1;
        /* true == dibuja rama, false == dibuja espacio. */
        boolean[] rama = new boolean[p];
        for (int i = 0; i < p; i++)
            /* Al inicio, no dibujamos ninguna rama. */
            rama[i] = false;
        String s = aCadena(raiz, 0, rama);
        return s.substring(0, s.length()-1);
    }

    /**
     * Convierte el vértice en vértice. Método auxililar para hacer
     * esta audición en un único lugar.
     * @param verticeArbolBinario el vértice de árbol binario que queremos
     *        como vértice.
     * @return el vértice recibido visto como vértice.
     * @throws ClassCastException si el vértice no es instancia de
     *         {@link Vertice}.
     */
    protected Vertice<T> vertice(VerticeArbolBinario<T> verticeArbolBinario) {
        /* Tenemos que suprimir advertencias. */
        @SuppressWarnings("unchecked") Vertice<T> n = (Vertice<T>)verticeArbolBinario;
        return n;
    }

    /* Método auxiliar recursivo que hace todo el trabajo. */
    private String aCadena(Vertice<T> vertice, int nivel, boolean[] rama) {
        /* Primero que nada agregamos el vertice a la cadena. */
        String s = vertice + "\n";
        /* A partir de aquí, dibujamos rama en este nivel. */
        rama[nivel] = true;
        if (vertice.izquierdo != null && vertice.derecho != null) {
            /* Si hay vertice izquierdo Y derecho, dibujamos ramas o
             * espacios. */
            s += espacios(nivel, rama);
            /* Dibujamos el conector al hijo izquierdo. */
            s += "├─›";
            /* Recursivamente dibujamos el hijo izquierdo y sus
               descendientes. */
            s += aCadena(vertice.izquierdo, nivel+1, rama);
            /* Dibujamos ramas o espacios. */
            s += espacios(nivel, rama);
            /* Dibujamos el conector al hijo derecho. */
            s += "└─»";
            /* Como ya dibujamos el último hijo, ya no hay rama en
               este nivel. */
            rama[nivel] = false;
            /* Recursivamente dibujamos el hijo derecho y sus
               descendientes. */
            s += aCadena(vertice.derecho, nivel+1, rama);
        } else if (vertice.izquierdo != null) {
            /* Dibujamos ramas o espacios. */
            s += espacios(nivel, rama);
            /* Dibujamos el conector al hijo izquierdo. */
            s += "└─›";
            /* Como ya dibujamos el último hijo, ya no hay rama en
               este nivel. */
            rama[nivel] = false;
            /* Recursivamente dibujamos el hijo izquierdo y sus
               descendientes. */
            s += aCadena(vertice.izquierdo, nivel+1, rama);
        } else if (vertice.derecho != null) {
            /* Dibujamos ramas o espacios. */
            s += espacios(nivel, rama);
            /* Dibujamos el conector al hijo derecho. */
            s += "└─»";
            /* Como ya dibujamos el último hijo, ya no hay rama en
               este nivel. */
            rama[nivel] = false;
            /* Recursivamente dibujamos el hijo derecho y sus
               descendientes. */
            s += aCadena(vertice.derecho, nivel+1, rama);
        }
        return s;
    }

    /* Dibuja los espacios (incluidas las ramas, de ser necesarias)
       que van antes de un vértice. */
    private String espacios(int n, boolean[] rama) {
        String s = "";
        for (int i = 0; i < n; i++)
            if (rama[i])
                /* Rama: dibújala. */
                s += "│  ";
            else
                /* No rama: dibuja espacio. */
                s += "   ";
        return s;
    }
} //Fin de ArbolBinario.java
