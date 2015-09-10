#pragma once

/**
 * @file arbolbinario.h
 *
 * @brief Prototipos de funciones para la estructura ArbolBinario y
 * NodoArbolBinario.
 *
 * Aquí se encuentran los prototipos de las funciones
 * correspondientes a la estructura ArbolBinario, y su estructura
 * auxiliar NodoArbolBinario.
 *
 * La estructura ArbolBinario implementa árboles binarios, árboles
 * binarios ordenados y árboles rojinegros, tratando de seguir un
 * diseño orientado a objetos en lugar de uno estructurado, que es
 * lo común en C. Por lo tanto, los nodos del árbol son de sólo
 * lectura; su creación y destrucción está a cargo de las funciones
 * definidas en este archivo.
 *
 * Las instancias de la estructura @ref ArbolBinario deben crearse
 * utilizando las funciones arbol_binario_ordenado_nuevo() o
 * arbol_rojinegro_nuevo():
 *
@code{.c}
ArbolBinario* ab_ordenado  = arbol_binario_ordenado_nuevo();
ArbolBinario* ab_rojinegro = arbol_rojinegro_nuevo();
@endcode
 *
 * Para agregarle elementos a una instancia de ArbolBinario, se
 * utilizan las funciones arbol_binario_ordenado_agrega() o
 * arbol_rojinegro_agrega():
 *
@code{.c}
for (int i = 0; i < 100; i++)
    arbol_binario_ordenado_agrega(ab_ordenado, srand() % 100);
for (int i = 0; i < 100; i++)
    arbol_rojinegro_agrega(ab_rojinegro, srand() % 100);
@endcode
 *
 * Si un árbol binario ordenado se le pasa como parámetro a
 * arbol_rojinegro_agrega(), o un árbol rojinegro se le pasa como
 * parámetro a arbol_binario_ordenado_agrega(), las funciones
 * abortarán.
 *
 * Para eliminar un elemento del árbol, las funciones
 * arbol_binario_ordenado_elimina() y arbol_rojinegro_elimina()
 * deben ser utilizadas, junto con una función de comparación (tipo
 * @ref func_compara), para poder hacer búsqueda binaria en los
 * árboles:
 *
@code{.c}
int n = 5;
arbol_binario_ordenado_elimina(ab_ordenado, &n, compara_enteros);
arbol_rojinegro_elimina(ab_ordenado, &n, compara_enteros);
@endcode
 *
 * Para recorrer el árbol, uno puede utilizar la estructura @ref
 * NodoArbolBinario; por ejemplo, para hacer un recorrido
 * *in-order*, podríamos escribir la siguiente función:
 *
@code{.c}
void
imprime_arbol(NodoArbolBinario* nodo) {
    if (nodo == NULL)
        return;
    imprime_arbol(nodo_arbol_binario_izquierdo(nodo));
    int* n = nodo_arbol_binario_elemento(nodo);
    printf("%d\n", *n);
    imprime_arbol(nodo_arbol_binario_derecho(nodo));
}
@endcode
 *
 * y entonces sólo mandarla llamar con la raíz del árbol:
 *
@code{.c}
printf("Árbol binario ordenado:\n");
imprime_arbol(arbol_binario_raiz(ab_ordenado);
printf("Árbol rojinegro:\n");
imprime_arbol(arbol_binario_raiz(ab_rojinegro);
@endcode
 *
 * También se puede usar el macro #ARBOL_BINARIO_PARA_CADA_NODO, que
 * recorre los nodos del árbol en *in-order* iterativamente.
 *
 * @author Canek Peláez Valdés <canek@ciencias.unam.mx>
 */

#include <stdbool.h>
#include "util.h"

/**
 * @brief Estructura para árboles binarios.
 *
 * La estructura @ref ArbolBinario es opaca; sus miembros no deben
 * ser accesados directamente.
 *
 * Un árbol binario tiene un apuntador a @ref NodoArbolBinario que
 * llamaremos raíz, y que podemos obtener usando la función
 * arbol_binario_raiz().
 */
typedef struct _ArbolBinario ArbolBinario;

/**
 * @brief Estructura para nodos de árboles binarios.
 *
 * La estructura @ref NodoArbolBinario es opaca; sus miembros no
 * deben ser accesados directamente.
 *
 * Un nodo de árbol binario tiene un elemento, que es un apuntador a
 * cualquier tipo de objeto; un apuntador a @ref NodoArbolBinario al
 * nodo padre en el árbol; un apuntador a NodoArbolBinario a su hijo
 * izquierdo, y un apuntador a NodoArbolBinario a su hijo derecho.
 *
 * Estos miembros los podemos acceder (pero no modificar) con las
 * funciones nodo_arbol_binario_elemento(),
 * nodo_arbol_binario_padre(), nodo_arbol_binario_izquierdo() y
 * nodo_arbol_binario_derecho(), respectivamente.
 */
typedef struct _NodoArbolBinario NodoArbolBinario;

/**
 * @brief Recorre los nodos de un árbol binario *in-order*.
 *
 * Simple macro para recorrer los nodos de un árbol binario; por
 * ejemplo, con un árbol binario ordenado con apuntadores a enteros,
 * se pueden imprimir todos sus elementos en orden usando:
 *
@code{.c}
ARBOL_BINARIO_PARA_CADA_NODO(nodo, arbol, {
    int* n = nodo_arbol_binario_elemento(nodo);
    printf("%d\n", *n);
});
@endcode
 *
 * @param nodo el nombre de la variable de tipo @ref
 * NodoArbolBinario que se usará para cada nodo.
 * @param arbol el árbol a recorrer.
 * @param BLOQUE el bloque de código del recorrido.
 */
#define ARBOL_BINARIO_PARA_CADA_NODO(nodo, arbol, BLOQUE)             \
{                                                                     \
        NodoArbolBinario* nodo = arbol_binario_raiz(arbol);           \
        Lista* tmp_pila_ ## nodo = lista_nueva();                     \
        while (nodo != NULL) {                                        \
                lista_agrega_final(tmp_pila_ ## nodo, nodo);          \
                nodo = nodo_arbol_binario_izquierdo(nodo);            \
        }                                                             \
        while (lista_longitud(tmp_pila_ ## nodo) > 0) {               \
                nodo = lista_elimina_ultimo(tmp_pila_ ## nodo);       \
                BLOQUE;                                               \
                nodo = nodo_arbol_binario_derecho(nodo);              \
                while (nodo != NULL) {                                \
                        lista_agrega_final(tmp_pila_ ## nodo, nodo);  \
                        nodo = nodo_arbol_binario_izquierdo(nodo);    \
                }                                                     \
        }                                                             \
}

/**
 * @brief Regresa la raíz de un árbol binario.
 * @param arbol el árbol binario del que queremos la raíz.
 * @return la raíz del árbol binario.
 */
NodoArbolBinario*  arbol_binario_raiz             (ArbolBinario*     arbol);

/**
 * @brief Regresa el número de elementos de un árbol binario.
 * @param arbol el árbol binario del que queremos el número de elementos.
 * @return el número de elementos del árbol binario.
 */
unsigned int       arbol_binario_elementos        (ArbolBinario*     arbol);

/**
 * @brief Regresa la profundidad de un árbol binario.
 * @param arbol el árbol binario del que queremos la profundidad.
 * @return la profundidad del árbol binario.
 */
unsigned int       arbol_binario_profundidad      (ArbolBinario*     arbol);

/**
 * @brief Gira el árbol binario a la izquierda sobre el nodo recibido.
 * @param arbol el árbol binario a girar a la izquierda.
 * @param nodo el nodo sobre el cual girar el árbol binario.
 */
void               arbol_binario_gira_izquierda   (ArbolBinario*     arbol,
                                                   NodoArbolBinario* nodo);

/**
 * @brief Gira el árbol binario a la derecha sobre el nodo recibido.
 * @param arbol el árbol binario a girar a la derecha.
 * @param nodo el nodo sobre el cual girar el árbol binario.
 */
void               arbol_binario_gira_derecha     (ArbolBinario*     arbol,
                                                   NodoArbolBinario* nodo);

/**
 * @brief Nos dice si un árbol binario es o no ordenado.
 * @param arbol el árbol binario del que queremos saber si está
 * ordenado.
 * @param compara apuntado a una función de comparación, para
 * comparar los elementos del árbol.
 */
bool               arbol_binario_es_ordenado      (ArbolBinario*     arbol,
                                                   func_compara      compara);

/**
 * @brief Nos dice si un árbol binario es rojinegro.
 *
 * En este momento la función sólo regresa `true` cuando el árbol
 * fue creado con arbol_rojinegro_nuevo().
 *
 * @param arbol el árbol binario que queremos saber si es rojinegro.
 * @return `true` si el árbol binario es rojinegro, `false` en otro
 * caso.
 */
bool               arbol_binario_es_rojinegro     (ArbolBinario*     arbol);

/**
 * @brief Regresa la representación en cadena de un árbol binario.
 * @param arbol el árbol del que queremos la representación en cadena.
 * @param a_cadena función para convertir a cadenas cada uno de los
 * elementos del árbol binario.
 * @return la representación en cadena del árbol binario.
 */
char*              arbol_binario_a_cadena         (ArbolBinario*     arbol,
                                                   func_a_cadena     a_cadena);

/**
 * @brief Libera la memoria usada por el árbol binario, pero no la
 * usada por sus elementos.
 * @param arbol el árbol binario que queremos liberar.
 */
void               arbol_binario_libera           (ArbolBinario*     arbol);

/**
 * @brief Libera la memoria usada por el árbol binario, junto conla
 * usada por sus elementos.
 * @param arbol el árbol binario que queremos liberar.
 */
void               arbol_binario_libera_todo      (ArbolBinario*     arbol);

/**
 * @brief Crea un nuevo árbol binario ordenado.
 * @param compara función de comparación para mantener ordenado el
 * árbol binario.
 * @return el nuevo árbol binario ordenado, que hay que liberar.
 */
ArbolBinario*      arbol_binario_ordenado_nuevo   (func_compara      compara);

/**
 * @brief Agrega un nuevo elemento a un árbol binario ordenado.
 * @param arbol el árbol binario ordenado al que queremos agregarle
 * un elemento. Si el árbol binario no es ordenado, la función
 * abortará.
 * @param elemento el elemento a agregar al árbol binario ordenado.
 * @return el nodo de árbol binario que contiene al nuevo elemento
 * dentro del árbol binario ordenado.
 */
NodoArbolBinario*  arbol_binario_ordenado_agrega  (ArbolBinario*     arbol,
                                                   void*             elemento);

/**
 * @brief Busca un elemento dentro de un árbol binario ordenado.
 * @param arbol el árbol binario ordenado en el que queremos buscar
 * el elemento. Si el árbol binario no es ordenado, la función
 * abortará.
 * @param elemento el elemento a buscar dentro del árbol binario
 * ordenado.
 * @return el nodo de árbol binario que contiene al elemento
 * buscado, o `NULL` si no se encuentra.
 */
NodoArbolBinario*  arbol_binario_ordenado_busca   (ArbolBinario*     arbol,
                                                   void*             elemento);

/**
 * @brief Elimina un elemento de un árbol binario ordenado.
 * @param arbol el árbol binario ordenado al que queremos eliminarle
 * un elemento. Si el árbol binario no es ordenado, la función
 * abortará.
 * @param elemento el elemento que queremos eliminar del árbol
 * binario ordenado. Si el elemento no está dentro del árbol, la
 * función no lo modifica.
 */
void               arbol_binario_ordenado_elimina (ArbolBinario*     arbol,
                                                   void*             elemento);

/**
 * @brief Crea un nuevo árbol rojinegro.
 * @param compara función de comparación para mantener ordenado el
 * árbol rojinegro.
 * @return el nuevo árbol rojinegro, que hay que liberar.
 */
ArbolBinario*      arbol_rojinegro_nuevo          (func_compara      compara);

/**
 * @brief Agrega un nuevo elemento a un árbol rojinegro.
 * @param arbol el árbol rojinegro al que queremos agregarle un
 * elemento. Si el árbol no es rojinegro, la función abortará.
 * @param elemento el elemento a agregar al árbol rojinegro.
 * @return el nodo de árbol binario que contiene al nuevo elemento
 * dentro del árbol rojinegro.
 */
NodoArbolBinario*  arbol_rojinegro_agrega         (ArbolBinario*     arbol,
                                                   void*             elemento);

/**
 * @brief Elimina un elemento de un árbol rojinegro.
 * @param arbol el árbol rojinegro al que queremos eliminarle un
 * elemento. Si el árbol binario no es rojinegro, la función
 * abortará.
 * @param elemento el elemento que queremos eliminar del árbol
 * rojinegro. Si el elemento no está dentro del árbol, la función no
 * lo modifica.
 */
void               arbol_rojinegro_elimina        (ArbolBinario*     arbol,
                                                   void*             elemento);

/**
 * @brief Regresa el elemento de un nodo de árbol binario.
 * @param nodo el nodo de árbol binario del que queremos su
 * elemento.
 * @return el elemento del nodo de árbol binario.
 */
void*              nodo_arbol_binario_elemento    (NodoArbolBinario* nodo);

/**
 * @brief Regresa el nodo padre de un nodo de árbol binario.
 * @param nodo el nodo de árbol binario del que queremos su nodo
 * padre.
 * @return el nodo padre del nodo de árbol binario.
 */
NodoArbolBinario*  nodo_arbol_binario_padre       (NodoArbolBinario* nodo);

/**
 * @brief Regresa el nodo izquierdo de un nodo de árbol binario.
 * @param nodo el nodo de árbol binario del que queremos su nodo
 * izquierdo.
 * @return el nodo izquierdo del nodo de árbol binario.
 */
NodoArbolBinario*  nodo_arbol_binario_izquierdo   (NodoArbolBinario* nodo);

/**
 * @brief Regresa el nodo derecho de un nodo de árbol binario.
 * @param nodo el nodo de árbol binario del que queremos su nodo
 * derecho.
 * @return el nodo derecho del nodo de árbol binario.
 */
NodoArbolBinario*  nodo_arbol_binario_derecho     (NodoArbolBinario* nodo);

/**
 * @brief Regresa el color de un nodo de árbol binario.
 * @param nodo el nodo de árbol binario del que queremos su color.
 * @return el color del nodo de árbol binario.
 */
Color              nodo_arbol_binario_color       (NodoArbolBinario* nodo);
