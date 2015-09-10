#pragma once

/**
 * @file diccionario.h
 *
 * @brief Prototipos de funciones para la estructura Diccionario.
 *
 * Aquí se encuentran los prototipos de las funciones
 * correspondientes a la estructura Diccionario.
 */

#include "lista.h"

/**
 * @brief Estructura para diccionarios.
 *
 * La estructura @ref Diccionario es opaca; sus miembros no deben
 * ser accesados directamente.
 */
typedef struct _Diccionario Diccionario;

/**
 * @brief Máxima carga que permitiremos tenga el diccionario.
 */
#define DICCIONARIO_MAXIMA_CARGA 0.72

/**
 * @brief Itera los elementos de un diccionario.
 *
 * Simple macro para implementar *for-each* para diccionarios; por
 * ejemplo, con un diccionario con apuntadores a enteros, se pueden
 * imprimir todos sus elementos usando:
 *
@code{.c}
DICCIONARIO_PARA_CADA(int*, n, diccionario, printf("%d\n", *n));
@endcode
 *
 * Se pueden hacer cosas más complejas también:
 *
@code{.c}
int suma = 0;
DICCIONARIO_PARA_CADA(int*, n, diccionario, {
        suma += *n;
});
@endcode
 *
 * @param T el tipo de los elementos del diccionario.
 * @param v el nombre de la variable que se usará para cada elemento.
 * @param d el diccionario a iterar.
 * @param BLOQUE el bloque de código de la iteración.
 */
#define DICCIONARIO_PARA_CADA(T, v, d, BLOQUE)                        \
{                                                                     \
        Lista* tmp_1_ ## v = diccionario_elementos(d);                \
        NodoLista* tmp__ ## v = lista_cabeza(tmp_1_ ## v);            \
        while (tmp__ ## v != NULL) {                                  \
                T v = nodo_lista_elemento(tmp__ ## v);                \
                BLOQUE;                                               \
                tmp__ ## v = nodo_lista_siguiente(tmp__ ## v);        \
        }                                                             \
        lista_libera(tmp_1_ ## v);                                    \
}

/**
 * @brief Crea un nuevo diccionario.
 * @param n el tamaño requerido del diccionario.
 * @param huella función de huellas diginales para las llaves.
 * @param compara función de comparación para las llaves.
 * @return el nuevo diccionario.
 */
Diccionario*   diccionario_nuevo       (int          n,
                                        func_huella  huella,
                                        func_compara compara);

/**
 * @brief Agrega un elemento a un diccionario.
 *
 * Si la llave ya existe en el diccionario, el valor correspondiente
 * será reemplazado porque el que esta función recibe. El viejo
 * valor no será liberado de la memoria.
 *
 * @param diccionario el diccionario al que se le agregará el
 * elemento.
 * @param llave la llave del nuevo elemento.
 * @param valor el nuevo elemento.
 */
void           diccionario_agrega      (Diccionario* diccionario,
                                        void*        llave,
                                        void*        valor);

/**
 * @brief Regresa el elemento asociado a una llave en un
 * diccionario.
 *
 * @param diccionario el diccionario del que queremos obtener un
 * elemento.
 * @param llave la llave del elemento que se desea obtener.
 * @return el elemento asociado a la llave en el diccionario, o
 * `NULL` si no hay ningún elemento asociado a la llave.
 */
void*          diccionario_dame        (Diccionario* diccionario,
                                        void*        llave);

/**
 * @brief Elimina el elemento asociado a una llave en un
 * diccionario.
 *
 * Si no hay ningún elemento asociado a la llave, la función
 * abortará.
 *
 * @param diccionario el diccionario al cual queremos eleminarle un
 * elemento.
 * @param llave la llave del elemento que queremos eliminar.
 */
void           diccionario_elimina     (Diccionario* diccionario,
                                        void*        llave);

/**
 * @brief Nos dice si una llave está o no en el diccionario.
 *
 * @param diccionario el diccionario al cual queremos saber si una
 * llave está en él.
 * @param llave la llave que queremos ver si está.
 * @return `true` si una llave está en el diccionario, `false` en
 * otro caso.
 */
bool           diccionario_tiene_llave (Diccionario* diccionario,
                                        void*        llave);

/**
 * @brief Regresa una lista con las llaves en un diccionario.
 *
 * La lista de llaves no tiene ningún orden significativo.
 *
 * @param diccionario el diccionario del cual se quieren las llaves.
 * @return una lista con las llaves en un diccionario, que el
 * usuario debe liberar.
 */
Lista*         diccionario_llaves      (Diccionario* diccionario);

/**
 * @brief Regresa una lista con los elementos en un diccionario.
 *
 * La lista de elementos no tiene ningún orden significativo.
 *
 * @param diccionario el diccionario del cual se quieren los elementos.
 * @return una lista con los elementos en un diccionario, que el
 * usuario debe liberar.
 */
Lista*         diccionario_elementos   (Diccionario* diccionario);

/**
 * @brief Calcula el número máximo y total de colisiones en un
 * diccionario.
 * @param diccionario el diccionario del cual queremos el número
 * máximo y total de colisiones.
 * @param[out] maximo apuntador a un entero donde se guardará el
 * número máximo de colisiones.
 * @param[out] total apuntador a un entero donde se guardará el
 * número total de colisiones.
 */
void           diccionario_colisiones  (Diccionario* diccionario,
                                        int*         maximo,
                                        int*         total);

/**
 * @brief Nos dice la carga de un diccionario.
 * @param diccionario el diccionario del cual queremos la carga.
 * @return la carga del diccionario.
 */
double         diccionario_carga       (Diccionario* diccionario);

/**
 * @brief Nos dice el total de elementos en un diccionario.
 * @param diccionario el diccionario del cual queremos el total.
 * @return el total de elementos en un diccionario.
 */
int            diccionario_total       (Diccionario* diccionario);

/**
 * @brief Libera la memoria usada por un diccionario.
 *
 * Opcionalmente, también libera la memoria usada por las llaves y/o
 * los valores del mismo.
 *
 * @param diccionario el diccionario al cual se le quiere liberar la
 * memoria que utiliza.
 * @param llaves si `true`, la función liberará la memoria usada por
 * las llaves del diccionario.
 * @param valores si `true`, la función liberará la memoria usada
 * por los valores del diccionario.
 */
void           diccionario_libera      (Diccionario* diccionario,
                                        bool         llaves,
                                        bool         valores);
