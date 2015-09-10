#pragma once

#include "util.h"

/**
 * @file arreglos.h
 *
 * @brief Definciones de prototipos de funciones para manipular
 * arreglos.
 *
 * Los arreglos son representados con `void**`, por lo que
 * generalmente habrá que hacer una audición del arreglo utilizado a
 * este tipo:
 *
@code{.c}
int** a = ARREGLO(int*, 10);
for (int i = 0; i < 10; i++)
        a[i] = entero_nuevo(rand() % 100);
arreglos_quicksort((void**)a, 10, compara_enteros);
@endcode
 *
 * Para hacer el código más legible, la macro
 * @ref ARREGLO_ANONIMO se ofrece también:
 *
@code{.c}
arreglos_quicksort(ARREGLO_ANONIMO(a), 10, compara_enteros);
@endcode
 */

/**
 * @brief Nos dice si un arreglo recibido está o no arreglado.
 * @param arreglo el arreglo que queremos ver si está ordenado.
 * @param n el tamaño del arreglo.
 * @param compara la función de comparación para comparar los
 * elementos del arreglo.
 * @return `true` si el arreglo está ordenado, `false` en otro caso.
 */
bool            arreglos_esta_ordenado     (void**        arreglo,
                                            int           n,
                                            func_compara  compara);
/**
 * @brief Realiza una búsqueda binaria en un arreglo.
 *
 * La función supone que el arreglo está ordenado bajo la función de
 * comparación `compara`. Si no es así, el comportamiento de la
 * función no está definido.
 *
 * @param arreglo el arreglo sobre el que queremos realizar una
 * búsqueda.
 * @param n el tamaño del arreglo.
 * @param elemento el elemento que queremos buscar dentro del
 * arreglo.
 * @param compara la función de comparación para comparar los
 * elementos del arreglo.
 * @return un entero entre `0` y `n-1` con el índice del elemento en
 * el arreglo si es que se encuentra, o `-1` en otro caso.
 */
int            arreglos_busqueda_binaria   (void**        arreglo,
                                            int           n,
                                            void*         elemento,
                                            func_compara  compara);

/**
 * @brief Ordena un arreglo usando SelectionSort. El ordenamiento se
 * hace en sitio.
 * @param arreglo el arreglo que queremos ordenar.
 * @param n el tamaño del arreglo.
 * @param compara la función de comparación para comparar los
 * elementos del arreglo.
 */
void           arreglos_selectionsort      (void**        arreglo,
                                            int           n,
                                            func_compara  compara);
/**
 * @brief Ordena un arreglo usando QuickSort. El ordenamiento se
 * hace en sitio.
 * @param arreglo el arreglo que queremos ordenar.
 * @param n el tamaño del arreglo.
 * @param compara la función de comparación para comparar los
 * elementos del arreglo.
 */
void           arreglos_quicksort          (void**        arreglo,
                                            int           n,
                                            func_compara  compara);
