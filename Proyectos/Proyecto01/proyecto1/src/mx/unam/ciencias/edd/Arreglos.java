/* -------------------------------------------------------------------
 * Arreglos.java
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

import java.util.Random;

/**
 * @autor Jose Ricardo Rodriguez Abreu
 * @version 1.5
 * @since Feb 25 2014
 * Clase para manipular arreglos genéricos.
 */
public class Arreglos {

    /**
     * Intercambia dos elementos de un arreglo.
     * @param a es el arreglo en el que intercabiará los elementos.
     * @param i es la posición de un elemento a intercambiar.
     * @param j es la posición de el segundo elemento intercambiar.
     */
    private static <T extends Comparable<T>> void intercambia(T[] a, int i, int j){
	T aux = a[i];
	a[i] = a[j];
	a[j] = aux;
    }
    
    /**
     * Ordena el arreglo recibido usando QuickSort.
     * @param a un arreglo cuyos elementos son comparables.
     * @param ini la posición de el primer elemento del arreglo.
     * @param fin la posición de el último elemento del arreglo.
     */
    private static <T extends Comparable<T>>
			      void quickSort(T[] a, int ini, int fin){
	if(fin - ini < 1){
	    return;
	}
	int i = ini + 1, j = fin;
	while(i < j) {
	    if(a[i].compareTo(a[ini]) > 0 && a[j].compareTo(a[ini]) <= 0){
		intercambia(a, i++, j--);
	    } else if(a[i].compareTo(a[ini]) <= 0){
		i++;
	    } else{
		j--;
	    } 
	}
	if(a[i].compareTo(a[ini]) > 0){
	    i--;
	}
	intercambia(a, i, ini);
	quickSort(a, ini, i-1);
	quickSort(a, i+1, fin);
    }
    
    /**
     * Ordena el arreglo recibido usando QickSort.
     * @param a un arreglo cuyos elementos son comparables.
     */
    public static <T extends Comparable<T>>
                     void quickSort(T[] a) {
	quickSort(a, 0, a.length-1);
    }

    /**
     * Ordena el arreglo recibido usando InsertionSort.
     * @param a un arreglo cuyos elementos son comparables.
     */
    public static <T extends Comparable<T>>
                     void insertionSort(T[] a) {
	int min;
	for(int i = 0; i < a.length; i++){
	    min = i;
	    for(int j = i; j < a.length; j++){
		if(a[j].compareTo(a[min]) < 0){
		    min = j;
		}
	    }
	    intercambia(a, i, min);
	}
    }

    /**
     * Hace una búsqueda binaria del elemento en el arreglo. Regresa
     * el índice del elemento en el arreglo, o -1 si no se
     * encuentra.
     * @param a el arreglo dónde buscar.
     * @param e el elemento a buscar.
     * @param ini la posición de el primer elemento del arreglo.
     * @param fin la posición de el último elemento del arreglo.
     * @return el índice del elemento en el arreglo, o -1 si no se
     * encuentra.
     */
    private static <T extends Comparable<T>>
			      int busquedaBinaria(T[] a, T e, int ini, int fin){
	if(fin < ini){
	    return -1;
	} 
	int m = (fin + ini) / 2;
	if(a[m].compareTo(e) == 0){
	    return m;
	} 
	if(a[m].compareTo(e) > 0){
	    return busquedaBinaria(a, e, ini, m -1);
	}
	return busquedaBinaria(a, e, m + 1, fin);
    }
    
    /**
     * Hace una búsqueda binaria del elemento en el arreglo. Regresa
     * el índice del elemento en el arreglo, o -1 si no se
     * encuentra.
     * @param a el arreglo dónde buscar.
     * @param e el elemento a buscar.
     * @return el índice del elemento en el arreglo, o -1 si no se
     * encuentra.
     */
     public static <T extends Comparable<T>>
                     int busquedaBinaria(T[] a, T e) {
	 return busquedaBinaria(a, e, 0, a.length -1);
    }	
} //Fin de Areglos.java
