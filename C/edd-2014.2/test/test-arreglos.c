#include <time.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <arreglos.h>

#define N 100

/* Prueba unitaria para arreglos_esta_ordenado. */
START_TEST(test_arreglos_esta_ordenado)
{
        srand((unsigned int)time(NULL));
        /* Con muy pocos elementos puede salir ordenado el
           arreglo. */
        int total = 10 + rand() % N;
        int** a = ARREGLO(int*, total);

        int ini = rand() % N;
        for (int i = 0; i < total; i++)
                a[i] = entero_nuevo(ini + i);
        fail_unless(arreglos_esta_ordenado(ARREGLO_ANONIMO(a),
                                           total, compara_enteros));
        for (int i = 0; i < total; i++)
                *a[i] = rand() % N;
        fail_if(arreglos_esta_ordenado(ARREGLO_ANONIMO(a), total,
                                       compara_enteros));
        for (int i = 0; i < total; i++)
                free(a[i]);
        free(a);
}
END_TEST

/* Prueba unitaria para arreglos_busqueda_binaria. */
START_TEST(test_arreglos_busqueda_binaria)
{
        srand((unsigned int)time(NULL));
        int total = 10 + rand() % N;
        int** a = ARREGLO(int*, total);

        int ini = rand() % N;
        for (int i = 0; i < total; i++)
                a[i] = entero_nuevo(ini + i);
        int r = arreglos_busqueda_binaria(ARREGLO_ANONIMO(a), total,
                                          a[rand() % total],
                                          compara_enteros);
        fail_unless(r != -1);
        int b = 0;
        for (int i = 0; i < total; i++)
                if (*a[i] > b)
                        b = *a[i] + 1;
        b += total;
        r = arreglos_busqueda_binaria(ARREGLO_ANONIMO(a), total,
                                      &b, compara_enteros);
        fail_if(r != -1);
        for (int i = 0; i < total; i++)
                free(a[i]);
        free(a);
}
END_TEST

/* Prueba unitaria para arreglos_selectionsort. */
START_TEST(test_arreglos_selectionsort)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        int** a = ARREGLO(int*, total);

        for (int i = 0; i < total; i++)
                a[i] = entero_nuevo(rand() % N);
        arreglos_selectionsort(ARREGLO_ANONIMO(a), total, compara_enteros);
        fail_unless(arreglos_esta_ordenado(ARREGLO_ANONIMO(a), total,
                                           compara_enteros));
        for (int i = 0; i < total; i++)
                free(a[i]);
        free(a);
}
END_TEST

/* Prueba unitaria para arreglos_quicksort. */
START_TEST(test_arreglos_quicksort)
{
        srand((unsigned int)time(NULL));
        int total = rand() % N;
        int** a = ARREGLO(int*, total);

        for (int i = 0; i < total; i++)
                a[i] = entero_nuevo(rand() % N);
        arreglos_quicksort(ARREGLO_ANONIMO(a), total, compara_enteros);
        fail_unless(arreglos_esta_ordenado(ARREGLO_ANONIMO(a), total,
                                           compara_enteros));
        for (int i = 0; i < total; i++)
                free(a[i]);
        free(a);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
arreglos_suite(void)
{
        Suite *s = suite_create ("Arreglos");

        TCase *tc_arreglos =
                tcase_create("Funciones para arreglos");
        tcase_add_test(tc_arreglos, test_arreglos_esta_ordenado);
        tcase_add_test(tc_arreglos, test_arreglos_busqueda_binaria);
        tcase_add_test(tc_arreglos, test_arreglos_selectionsort);
        tcase_add_test(tc_arreglos, test_arreglos_quicksort);
        suite_add_tcase(s, tc_arreglos);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = arreglos_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all (sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
