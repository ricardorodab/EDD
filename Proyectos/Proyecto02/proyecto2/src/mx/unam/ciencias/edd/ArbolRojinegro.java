/* -------------------------------------------------------------------
 * ArbolRojinegro.java
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

/**
 * @autor Jose Ricardo Rodriguez Abreu
 * @version 1.5
 * @since Mar 25 2014
 *
 * Clase para árboles rojinegros. Un árbol rojinegro cumple las
 * siguientes propiedades:
 *
 * <ol>
 *  <li>Todos los vértices son NEGROS o ROJOS.</li>
 *  <li>La raíz es NEGRA.</li>
 *  <li>Todas las hojas (<tt>null</tt>) son NEGRAS (al igual que la
 *      raíz).
 *  <li>Un vértice ROJO siempre tiene dos hijos NEGROS.</li>
 *  <li>Todo camino de un vértice a alguno de sus descendientes tiene
 *      el mismo número de vértices NEGROS.</li>
 * </ol>
 *
 * Los árboles rojinegros son autobalanceados, y por lo tanto las
 * operaciones de inserción, eliminación y búsqueda pueden
 * realizarse en <i>O</i>(log <i>n</i>).
 */
public class ArbolRojinegro<T extends Comparable<T>>
    extends ArbolBinarioOrdenado<T> {

    /**
     * Agrega un nuevo elemento al árbol. El método invoca al método
     * {@link ArbolBinarioOrdenado#agrega}, y después balancea el
     * árbol recoloreando vértices y girando el árbol como sea
     * necesario.
     * @param elemento el elemento a agregar.
     * @return un vértice que contiene al nuevo elemento.
     */
    @Override public VerticeArbolBinario<T> agrega(T elemento) {
	Vertice<T> v =vertice(super.agrega(elemento));
	v.color = Color.ROJO;
        balancearAgrega(v);
	return v;
    }

    /**
     * Elimina un elemento del árbol. El método elimina el vértice que
     * contiene el elemento, y recolorea y gira el árbol como sea
     * necesario para rebalancearlo.
     * @param elemento el elemento a eliminar del árbol.
     */
    @Override public void elimina(T elemento) {
	//Buscamos al vertice a eliminar y si no existe terminamos 
	Vertice<T> v = vertice(busca(elemento));
	Vertice<T> h = null;
	Vertice<T> fantasma = new Vertice<T>(null);
	if(v != null){
	    this.elementos--;
	    //Buscamos al anterior de v
	    Vertice<T> anterior = super.buscaVerticeAnterior(v);
	    //Si tiene anterior intercambiamos los elementos
	    if(anterior != null){
		v.elemento = anterior.elemento;
		anterior.elemento = elemento;
		v = anterior;
	    }
	    //Si v no tiene hijos creamos al fantasma
		if(!(v.hayDerecho() || v.hayIzquierdo())){
		    fantasma.color = Color.NEGRO;
		    v.izquierdo = fantasma;
		    v.izquierdo.padre = v;
		}
		//Subimos a el hijo de v
		if(v.hayIzquierdo()){
		    if(v.padre == null){
			v.izquierdo.padre = null;
			this.raiz = v.izquierdo;
			h = this.raiz;

		    }else if(v.padre.izquierdo == v){
			v.padre.izquierdo = v.izquierdo;
			v.izquierdo.padre = v.padre;
			h = v.izquierdo;
		    }else{
			v.padre.derecho = v.izquierdo;
			v.izquierdo.padre = v.padre;
			h = v.izquierdo;
		    }
		}else{
		    if(v.padre == null){
			v.derecho.padre = null;
			this.raiz = v.derecho;
			v.derecho = null;
			h = this.raiz;
		    }else if(v.padre.izquierdo == v){
			v.padre.izquierdo = v.derecho;
			v.derecho.padre = v.padre;
			h = v.derecho;
		    }else{
			v.padre.derecho = v.derecho;
			v.derecho.padre = v.padre;
			h = v.derecho;
		    }
		}
		//Si h no tiene padre, h = raiz.
		if(h.padre == null)
		    this.raiz = h;
		//Si h es rojo lo coloreamos de negro y terminamos
		if(h.color == Color.ROJO){
		    h.color = Color.NEGRO;
		    return;
		}
		//Si v y h son negros rebalanceamos y eliminamos al fantasma
		if(v.color == Color.NEGRO && h.color == Color.NEGRO){		
		    balancearElimina(h);
		    cazaFantasma(fantasma);
		    return;
		}
		//Si v es rojo eliminamos al fantasma.
		if(v.color == Color.ROJO){
		    cazaFantasma(fantasma);
		    return;
		}
		    
	}
    }

    /**
     * Metodo balancea el arbol rojinegro
     * @param v es el vertice del cual parte
     */
    private void balancearElimina(Vertice<T> v){
	//Caso 1 RAIZ
	if(v.padre == null){
	    this.raiz = v;
	    v.color = Color.NEGRO;
	    return;
	}
	//Caso 2 HERMANO ROJO
	if(getHermano(v).color == Color.ROJO){
	    v.padre.color = Color.ROJO;
	    getHermano(v).color = Color.NEGRO;
	    if(v.padre.izquierdo == v)
		giraIzquierda(v.padre);
	    else
		giraDerecha(v.padre);
	    //Actualizar V
	    //  hermano = getHermano(v);
	 
	}
	//Caso 3 TODOS SON NEGROS
	if(v.padre.color == Color.NEGRO && existeNegro(getHermano(v)) && existeNegro(getHermano(v).izquierdo) && existeNegro(getHermano(v).derecho)){
	    getHermano(v).color = Color.ROJO;
		balancearElimina(v.padre);
		return;
	}
	//Caso 4 HERMANO Y SOBRINOS NEGROS Y PADRE ROJO
	if(existeNegro(getHermano(v)) && v.padre.color == Color.ROJO && existeNegro(getHermano(v).izquierdo)
	   && existeNegro(getHermano(v).derecho)){
	    v.padre.color = Color.NEGRO;
	    getHermano(v).color = Color.ROJO;
	    return;
	    
	}
	//Caso 5 HERMANO NEGRO Y SOBRINOS BICOLORES
	if(v.padre.izquierdo == v && !existeNegro(getHermano(v).izquierdo) && existeNegro(getHermano(v).derecho)){
	    getHermano(v).color = Color.ROJO;
	    getHermano(v).izquierdo.color = Color.NEGRO;
	    giraDerecha(getHermano(v));
	}else if(v.padre.derecho == v && existeNegro(getHermano(v).izquierdo) && !existeNegro(getHermano(v).derecho)){
	    getHermano(v).color = Color.ROJO;
	    getHermano(v).derecho.color = Color.NEGRO;
	    giraIzquierda(getHermano(v));
	}
	//Caso 6 SOBRINO INVERSO DE V ES ROJO
	if(v.padre.izquierdo == v){
	    if(!existeNegro(getHermano(v).derecho)){
		getHermano(v).color = v.padre.color;
		    v.padre.color = Color.NEGRO;
		    getHermano(v).derecho.color = Color.NEGRO;
		    giraIzquierda(v.padre);
	    }
	}else{
	    if(!existeNegro(getHermano(v).izquierdo)){
		getHermano(v).color = v.padre.color;
		    v.padre.color = Color.NEGRO;
		    getHermano(v).izquierdo.color = Color.NEGRO;
		    giraDerecha(v.padre);
	    }
	}	
    }

    /**
     * Metodo que balancea nuestro arbol rojinegro.
     * @param v es el vertice a partir rebalancea.
     */
    private void balancearAgrega(Vertice<T> v){
	if(v == this.raiz){
	    v.color = Color.NEGRO;
	    return;
	}else if(v.padre.getColor() == Color.NEGRO){
	    return;
	}
	Vertice<T> abuelo = v.padre.padre;
	if(v.padre == abuelo.derecho){
	    if(abuelo.izquierdo != null &&
	       abuelo.izquierdo.getColor() == Color.ROJO){
		v.padre.color = Color.NEGRO;
		abuelo.izquierdo.color = Color.NEGRO;
		abuelo.color = Color.ROJO;
		balancearAgrega(abuelo);
		return;	    
	    }else if(v.padre.izquierdo == v){
		Vertice<T> v2 = v.padre;
		giraDerecha(v.padre);
		balancearAgrega(v2); 
	    }else if(v.padre.derecho == v){
		v.padre.color = Color.NEGRO;
		abuelo.color = Color.ROJO;
		giraIzquierda(abuelo);
	    }
	}else if(v.padre == abuelo.izquierdo){
	    if(abuelo.derecho != null &&
	       abuelo.derecho.getColor() == Color.ROJO){
		v.padre.color = Color.NEGRO;
		abuelo.derecho.color = Color.NEGRO;
		abuelo.color = Color.ROJO;
		balancearAgrega(abuelo);
		return;
	    }else if(v.padre.derecho == v){
		Vertice<T> v2 = v.padre;
		giraIzquierda(v.padre);
		balancearAgrega(v2); 
	    
	    }else if(v.padre.izquierdo == v){
		v.padre.color = Color.NEGRO;
		abuelo.color = Color.ROJO;
		giraDerecha(abuelo);
	    }
	}   	
	
    }

    /**
     * Metodo que nos da el hermano de un vertice.
     * @param v - es el vertice a buscar su hermano.
     * @return Vertice<T> - es el vertice hermano.
     */
    private Vertice<T> getHermano(Vertice<T> v){
	if(v.padre == null)
	    return null;
	if(v.padre.derecho == v)
	    return v.padre.izquierdo;
	else
	    return v.padre.derecho;
    }

    /**
     * Metodo que nos dice si el vertice dado es negro
     * @param v - es el vertice a comprobar
     * @return Si no existe o si es negro regresa true.
     */
    private boolean existeNegro(Vertice<T> v){
	return v == null || v.color == Color.NEGRO;
    }
    
    /**
     * Metodo que elimina el vertice fantasma que creamos
     * @param v - es el vertice a eliminar
     */
    private void cazaFantasma(Vertice<T> v){
	if(v.padre == null){
	    if(v == this.raiz){
		this.raiz = null;
		return;
	    }
	    return;
	}else{
	    Vertice<T> padre = v.padre;
	    if(v == padre.izquierdo){
		if(v.hayIzquierdo()){
		    padre.izquierdo = v.izquierdo;
		    v.izquierdo.padre = padre;
		}else if(v.hayDerecho()){
		    padre.izquierdo = v.derecho;
		    v.derecho.padre = padre;
		}else{
		    padre.izquierdo = null;
		}		
	    }else{
		if(v.hayIzquierdo()){
		    padre.derecho = v.izquierdo;
		    v.izquierdo.padre = padre;
		}else if(v.hayDerecho()){
		    padre.derecho = v.derecho;
		    v.derecho.padre = padre;
		}else{
		    padre.derecho = null;
		}
	    }
	}
    } 
} //Fin de ArbolRojinegro.java
