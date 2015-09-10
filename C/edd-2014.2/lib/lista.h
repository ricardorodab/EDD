#pragma once

/**
 * @file lista.h
 *
 * @brief Prototipos de funciones para las estructuras Lista y
 * NodoLista.
 *
 * Aquí se encuentran los prototipos de las funciones
 * correspondientes a la estructura Lista, y su estructura auxiliar
 * NodoLista.
 *
 * La estructura Lista implementa listas doblemente ligadas tratando
 * de seguir un diseño orientado a objetos en lugar de uno
 * estructurado, que es lo común en C. Por lo tanto, los nodos de la
 * lista son de sólo lectura; su creación y destrucción está a cargo
 * de las funciones definidas en este archivo.
 *
 * Las instancias de la estructura @ref Lista deben crearse
 * utilizando la función lista_nueva():
 *
@code{.c}
Lista lista = lista_nueva();
@endcode
 *
 * A una instancia de Lista se le pueden agregar elementos al inicio
 * o al final de la misma; ambas operaciones toman el mismo tiempo:
 *
@code{.c}
lista_agrega_final(lista,  entero_nuevo(2));
lista_agrega_final(lista,  entero_nuevo(3));
lista_agrega_inicio(lista, entero_nuevo(1));
lista_agrega_inicio(lista, entero_nuevo(0));
@endcode
 *
 * Para eliminar un elemento de la lista, la función lista_elimina()
 * debe ser utilizada, junto con una función de comparación (tipo
 * @ref func_compara) para poder buscar el elemento a eliminar en la
 * lista:
 *
@code{.c}
int n = 3;
lista_elimina(lista, &n, compara_enteros);
@endcode
 *
 * Se pude utilizar la función compara_apuntadores() para comparar
 * apuntadores directamente si así se requiere.
 *
 * Para recorrer la lista, uno puede seguir el siguiente patrón:
 *
@code{.c}
NodoLista* nodo = lista_cabeza(lista);
while (nodo != NULL) {
        int* n = nodo_lista_elemento(nodo);
        printf("%d\n", *n);
        nodo = nodo_lista_siguiente(nodo);
}
@endcode
 *
 * O también se puede hacer uso del macro #LISTA_PARA_CADA (que
 * básicamente se expande al código de arriba):
 *
@code{.c}
LISTA_PARA_CADA(int*, n, lista, printf("%d\n", *n));
@endcode
 *
 * @author Canek Peláez Valdés <canek@ciencias.unam.mx>
 */

#include <stdbool.h>
#include "util.h"

/**
 * @brief Estructura para listas doblemente ligadas.
 *
 * La estructura @ref Lista es opaca; sus miembros no deben ser
 * accesados directamente.
 *
 * Las listas tienen un apuntador a un @ref NodoLista que es el
 * primer nodo de la lista y que llamaremos la *cabeza*, y un
 * apuntador a un NodoLista que es el último elemento de la lista y
 * que llamaremos el *rabo*. Cuando la lista es vacía la cabeza y el
 * rabo son `NULL`; cuando la lista tiene un único elemento la
 * cabeza y el rabo apuntan al mismo NodoLista; y en el resto de los
 * casos la cabeza y el rabo son diferentes.
 *
 * Se puede obtener la cabeza de la lista usando la función
 * lista_cabeza(), y el rabo usando lista_rabo().
 */
typedef struct _Lista Lista;

/**
 * @brief Estructura para nodos de listas doblemente ligadas.
 *
 * La estructura @ref NodoLista es opaca; sus miembros no deben ser
 * accesados directamente.
 *
 * Cada @ref NodoLista consiste de un apuntador a un elemento, un
 * apuntador a otro @ref NodoLista que es el nodo anterior, y un
 * apuntador a otro NodoLista que es el nodo siguiente. Si un
 * NodoLista es la cabeza de la lista, su anterior será `NULL`; si
 * es el rabo, su siguiente será `NULL`. En todos los otros casos el
 * anterior y el siguiente serán distintos de `NULL`.
 *
 * Para obtener el elemento de un nodo se puede usar la función
 * nodo_lista_elemento(), para obtener el nodo anterior se puede
 * usar nodo_lista_anterior(), y para obtener el siguiente se puede
 * usar nodo_lista_siguiente().
 */
typedef struct _NodoLista NodoLista;

/**
 * @brief Itera los elementos de una lista.
 *
 * Simple macro para implementar *for-each*; por ejemplo, con una
 * lista con apuntadores a enteros, se pueden imprimir todos sus
 * elementos usando:
 *
@code{.c}
LISTA_PARA_CADA(int*, n, lista, printf("%d\n", *n));
@endcode
 *
 * Se pueden hacer cosas más complejas también:
 *
@code{.c}
int suma = 0;
LISTA_PARA_CADA(int*, n, lista, {
        suma += *n;
});
@endcode
 *
 * @param T el tipo de los elementos de la lista.
 * @param v el nombre de la variable que se usará para cada elemento.
 * @param l la lista a iterar.
 * @param BLOQUE el bloque de código de la iteración.
 */
#define LISTA_PARA_CADA(T, v, l, BLOQUE)                              \
{                                                                     \
        NodoLista* tmp__ ## v = lista_cabeza(l);                      \
        while (tmp__ ## v != NULL) {                                  \
                T v = nodo_lista_elemento(tmp__ ## v);                \
                BLOQUE;                                               \
                tmp__ ## v = nodo_lista_siguiente(tmp__ ## v);        \
        }                                                             \
}

/**
 * @brief Crea una nueva lista.
 *
 * Una lista vacía **no** es `NULL` en esta implementación de listas
 * ligadas.
 *
 * @return la nueva lista, que debe ser liberada por el usuario.
 */
Lista*     lista_nueva           (void);

/**
 * @brief Regresa el primer nodo de una lista.
 * @param lista la lista de la que se quiere el primer nodo.
 * @return el primer nodo de la lista, o `NULL` si la lista es vacía.
 */
NodoLista* lista_cabeza          (Lista*        lista);

/**
 * @brief Regresa el último nodo de una lista.
 * @param lista la lista de la que se quiere el último nodo.
 * @return el último nodo de la lista, o `NULL` si la lista es vacía.
 */
NodoLista* lista_rabo            (Lista*        lista);

/**
 * @brief Regresa la longitud de una lista.
 * @param lista la lista de la que se quiere la longitud.
 * @return la longitud de la lista.
 */
int        lista_longitud        (Lista*        lista);

/**
 * @brief Agrega un elemento al inicio de una lista.
 *
 * Al llamar esta función, el elemento agregado se convierte en la
 * cabeza de la lista.
 *
 * @param lista la lista a la que se le agregará un elemento.
 * @param elemento el elemento a agregar.
 */
void       lista_agrega_inicio   (Lista*        lista,
                                  void*         elemento);
/**
 * @brief Agrega un elemento al final de una lista.
 *
 * Al llamar esta función, el elemento agregado se convierte en el
 * rabo de la lista.
 *
 * @param lista la lista a la que se le agregará un elemento.
 * @param elemento el elemento a agregar.
 */
void       lista_agrega_final    (Lista*        lista,
                                  void*         elemento);

/**
 * @brief Inserta un elemento en la lista antes del nodo recibido.
 *
 * @param lista la lista a la que se le quiere insertar un elemento.
 * @param nodo el nodo antes del cuál se insertará el elemento.
 * @param elemento el elemento a insertar.
 */
void       lista_inserta_antes   (Lista*        lista,
                                  NodoLista*    nodo,
                                  void*         elemento);

/**
 * @brief Inserta un elemento en la lista después del nodo recibido.
 *
 * @param lista la lista a la que se le quiere insertar un elemento.
 * @param nodo el nodo después del cuál se insertará el elemento.
 * @param elemento el elemento a insertar.
 */
void       lista_inserta_despues (Lista*        lista,
                                  NodoLista*    nodo,
                                  void*         elemento);

/**
 * @brief Elimina un elemento de la lista.
 *
 * Elimina un elemento de la lista, usando la función recibida para
 * comparar por igualdad. Si el elemento no está contenido en la
 * lista, la función no hace nada. Si hay varios elementos de la
 * lista tales que, usando la función de comparación, el elemento
 * recibido es igual a todos ellos, sólo se elimina el primero.
 *
 * @param lista la lista a la que se le quiere eliminar un elemento.
 * @param elemento el elemento a eliminar.
 * @param compara función de comparación para poder encontrar el
 * elemento.
 */
void       lista_elimina         (Lista*        lista,
                                  void*         elemento,
                                  func_compara  compara);

/**
 * @brief Elimina el primer elemento de la lista.
 *
 * Si la lista es vacía, la función abortará.
 *
 * @param lista la lista a la que se le eliminará el primer
 * elemento.
 */
void*      lista_elimina_primero (Lista*        lista);

/**
 * @brief Elimina el último elemento de la lista.
 *
 * Si la lista es vacía, la función abortará.
 *
 * @param lista la lista a la que se le eliminará el último
 * elemento.
 */
void*      lista_elimina_ultimo  (Lista*        lista);

/**
 * @brief Elimina un nodo de una lista.
 *
 * Si el nodo recibido no es parte de la lista, el comportamiento de
 * esta función no está definido.
 *
 * @param lista la lista a la que se le eliminará un nodo.
 * @param nodo el nodo a eliminar de la lista.
 */
void       lista_elimina_nodo    (Lista*        lista,
                                  NodoLista*    nodo);

/**
 * @brief Busca un elemento en una lista.
 *
 * Busca un elemento en la lista, usando la función recibida para
 * comparar por igualdad; si lo encuentra, regresa el nodo que lo
 * contiene. Si el elemento no está contenido en la lista, la
 * función regresa `NULL`. Si hay varios elementos de la lista tales
 * que, usando la función de comparación, el elemento recibido es
 * igual a todos ellos, se regresa el primero.
 *
 * @param lista la lista a la que se le quiere buscar un elemento.
 * @param elemento el elemento a buscar.
 * @param compara función de comparación para poder encontrar el
 * elemento.
 * @return el primer nodo que contiene al elemento, o `NULL`.
 */
NodoLista* lista_busca           (Lista*        lista,
                                  void*         elemento,
                                  func_compara  compara);

/**
 * @brief Regresa el *i*-ésimo nodo de una lista, comenzando desde
 * 0.
 * @param lista la lista de la cuál queremos el *i*-ésimo nodo.
 * @param indice el índice del nodo que queremos.
 * @return el *i*-ésimo nodo de la lista, comenzando desde 0, o
 * `NULL` si `indice` es menor que 0, o mayor o igual que la
 * longitud de la lista.
 */
NodoLista* lista_dame            (Lista*        lista,
                                  int           indice);
/**
 * @brief Regresa la reversa de una lista.
 *
 * La reversa de una lista es una lista con los mismos elementos que
 * la original, pero en el orden inverso.
 *
 * @param lista la lista de la cual queremos su reversa.
 * @return la reversa de la lista. La lista debe liberarse.
 */
Lista*     lista_reversa         (Lista*        lista);

/**
 * @brief Regresa la copia de una lista.
 *
 * @param lista la lista de la cual queremos su copia.
 * @return la copia de la lista. La lista debe liberarse.
 */
Lista*     lista_copia           (Lista*        lista);

/**
 * @brief Nos dice si una lista está o no ordenada.
 *
 * @param lista la lista que queremos saber si está ordenada.
 * @param compara función de comparación para poder comparar los
 * elementos de la lista.
 * @return `true` si la lista está ordenada, `false` en otro caso.
 */
bool       lista_esta_ordenada   (Lista*        lista,
                                  func_compara  compara);

/**
 * @brief Busca un elemento en una lista ordenada.
 *
 * La función es casi idéntica a lista_busca(), sólo deja de buscar
 * cuando se encuentra un elemento en la lista mayor al recibido. El
 * comportamiento de la función si la lista no está ordenada no está
 * definido.
 *
 * @param lista la lista ordenada a la que se le quiere buscar un
 * elemento.
 * @param elemento el elemento a buscar.
 * @param compara función de comparación para poder encontrar el
 * elemento.
 * @return el primer nodo que contiene al elemento, o `NULL`.
 */
NodoLista* lista_ordenada_busca  (Lista*        lista,
                                  void*         elemento,
                                  func_compara  compara);

/**
 * @brief Regresa una copia ordenada de una lista.
 *
 * La función implementa el algoritmo MergeSort para ordenar la
 * lista recibida.
 *
 * @param lista la lista que se quiere ordenar.
 * @param compara función de comparación para poder ordenar la
 * lista.
 * @return una copia ordenada de la lista. La lista debe liberarse.
 */
Lista*     lista_mergesort       (Lista*        lista,
                                  func_compara  compara);

/**
 * @brief Libera la memoria usada por una lista.
 *
 * La función libera la memoria usada por la lista, pero no la que
 * utilizan los elementos dentro de ella.
 *
 * @param lista la lista a liberar.
 */
void       lista_libera          (Lista*        lista);

/**
 * @brief Libera la memoria usada por la lista y sus elementos.
 *
 * La función libera la memoria usada por la lista, junto con la que
 * utilizan elementos dentro de ella. Si los elementos de la lista
 * tienen asiganada su memoria en la pila de ejecución, el
 * comportamiento de esta función no está definido: en ese caso es
 * mejor usar lista_libera().
 *
 * @param lista la lista a liberar junto con sus elementos.
 */
void       lista_libera_todo     (Lista*        lista);


/**
 * @brief Regresa el elemento de un nodo.
 * @param nodo el nodo del que se quiere el elemento.
 * @return el elemento del nodo.
 */
void*      nodo_lista_elemento   (NodoLista*    nodo);

/**
 * @brief Regresa el nodo anterior de un nodo.
 * @param nodo el nodo del que se quiere su nodo anterior.
 * @return el nodo anterior del nodo.
 */
NodoLista* nodo_lista_anterior   (NodoLista*    nodo);

/**
 * @brief Regresa el nodo siguiente de un nodo.
 * @param nodo el nodo del que se quiere su nodo siguiente.
 * @return el nodo siguiente del nodo.
 */
NodoLista* nodo_lista_siguiente  (NodoLista*    nodo);

/**
 * @brief Busca un elemento en la lista a partir de un nodo
 * específico.
 *
 * Busca un elemento en la lista, comenzando por el nodo recibido,
 * usando la función recibida para comparar por igualdad; si lo
 * encuentra, regresa el nodo que lo contiene. Si el elemento no
 * está contenido en ningún nodo subsecuente, la función regresa
 * `NULL`. Si hay varios elementos de la lista tales que, usando la
 * función de comparación, el elemento recibido es igual a todos
 * ellos, se regresa el primero que se encuentre.
 *
 * @param nodo el nodo a partir del cual buscaremos un elemento.
 * @param elemento el elemento a buscar.
 * @param compara función de comparación para poder encontrar el
 * elemento.
 * @return el primer nodo que contiene al elemento, o `NULL`.
 */
NodoLista* nodo_lista_busca      (NodoLista*    nodo,
                                  void*         elemento,
                                  func_compara  compara);
