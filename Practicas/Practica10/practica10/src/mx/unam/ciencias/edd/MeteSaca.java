/* -------------------------------------------------------------------
 * MeteSaca.java
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
 * @since Feb 16 2014
 * Clase abtracta para estructuras lineales restringidas a
 * operaciones mete/saca/mira, todas ocupando una lista subyaciente.
 */
public abstract class MeteSaca<T> {

    /** Lista subyaciente. */
    protected Lista<T> lista;

    /**
     * Constructor único que incializa la lista.
     */
    public MeteSaca() {
        this.lista = new Lista<T>();
    }

    /**
     * Agrega un elemento a la estructura.
     * @param elemento el elemento a agregar.
     */
    public void mete(T elemento) {
        this.lista.agregaFinal(elemento);
    }

    /**
     * Elimina un elemento de la estructura y lo regresa.
     * @return el elemento eliminado.
     * @throws NoSuchElementException si la estructura está vacía.
     */
    public abstract T saca();

    /**
     * Nos permite ver el elemento en un extremo de la estructura,
     * sin sacarlo de la misma.
     * @return el elemente en un extremo de la estructura.
     * @throws NoSuchElementException si la estructura está vacía.
     */
    public abstract T mira();

    /**
     * Nos dice si la estructura está vacía.
     * @return <tt>true</tt> si la estructura no tiene elementos,
     *         <tt>false</tt> en otro caso.
     */
    public boolean esVacia() {
	if(this.lista.getLongitud() == 0){
	    return true;
	}else{
	    return false;
	}
    }
} // Fin de MeteSaca.java
