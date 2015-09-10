package mx.unam.ciencias.edd.test;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Random;
import mx.unam.ciencias.edd.ArbolBinarioOrdenado;
import mx.unam.ciencias.edd.Cola;
import mx.unam.ciencias.edd.Lista;
import mx.unam.ciencias.edd.VerticeArbolBinario;
import org.junit.Assert;
import org.junit.Test;

/**
 * Clase para pruebas unitarias de la clase {@link
 * ArbolBinarioOrdenado}.
 */
public class TestArbolBinarioOrdenado {

    private int total;
    private Random random;
    private ArbolBinarioOrdenado<Integer> arbol;

    private static <T extends Comparable<T>> void
                      comparaSubarbol(VerticeArbolBinario<T> v,
                                      T elemento,
                                      boolean menores) {
        Cola<VerticeArbolBinario<T>> c = new Cola<VerticeArbolBinario<T>>();
        c.mete(v);
        while (!c.esVacia()) {
            VerticeArbolBinario<T> vv = c.saca();
            T el = vv.get();
            if (menores)
                Assert.assertTrue(el.compareTo(elemento) <= 0);
            else
                Assert.assertTrue(el.compareTo(elemento) >= 0);
            if (vv.hayIzquierdo())
                c.mete(vv.getIzquierdo());
            if (vv.hayDerecho())
                c.mete(vv.getDerecho());
        }
    }

    /* Método auxiliar recursivo para validad un árbol binario
     * ordenado. */
    private static <T extends Comparable<T>> void
                      arbolOrdenadoValido(VerticeArbolBinario<T> v) {
        T elemento = v.get();
        try {
            if (v.hayIzquierdo()) {
                VerticeArbolBinario<T> i = v.getIzquierdo();
                T izquierdo = i.get();
                Assert.assertTrue(izquierdo.compareTo(elemento) <= 0);
                comparaSubarbol(i, elemento, true);
                arbolOrdenadoValido(i);
            }
            if (v.hayDerecho()) {
                VerticeArbolBinario<T> d = v.getDerecho();
                T derecho = d.get();
                Assert.assertTrue(derecho.compareTo(elemento) >= 0);
                comparaSubarbol(d, elemento, false);
                arbolOrdenadoValido(d);
            }
        } catch (NoSuchElementException sdee) {
            Assert.fail();
        }
    }

    /**
     * Valida un árbol ordenado. Comprueba que para todo nodo A se
     * cumpla que si A tiene como hijo izquierdo a B, entonces B ≤
     * A, y si A tiene como hijo derecho a C, entonces A ≤ C.
     * @param arbol el árbol a revisar.
     */
    public static <T extends Comparable<T>> void
                     arbolOrdenadoValido(ArbolBinarioOrdenado<T> arbol) {
        if (arbol.getElementos() == 0)
            return;
        arbolOrdenadoValido(arbol.raiz());
    }

    /**
     * Crea un árbol binario para cada prueba.
     */
    public TestArbolBinarioOrdenado() {
        random = new Random();
        arbol = new ArbolBinarioOrdenado<Integer>();
        total = 1 + random.nextInt(100);
    }

    /**
     * Prueba unitaria para {@link ArbolBinarioOrdenado#agrega}.
     */
    @Test public void testAgrega() {
        for (int i = 0; i < total; i++) {
            int n = random.nextInt(100);
            arbol.agrega(n);
            TestArbolBinario.arbolValido(arbol);
            Assert.assertTrue(arbol.getElementos() == i+1);
            VerticeArbolBinario<Integer> it = arbol.busca(n);
            Assert.assertTrue(it != null);
            Assert.assertTrue(it.get() == n);
            arbolOrdenadoValido(arbol);
        }
    }

    /* Llena el árbol con elementos no repetidos. */
    private int[] arregloSinRepetidos() {
        int[] a = new int[total];
        for (int i = 0; i < total; i++) {
            int r;
            boolean repetido = false;
            do {
                r = random.nextInt(1000);
                repetido = false;
                for (int j = 0; j < i; j++)
                    if (r == a[j])
                        repetido = true;
            } while (repetido);
            a[i] = r;
        }
        return a;
    }

    /**
     * Prueba unitaria para {@link ArbolBinarioOrdenado#elimina}.
     */
    @Test public void testElimina() {
        int[] a = arregloSinRepetidos();
        for (int n : a)
            arbol.agrega(n);
        int n = total;
        while (arbol.getElementos() > 0) {
            Assert.assertTrue(arbol.getElementos() == n);
            int i = random.nextInt(total);
            if (a[i] == -1)
                continue;
            int e = a[i];
            VerticeArbolBinario<Integer> it = arbol.busca(e);
            Assert.assertTrue(it != null);
            Assert.assertTrue(it.get() == e);
            arbol.elimina(e);
            it = arbol.busca(e);
            Assert.assertTrue(it == null);
            Assert.assertTrue(arbol.getElementos() == --n);
            TestArbolBinario.arbolValido(arbol);
            arbolOrdenadoValido(arbol);
            a[i] = -1;
        }
    }

    /**
     * Prueba unitaria para {@link ArbolBinarioOrdenado#busca}.
     */
    @Test public void testBusca() {
        int[] a = arregloSinRepetidos();
        for (int n : a)
            arbol.agrega(n);
        for (int i : a) {
            VerticeArbolBinario<Integer> it = arbol.busca(i);
            Assert.assertTrue(it != null);
            Assert.assertTrue(it.get() == i);
        }
        int m = 1500 + random.nextInt(100);
        Assert.assertTrue(arbol.busca(m) == null);
    }

    /**
     * Prueba unitaria para {@link ArbolBinarioOrdenado#iterator}.
     */
    @Test public void testIterator() {
        Lista<Integer> lista = new Lista<Integer>();
        for (int i = 0; i < total; i++) {
            int n = random.nextInt(100);
            arbol.agrega(n);
            lista.agregaFinal(n);
        }
        lista = Lista.mergeSort(lista);
        int c = 0;
        Iterator<Integer> i1 = arbol.iterator();
        Iterator<Integer> i2 = lista.iterator();
        while (i1.hasNext() && i2.hasNext())
            Assert.assertTrue(i1.next() == i2.next());
        Assert.assertTrue(!i1.hasNext() && !i2.hasNext());
    }
}
