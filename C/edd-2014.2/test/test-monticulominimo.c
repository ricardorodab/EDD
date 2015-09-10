#include <time.h>
#include <check.h>
#include <stdlib.h>

#include <lista.h>
#include <monticulominimo.h>

#define N 100
#define GRAN_N 1000

typedef struct _Numero Numero;

struct _Numero {
        int n;
        int i;
};

static Numero*
numero_nuevo(int n)
{
        Numero* num = NUEVO(Numero);
        num->n = n;
        num->i = -1;
        return num;
}

static int*
numero_indice(const void* a)
{
        Numero* num = (Numero*)a;
        return &num->i;
}

static int
numero_compara(const void* a,
               const void* b)
{
        Numero* na = (Numero*)a;
        Numero* nb = (Numero*)b;
        return na->n - nb->n;
}

static bool
verifica(MonticuloMinimo* m,
         int              i)
{
        if (i > monticulo_minimo_ultimo(m))
                return true;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;
        bool verifica_izq = true, verifica_der = true;
        if (izq <= monticulo_minimo_ultimo(m) &&
            numero_compara(monticulo_minimo_dame(m, i),
                           monticulo_minimo_dame(m, izq)) <= 0)
                verifica_izq = verifica(m, izq);
        if (der <= monticulo_minimo_ultimo(m) &&
            numero_compara(monticulo_minimo_dame(m, i),
                           monticulo_minimo_dame(m, der)) <= 0)
                verifica_der = verifica(m, der);
        return verifica_izq && verifica_der;
}

/* Verifica que el montículo sea correcto. */
static int
monticulo_minimo_verifica(MonticuloMinimo* m)
{
        return verifica(m, 0);
}

/* Prueba unitaria para monticulo_minimo_nuevo. */
START_TEST(test_monticulo_minimo_nuevo)
{
        MonticuloMinimo* m = monticulo_minimo_nuevo(numero_compara,
                                                    numero_indice);
        fail_unless(monticulo_minimo_verifica(m));
        monticulo_minimo_libera(m);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_nuevo_de_lista. */
START_TEST(test_monticulo_minimo_nuevo_de_lista)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % N;
        Lista* lista = lista_nueva();
        for (int i = 0; i < total; i++) {
                Numero* n = numero_nuevo(rand() % N);
                lista_agrega_final(lista, n);
        }
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo_de_lista(lista,
                                            numero_compara,
                                            numero_indice);
        fail_unless(monticulo_minimo_verifica(m));
        monticulo_minimo_libera(m);
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_agrega. */
START_TEST(test_monticulo_minimo_agrega)
{
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo(numero_compara, numero_indice);
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % N;
        for (int i = 0; i < total; i++) {
                Numero* n = numero_nuevo(rand() % N);
                monticulo_minimo_agrega(m, n);
                fail_unless(monticulo_minimo_verifica(m));
        }
        monticulo_minimo_libera_todo(m);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_elimina. */
START_TEST(test_monticulo_minimo_elimina)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % N;
        Lista* lista = lista_nueva();
        for (int i = 0; i < total; i++) {
                Numero* n = numero_nuevo(rand() % N);
                lista_agrega_final(lista, n);
        }
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo_de_lista(lista,
                                            numero_compara,
                                            numero_indice);
        fail_unless(monticulo_minimo_verifica(m));
        while (!monticulo_minimo_es_vacio(m)) {
                Numero* min = nodo_lista_elemento(lista_cabeza(lista));
                LISTA_PARA_CADA(Numero*, e, lista, {
                                if (numero_compara(e, min) < 0)
                                        min = e;
                        });
                Numero* hmin = monticulo_minimo_elimina(m);
                fail_unless(!numero_compara(min, hmin));
                lista_elimina(lista, min, numero_compara);
                fail_unless(monticulo_minimo_verifica(m));
        }
        monticulo_minimo_libera(m);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_es_vacio. */
START_TEST(test_monticulo_minimo_es_vacio)
{
        srand((unsigned int)time(NULL));
        MonticuloMinimo* m = monticulo_minimo_nuevo(numero_compara,
                                              numero_indice);
        fail_unless(monticulo_minimo_es_vacio(m));
        Numero* n = numero_nuevo(rand() % N);
        monticulo_minimo_agrega(m, n);
        fail_if(monticulo_minimo_es_vacio(m));
        Numero* e = monticulo_minimo_elimina(m);
        free(e);
        fail_unless(monticulo_minimo_es_vacio(m));
        monticulo_minimo_libera(m);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_reordena. */
START_TEST(test_monticulo_minimo_reordena)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % N;
        Lista* lista = lista_nueva();
        for (int i = 0; i < total; i++) {
                Numero* n = numero_nuevo(rand() % N);
                lista_agrega_final(lista, n);
        }
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo_de_lista (lista,
                                             numero_compara,
                                             numero_indice);
        fail_unless(monticulo_minimo_verifica(m));
        Numero* n = nodo_lista_elemento(lista_dame(lista, rand() % total));
        n->n = n->n/2;
        monticulo_minimo_reordena(m, n);
        fail_unless(monticulo_minimo_verifica(m));
        monticulo_minimo_libera(m);
        lista_libera_todo(lista);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_ultimo. */
START_TEST(test_monticulo_minimo_ultimo)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % N;
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo(numero_compara, numero_indice);
        for (int i = 0; i < total; i++) {
                monticulo_minimo_agrega(m, numero_nuevo(i));
                fail_unless(monticulo_minimo_ultimo(m) == i);
        }
        monticulo_minimo_libera_todo(m);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_dame. */
START_TEST(test_monticulo_minimo_dame)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % N;
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo(numero_compara, numero_indice);
        for (int i = 0; i < total; i++) {
                monticulo_minimo_agrega(m, numero_nuevo(i));
                Numero* n = monticulo_minimo_dame(m, i);
                fail_unless(n->n == i);
        }
        monticulo_minimo_libera_todo(m);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_libera. */
START_TEST(test_monticulo_minimo_libera)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % GRAN_N;
        Numero** v = ARREGLO(Numero*, total);
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo(numero_compara, numero_indice);
        for (int i = 0; i < total; i++) {
                v[i] = numero_nuevo(rand() % N);
                monticulo_minimo_agrega(m, v[i]);
        }
        monticulo_minimo_libera(m);
        for (int i = 0; i < total; i++)
                free(v[i]);
        free(v);
}
END_TEST

/* Prueba unitaria para monticulo_minimo_libera_todo. */
START_TEST(test_monticulo_minimo_libera_todo)
{
        srand((unsigned int)time(NULL));
        int total = 1 + rand() % GRAN_N;
        MonticuloMinimo* m;
        m = monticulo_minimo_nuevo(numero_compara, numero_indice);
        for (int i = 0; i < total; i++) {
                Numero* n = numero_nuevo(rand() % N);
                monticulo_minimo_agrega(m, n);
        }
        monticulo_minimo_libera_todo(m);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
monticulo_minimo_suite(void)
{
        Suite *s = suite_create ("Montículo mínimo");

        TCase *tc_monticulo =
                tcase_create("Funciones de la estructura montículo mínimo");

        tcase_add_test(tc_monticulo, test_monticulo_minimo_nuevo);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_nuevo_de_lista);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_agrega);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_elimina);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_es_vacio);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_reordena);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_ultimo);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_dame);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_libera);
        tcase_add_test(tc_monticulo, test_monticulo_minimo_libera_todo);
        suite_add_tcase(s, tc_monticulo);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = monticulo_minimo_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all (sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
