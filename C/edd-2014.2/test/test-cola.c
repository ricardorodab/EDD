#include <time.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <cola.h>

#define N 100
#define GRAN_N 10000

/* Prueba unitaria para cola_nueva. */
START_TEST(test_cola_nueva)
{
        Cola* cola = cola_nueva();
        fail_unless(cola != NULL);
        fail_unless(cola_es_vacia(cola));
        cola_libera(cola);
}
END_TEST

/* Prueba unitaria para cola_mete. */
START_TEST(test_cola_mete)
{
        srand((unsigned int)time(NULL));
        Cola* cola = cola_nueva();
        int total = rand() % N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                cola_mete(cola, &a[i]);
        }
        for (int i = 0; i < total; i++) {
                int* n = cola_saca(cola);
                fail_unless(n == &a[i]);
        }
        cola_libera(cola);
        free(a);
}
END_TEST

/* Prueba unitaria para cola_saca. */
START_TEST(test_cola_saca)
{
        srand((unsigned int)time(NULL));
        Cola* cola = cola_nueva();
        int total = rand() % N;
        for (int i = 0; i < total; i++)
                cola_mete(cola, entero_nuevo(rand() % N));
        for (int i = 1; i < total; i++) {
                int* n = cola_saca(cola);
                fail_if(cola_es_vacia(cola));
                free(n);
        }
        int* n = cola_saca(cola);
        fail_unless(cola_es_vacia(cola));
        cola_libera(cola);
        free(n);
}
END_TEST

/* Prueba unitaria para cola_es_vacia. */
START_TEST(test_cola_es_vacia)
{
        srand((unsigned int)time(NULL));
        Cola* cola = cola_nueva();
        fail_unless(cola_es_vacia(cola));
        int total = rand() % N;
        for (int i = 0; i < total; i++) {
                cola_mete(cola, entero_nuevo(rand() % N));
                fail_if(cola_es_vacia(cola));
        }
        for (int i = 1; i < total; i++) {
                int* n = cola_saca(cola);
                fail_if(cola_es_vacia(cola));
                free(n);
                fail_if(cola_es_vacia(cola));
        }
        int* n = cola_saca(cola);
        fail_unless(cola_es_vacia(cola));
        cola_libera(cola);
        free(n);
}
END_TEST

/* Prueba unitaria para cola_es_vacia. */
START_TEST(test_cola_libera)
{
        srand((unsigned int)time(NULL));
        Cola* cola = cola_nueva();
        int total = rand() % GRAN_N;
        int* a = ARREGLO(int, total);
        for (int i = 0; i < total; i++) {
                a[i] = rand() % N;
                cola_mete(cola, &a[i]);
        }
        cola_libera(cola);
        free(a);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
cola_suite(void)
{
        Suite *s = suite_create("Cola");

        TCase *tc_cola =
                tcase_create("Funciones de la estructura cola");
        tcase_add_test(tc_cola, test_cola_nueva);
        tcase_add_test(tc_cola, test_cola_mete);
        tcase_add_test(tc_cola, test_cola_saca);
        tcase_add_test(tc_cola, test_cola_es_vacia);
        tcase_add_test(tc_cola, test_cola_libera);
        suite_add_tcase(s, tc_cola);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = cola_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
