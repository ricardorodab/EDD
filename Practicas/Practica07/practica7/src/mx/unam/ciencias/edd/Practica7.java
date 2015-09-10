package mx.unam.ciencias.edd;

import java.util.Random;

/**
 * Práctica 7: Gráficas.
 */
public class Practica7 {

    private static String cadena;

    public static void main(String[] args) {
        /*
         *    b─────d
         *   ╱│╲    │╲
         *  ╱ │ ╲   │ ╲
         * a  │  ╲  │  f
         *  ╲ │   ╲ │ ╱
         *   ╲│    ╲│╱
         *    c─────e
         */
        Grafica<String> g = new Grafica<String>();
        g.agrega("a");
        g.agrega("b");
        g.agrega("c");
        g.agrega("d");
        g.agrega("e");
        g.agrega("f");

        g.conecta("a", "b");
        g.conecta("a", "c");
        g.conecta("b", "c");
        g.conecta("b", "d");
        g.conecta("b", "e");
        g.conecta("c", "e");
        g.conecta("d", "e");
        g.conecta("d", "f");
        g.conecta("e", "f");

        /* BFS */
        g.paraCadaVertice(new AccionVerticeGrafica<String>() {
                public void actua(VerticeGrafica<String> vertice) {
                    vertice.setColor(Color.ROJO);
                }
            });
        Cola<VerticeGrafica<String>> c = new Cola<VerticeGrafica<String>>();
        VerticeGrafica<String> it = g.vertice("a");
        it.setColor(Color.NEGRO);
        c.mete(it);
        cadena = "BFS 1: ";
        while (!c.esVacia()) {
            it = c.saca();
            cadena += it.getElemento() + ", ";
            while (it.hayVecino()) {
                VerticeGrafica<String> vec = it.vecino();
                if (vec.getColor() == Color.ROJO) {
                    vec.setColor(Color.NEGRO);
                    c.mete(vec);
                }
            }
        }
        System.out.println(cadena);

        /* BFS de la clase */
        cadena = "BFS 2: ";
        g.bfs("a", new AccionVerticeGrafica<String>() {
                public void actua(VerticeGrafica<String> vertice) {
                    cadena += vertice.getElemento() + ", ";
                }
            });
        System.out.println(cadena);

        /* DFS */
        g.paraCadaVertice(new AccionVerticeGrafica<String>() {
                public void actua(VerticeGrafica<String> vertice) {
                    vertice.setColor(Color.ROJO);
                }
            });
        Pila<VerticeGrafica<String>> p = new Pila<VerticeGrafica<String>>();
        it = g.vertice("a");
        it.setColor(Color.NEGRO);
        p.mete(it);
        cadena = "DFS 1: ";
        while (!p.esVacia()) {
            it = p.saca();
            cadena += it.getElemento() + ", ";
            while (it.hayVecino()) {
                VerticeGrafica<String> vec = it.vecino();
                if (vec.getColor() == Color.ROJO) {
                    vec.setColor(Color.NEGRO);
                    p.mete(vec);
                }
            }
        }
        System.out.println(cadena);

        /* DFS de la clase */
        cadena = "DFS 2: ";
        g.dfs("a", new AccionVerticeGrafica<String>() {
                public void actua(VerticeGrafica<String> vertice) {
                    cadena += vertice.getElemento() + ", ";
                }
            });
        System.out.println(cadena);
    }
}
