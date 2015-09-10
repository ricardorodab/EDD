#include <time.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <lista.h>
#include <arbolbinario.h>

#define N 100
#define GRAN_N 10000

static int
ab_valida_nodos(NodoArbolBinario* nodo)
{
        if (nodo == NULL)
                return 0;
        NodoArbolBinario* izq = nodo_arbol_binario_izquierdo(nodo);
        NodoArbolBinario* der = nodo_arbol_binario_derecho(nodo);
        if (izq != NULL)
                fail_unless(nodo_arbol_binario_padre(izq) == nodo);
        if (der != NULL)
                fail_unless(nodo_arbol_binario_padre(der) == nodo);
        return 1 + ab_valida_nodos(izq) + ab_valida_nodos(der);
}

static bool
arbol_binario_valido(ArbolBinario* arbol)
{
        fail_unless(ab_valida_nodos(arbol_binario_raiz(arbol)) ==
                    arbol_binario_elementos(arbol));
        return true;
}

static void
mete_ordenados(NodoArbolBinario* nodo,
               Lista*            lista)
{
        if (nodo == NULL)
                return;
        mete_ordenados(nodo_arbol_binario_izquierdo(nodo), lista);
        lista_agrega_final(lista, nodo_arbol_binario_elemento(nodo));
        mete_ordenados(nodo_arbol_binario_derecho(nodo), lista);
}

static bool
arbol_binario_ordenado_valido(ArbolBinario* arbol)
{
        Lista* lista = lista_nueva();
        mete_ordenados(arbol_binario_raiz(arbol), lista);
        fail_unless(lista_longitud(lista) == arbol_binario_elementos(arbol));
        fail_unless(lista_esta_ordenada(lista, compara_enteros));
        return true;
}

static bool
ar_valida_colores(NodoArbolBinario* nodo)
{
        if (nodo == NULL)
                return true;
        NodoArbolBinario* izq = nodo_arbol_binario_izquierdo(nodo);
        NodoArbolBinario* der = nodo_arbol_binario_derecho(nodo);
        if (nodo_arbol_binario_color(nodo) == COLOR_ROJO) {
                fail_if(izq != NULL &&
                        nodo_arbol_binario_color(izq) == COLOR_ROJO);
                fail_if(der != NULL &&
                        nodo_arbol_binario_color(der) == COLOR_ROJO);
        }
        return ar_valida_colores(izq) && ar_valida_colores(der);
}

static int
ar_cuenta_negros(NodoArbolBinario* nodo)
{
        if (nodo == NULL)
                return 1;
        NodoArbolBinario* izq = nodo_arbol_binario_izquierdo(nodo);
        NodoArbolBinario* der = nodo_arbol_binario_derecho(nodo);
        int li = ar_cuenta_negros(izq);
        int ld = ar_cuenta_negros(der);
        fail_unless(li == ld);
        if (nodo_arbol_binario_color(nodo) == COLOR_ROJO)
                return li;
        else
                return 1 + ld;
}

static bool
arbol_rojinegro_valido(ArbolBinario* arbol)
{
        NodoArbolBinario* raiz = arbol_binario_raiz(arbol);
        if (raiz == NULL)
                return true;
        fail_unless(nodo_arbol_binario_color(raiz) == COLOR_NEGRO);
        fail_unless(ar_valida_colores(raiz));
        fail_unless(ar_cuenta_negros(raiz) > 0);
        return true;
}

/* Prueba unitaria para arbol_binario_raiz. */
START_TEST(test_arbol_binario_raiz)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        fail_unless(arbol_binario_raiz(arbol) == NULL);
        int n = 0;
        arbol_binario_ordenado_agrega(arbol, &n);
        NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
        fail_unless(arbol_binario_raiz(arbol) != NULL);
        fail_unless(nodo_arbol_binario_padre(nodo) == NULL);
        void* e = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(e, &n));
        arbol_binario_libera(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_elementos. */
START_TEST(test_arbol_binario_elementos)
{
        srand((unsigned int)time(NULL));
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                arbol_binario_ordenado_agrega(arbol, n);
                fail_unless(arbol_binario_elementos(arbol) == i + 1);
        }
        for (int i = 0; i < total; i++) {
                NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
                int* n = nodo_arbol_binario_elemento(nodo);
                arbol_binario_ordenado_elimina(arbol, n);
                fail_unless(arbol_binario_elementos(arbol) == total - i - 1);
                free(n);
        }
        arbol_binario_libera(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_profundidad. */
START_TEST(test_arbol_binario_profundidad)
{
        srand((unsigned int)time(NULL));
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        fail_unless(arbol_binario_profundidad(arbol) == -1);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(i);
                arbol_binario_ordenado_agrega(arbol, n);
                fail_unless(arbol_binario_profundidad(arbol) == i);
        }
        for (int i = 0; i < total; i++) {
                NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
                int* n = nodo_arbol_binario_elemento(nodo);
                arbol_binario_ordenado_elimina(arbol, n);
                fail_unless(arbol_binario_profundidad(arbol) == total - i - 2);
                free(n);
        }
        arbol_binario_libera(arbol);
}
END_TEST

static int*
arreglo_sin_repetidos(int total)
{
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                int r;
                bool repetido = false;
                do {
                        r = rand() % GRAN_N;
                        repetido = false;
                        for (int j = 0; j < i; j++)
                                if (r == a[j])
                                        repetido = true;
                } while (repetido);
                a[i] = r;
        }
        return a;
}


/* Prueba unitaria para arbol_binario_gira_izquierda. */
START_TEST(test_arbol_binario_gira_izquierda)
{
        srand((unsigned int)time(NULL));
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        if (total == 1)
            total++;
        int* a = arreglo_sin_repetidos(total);
        a[total-2] = 2000;
        a[total-1] = 2001;
        for (int i = 0; i < total; i++)
                arbol_binario_ordenado_agrega(arbol, &a[i]);
        NodoArbolBinario* nodo = NULL;
        int P = -1;
        do {
                P = a[rand() % total];
                nodo = arbol_binario_ordenado_busca(arbol, &P);
                fail_unless(nodo != NULL);
                void* e = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(e, &P));
        } while (nodo_arbol_binario_derecho(nodo) == NULL);
        nodo = nodo_arbol_binario_derecho(nodo);
        int* n = nodo_arbol_binario_elemento(nodo);
        int Q = *n;
        int A = -1, B = -1, C = -1;
        if (nodo_arbol_binario_izquierdo(nodo) != NULL) {
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                B = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        if (nodo_arbol_binario_derecho(nodo) != NULL) {
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                C = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        nodo = nodo_arbol_binario_padre(nodo);
        if (nodo_arbol_binario_izquierdo(nodo) != NULL) {
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                A = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        arbol_binario_gira_izquierda(arbol, nodo);
        fail_unless(arbol_binario_elementos(arbol) == total);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        for (int i = 0; i < total; i++) {
                NodoArbolBinario* tmp;
                tmp = arbol_binario_ordenado_busca(arbol, &a[i]);
                fail_unless(tmp != NULL);
        }
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &P));
        fail_unless(nodo_arbol_binario_padre(nodo) != NULL);
        nodo = nodo_arbol_binario_padre(nodo);
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &Q));
        if (C != -1) {
                fail_unless(nodo_arbol_binario_derecho(nodo) != NULL);
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &C));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        fail_unless(nodo_arbol_binario_izquierdo(nodo) != NULL);
        nodo = nodo_arbol_binario_izquierdo(nodo);
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &P));
        if (A != -1) {
                fail_unless(nodo_arbol_binario_izquierdo(nodo) != NULL);
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &A));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        if (B != -1) {
                fail_unless(nodo_arbol_binario_derecho(nodo) != NULL);
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &B));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        arbol_binario_libera(arbol);
        free(a);
}
END_TEST

/* Prueba unitaria para arbol_binario_gira_derecha. */
START_TEST(test_arbol_binario_gira_derecha)
{
        srand((unsigned int)time(NULL));
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        if (total == 1)
            total++;
        int* a = arreglo_sin_repetidos(total);
        a[total-2] = 2001;
        a[total-1] = 2000;
        for (int i = 0; i < total; i++)
                arbol_binario_ordenado_agrega(arbol, &a[i]);
        NodoArbolBinario* nodo = NULL;
        int Q = -1;
        do {
                Q = a[rand() % total];
                nodo = arbol_binario_ordenado_busca(arbol, &Q);
                fail_unless(nodo != NULL);
                void* e = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(e, &Q));
        } while (nodo_arbol_binario_izquierdo(nodo) == NULL);
        nodo = nodo_arbol_binario_izquierdo(nodo);
        int* n = nodo_arbol_binario_elemento(nodo);
        int P = *n;
        int A = -1, B = -1, C = -1;
        if (nodo_arbol_binario_izquierdo(nodo) != NULL) {
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                A = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        if (nodo_arbol_binario_derecho(nodo) != NULL) {
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                B = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        nodo = nodo_arbol_binario_padre(nodo);
        if (nodo_arbol_binario_derecho(nodo) != NULL) {
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                C = *n;
                nodo = nodo_arbol_binario_padre(nodo);
        }
        arbol_binario_gira_derecha(arbol, nodo);
        fail_unless(arbol_binario_elementos(arbol) == total);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        for (int i = 0; i < total; i++) {
                NodoArbolBinario* tmp;
                tmp = arbol_binario_ordenado_busca(arbol, &a[i]);
                fail_unless(tmp != NULL);
        }
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &Q));
        fail_unless(nodo_arbol_binario_padre(nodo) != NULL);
        nodo = nodo_arbol_binario_padre(nodo);
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &P));
        if (A != -1) {
                fail_unless(nodo_arbol_binario_izquierdo(nodo) != NULL);
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &A));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        fail_unless(nodo_arbol_binario_derecho(nodo) != NULL);
        nodo = nodo_arbol_binario_derecho(nodo);
        n = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(n, &Q));
        if (B != -1) {
                fail_unless(nodo_arbol_binario_izquierdo(nodo) != NULL);
                nodo = nodo_arbol_binario_izquierdo(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &B));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        if (C != -1) {
                fail_unless(nodo_arbol_binario_derecho(nodo) != NULL);
                nodo = nodo_arbol_binario_derecho(nodo);
                n = nodo_arbol_binario_elemento(nodo);
                fail_unless(!compara_enteros(n, &C));
                nodo = nodo_arbol_binario_padre(nodo);
        }
        arbol_binario_libera(arbol);
        free(a);
}
END_TEST

/* Prueba unitaria para arbol_binario_es_ordenado. */
START_TEST(test_arbol_binario_es_ordenado)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                arbol_binario_ordenado_agrega(arbol, n);
                fail_unless(arbol_binario_es_ordenado(arbol, compara_enteros));
        }
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_es_rojinegro. */
START_TEST(test_arbol_binario_es_rojinegro)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        fail_unless(arbol_binario_es_rojinegro(arbol));
        arbol_binario_libera(arbol);
        arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        fail_if(arbol_binario_es_rojinegro(arbol));
        arbol_binario_libera(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_a_cadena. */
START_TEST(test_arbol_binario_a_cadena)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        arbol_binario_ordenado_agrega(arbol, entero_nuevo(1));
        arbol_binario_ordenado_agrega(arbol, entero_nuevo(0));
        arbol_binario_ordenado_agrega(arbol, entero_nuevo(2));
        char* s;
        s = arbol_binario_a_cadena(arbol, FUNC_A_CADENA(pentero_a_cadena));
        const char* t = "1\n"
                "├─›0\n"
                "└─»2\n";
        fail_unless(!strcmp(s, t));
        free(s);
}
END_TEST

/* Prueba unitaria para arbol_binario_libera. */
START_TEST(test_arbol_binario_libera)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % GRAN_N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % total;
                arbol_binario_ordenado_agrega(arbol, &a[i]);
        }
        arbol_binario_libera(arbol);
        free(a);
}
END_TEST

/* Prueba unitaria para arbol_binario_libera_todo. */
START_TEST(test_arbol_binario_libera_todo)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % GRAN_N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                arbol_binario_ordenado_agrega(arbol, n);
        }
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_ordenado_nuevo. */
START_TEST(test_arbol_binario_ordenado_nuevo)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        fail_unless(arbol != NULL);
        fail_unless(arbol_binario_es_ordenado(arbol, NULL));
        fail_unless(arbol_binario_raiz(arbol) == NULL);
        fail_unless(arbol_binario_elementos(arbol) == 0);
        arbol_binario_libera(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_ordenado_agrega. */
START_TEST(test_arbol_binario_ordenado_agrega)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                arbol_binario_ordenado_agrega(arbol, n);
                fail_unless(arbol_binario_valido(arbol));
                fail_unless(arbol_binario_ordenado_valido(arbol));
                fail_unless(arbol_binario_elementos(arbol) == i+1);
                fail_unless(arbol_binario_ordenado_busca(arbol, n) != NULL);
        }
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para arbol_binario_ordenado_busca. */
START_TEST(test_arbol_binario_ordenado_busca)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % total;
                arbol_binario_ordenado_agrega(arbol, &a[i]);
        }
        for (int i = 0; i < total; i++)
                fail_unless(arbol_binario_ordenado_busca(arbol, &a[i]) !=
                            NULL);
        int n = -1;
        fail_unless(arbol_binario_ordenado_busca(arbol, &n) == NULL);
        n = total;
        fail_unless(arbol_binario_ordenado_busca(arbol, &n) == NULL);
        arbol_binario_libera(arbol);
        free(a);
}
END_TEST

/* Prueba unitaria para arbol_binario_ordenado_elimina. */
START_TEST(test_arbol_binario_ordenado_elimina)
{
        ArbolBinario* arbol = arbol_binario_ordenado_nuevo(compara_enteros);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(i);
                arbol_binario_ordenado_agrega(arbol, n);
        }
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        fail_unless(arbol_binario_elementos(arbol) == total);
        int t = -1;
        arbol_binario_ordenado_elimina(arbol, &t);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        fail_unless(arbol_binario_elementos(arbol) == total);
        t = total;
        arbol_binario_ordenado_elimina(arbol, &t);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        fail_unless(arbol_binario_elementos(arbol) == total);
        for (int i = 0; i < total; i++) {
                arbol_binario_ordenado_elimina(arbol, &i);
                fail_unless(arbol_binario_valido(arbol));
                fail_unless(arbol_binario_ordenado_valido(arbol));
                fail_unless(arbol_binario_elementos(arbol) == total-i-1);
                fail_unless(arbol_binario_ordenado_busca(arbol, &i) == NULL);
        }
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para arbol_rojinegro_nuevo. */
START_TEST(test_arbol_rojinegro_nuevo)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        fail_unless(arbol != NULL);
        fail_unless(arbol_binario_es_ordenado(arbol, NULL));
        fail_unless(arbol_binario_es_rojinegro(arbol));
        fail_unless(arbol_binario_raiz(arbol) == NULL);
        fail_unless(arbol_binario_elementos(arbol) == 0);
        arbol_binario_libera(arbol);
}
END_TEST

/* Prueba unitaria para arbol_rojinegro_agrega. */
START_TEST(test_arbol_rojinegro_agrega)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                arbol_rojinegro_agrega(arbol, n);
                fail_unless(arbol_binario_valido(arbol));
                fail_unless(arbol_binario_ordenado_valido(arbol));
                fail_unless(arbol_rojinegro_valido(arbol));
                fail_unless(arbol_binario_elementos(arbol) == i+1);
                fail_unless(arbol_binario_ordenado_busca(arbol, n) != NULL);
        }
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para arbol_rojinegro_elimina. */
START_TEST(test_arbol_rojinegro_elimina)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        int total = 10;//rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(i);
                arbol_rojinegro_agrega(arbol, n);
        }
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        fail_unless(arbol_rojinegro_valido(arbol));
        fail_unless(arbol_binario_elementos(arbol) == total);
        int t = -1;
        arbol_rojinegro_elimina(arbol, &t);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        fail_unless(arbol_rojinegro_valido(arbol));
        fail_unless(arbol_binario_elementos(arbol) == total);
        t = total;
        arbol_rojinegro_elimina(arbol, &t);
        fail_unless(arbol_binario_valido(arbol));
        fail_unless(arbol_binario_ordenado_valido(arbol));
        fail_unless(arbol_rojinegro_valido(arbol));
        fail_unless(arbol_binario_elementos(arbol) == total);
        for (int i = 0; i < total; i++) {
                arbol_rojinegro_elimina(arbol, &i);
                fail_unless(arbol_binario_valido(arbol));
                fail_unless(arbol_binario_ordenado_valido(arbol));
                fail_unless(arbol_rojinegro_valido(arbol));
                fail_unless(arbol_binario_elementos(arbol) == total-i-1);
                fail_unless(arbol_binario_ordenado_busca(arbol, &i) == NULL);
        }
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para nodo_arbol_binario_elemento. */
START_TEST(test_nodo_arbol_binario_elemento)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        int n = rand() % N;
        arbol_rojinegro_agrega(arbol, &n);
        NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
        fail_unless(nodo != NULL);
        int* e = nodo_arbol_binario_elemento(nodo);
        fail_unless(!compara_enteros(e, &n));
        arbol_binario_libera(arbol);
}
END_TEST

/* Prueba unitaria para nodo_arbol_binario_padre. */
START_TEST(test_nodo_arbol_binario_padre)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        arbol_rojinegro_agrega(arbol, entero_nuevo(0));
        arbol_rojinegro_agrega(arbol, entero_nuevo(1));
        int n = 1;
        NodoArbolBinario* nodo = arbol_binario_ordenado_busca(arbol, &n);
        NodoArbolBinario* padre = nodo_arbol_binario_padre(nodo);
        fail_unless(padre != NULL);
        n = 0;
        int* e = nodo_arbol_binario_elemento(padre);
        fail_unless(!compara_enteros(e, &n));
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para nodo_arbol_binario_izquierdo. */
START_TEST(test_nodo_arbol_binario_izquierdo)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        arbol_rojinegro_agrega(arbol, entero_nuevo(1));
        arbol_rojinegro_agrega(arbol, entero_nuevo(0));
        NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
        NodoArbolBinario* izq = nodo_arbol_binario_izquierdo(nodo);
        fail_unless(izq != NULL);
        int n = 0;
        int* e = nodo_arbol_binario_elemento(izq);
        fail_unless(!compara_enteros(e, &n));
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para nodo_arbol_binario_derecho. */
START_TEST(test_nodo_arbol_binario_derecho)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        arbol_rojinegro_agrega(arbol, entero_nuevo(0));
        arbol_rojinegro_agrega(arbol, entero_nuevo(1));
        NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
        NodoArbolBinario* der = nodo_arbol_binario_derecho(nodo);
        fail_unless(der != NULL);
        int n = 1;
        int* e = nodo_arbol_binario_elemento(der);
        fail_unless(!compara_enteros(e, &n));
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para nodo_arbol_binario_color. */
START_TEST(test_nodo_arbol_binario_color)
{
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        arbol_rojinegro_agrega(arbol, entero_nuevo(0));
        NodoArbolBinario* nodo = arbol_binario_raiz(arbol);
        fail_unless(nodo != NULL);
        fail_unless(nodo_arbol_binario_color(nodo) == COLOR_NEGRO);
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Prueba unitaria para ARBOL_BINARIO_PARA_CADA_NODO. */
START_TEST(test_ARBOL_BINARIO_PARA_CADA_NODO)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        ArbolBinario* arbol = arbol_rojinegro_nuevo(compara_enteros);
        for (int i = 0; i < total; i++)
                arbol_rojinegro_agrega(arbol, entero_nuevo(i));
        int i = 0;
        ARBOL_BINARIO_PARA_CADA_NODO(nodo, arbol, {
                        int* n = nodo_arbol_binario_elemento(nodo);
                        fail_unless(i++ == *n);
                });
        fail_unless(i == total);
        arbol_binario_libera_todo(arbol);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
arbol_binario_suite(void)
{
        Suite *s = suite_create("Árbol binario");

        TCase *tc_arbol_binario =
                tcase_create("Funciones de la estructura árbol binario");
        tcase_add_test(tc_arbol_binario, test_arbol_binario_raiz);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_elementos);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_profundidad);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_gira_izquierda);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_gira_derecha);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_es_ordenado);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_es_rojinegro);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_a_cadena);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_libera);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_libera_todo);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_ordenado_nuevo);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_ordenado_agrega);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_ordenado_busca);
        tcase_add_test(tc_arbol_binario, test_arbol_binario_ordenado_elimina);
        tcase_add_test(tc_arbol_binario, test_arbol_rojinegro_nuevo);
        tcase_add_test(tc_arbol_binario, test_arbol_rojinegro_agrega);
        tcase_add_test(tc_arbol_binario, test_arbol_rojinegro_elimina);
        tcase_add_test(tc_arbol_binario, test_nodo_arbol_binario_elemento);
        tcase_add_test(tc_arbol_binario, test_nodo_arbol_binario_padre);
        tcase_add_test(tc_arbol_binario, test_nodo_arbol_binario_izquierdo);
        tcase_add_test(tc_arbol_binario, test_nodo_arbol_binario_derecho);
        tcase_add_test(tc_arbol_binario, test_nodo_arbol_binario_color);
        tcase_add_test(tc_arbol_binario, test_ARBOL_BINARIO_PARA_CADA_NODO);
        suite_add_tcase(s, tc_arbol_binario);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = arbol_binario_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
