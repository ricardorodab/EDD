#include <time.h>
#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>

#define N 100
#define GRAN_N 10000
#define CADENA_PRUEBA                           \
        "en un lugar de la mancha de cuyo "     \
        "nombre no quiero acordarme"
#define HUELLA_BJ     0x6e6a20b1
#define HUELLA_XOR    0x6f3d284f
#define HUELLA_GLIB   0xe7e60d00

/* Prueba unitaria para entero_nuevo. */
START_TEST(test_entero_nuevo)
{
        srand((unsigned int)time(NULL));
        int v = rand() % N;
        int* n = entero_nuevo(v);
        fail_unless(v == *n);
        free(n);
}
END_TEST

/* Prueba unitaria para compara_enteros. */
START_TEST(test_compara_enteros)
{
        srand((unsigned int)time(NULL));
        int a = rand() % N;
        int b = a+1;
        fail_unless(compara_enteros(&a, &b) < 0);
        fail_unless(!compara_enteros(&a, &a));
        fail_unless(compara_enteros(&b, &a) > 0);
}
END_TEST

/* Prueba unitaria para entero_a_cadena. */
START_TEST(test_entero_a_cadena)
{
        char* s = entero_a_cadena(1234);
        fail_unless(!strcmp(s, "1234"));
}
END_TEST

/* Prueba unitaria para pentero_a_cadena. */
START_TEST(test_pentero_a_cadena)
{
        int n = 1234;
        char* s = pentero_a_cadena(&n);
        fail_unless(!strcmp(s, "1234"));
}
END_TEST

/* Prueba unitaria para concatena_cadenas. */
START_TEST(test_concatena_cadenas)
{
        char* c = concatena_cadenas("A", "B", "C", "D", "E", NULL);
        fail_unless(!strcmp(c, "ABCDE"));
        free(c);
        c = concatena_cadenas("E", "D", "C", "B", "A", NULL);
        fail_unless(!strcmp(c, "EDCBA"));
        free(c);
}
END_TEST

/* Prueba unitaria para libera_cadenas. */
START_TEST(test_libera_cadenas)
{
        char* A = strdup("A");
        char* B = strdup("B");
        char* C = strdup("C");
        char* D = strdup("D");
        char* E = strdup("E");
        libera_cadenas(A, B, C, D, E, NULL);
}
END_TEST

/* Prueba unitaria para huella_cadena_bj. */
START_TEST(test_huella_cadena_bj)
{
        int h = huella_cadena_bj(CADENA_PRUEBA);
        fail_unless(h == HUELLA_BJ);
}
END_TEST

/* Prueba unitaria para huella_cadena_xor. */
START_TEST(test_huella_cadena_xor)
{
        int h = huella_cadena_xor(CADENA_PRUEBA);
        fail_unless(h == HUELLA_XOR);
}
END_TEST

/* Prueba unitaria para huella_cadena_glib. */
START_TEST(test_huella_cadena_glib)
{
        int h = huella_cadena_glib(CADENA_PRUEBA);
        fail_unless(h == HUELLA_GLIB);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
util_suite(void)
{
        Suite *s = suite_create("Útil");

        TCase *tc_util =
                tcase_create("Funciones utilitarias");
        tcase_add_test(tc_util, test_entero_nuevo);
        tcase_add_test(tc_util, test_compara_enteros);
        tcase_add_test(tc_util, test_entero_a_cadena);
        tcase_add_test(tc_util, test_pentero_a_cadena);
        tcase_add_test(tc_util, test_concatena_cadenas);
        tcase_add_test(tc_util, test_libera_cadenas);
        tcase_add_test(tc_util, test_huella_cadena_bj);
        tcase_add_test(tc_util, test_huella_cadena_xor);
        tcase_add_test(tc_util, test_huella_cadena_glib);
        suite_add_tcase(s, tc_util);

        return s;
}

int
main(int   argc,
     char* argv[])
{
        int fallas;
        Suite *s = util_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_ENV);
        fallas = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
