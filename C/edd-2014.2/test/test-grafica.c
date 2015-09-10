#include <time.h>
#include <check.h>
#include <stdlib.h>

#include <lista.h>
#include <grafica.h>
#include <util.h>

#define N 100
#define GRAN_N 200

typedef struct _Datos Datos;

struct _Datos {
        int indice;
        char** orden;
};

/* Prueba unitaria para grafica_nueva. */
START_TEST(test_grafica_nueva)
{
        Grafica* g = grafica_nueva(compara_enteros);
        Lista* l = grafica_vertices(g);
        fail_unless(lista_longitud(l) == 0);
        lista_libera(l);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para grafica_agrega. */
START_TEST(test_grafica_agrega)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = entero_nuevo(rand() % N);
        grafica_agrega(g, a);
        fail_unless(grafica_contiene(g, a));
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_conecta. */
START_TEST(test_grafica_conecta)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = entero_nuevo(rand() % N);
        grafica_agrega(g, a);
        /* Garantizamos que sean distintos. */
        int* b = entero_nuevo(*a + 1);
        grafica_agrega(g, b);
        fail_if(grafica_estan_conectados(g, a, b));
        grafica_conecta(g, a, b, 1);
        fail_unless(grafica_estan_conectados(g, a, b));
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_elimina. */
START_TEST(test_grafica_elimina)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = entero_nuevo(rand() % N);
        grafica_agrega(g, a);
        fail_unless(grafica_contiene(g, a));
        grafica_elimina(g, a);
        fail_if(grafica_contiene(g, a));
        free(a);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para grafica_desconecta. */
START_TEST(test_grafica_desconecta)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = entero_nuevo(rand() % N);
        grafica_agrega(g, a);
        /* Garantizamos que sean distintos. */
        int* b = entero_nuevo(*a + 1);
        grafica_agrega(g, b);
        fail_if(grafica_estan_conectados(g, a, b));
        grafica_conecta(g, a, b, 1);
        fail_unless(grafica_estan_conectados(g, a, b));
        grafica_desconecta(g, a, b);
        fail_if(grafica_estan_conectados(g, a, b));
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_vertice. */
START_TEST(test_grafica_vertice)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int total = rand() % N;
        for (int i = 0; i < total; i++)
                grafica_agrega(g, entero_nuevo(i));
        for (int i = 0; i < total; i++) {
                VerticeGrafica* v = grafica_vertice(g, &i);
                fail_unless(v != NULL);
                int* n = vertice_grafica_elemento(v);
                fail_unless(*n == i);
        }
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_vertices. */
START_TEST(test_grafica_vertices)
{
        srand((unsigned int)time(NULL));
        char* es[] = { "a", "b", "c", "d", "e", "f" };
        Grafica* g =
                grafica_nueva(FUNC_COMPARA(strcmp));
        for (int i = 0; i < 6; i++)
                grafica_agrega(g, es[i]);
        Lista* l = grafica_vertices(g);
        int i = 0;
        LISTA_PARA_CADA(VerticeGrafica*, v, l, {
                        void* e = vertice_grafica_elemento(v);
                        fail_unless(!strcmp(e, es[i++]));
                });
        lista_libera(l);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para grafica_estan_conectados. */
START_TEST(test_grafica_estan_conectados)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = entero_nuevo(rand() % N);
        grafica_agrega(g, a);
        /* Garantizamos que sean distintos. */
        int* b = entero_nuevo(*a + 1);
        grafica_agrega(g, b);
        fail_if(grafica_estan_conectados(g, a, b));
        grafica_conecta(g, a, b, 1);
        fail_unless(grafica_estan_conectados(g, a, b));
        grafica_desconecta(g, a, b);
        fail_if(grafica_estan_conectados(g, a, b));
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_peso. */
START_TEST(test_grafica_peso)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = i+1;
                grafica_agrega(g, &a[i]);
        }
        for (int i = 0; i < total; i++)
                for (int j = i+1; j < total; j++)
                        grafica_conecta(g, &a[i], &a[j], a[i]*a[j]);
        for (int i = 0; i < total; i++) {
                for (int j = i+1; j < total; j++) {
                        int peso = (int)grafica_peso(g, &a[i], &a[j]);
                        fail_unless(peso == (a[i]*a[j]));
                }
        }
        grafica_libera(g);
        free(a);
}
END_TEST

/* Prueba unitaria para grafica_contiene. */
START_TEST(test_grafica_contiene)
{
        srand((unsigned int)time(NULL));
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = entero_nuevo(rand() % N);
        grafica_agrega(g, a);
        fail_unless(grafica_contiene(g, a));
        grafica_elimina(g, a);
        fail_if(grafica_contiene(g, a));
        free(a);
        grafica_libera_todo(g);
}
END_TEST

/* Función auxiliar que genera una gráfica. */
static Grafica*
llena_grafica(void)
{
        Grafica* g = grafica_nueva(FUNC_COMPARA(strcmp));
        grafica_agrega(g, strdup("a"));
        grafica_agrega(g, strdup("b"));
        grafica_agrega(g, strdup("c"));
        grafica_agrega(g, strdup("d"));
        grafica_agrega(g, strdup("e"));
        grafica_agrega(g, strdup("f"));
        grafica_conecta(g, "a", "b", 1);
        grafica_conecta(g, "a", "c", 2);
        grafica_conecta(g, "b", "d", 3);
        grafica_conecta(g, "c", "e", 4);
        grafica_conecta(g, "d", "f", 5);
        grafica_conecta(g, "e", "f", 6);
        return g;
}

static void
verifica_orden(const void* elemento,
               const void* datos)
{
        Datos* dv = (Datos*)datos;
        fail_unless(!strcmp(dv->orden[dv->indice++], elemento));
}

/* Prueba unitaria para grafica_itera_bfs. */
START_TEST(test_grafica_itera_bfs)
{
        char* bfs[] = { "a", "b", "c", "d", "e", "f" };
        Datos d;
        d.indice = 0;
        d.orden = (char**)bfs;

        Grafica* g = llena_grafica();
        fail_unless(grafica_estan_conectados(g, "a", "b"));
        grafica_itera_bfs(g, "a", verifica_orden, &d);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_itera_dfs. */
START_TEST(test_grafica_itera_dfs)
{
        char* dfs[] = { "a", "c", "e", "f", "d", "b" };
        Datos d;
        d.indice = 0;
        d.orden = (char**)dfs;

        Grafica* g = llena_grafica();
        grafica_itera_dfs(g, "a", verifica_orden, &d);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_trayectoria_minima. */
START_TEST(test_grafica_trayectoria_minima)
{
        char* min[] = { "a", "b", "d" };
        Grafica* g = llena_grafica();
        Lista* t = grafica_trayectoria_minima(g, "a", "d");
        int i = 0;
        LISTA_PARA_CADA(char*, s, t, fail_unless(!strcmp(s, min[i++])));
        lista_libera(t);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para grafica_dijkstra. */
START_TEST(test_grafica_dijkstra)
{
        Grafica* g = grafica_nueva(compara_enteros);
        for (int i = 1; i <= 6; i++)
                grafica_agrega(g, entero_nuevo(i));

        int a, b;
        a = 1; b = 2;
        grafica_conecta(g, &a, &b, 1);
        a = 1; b = 3;
        grafica_conecta(g, &a, &b, 5);
        a = 1; b = 4;
        grafica_conecta(g, &a, &b, 10);
        a = 2; b = 3;
        grafica_conecta(g, &a, &b, 6);
        a = 2; b = 5;
        grafica_conecta(g, &a, &b, 1);
        a = 3; b = 4;
        grafica_conecta(g, &a, &b, 4);
        a = 3; b = 5;
        grafica_conecta(g, &a, &b, 7);
        a = 3; b = 6;
        grafica_conecta(g, &a, &b, 8);
        a = 4; b = 6;
        grafica_conecta(g, &a, &b, 1);
        a = 5; b = 6;
        grafica_conecta(g, &a, &b, 1);

        int min[] = { 1, 2, 5, 6, 4 };

        a = 1; b = 4;

        Lista* dijkstra = grafica_dijkstra(g, &a, &b);
        fail_unless(lista_longitud(dijkstra) == 5);

        int i = 0;
        LISTA_PARA_CADA(int*, n, dijkstra, fail_unless(*n == min[i++]));
        lista_libera(dijkstra);
        grafica_libera_todo(g);
}
END_TEST

static Grafica*
grafica_aleatoria(int total)
{
        Grafica* g = grafica_nueva(compara_enteros);
        int** v = ARREGLO(int*, total);
        for (int i = 0; i < total; i++) {
                v[i] = entero_nuevo(i);
                grafica_agrega(g, v[i]);
        }
        for (int i = 0; i < total; i++) {
                for (int j = i+1; j < total; j++) {
                        double w = 1 + rand() % total;
                        if (rand() % 2 == 0)
                                /* 50% de probabilidad de arista.*/
                                grafica_conecta (g, v[i], v[j], w);
                }
        }
        free(v);
        return g;
}

/* Prueba unitaria para grafica_libera. */
START_TEST(test_grafica_libera)
{
        srand((unsigned int)time(NULL));
        int total = rand() % GRAN_N;
        Grafica* g = grafica_aleatoria(total);
        Lista* v = grafica_vertices(g);
        LISTA_PARA_CADA(VerticeGrafica*, vg, v, {
                        void* e = vertice_grafica_elemento(vg);
                        free(e);
                });
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para grafica_libera_todo. */
START_TEST(test_grafica_libera_todo)
{
        srand((unsigned int)time(NULL));
        int total = rand() % GRAN_N;
        Grafica* g = grafica_aleatoria(total);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para vertice_grafica_elemento. */
START_TEST(test_vertice_grafica_elemento)
{
        Grafica* g = grafica_nueva(compara_enteros);
        grafica_agrega(g, entero_nuevo(1));
        int n = 1;
        VerticeGrafica* vg = grafica_vertice(g, &n);
        fail_unless(vg != NULL);
        int* e = vertice_grafica_elemento(vg);
        fail_unless(e != NULL);
        fail_unless(n == *e);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para vertice_grafica_iterador_aristas. */
START_TEST(test_vertice_grafica_iterador_aristas)
{
        Grafica* g = grafica_nueva(compara_enteros);
        int a[] = { 1, 2, 3 };
        grafica_agrega(g, &a[0]);
        grafica_agrega(g, &a[1]);
        grafica_agrega(g, &a[2]);
        grafica_conecta(g, &a[0], &a[1], 1);
        grafica_conecta(g, &a[1], &a[2], 2);
        grafica_conecta(g, &a[2], &a[0], 3);
        VerticeGrafica* vg = grafica_vertice(g, &a[0]);
        fail_unless(vg != NULL);
        NodoLista* na = vertice_grafica_iterador_aristas(vg);
        fail_unless(na != NULL);
        AristaGrafica* ag = nodo_lista_elemento(na);
        fail_unless(ag != NULL);
        int p = (int)arista_grafica_peso(ag);
        fail_unless(p == 1);
        VerticeGrafica* vec = arista_grafica_vecino(ag);
        fail_unless(vec != NULL);
        int* n = vertice_grafica_elemento(vec);
        fail_unless(n != NULL);
        fail_unless(a[1] == *n);
        na = nodo_lista_siguiente(na);
        fail_unless(na != NULL);
        ag = nodo_lista_elemento(na);
        fail_unless(ag != NULL);
        p = (int)arista_grafica_peso(ag);
        fail_unless(p == 3);
        vec = arista_grafica_vecino(ag);
        fail_unless(vec != NULL);
        n = vertice_grafica_elemento(vec);
        fail_unless(n != NULL);
        fail_unless(a[2] == *n);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para vertice_grafica_color. */
START_TEST(test_vertice_grafica_color)
{
        Grafica* g = grafica_nueva(compara_enteros);
        grafica_agrega(g, entero_nuevo(1));
        int n = 1;
        VerticeGrafica* vg = grafica_vertice(g, &n);
        fail_unless(vg != NULL);
        Color c = vertice_grafica_color(vg);
        fail_unless(c == COLOR_NINGUNO);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para vertice_grafica_define_color. */
START_TEST(test_vertice_grafica_define_color)
{
        Grafica* g = grafica_nueva(compara_enteros);
        grafica_agrega(g, entero_nuevo(1));
        int n = 1;
        VerticeGrafica* vg = grafica_vertice(g, &n);
        fail_unless(vg != NULL);
        Color c = vertice_grafica_color(vg);
        fail_unless(c == COLOR_NINGUNO);
        vertice_grafica_define_color(vg, COLOR_ROJO);
        c = vertice_grafica_color(vg);
        fail_unless(c == COLOR_ROJO);
        grafica_libera_todo(g);
}
END_TEST

/* Prueba unitaria para arista_grafica_vecino. */
START_TEST(test_arista_grafica_vecino)
{
        Grafica* g = grafica_nueva(compara_enteros);
        int a[] = { 1, 2, 3 };
        grafica_agrega(g, &a[0]);
        grafica_agrega(g, &a[1]);
        grafica_agrega(g, &a[2]);
        grafica_conecta(g, &a[0], &a[1], 1);
        grafica_conecta(g, &a[1], &a[2], 2);
        grafica_conecta(g, &a[2], &a[0], 3);
        VerticeGrafica* vg = grafica_vertice(g, &a[0]);
        fail_unless(vg != NULL);
        NodoLista* na = vertice_grafica_iterador_aristas(vg);
        fail_unless(na != NULL);
        AristaGrafica* ag = nodo_lista_elemento(na);
        fail_unless(ag != NULL);
        VerticeGrafica* vec = arista_grafica_vecino(ag);
        fail_unless(vec != NULL);
        int* n = vertice_grafica_elemento(vec);
        fail_unless(*n == a[1]);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para arista_grafica_peso. */
START_TEST(test_arista_grafica_peso)
{
        Grafica* g = grafica_nueva(compara_enteros);
        int a[] = { 1, 2, 3 };
        grafica_agrega(g, &a[0]);
        grafica_agrega(g, &a[1]);
        grafica_agrega(g, &a[2]);
        grafica_conecta(g, &a[0], &a[1], 1);
        grafica_conecta(g, &a[1], &a[2], 2);
        grafica_conecta(g, &a[2], &a[0], 3);
        VerticeGrafica* vg = grafica_vertice(g, &a[0]);
        fail_unless(vg != NULL);
        NodoLista* na = vertice_grafica_iterador_aristas(vg);
        fail_unless(na != NULL);
        AristaGrafica* ag = nodo_lista_elemento(na);
        fail_unless(ag != NULL);
        double peso = arista_grafica_peso(ag);
        fail_unless(peso == 1);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para VERTICE_GRAFICA_PARA_CADA_ARISTA. */
START_TEST(test_VERTICE_GRAFICA_PARA_CADA_ARISTA)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = ARREGLO(int, total);
        for (int i = 1; i <= total; i++) {
                a[i] = i;
                grafica_agrega(g, &a[i]);
        }
        for (int i = 1; i <= total; i++)
                for (int j = i+1; j <= total; j++)
                        grafica_conecta(g, &a[i], &a[j], a[i]*a[j]);
        Lista* vs = grafica_vertices(g);
        NodoLista* nvs = lista_cabeza(vs);
        int i = 0;
        while (nvs != NULL) {
                i++;
                VerticeGrafica* vg = nodo_lista_elemento(nvs);
                int* n = vertice_grafica_elemento(vg);
                fail_unless(i == *n);
                int j = 0;
                VERTICE_GRAFICA_PARA_CADA_ARISTA(ar, vg, {
                                j = (j + 1 != i) ? j + 1 : j + 2;
                                VerticeGrafica* vec;
                                vec = arista_grafica_vecino(ar);
                                n = vertice_grafica_elemento(vec);
                                fail_unless(j == *n);
                                fail_unless(arista_grafica_peso(ar) == (i*j));
                  });
                nvs = nodo_lista_siguiente(nvs);
        }
        lista_libera(vs);
        grafica_libera(g);
}
END_TEST

/* Prueba unitaria para VERTICE_GRAFICA_PARA_CADA_VECINO. */
START_TEST(test_VERTICE_GRAFICA_PARA_CADA_VECINO)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        Grafica* g = grafica_nueva(compara_enteros);
        int* a = ARREGLO(int, total);
        for (int i = 1; i <= total; i++) {
                a[i] = i;
                grafica_agrega(g, &a[i]);
        }
        for (int i = 1; i <= total; i++)
                for (int j = i+1; j <= total; j++)
                        grafica_conecta(g, &a[i], &a[j], 1);
        Lista* vs = grafica_vertices(g);
        NodoLista* nvs = lista_cabeza(vs);
        int i = 0;
        while (nvs != NULL) {
                i++;
                VerticeGrafica* vg = nodo_lista_elemento(nvs);
                int* n = vertice_grafica_elemento(vg);
                fail_unless(i == *n);
                int j = 0;
                VERTICE_GRAFICA_PARA_CADA_VECINO(vec, vg, {
                                j = (j + 1 != i) ? j + 1 : j + 2;
                                n = vertice_grafica_elemento(vec);
                                fail_unless(j == *n);
                  });
                nvs = nodo_lista_siguiente(nvs);
        }
        lista_libera(vs);
        grafica_libera(g);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
grafica_suite(void)
{
        Suite *s = suite_create ("Gráfica");

        TCase *tc_grafica =
                tcase_create("Funciones de la estructura gráfica");
        tcase_add_test(tc_grafica, test_grafica_nueva);
        tcase_add_test(tc_grafica, test_grafica_agrega);
        tcase_add_test(tc_grafica, test_grafica_conecta);
        tcase_add_test(tc_grafica, test_grafica_elimina);
        tcase_add_test(tc_grafica, test_grafica_desconecta);
        tcase_add_test(tc_grafica, test_grafica_vertice);
        tcase_add_test(tc_grafica, test_grafica_vertices);
        tcase_add_test(tc_grafica, test_grafica_estan_conectados);
        tcase_add_test(tc_grafica, test_grafica_peso);
        tcase_add_test(tc_grafica, test_grafica_contiene);
        tcase_add_test(tc_grafica, test_grafica_itera_bfs);
        tcase_add_test(tc_grafica, test_grafica_itera_dfs);
        tcase_add_test(tc_grafica, test_grafica_trayectoria_minima);
        tcase_add_test(tc_grafica, test_grafica_dijkstra);
        tcase_add_test(tc_grafica, test_grafica_libera);
        tcase_add_test(tc_grafica, test_grafica_libera_todo);
        tcase_add_test(tc_grafica, test_vertice_grafica_elemento);
        tcase_add_test(tc_grafica, test_vertice_grafica_iterador_aristas);
        tcase_add_test(tc_grafica, test_vertice_grafica_color);
        tcase_add_test(tc_grafica, test_vertice_grafica_define_color);
        tcase_add_test(tc_grafica, test_arista_grafica_vecino);
        tcase_add_test(tc_grafica, test_arista_grafica_peso);
        tcase_add_test(tc_grafica, test_VERTICE_GRAFICA_PARA_CADA_ARISTA);
        tcase_add_test(tc_grafica, test_VERTICE_GRAFICA_PARA_CADA_VECINO);
        suite_add_tcase(s, tc_grafica);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = grafica_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all (sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
