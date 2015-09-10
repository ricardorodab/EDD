#pragma once

/**
 * @file monticulominimo.h
 *
 * @brief Prototipos de funciones para la estructura
 * MonticuloMinimo.
 *
 * Aquí se encuentran los prototipos de las funciones
 * correspondientes a la estructura MonticuloMinimo.
 *
 * Los montículos mínimos (*min heaps*) necesitan una función de
 * comparación para poder poner el mínimo en el tope del montículo,
 * y una función de índice para poder reacomodarlos rápidamente.
 */

#include "lista.h"

/**
 * @brief Estructura para montículos mínimos.
 *
 * La estructura @ref MonticuloMinimo es opaca; sus miembros no
 * deben ser accesados directamente.
 */
typedef struct _MonticuloMinimo MonticuloMinimo;

/**
 * @brief Crea un nuevo montículo mínimo.
 * @param compara función de comparación para los elementos del
 * montículo.
 * @param indice función de índice para los elementos del montículo.
 * @return un nuevo montículo mínimo, que hay que liberar.
 */
MonticuloMinimo* monticulo_minimo_nuevo          (func_compara     compara,
                                                  func_indice      indice);

/**
 * @brief Crea un nuevo montículo mínimo a partir de una lista.
 *
 * Si se usa monticulo_minimo_nuevo(), seguido de varias llamadas a
 * monticulo_minimo_agrega(), agregar *n* elementos toma tiempo
 * *O*(*n* log *n*). Usando esta función, y suponiendo que ya no hay
 * necesidad de agregar más elementos, crear un montículo de *n*
 * elementos toma tiempo *O*(*n*).
 *
 * @param lista una lista ligada con elementos que se agregarán al
 * montículo.
 * @param compara función de comparación para los elementos del
 * montículo.
 * @param indice función de índice para los elementos del montículo.
 * @return un nuevo montículo mínimo con *n* elementos, que hay que
 * liberar.
 */
MonticuloMinimo* monticulo_minimo_nuevo_de_lista (Lista*           lista,
                                                  func_compara     compara,
                                                  func_indice      indice);
/**
 * @brief Agrega un nuevo elemento a un montículo mínimo.
 * @param monticulo el montículo al que se le agregará un elemento.
 * @param elemento el elemento a agregar al montículo.
 */
void             monticulo_minimo_agrega         (MonticuloMinimo* monticulo,
                                                  void*            elemento);

/**
 * @brief Elimina el tope de un montículo mínimo.
 *
 * Si el montículo está vacío, la función abortará.
 *
 * @param monticulo el montículo al que se le eliminará su tope.
 * @return el tope eliminado del montículo.
 */
void*            monticulo_minimo_elimina        (MonticuloMinimo* monticulo);

/**
 * @brief Nos dice si un montículo mínimo es vacío.
 * @param monticulo el montículo del que queremos saber si está
 * vacío.
 * @return `true` si el montículo está vacío, `false` en otro caso.
 */
bool             monticulo_minimo_es_vacio       (MonticuloMinimo* monticulo);

/**
 * @brief Reordena un montículo mínimo a partir de un elemento cuyo
 * valor disminuyó.
 *
 * Si el elemento cuyo valor cambió, no fue disminuyendo, el
 * comportamiento de esta función queda sin definir.
 *
 * @param monticulo el monticulo a reordenar.
 * @param elemento el elemento del montículo cuyo valor disminuyó.
 */
void             monticulo_minimo_reordena       (MonticuloMinimo* monticulo,
                                                  void*            elemento);

/**
 * @brief Nos da el índice del último elemento del montículo.
 *
 * Nos da el índice en el árbol binario, recorrido por BFS, del
 * último del montículo.
 *
 * @param monticulo el montículo del que queremos saber el índice
 * del último elemento.
 * @return el índice del último elemento del montículo.
 */
int              monticulo_minimo_ultimo         (MonticuloMinimo* monticulo);

/**
 * @brief Nos da el *i*-ésimo elemento del montículo.
 *
 * Nos da el *i*-ésimo elemento del montículo, en el orden dado de
 * recorrerlo con BFS.
 *
 * @param monticulo el montículo del que queremos el *i*-ésimo
 * elemento.
 * @param indice el índice del elemento que queremos.
 * @return el *i*-ésimo elemento del montículo.
 */
void*            monticulo_minimo_dame           (MonticuloMinimo* monticulo,
                                                  int              indice);

/**
 * @brief Libera la memoria utilizada por un montículo mínimo, pero
 * no por sus elementos.
 * @param monticulo el montículo que queremos liberar.
 */
void             monticulo_minimo_libera         (MonticuloMinimo* monticulo);

/**
 * @brief Libera la memoria utilizada por un montículo mínimo, junto
 * con la de sus elementos.
 * @param monticulo el montículo que queremos liberar.
 */
void             monticulo_minimo_libera_todo    (MonticuloMinimo* monticulo);
