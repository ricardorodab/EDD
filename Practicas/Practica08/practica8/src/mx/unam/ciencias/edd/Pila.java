/* -------------------------------------------------------------------
 * Pila.java
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
 * Clase para pilas genéricas.
 */
public class Pila<T> extends MeteSaca<T> {

    /**
     * Construye una pila vacía.
     */
    public Pila() {
	super();
    }

    /**
     * Elimina el elemento en el tope de la pila y lo regresa.
     * @return el elemento en el tope de la pila.
     */
    @Override public T saca() {
        return this.lista.eliminaUltimo();
    }

    /**
     * Nos permite ver el elemento en el tope de la pila, sin
     * sacarlo de la misma.
     */
    @Override public T mira() {
	return this.lista.getUltimo();
    }
} //Fin de Pila.java
