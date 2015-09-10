#include <time.h>
#include <check.h>
#include <stdlib.h>

#include <util.h>
#include <lista.h>
#include <diccionario.h>

#define N 1024

/* Prueba unitaria para diccionario_nuevo. */
START_TEST(test_diccionario_nuevo)
{
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_xor),
                              FUNC_COMPARA(strcmp));
        Lista* k = diccionario_llaves(d);
        Lista* v = diccionario_elementos(d);
        fail_unless(diccionario_total(d) == 0);
        fail_unless(lista_longitud(k) == 0);
        fail_unless(lista_longitud(v) == 0);
        lista_libera(k);
        lista_libera(v);
        fail_unless(diccionario_carga(d) == 0.0);
        int m, c;
        diccionario_colisiones(d, &m, &c);
        fail_unless(c == 0);
        diccionario_libera(d, false, false);
}
END_TEST

/* Prueba unitaria para diccionario_agrega. */
START_TEST(test_diccionario_agrega)
{
        srand((unsigned int)time(NULL));
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        char* k = entero_a_cadena(rand() % N);
        char* v = entero_a_cadena(rand() % N);
        diccionario_agrega(d, k, v);
        char* r = diccionario_dame(d, k);
        fail_unless(r != NULL);
        fail_unless(!strcmp(r, v));
        Lista* lk = diccionario_llaves(d);
        Lista* lv = diccionario_elementos(d);
        fail_unless(lista_longitud(lk) == 1);
        fail_unless(lista_longitud(lv) == 1);
        diccionario_libera(d, true, true);
        lista_libera(lk);
        lista_libera(lv);
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        int ini = rand() % N;
        for (int i = 0; i < N*4; i++) {
                k = entero_a_cadena(ini + i);
                fail_unless(diccionario_dame(d, k) == NULL);
                v = concatena_cadenas(k, k, NULL);
                diccionario_agrega(d, k, v);
                r = diccionario_dame(d, k);
                fail_unless(r != NULL);
                fail_unless(!strcmp(r, v));
                fail_unless(r == v);
                fail_unless(diccionario_carga(d) <
                            DICCIONARIO_MAXIMA_CARGA);
        }
        diccionario_libera(d, true, true);
}
END_TEST

/* Prueba unitaria para diccionario_dame. */
START_TEST(test_diccionario_dame)
{
        srand((unsigned int)time(NULL));
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        int n = rand() % N;
        char* k1 = entero_a_cadena(n);
        char* k2 = entero_a_cadena(n+1);
        char* v = entero_a_cadena(rand() % N);
        diccionario_agrega(d, k1, v);
        fail_unless(strcmp(diccionario_dame(d, k1), v) == 0);
        fail_unless(diccionario_dame(d, k2) == NULL);
        diccionario_libera(d, true, true);
        free(k2);
}
END_TEST

/* Prueba unitaria para diccionario_elimina. */
START_TEST(test_diccionario_elimina)
{
        srand((unsigned int)time(NULL));
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        char* k = entero_a_cadena(rand() % N);
        char* v = entero_a_cadena(rand() % N);
        diccionario_agrega(d, k, v);
        Lista* lk = diccionario_llaves(d);
        Lista* lv = diccionario_elementos(d);
        fail_unless(lista_longitud(lk) == 1);
        fail_unless(lista_longitud(lv) == 1);
        lista_libera(lk);
        lista_libera(lv);
        diccionario_elimina(d, k);
        fail_unless(diccionario_dame(d, k) == NULL);
        lk = diccionario_llaves(d);
        lv = diccionario_elementos(d);
        fail_unless(lista_longitud(lk) == 0);
        fail_unless(lista_longitud(lv) == 0);
        lista_libera(lk);
        lista_libera(lv);
        diccionario_libera(d, false, false);
        free(k);
        free(v);
}
END_TEST

/* Prueba unitaria para diccionario_tiene_llave. */
START_TEST(test_diccionario_tiene_llave)
{
        srand((unsigned int)time(NULL));
        int n = (rand() % N) + 10;
        Diccionario* d;
        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        for (int i = 0; i < n; i++) {
                char* k = entero_a_cadena(n + i);
                char* v = entero_a_cadena(rand() % n);
                fail_if(diccionario_tiene_llave(d, k));
                diccionario_agrega(d, k, v);
                fail_unless(diccionario_tiene_llave(d, k));
        }
        diccionario_libera(d, true, true);
}
END_TEST

/* Prueba unitaria para diccionario_llaves. */
START_TEST(test_diccionario_llaves)
{
        srand((unsigned int)time(NULL));
        int n = (rand() % N) + 10;
        Diccionario* d;
        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        for (int i = 0; i < n; i++) {
                char* k = entero_a_cadena(n + i);
                char* v = entero_a_cadena(rand() % n);
                diccionario_agrega(d, k, v);
        }
        Lista* lk = diccionario_llaves(d);
        fail_unless(lista_longitud(lk) == n);
        lista_libera(lk);
        diccionario_libera(d, true, true);
}
END_TEST

/* Prueba unitaria para diccionario_elementos. */
START_TEST(test_diccionario_elementos)
{
        srand((unsigned int)time(NULL));
        int n = (rand() % N) + 10;
        Diccionario* d;
        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        for (int i = 0; i < n; i++) {
                char* k = entero_a_cadena(n + i);
                char* v = entero_a_cadena(rand() % n);
                diccionario_agrega(d, k, v);
        }
        Lista* lv = diccionario_elementos(d);
        fail_unless(lista_longitud(lv) == n);
        lista_libera(lv);
        diccionario_libera(d, true, true);
}
END_TEST

/* Prueba unitaria para diccionario_colisiones. */
START_TEST(test_diccionario_colisiones)
{
        srand((unsigned int)time(NULL));
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_xor),
                              FUNC_COMPARA(strcmp));
        char *k, *v;
        k = strdup("abcdefgh");
        v = entero_a_cadena(rand() % N);
        diccionario_agrega(d, k, v);
        k = strdup("efghabcd");
        v = entero_a_cadena(rand() % N);
        diccionario_agrega(d, k, v);
        int maximo = 0, total = 0;
        diccionario_colisiones(d, &maximo, &total);
        fail_unless(maximo == 1);
        fail_unless(total == 1);
        diccionario_libera(d, true, true);
}
END_TEST

/* Prueba unitaria para diccionario_carga. */
START_TEST(test_diccionario_carga)
{
        srand((unsigned int)time(NULL));
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        int ini = rand() % N;
        double c = 0.0;
        for (int i = 0; i < N; i++) {
                char* k = entero_a_cadena(ini + i);
                diccionario_agrega(d, k, k);
                fail_unless(diccionario_carga(d) > c);
                c = diccionario_carga(d);
                fail_unless(diccionario_carga(d) <= DICCIONARIO_MAXIMA_CARGA);
        }
        for (int i = 0; i < N*3; i++) {
                char* k = entero_a_cadena(ini + N + i);
                diccionario_agrega(d, k, k);
                fail_unless(diccionario_carga(d) <= DICCIONARIO_MAXIMA_CARGA);
        }
        diccionario_libera(d, true, false);
}
END_TEST

/* Prueba unitaria para diccionario_total. */
START_TEST(test_diccionario_total)
{
        srand((unsigned int)time(NULL));
        Diccionario* d;
        d = diccionario_nuevo(N,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        int ini = rand() % N;
        for (int i = 0; i < N*4; i++) {
                char* k = entero_a_cadena(ini + i);
                diccionario_agrega(d, k, k);
                fail_unless(diccionario_total(d) == i+1);
        }
        diccionario_libera(d, true, false);
}
END_TEST

/* Prueba unitaria para diccionario_libera. */
START_TEST(test_diccionario_libera)
{
        srand((unsigned int)time(NULL));
        int n = (rand() % N) + 10;
        Diccionario* d;
        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        for (int i = 0; i < n; i++) {
                char* k = entero_a_cadena(n + i);
                char* v = entero_a_cadena(rand() % n);
                diccionario_agrega(d, k, v);
        }
        diccionario_libera(d, true, true);

        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        char** ks = ARREGLO(char*, n);
        char** vs = ARREGLO(char*, n);
        for (int i = 0; i < n; i++) {
                ks[i] = entero_a_cadena(n + i);
                vs[i] = entero_a_cadena(rand() % n);
                diccionario_agrega(d, ks[i], vs[i]);
        }
        diccionario_libera(d, false, true);
        for (int i = 0; i < n; i++)
                free(ks[i]);
        free(ks);
        free(vs);

        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        ks = ARREGLO(char*, n);
        vs = ARREGLO(char*, n);
        for (int i = 0; i < n; i++) {
                ks[i] = entero_a_cadena(n + i);
                vs[i] = entero_a_cadena(rand() % n);
                diccionario_agrega(d, ks[i], vs[i]);
        }
        diccionario_libera(d, true, false);
        for (int i = 0; i < n; i++)
                free(vs[i]);
        free(ks);
        free(vs);

        d = diccionario_nuevo(n,
                              FUNC_HUELLA(huella_cadena_glib),
                              FUNC_COMPARA(strcmp));
        ks = ARREGLO(char*, n);
        vs = ARREGLO(char*, n);
        for (int i = 0; i < n; i++) {
                ks[i] = entero_a_cadena(n + i);
                vs[i] = entero_a_cadena(rand() % n);
                diccionario_agrega(d, ks[i], vs[i]);
        }
        diccionario_libera(d, false, false);
        for (int i = 0; i < n; i++) {
                free(ks[i]);
                free(vs[i]);
        }
        free(ks);
        free(vs);
}
END_TEST

/* Prueba unitaria para DICCIONARIO_PARA_CADA. */
START_TEST(test_DICCIONARIO_PARA_CADA)
{
        srand((unsigned int)time(NULL));
        Diccionario* d = diccionario_nuevo(N,
                                           FUNC_HUELLA(huella_cadena_glib),
                                           FUNC_COMPARA(strcmp));
        char** a = ARREGLO(char*, N);

        int ini = rand() % N;
        for (int i = 0; i < N; i++) {
                a[i] = entero_a_cadena(ini + i);
                diccionario_agrega(d, a[i], a[i]);
        }

        int c = 0;
        DICCIONARIO_PARA_CADA(char*, s, d, {
                        c++;
                        bool found = false;
                        for (int j = 0; j < N; j++)
                                if (!strcmp(a[j], s))
                                        found = true;
                        fail_unless(found);
                });
        fail_unless(c == N);
        diccionario_libera(d, true, false);
        free(a);
}
END_TEST

/* Genera el conjunto de pruebas unitarias. */
Suite*
diccionario_suite(void)
{
	Suite *s = suite_create ("Diccionario");

	TCase *tc_diccionario =
		tcase_create("Funciones de la estructura diccionario");
        tcase_add_test(tc_diccionario, test_diccionario_nuevo);
        tcase_add_test(tc_diccionario, test_diccionario_agrega);
        tcase_add_test(tc_diccionario, test_diccionario_dame);
        tcase_add_test(tc_diccionario, test_diccionario_elimina);
        tcase_add_test(tc_diccionario, test_diccionario_tiene_llave);
        tcase_add_test(tc_diccionario, test_diccionario_llaves);
        tcase_add_test(tc_diccionario, test_diccionario_elementos);
        tcase_add_test(tc_diccionario, test_diccionario_colisiones);
        tcase_add_test(tc_diccionario, test_diccionario_carga);
        tcase_add_test(tc_diccionario, test_diccionario_total);
        tcase_add_test(tc_diccionario, test_diccionario_libera);
        tcase_add_test(tc_diccionario, test_DICCIONARIO_PARA_CADA);
	suite_add_tcase(s, tc_diccionario);

	return s;
}

int
main(int   argc,
     char* argv[])
{
	int fallas;
	Suite *s = diccionario_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all (sr, CK_ENV);
	fallas = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (fallas == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
