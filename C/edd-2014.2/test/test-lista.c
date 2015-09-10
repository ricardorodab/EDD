#include <time.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <lista.h>

#define N 100
#define GRAN_N 10000

static bool
lista_consistente(Lista* lista)
{
        int n = lista_longitud(lista);
        int* a = ARREGLO(int, n);
        int* b = ARREGLO(int, n);
        NodoLista* nodo = lista_cabeza(lista);
        for (int i = 0; i < n; i++) {
                fail_if(nodo == NULL);
                int* v = nodo_lista_elemento(nodo);
                a[i] = *v;
                nodo = nodo_lista_siguiente(nodo);
        }
        fail_if(nodo != NULL);
        nodo = lista_rabo(lista);
        for (int i = n - 1; i >= 0; i--) {
                fail_if(nodo == NULL);
                int* v = nodo_lista_elemento(nodo);
                b[i] = *v;
                nodo = nodo_lista_anterior(nodo);
        }
        fail_if(nodo != NULL);
        for (int i = 0; i < n; i++)
                fail_if(a[i] != b[i]);
        free(a);
        free(b);
        return true;
}

/* Prueba unitaria para lista_nueva. */
START_TEST(test_lista_nueva)
{
        Lista* lista = lista_nueva();
        fail_unless(lista != NULL);
        fail_unless(lista_cabeza(lista) == NULL);
        fail_unless(lista_rabo(lista) == NULL);
        fail_unless(lista_longitud(lista) == 0);
        fail_unless(lista_consistente(lista));
        int n = 0;
        fail_unless(lista_busca(lista, &n, compara_enteros) == NULL);
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_cabeza. */
START_TEST(test_lista_cabeza)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        fail_unless(lista_cabeza(lista) == NULL);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                lista_agrega_inicio(lista, n);
                NodoLista* nodo = lista_cabeza(lista);
                void* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(n, e));
                fail_unless(lista_consistente(lista));
        }
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_rabo. */
START_TEST(test_lista_rabo)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        fail_unless(lista_rabo(lista) == NULL);
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                lista_agrega_final(lista, n);
                NodoLista* nodo = lista_rabo(lista);
                void* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(n, e));
                fail_unless(lista_consistente(lista));
        }
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_longitud. */
START_TEST(test_lista_longitud)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                int* n = entero_nuevo(rand() % total);
                lista_agrega_final(lista, n);
                fail_unless(lista_longitud(lista) == i + 1);
        }
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_agrega_inicio. */
START_TEST(test_lista_agrega_inicio)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        Lista* lista = lista_nueva();
        int* a = ARREGLO(int*, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % total;
                lista_agrega_inicio(lista, &a[i]);
                NodoLista* nodo = lista_cabeza(lista);
                int* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(e, &a[i]));
                fail_unless(lista_longitud(lista) == i + 1);
                fail_unless(lista_consistente(lista));
        }
        NodoLista* tmp = lista_cabeza(lista);
        for (int i = 0; i < total; i++) {
                int* e = nodo_lista_elemento(tmp);
                fail_unless(!compara_enteros(e, &a[total-i-1]));
                tmp = nodo_lista_siguiente(tmp);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_agrega_final. */
START_TEST(test_lista_agrega_final)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % total;
                lista_agrega_final(lista, &a[i]);
                NodoLista* nodo = lista_rabo(lista);
                int* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(e, &a[i]));
                fail_unless(lista_longitud(lista) == i + 1);
                fail_unless(lista_consistente(lista));
        }
        NodoLista* tmp = lista_cabeza(lista);
        for (int i = 0; i < total; i++) {
                int* e = nodo_lista_elemento(tmp);
                fail_unless(!compara_enteros(e, &a[i]));
                tmp = nodo_lista_siguiente(tmp);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_inserta_antes. */
START_TEST(test_lista_inserta_antes)
{
        Lista* lista = lista_nueva();
        lista_agrega_final(lista, entero_nuevo(1));
        lista_agrega_final(lista, entero_nuevo(3));
        NodoLista* nodo = lista_rabo(lista);
        lista_inserta_antes(lista, nodo, entero_nuevo(2));
        fail_unless(lista_consistente(lista));
        fail_unless(lista_esta_ordenada(lista, compara_enteros));
        nodo = lista_cabeza(lista);
        lista_inserta_antes(lista, nodo, entero_nuevo(0));
        fail_unless(lista_consistente(lista));
        fail_unless(lista_esta_ordenada(lista, compara_enteros));
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_inserta_despues. */
START_TEST(test_lista_inserta_despues)
{
        Lista* lista = lista_nueva();
        lista_agrega_final(lista, entero_nuevo(0));
        lista_agrega_final(lista, entero_nuevo(2));
        NodoLista* nodo = lista_cabeza(lista);
        lista_inserta_despues(lista, nodo, entero_nuevo(1));
        fail_unless(lista_consistente(lista));
        fail_unless(lista_esta_ordenada(lista, compara_enteros));
        nodo = lista_rabo(lista);
        lista_inserta_despues(lista, nodo, entero_nuevo(3));
        fail_unless(lista_consistente(lista));
        fail_unless(lista_esta_ordenada(lista, compara_enteros));
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_elimina. */
START_TEST(test_lista_elimina)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        fail_unless(lista_cabeza(lista) == NULL);
        fail_unless(lista_rabo(lista) == NULL);
        fail_unless(lista_longitud(lista) == 0);
        fail_unless(lista_consistente(lista));
        int t = 0;
        lista_elimina(lista, &t, compara_enteros);
        fail_unless(lista_cabeza(lista) == NULL);
        fail_unless(lista_rabo(lista) == NULL);
        fail_unless(lista_longitud(lista) == 0);
        fail_unless(lista_consistente(lista));
        int total = 5 + rand() % N;
        int* a = ARREGLO(int*, total);
        for (int i = 0; i < total; i++) {
                a[i] = i;
                lista_agrega_final(lista, &a[i]);
                fail_unless(lista_consistente(lista));
        }
        fail_unless(lista_longitud(lista) == total);
        int* e;
        e = nodo_lista_elemento(lista_cabeza(lista));
        fail_unless(!compara_enteros(e, &a[0]));
        e = nodo_lista_elemento(lista_dame(lista, total/2));
        fail_unless(!compara_enteros(e, &a[total/2]));
        e = nodo_lista_elemento(lista_rabo(lista));
        fail_unless(!compara_enteros(e, &a[total-1]));

        lista_elimina(lista, &a[total/2], compara_enteros);
        fail_unless(lista_consistente(lista));
        fail_unless(lista_busca(lista, &a[total/2],
                                compara_enteros) == NULL);
        fail_unless(lista_longitud(lista) == total - 1);
        lista_elimina(lista, &a[0], compara_enteros);
        fail_unless(lista_consistente(lista));
        fail_unless(lista_busca(lista, &a[0],
                                compara_enteros) == NULL);
        fail_unless(lista_longitud(lista) == total - 2);
        lista_elimina(lista, &a[total-1], compara_enteros);
        fail_unless(lista_consistente(lista));
        fail_unless(lista_busca(lista, &a[total-1],
                                compara_enteros) == NULL);
        fail_unless(lista_longitud(lista) == total - 3);
        int i = 3;
        while (lista_longitud(lista) > 0) {
                e = nodo_lista_elemento(lista_cabeza(lista));
                lista_elimina(lista, e, compara_enteros);
                fail_unless(lista_consistente(lista));
                fail_unless(lista_longitud(lista) == total - (++i));
                fail_unless(lista_busca(lista, e,
                                        compara_enteros) == NULL);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_elimina_primero. */
START_TEST(test_lista_elimina_primero)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = i;
                lista_agrega_final(lista, &a[i]);
        }
        int i = 0;
        while (lista_longitud(lista) > 0) {
                void* e = nodo_lista_elemento(lista_cabeza(lista));
                fail_unless(!compara_enteros(e, &a[i]));
                e = lista_elimina_primero(lista);
                fail_unless(lista_consistente(lista));
                fail_unless(!compara_enteros(e, &a[i++]));
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_elimina_ultimo. */
START_TEST(test_lista_elimina_ultimo)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = i;
                lista_agrega_final(lista, &a[i]);
        }
        int i = total - 1;
        while (lista_longitud(lista) > 0) {
                void* e = nodo_lista_elemento(lista_rabo(lista));
                fail_unless(!compara_enteros(e, &a[i]));
                e = lista_elimina_ultimo(lista);
                fail_unless(lista_consistente(lista));
                fail_unless(!compara_enteros(e, &a[i--]));
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_elimina_nodo. */
START_TEST(test_lista_elimina_nodo)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int*, total);
        for (int i = 0; i < total; i++) {
                a[i] = i;
                lista_agrega_final(lista, &a[i]);
        }
        fail_unless(lista_longitud(lista) == total);
        while (lista_longitud(lista) > 0) {
                int n = lista_longitud(lista);
                NodoLista* nodo = lista_dame(lista, rand() % n);
                int* e = nodo_lista_elemento(nodo);
                lista_elimina_nodo(lista, nodo);
                fail_unless(lista_consistente(lista));
                fail_unless(lista_busca(lista, e,
                                        compara_enteros) == NULL);
                fail_unless(lista_longitud(lista) == --total);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_busca. */
START_TEST(test_lista_busca)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = i;
                lista_agrega_final(lista, &a[i]);
        }
        for (int i = 0; i < total; i++)
                fail_unless(lista_busca(lista, &a[i],
                                        compara_enteros) != NULL);
        int n = -1;
        fail_unless(lista_busca(lista, &n,
                                compara_enteros) == NULL);
        n = total;
        fail_unless(lista_busca(lista, &n,
                                compara_enteros) == NULL);
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_dame. */
START_TEST(test_lista_dame)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = i;
                lista_agrega_final(lista, &a[i]);
        }
        for (int i = 0; i < total; i++) {
                NodoLista* nodo = lista_dame(lista, i);
                void* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(e, &a[i]));
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_reversa. */
START_TEST(test_lista_reversa)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                void* e = entero_nuevo(rand() % N);
                lista_agrega_final(lista, e);
        }
        Lista* reversa = lista_reversa(lista);
        fail_unless(lista_consistente(reversa));
        NodoLista* nl = lista_cabeza(lista);
        NodoLista* nr = lista_rabo(reversa);
        while (nl != NULL && nr != NULL) {
                void* nle = nodo_lista_elemento(nl);
                void* nre = nodo_lista_elemento(nr);
                fail_unless(!compara_enteros(nle, nre));
                nl = nodo_lista_siguiente(nl);
                nr = nodo_lista_anterior(nr);
        }
        fail_unless(nl == NULL && nr == NULL);
        lista_libera(lista);
        lista_libera_todo(reversa);
}
END_TEST

/* Prueba unitaria para lista_copia. */
START_TEST(test_lista_copia)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                void* e = entero_nuevo(rand() % N);
                lista_agrega_final(lista, e);
        }
        Lista* copia = lista_copia(lista);
        fail_unless(lista_consistente(copia));
        NodoLista* nl = lista_cabeza(lista);
        NodoLista* nc = lista_cabeza(copia);
        while (nl != NULL && nc != NULL) {
                void* nle = nodo_lista_elemento(nl);
                void* nce = nodo_lista_elemento(nc);
                fail_unless(!compara_enteros(nle, nce));
                nl = nodo_lista_siguiente(nl);
                nc = nodo_lista_siguiente(nc);
        }
        fail_unless(nl == NULL && nc == NULL);
        lista_libera(lista);
        lista_libera_todo(copia);
}
END_TEST

/* Prueba unitaria para lista_esta_ordenada. */
START_TEST(test_lista_esta_ordenada)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        fail_unless(lista_esta_ordenada(lista, compara_enteros));
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                void* e = entero_nuevo(i);
                lista_agrega_final(lista, e);
                fail_unless(lista_esta_ordenada(lista, compara_enteros));
        }
        lista_libera_todo(lista);
        lista = lista_nueva();
        lista_agrega_final(lista, entero_nuevo(0));
        for (int i = 1; i < total; i++) {
                void* e = entero_nuevo(i);
                if ((i % 2) == 0)
                        lista_agrega_final(lista, e);
                else
                        lista_agrega_inicio(lista, e);
                fail_unless(!lista_esta_ordenada(lista, compara_enteros));
        }
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_ordenada_busca. */
START_TEST(test_lista_ordenada_busca)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                void* e = entero_nuevo(i);
                lista_agrega_final(lista, e);
        }
        NodoLista* nodo;
        for (int i = 0; i < total; i++) {
                nodo = lista_ordenada_busca(lista, &i,
                                            compara_enteros);
                fail_unless(nodo != NULL);
        }
        int n = -1;
        nodo = lista_ordenada_busca(lista, &n, compara_enteros);
        fail_unless(nodo == NULL);
        n = total;
        nodo = lista_ordenada_busca(lista, &n, compara_enteros);
        fail_unless(nodo == NULL);
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para lista_mergesort. */
START_TEST(test_lista_mergesort)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = 2 + rand() % N;
        for (int i = 0; i < total; i++) {
                void* e = entero_nuevo(i);
                if ((i % 2) == 0)
                        lista_agrega_final(lista, e);
                else
                        lista_agrega_inicio(lista, e);
        }
        fail_unless(!lista_esta_ordenada(lista, compara_enteros));
        Lista* ordenada = lista_mergesort(lista, compara_enteros);
        fail_unless(lista_esta_ordenada(ordenada, compara_enteros));
        fail_unless(lista_longitud(lista) ==
                    lista_longitud(ordenada));
        LISTA_PARA_CADA(int*, e, lista, {
                        NodoLista* nodo;
                        nodo = lista_busca(ordenada, e, compara_enteros);
                        fail_unless(nodo != NULL);
                });
        lista_libera_todo(lista);
        lista_libera(ordenada);
}
END_TEST

/* Prueba unitaria para lista_libera. */
START_TEST(test_lista_libera)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % GRAN_N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % GRAN_N;
                lista_agrega_final(lista, &a[i]);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para lista_libera_todo. */
START_TEST(test_lista_libera_todo)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % GRAN_N;
        for (int i = 0; i < total; i++) {
                void* e = entero_nuevo(rand() % GRAN_N);
                lista_agrega_final(lista, e);
        }
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para nodo_lista_elemento. */
START_TEST(test_nodo_lista_elemento)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                lista_agrega_final(lista, &a[i]);
        }
        for (int i = 0; i < total; i++) {
                NodoLista* nodo = lista_dame(lista, i);
                fail_unless(nodo != NULL);
                void* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(e, &a[i]));
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para nodo_lista_anterior. */
START_TEST(test_nodo_lista_anterior)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                lista_agrega_final(lista, &a[i]);
        }
        NodoLista* nodo = lista_rabo(lista);
        int c = total-1;
        while (nodo != NULL) {
                void* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(e, &a[c--]));
                nodo = nodo_lista_anterior(nodo);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para nodo_lista_siguiente. */
START_TEST(test_nodo_lista_siguiente)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                lista_agrega_final(lista, &a[i]);
        }
        NodoLista* nodo = lista_cabeza(lista);
        int c = 0;
        while (nodo != NULL) {
                void* e = nodo_lista_elemento(nodo);
                fail_unless(!compara_enteros(e, &a[c++]));
                nodo = nodo_lista_siguiente(nodo);
        }
        lista_libera(lista);
        free(a);
}
END_TEST

/* Prueba unitaria para nodo_lista_busca. */
START_TEST(test_nodo_lista_busca)
{
        srand((unsigned int)time(NULL));
        Lista* lista = lista_nueva();
        int total = rand() % N;
        int a = rand() % total;
        int b = a + 1;
        for (int i = 0; i < total; i++) {
                if ((i % 2) == 0)
                        lista_agrega_final(lista, &a);
                else
                        lista_agrega_final(lista, &b);
        }
        NodoLista* nodo = lista_cabeza(lista);
        int i = 0;
        while (nodo != NULL) {
                void* e = nodo_lista_elemento(nodo);
                if ((i++ % 2) == 0) {
                        fail_unless(!compara_enteros(e, &a));
                        nodo = nodo_lista_busca(nodo, &b, compara_enteros);
                } else {
                        fail_unless(!compara_enteros(e, &b));
                        nodo = nodo_lista_busca(nodo, &a, compara_enteros);
                }
        }
        fail_unless(i == total);
        lista_libera(lista);
}
END_TEST

/* Prueba unitaria para LISTA_PARA_CADA. */
START_TEST(test_LISTA_PARA_CADA)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        Lista* lista = lista_nueva();
        for (int i = 0; i < total; i++)
                lista_agrega_final(lista, entero_nuevo(i));
        int i = 0;
        LISTA_PARA_CADA(int*, n, lista, fail_unless(i++ == *n));
        fail_unless(i == total);
        lista_libera_todo(lista);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
lista_suite(void)
{
        Suite *s = suite_create("Lista");

        TCase *tc_lista =
                tcase_create("Funciones de la estructura lista");
        tcase_add_test(tc_lista, test_lista_nueva);
        tcase_add_test(tc_lista, test_lista_cabeza);
        tcase_add_test(tc_lista, test_lista_rabo);
        tcase_add_test(tc_lista, test_lista_longitud);
        tcase_add_test(tc_lista, test_lista_agrega_inicio);
        tcase_add_test(tc_lista, test_lista_agrega_final);
        tcase_add_test(tc_lista, test_lista_inserta_antes);
        tcase_add_test(tc_lista, test_lista_inserta_despues);
        tcase_add_test(tc_lista, test_lista_elimina);
        tcase_add_test(tc_lista, test_lista_elimina_primero);
        tcase_add_test(tc_lista, test_lista_elimina_ultimo);
        tcase_add_test(tc_lista, test_lista_elimina_nodo);
        tcase_add_test(tc_lista, test_lista_busca);
        tcase_add_test(tc_lista, test_lista_dame);
        tcase_add_test(tc_lista, test_lista_reversa);
        tcase_add_test(tc_lista, test_lista_copia);
        tcase_add_test(tc_lista, test_lista_esta_ordenada);
        tcase_add_test(tc_lista, test_lista_ordenada_busca);
        tcase_add_test(tc_lista, test_lista_mergesort);
        tcase_add_test(tc_lista, test_lista_libera);
        tcase_add_test(tc_lista, test_lista_libera_todo);
        tcase_add_test(tc_lista, test_nodo_lista_elemento);
        tcase_add_test(tc_lista, test_nodo_lista_anterior);
        tcase_add_test(tc_lista, test_nodo_lista_siguiente);
        tcase_add_test(tc_lista, test_nodo_lista_busca);
        tcase_add_test(tc_lista, test_LISTA_PARA_CADA);
        suite_add_tcase(s, tc_lista);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = lista_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
