#include <time.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <pila.h>

#define N 100
#define GRAN_N 10000

/* Prueba unitaria para pila_nueva. */
START_TEST(test_pila_nueva)
{
        Pila* pila = pila_nueva();
        fail_unless(pila != NULL);
        fail_unless(pila_es_vacia(pila));
        pila_libera(pila);
}
END_TEST

/* Prueba unitaria para pila_mete. */
START_TEST(test_pila_mete)
{
        srand((unsigned int)time(NULL));
        Pila* pila = pila_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                pila_mete(pila, &a[i]);
        }
        for (int i = 0; i < total; i++) {
                int* n = pila_saca(pila);
                fail_unless(n == &a[total - i - 1]);
        }
        pila_libera(pila);
        free(a);
}
END_TEST

/* Prueba unitaria para pila_saca. */
START_TEST(test_pila_saca)
{
        srand((unsigned int)time(NULL));
        Pila* pila = pila_nueva();
        int total = rand() % N;
        for (int i = 0; i < total; i++)
                pila_mete(pila, entero_nuevo(rand() % N));
        for (int i = 1; i < total; i++) {
                int* n = pila_saca(pila);
                fail_if(pila_es_vacia(pila));
                free(n);
        }
        int* n = pila_saca(pila);
        fail_unless(pila_es_vacia(pila));
        pila_libera(pila);
        free(n);
}
END_TEST

/* Prueba unitaria para pila_es_vacia. */
START_TEST(test_pila_es_vacia)
{
        srand((unsigned int)time(NULL));
        Pila* pila = pila_nueva();
        fail_unless(pila_es_vacia(pila));
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                pila_mete(pila, entero_nuevo(rand() % N));
                fail_if(pila_es_vacia(pila));
        }
        for (int i = 1; i < total; i++) {
                int* n = pila_saca(pila);
                fail_if(pila_es_vacia(pila));
                free(n);
                fail_if(pila_es_vacia(pila));
        }
        int* n = pila_saca(pila);
        fail_unless(pila_es_vacia(pila));
        pila_libera(pila);
        free(n);
}
END_TEST

/* Prueba unitaria para pila_es_vacia. */
START_TEST(test_pila_libera)
{
        srand((unsigned int)time(NULL));
        Pila* pila = pila_nueva();
        int total = rand() % GRAN_N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                pila_mete(pila, &a[i]);
        }
        pila_libera(pila);
        free(a);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
pila_suite(void)
{
        Suite *s = suite_create("Pila");

        TCase *tc_pila =
                tcase_create("Funciones de la estructura pila");
        tcase_add_test(tc_pila, test_pila_nueva);
        tcase_add_test(tc_pila, test_pila_mete);
        tcase_add_test(tc_pila, test_pila_saca);
        tcase_add_test(tc_pila, test_pila_es_vacia);
        tcase_add_test(tc_pila, test_pila_libera);
        suite_add_tcase(s, tc_pila);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = pila_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
