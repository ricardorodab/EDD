#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#include "lista.h"
#include "arreglos.h"
#include "arbolbinario.h"
#include "diccionario.h"

static struct timespec tiempo_inicial;
static struct timespec tiempo_actual;
static long tiempo_total;

#define semilla 1400525841
#define busca ((int)(N / 4.5))

static int* entero = NULL;
static char* cadena = NULL;
static bool ordenado = false;

#define  QUICKSORT                0
#define  MERGESORT                1
#define  ARBOL_BINARIO_ORDENADO   2
#define  ARBOL_ROJINEGRO          3
#define  DICCIONARIO              4

#define INICIA_CONTEO clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tiempo_inicial)
#define TERMINA_CONTEO(s)                                                    \
{                                                                            \
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tiempo_actual);             \
        tiempo_total =                                                       \
                (tiempo_actual.tv_sec - tiempo_inicial.tv_sec) * 1000000000  \
                + tiempo_actual.tv_nsec - tiempo_inicial.tv_nsec;            \
        printf("Tiempo %s %'d veces: %2.9f segundos\n",                      \
               (s), N, (tiempo_total/1000000000.0));                         \
}

static void
main_quicksort(int N)
{
        int** a = ARREGLO(int*, N);
        INICIA_CONTEO;
        for (int i = 0; i < N; i++) {
                int j = ordenado ? i : rand() % N;
                int* n = entero_nuevo(j);
                a[i] = n;
                if (i == busca)
                        entero = n;
        }
        TERMINA_CONTEO("agregar a arreglo     ");

        INICIA_CONTEO;
        arreglos_quicksort(ARREGLO_ANONIMO(a), N, FUNC_COMPARA(compara_enteros));
        TERMINA_CONTEO("arreglos_quicksort    ");

        INICIA_CONTEO;
        arreglos_busqueda_binaria(ARREGLO_ANONIMO(a), N,
                                  entero, FUNC_COMPARA(compara_enteros));
        TERMINA_CONTEO("arreglos_busqueda_bin ");
}

static void
main_mergesort(int N)
{
        Lista* l = lista_nueva();

        INICIA_CONTEO;
        for (int i = 0; i < N; i++) {
                int j = ordenado ? i : rand() % N;
                int* n = entero_nuevo(j);
                lista_agrega_final(l, n);
                if (i == busca)
                        entero = n;
        }
        TERMINA_CONTEO("lista_agrega_final    ");

        INICIA_CONTEO;
        Lista* o = lista_mergesort(l, FUNC_COMPARA(compara_enteros));
        TERMINA_CONTEO("lista_mergesort       ");

        INICIA_CONTEO;
        lista_busca(o, entero, FUNC_COMPARA(compara_enteros));
        TERMINA_CONTEO("lista_busca           ");

        lista_libera(l);
        lista_libera_todo(o);
}

static void
main_arbol_binario_ordenado(int N)
{
        ArbolBinario* a = arbol_binario_ordenado_nuevo(FUNC_COMPARA(compara_enteros));

        INICIA_CONTEO;
        for (int i = 0; i < N; i++) {
                int j = ordenado ? i : rand() % N;
                int* n = entero_nuevo(j);
                arbol_binario_ordenado_agrega(a, n);
                if (i == busca)
                        entero = n;
        }
        TERMINA_CONTEO("arbol_bin_ord_agrega  ");

        INICIA_CONTEO;
        arbol_binario_ordenado_busca(a, entero);
        TERMINA_CONTEO("arbol_bin_ord_busca   ");

        arbol_binario_libera_todo(a);
}

static void
main_arbol_rojinegro(int N)
{
        ArbolBinario* a = arbol_rojinegro_nuevo(FUNC_COMPARA(compara_enteros));

        INICIA_CONTEO;
        for (int i = 0; i < N; i++) {
                int j = ordenado ? i : rand() % N;
                int* n = entero_nuevo(j);
                arbol_rojinegro_agrega(a, n);
                if (i == busca)
                        entero = n;
        }
        TERMINA_CONTEO("arbol_rojinegro_agrega");

        INICIA_CONTEO;
        arbol_binario_ordenado_busca(a, entero);
        TERMINA_CONTEO("arbol_rojinegro_busca ");

        arbol_binario_libera_todo(a);
}

static void
main_diccionario(int N)
{
        Diccionario* d = diccionario_nuevo(N,
                                           FUNC_HUELLA(huella_cadena_glib),
                                           FUNC_COMPARA(strcmp));

        INICIA_CONTEO;
        for (int i = 0; i < N; i++) {
                int j = ordenado ? i : rand() % N;
                char* s = entero_a_cadena(j);
                diccionario_agrega(d, s, s);
                if (i == busca)
                        cadena = s;
        }
        TERMINA_CONTEO("diccionario_agrega    ");

        INICIA_CONTEO;
        diccionario_dame(d, cadena);
        TERMINA_CONTEO("diccionario_dame      ");

        int maximo = 0, total = 0;
        diccionario_colisiones(d, &maximo, &total);

        diccionario_libera(d, true, false);

        printf("\nMáximo número de colisiones: %d\n", maximo);
        printf("Total número de colisiones: %d\n", total);
}

int
main(int   argc,
     char* argv[])
{
        setlocale(LC_ALL, "");
        srand(semilla);

        int modo = -1;
        int N = -1;
        for (int i = 1; i < argc; i++) {
                if (!strcmp(argv[i], "--quicksort"))
                        modo = QUICKSORT;
                else if (!strcmp(argv[i], "--mergesort"))
                        modo = MERGESORT;
                else if (!strcmp(argv[i], "--arbol-binario-ordenado"))
                        modo = ARBOL_BINARIO_ORDENADO;
                else if (!strcmp(argv[i], "--arbol-rojinegro"))
                        modo = ARBOL_ROJINEGRO;
                else if (!strcmp(argv[i], "--diccionario"))
                        modo = DICCIONARIO;
                else if (!strcmp(argv[i], "--ordenado"))
                        ordenado = true;
                else
                        N = atoi(argv[i]);
        }

        if (modo == -1 || N == -1) {
                fprintf(stderr,
                        "Uso: %s\n"
                        "        [ --quicksort              |\n"
                        "          --mergesort              |\n"
                        "          --arbol-binario-ordenado |\n"
                        "          --arbol-rojinegro        |\n"
                        "          --diccionario            ] N\n", argv[0]);
                exit(1);
        }

        if (N < 1)
                return 0;

        switch (modo) {
        case QUICKSORT:
                main_quicksort(N);
                break;
        case MERGESORT:
                main_mergesort(N);
                break;
        case ARBOL_BINARIO_ORDENADO:
                main_arbol_binario_ordenado(N);
                break;
        case ARBOL_ROJINEGRO:
                main_arbol_rojinegro(N);
                break;
        case DICCIONARIO:
                main_diccionario(N);
                break;
        }

        return 0;
}
