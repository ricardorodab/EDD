#pragma once

/**
 * @file grafica.h
 *
 * @brief Prototipos de funciones para las estructuras Grafica,
 * VerticeGrafica, y AristaGrafica.
 *
 * Aquí se encuentran los prototipos de las funciones
 * correspondientes a la estructura Grafica, y sus estructuras
 * auxiliares VerticeGrafica y AristaGrafica.
 *
 * Los vértices de gráfica pueden recorrer sus listas de aristas que
 * lo conectan con otros vértices, y de ellos obtener los vértices
 * vecinos si así se desea:
 *
@code{.c}
Grafica* g = grafica_nueva(FUNC_COMPARA(strcmp));
grafica_agrega(g, "a");
// LLenamos la gráfica
VerticeGrafica* vg = grafica_vertice("a")
NodoLista* n = vertice_grafica_arista(vg);
while (n != NULL) {
        AristaGrafica* a = nodo_lista_elemento(n);
        double p = arista_grafica_peso(a);
        VerticeGrafica* vecino = arista_grafica_vecino(a);
        // Hacemos algo con la arista o el vecino.
        nodo = nodo_lista_siguiente(nodo);
}
@endcode
 *
 * También se puede hacer uso de las macros
 * #VERTICE_GRAFICA_PARA_CADA_ARISTA y
 * #VERTICE_GRAFICA_PARA_CADA_VECINO (que básicamente se expanden al
 * código de arriba).
 */

#include "lista.h"

/**
 * @brief Estructura para gráficas.
 *
 * La estructura @ref Grafica es opaca; sus miembros no deben ser
 * accesados directamente.
 */
typedef struct _Grafica Grafica;

/**
 * @brief Estructura para vértices de gráficas.
 *
 * La estructura @ref VerticeGrafica es opaca; sus miembros no deben
 * ser accesados directamente.
 */
typedef struct _VerticeGrafica VerticeGrafica;

/**
 * @brief Estructura para aristas de gráficas.
 *
 * La estructura @ref AristaGrafica es opaca; sus miembros no deben
 * ser accesados directamente.
 */
typedef struct _AristaGrafica AristaGrafica;

/**
 * @brief Itera los vértices de una gráfica.
 *
 * Simple macro para iterar todos los vértices de una gráfica en el
 * orden en el que fueron agregados. Por ejemplo, para imprimir
 * todos los vértices de la gráfica de cadenas usaríamos:
 *
@code{.c}
GRAFICA_PARA_CADA_VERTICE(vertice, grafica, {
        char* s = vertice_grafica_elemento(vertice);
        printf("Vértice: %s\n", s);
});
@endcode
 */
#define GRAFICA_PARA_CADA_VERTICE(a, vg, BLOQUE)                      \
{                                                                     \
        NodoLista* tmp__ ## a = vertice_grafica_iterador_aristas(vg); \
        while (tmp__ ## a != NULL) {                                  \
                AristaGrafica* a;                                     \
                a = nodo_lista_elemento(tmp__ ## a);                  \
                BLOQUE;                                               \
                tmp__ ## a = nodo_lista_siguiente(tmp__ ## a);        \
        }                                                             \
}

/**
 * @brief Itera las aristas de un vértice de gráfica.
 *
 * Simple macro para iterar las aristas de un vértice. Por ejemplo,
 * para un vértice de una gráfica de cadenas, podemos imprimir todos
 * sus vecinos junto con el peso de la arista que los une usando:
 *
@code{.c}
VERTICE_GRAFICA_PARA_CADA_ARISTA(a, vg, {
        VerticeGrafica* vecino = arista_grafica_vecino(a);
        double p = arista_grafica_peso(a);
        char* s = vertice_grafica_elemento(vecino);
        printf("Vecino: %s\n", s);
        printf("Peso  : %g\n", p);
});
@endcode
 *
 * @param a el nombre la variable de tipo @ref AristaGrafica que
 * tomará la arista del vértice en cada vuelta de la iteración.
 * @param vg el vértice de gráfica del que queremos iterar sus
 * aristas.
 * @param BLOQUE el bloque de código de la iteración.
 */
#define VERTICE_GRAFICA_PARA_CADA_ARISTA(a, vg, BLOQUE)               \
{                                                                     \
        NodoLista* tmp__ ## a = vertice_grafica_iterador_aristas(vg); \
        while (tmp__ ## a != NULL) {                                  \
                AristaGrafica* a;                                     \
                a = nodo_lista_elemento(tmp__ ## a);                  \
                BLOQUE;                                               \
                tmp__ ## a = nodo_lista_siguiente(tmp__ ## a);        \
        }                                                             \
}

/**
 * @brief Itera los vecinos de un vértice de gráfica.
 *
 * Simple macro para iterar los vecinos de un vértice. Por ejemplo,
 * para un vértice de una gráfica de cadenas, podemos imprimir todos
 * sus vecinos usando:
 *
@code{.c}
int i = 1;
VERTICE_GRAFICA_PARA_CADA_VECINO(v, vg, {
        char* s = vertice_grafica_elemento(v);
        printf("Vecino %d: %s\n", i++, s);
});
@endcode
 *
 * @param v el nombre la variable de tipo @ref VerticeGrafica que
 * tomará el vecino del vértice en cada vuelta de la iteración.
 * @param vg el vértice de gráfica del que queremos iterar sus
 * vecinos.
 * @param BLOQUE el bloque de código de la iteración.
 */
#define VERTICE_GRAFICA_PARA_CADA_VECINO(v, vg, BLOQUE)               \
{                                                                     \
        NodoLista* tmp__ ## v = vertice_grafica_iterador_aristas(vg); \
        while (tmp__ ## v != NULL) {                                  \
                AristaGrafica* tmp__2__ ## v;                         \
                tmp__2__ ## v = nodo_lista_elemento(tmp__ ## v);      \
                VerticeGrafica* v;                                    \
                v = arista_grafica_vecino(tmp__2__ ## v);             \
                BLOQUE;                                               \
                tmp__ ## v = nodo_lista_siguiente(tmp__ ## v);        \
        }                                                             \
}

/**
 * @brief Crea una nueva gráfica.
 * @param compara función de comparación para los elementos de la
 * gráfica.
 * @return la nueva gráfica.
 */
Grafica*        grafica_nueva                    (func_compara    compara);

/**
 * @brief Agrega un nuevo elemento a una gráfica.
 * @param grafica la gráfica a la cual agregaremos el elemento.
 * @param elemento el elemento a agregar. Si el elemento ya está
 * dentro de la gráfica, la función abortará.
 */
void            grafica_agrega                   (Grafica*        grafica,
                                                  void*           elemento);

/**
 * @brief Conecta dos elementos de una gráfica.
 *
 * Si alguno de los dos elementos no está en la gráfica, la función
 * abortará.
 *
 * @param grafica la gráfica en la cual conectaremos los elementos.
 * @param a el primer elemento a conectar.
 * @param b el segundo elemento a conectar.
 * @param peso el peso de la arista entre los dos elementos.
 */
void            grafica_conecta                  (Grafica*        grafica,
                                                  void*           a,
                                                  void*           b,
                                                  double          peso);

/**
 * @brief Elimina un elemento de una gráfica.
 *
 * Si el elemento no está en la gráfica, la función abortará.
 *
 * @param grafica la gráfica de la cuál queremos eliminar un
 * elemento.
 * @param elemento el elemento a eliminar de la gráfica.
 */
void            grafica_elimina                  (Grafica*        grafica,
                                                  void*           elemento);

/**
 * @brief Desconecta dos elementos de una gráfica.
 *
 * Si alguno de los dos elementos no está en la gráfica, la función
 * abortará.
 *
 * @param grafica la gráfica en la cual desconectaremos los
 * elementos.
 * @param a el primer elemento a desconectar.
 * @param b el segundo elemento a desconectar.
 */
void            grafica_desconecta               (Grafica*        grafica,
                                                  void*           a,
                                                  void*           b);

/**
 * @brief regresa el vértice de una gráfica que contenga a un
 * elemento determinado.
 *
 * Si el elemento no está en la gráfica, el método abortará.
 *
 * @param grafica la gráfica de la cuál queremos el vértice.
 * @param elemento el elemento del cuál queremos el vértice que lo
 * contenga.
 * @return el vértice de la gráfica que contiene al elemento.
 */
VerticeGrafica* grafica_vertice                  (Grafica*        grafica,
                                                  void*           elemento);

/**
 * @brief Regresa una lista con los vértices de una gráfica.
 *
 * Regresa una lista con los vértices de la gráfica, en el orden en
 * que fueron agregados. La lista debe de ser liberada.
 *
 * @param grafica la gráfica de la que queremos sus vértices.
 * @return una lista con los vértices de la gráfica, en el orden en
 * que fueron agregados.
 */
Lista*          grafica_vertices                 (Grafica*        grafica);

/**
 * @brief Nos dice si dos elementos están conectados en una gráfica.
 *
 * Si alguno de los dos elementos no está en la gráfica, la función
 * abortará.
 *
 * @param grafica la gráfica dónde queremos ver si dos vértices
 * están conectados.
 * @param a el primer elemento.
 * @param b el segundo elemento.
 * @return `true` si los vértices que contienen a los dos elementos
 * están conectados, `false` en otro caso.
 */
bool            grafica_estan_conectados         (Grafica*        grafica,
                                                  void*           a,
                                                  void*           b);

/**
 * @brief Nos dice el peso de dos elementos conectados en una gráfica.
 *
 * Si alguno de los dos elementos no está en la gráfica, la función
 * abortará; lo mismo ocurrirá si los dos elementos no están
 * conectados.
 *
 * @param grafica la gráfica dónde queremos ver el peso entre dos
 * vértices conectados.
 * @param a el primer elemento.
 * @param b el segundo elemento.
 * @return el peso entre los vértices que contienen a los dos
 * elementos conectados.
 */
double          grafica_peso                     (Grafica*        grafica,
                                                  void*           a,
                                                  void*           b);

/**
 * Nos dice si un elemento es vértice de una gráfica.
 * @param grafica la gráfica de la cual queremos saber si el
 * elemento está contenido en ella.
 * @param elemento el elemento que queremos saber si está en la
 * gráfica.
 * @return `true` si un vértice de la gráfica tiene a `elemento`
 * como elemento, `false` en otro caso.
 */
bool            grafica_contiene                 (Grafica*        grafica,
                                                  void*           elemento);

/**
 * @brief Itera los vértices de la gráfica usando BFS.
 *
 * Itera los vértices de la gráfica comenzando en el vértice que
 * contenga al elemento `elemento`. Si `elemento` no está contenido
 * dentro de la gráfica, la función abortará.
 *
 * Por ejemplo, para sumar todos los elementos de una componente
 * conexa de una gráfica de enteros, uno haría:
 *
@code{.c}
static void
suma_vertices(int* e, int* suma)
{
        *suma += *e;
}

int
main(int argc, char* argv[])
{
        Grafica g = grafica_nueva(compara_enteros);
        int a = 1;
        grafica_agrega(g, &a);
        // LLenamos la gráfica.
        int suma = 0;
        grafica_itera_bfs(g, &a, FUNC_PROCESA(suma_vertices), &suma);
        printf("La suma de los vértices es: %d\n", suma);
        return 0;
}
@endcode
 * @param grafica la gráfica donde queremos hacer el recorrido BFS.
 * @param elemento el elemento de la gráfica donde queremos comenzar
 * el recorrido.
 * @param procesa la función de procesamiento para procesar cada
 * elemento de la gráfica.
 * @param datos un apuntador a datos extra para la función de
 * procesamiento.
 */
void            grafica_itera_bfs                (Grafica*        grafica,
                                                  void*           elemento,
                                                  func_procesa    procesa,
                                                  void*           datos);

/**
 * @brief Itera los vértices de la gráfica usando DFS.
 *
 * Itera los vértices de la gráfica comenzando en el vértice que
 * contenga al elemento `elemento`. Si `elemento` no está contenido
 * dentro de la gráfica, la función abortará.
 *
 * Se utiliza igual que grafica_itera_bfs(), sólo que usando DFS en
 * lugar de BFS.
 *
 * @param grafica la gráfica donde queremos hacer el recorrido DFS.
 * @param elemento el elemento de la gráfica donde queremos comenzar
 * el recorrido.
 * @param procesa la función de procesamiento para procesar cada
 * elemento de la gráfica.
 * @param datos un apuntador a datos extra para la función de
 * procesamiento.
 */
void            grafica_itera_dfs                (Grafica*        grafica,
                                                  void*           elemento,
                                                  func_procesa    procesa,
                                                  void*           datos);

/**
 * @brief Regresa una trayectoria de distancia mínima del elemento
 * `a` al elemento `b`.
 *
 * Regresa una lista con elementos de la gráfica tal que representa
 * la trayectoria de distancia mínima entre dos elementos. La
 * distancia entre dos elementos es 1 si son vecinos. La lista
 * regresada debe de ser liberada. Si alguno de los dos elementos no
 * está en la gráfica, la función abortará.
 *
 * @param grafica la gráfica sobre la queremos encontrar una
 * trayectoria de distancia mínima.
 * @param a el primer elemento.
 * @param b el segundo elemento.
 * @return una trayectoria de distancia mínima del elemento `a` al
 * elemento `b`. Si no existe ninguna trayectoria entre `a` y `b`,
 * la lista será vacía.
 */
Lista*          grafica_trayectoria_minima       (Grafica*        grafica,
                                                  void*           a,
                                                  void*           b);

/**
 * @brief Regresa una trayectoria de peso mínimo del elemento `a` al
 * elemento `b`.
 *
 * Regresa una lista con elementos de la gráfica tal que representa
 * la trayectoria de peso mínimo entre dos elementos. El peso entre
 * dos elementos es el peso de la arista que los conecta; si no hay
 * tal arista, el peso es infinito. La lista regresada debe de ser
 * liberada. Si alguno de los dos elementos no está en la gráfica,
 * la función abortará.
 *
 * @param grafica la gráfica sobre la queremos encontrar una
 * trayectoria de peso mínimo.
 * @param a el primer elemento.
 * @param b el segundo elemento.
 * @return una trayectoria de peso mínimo del elemento `a` al
 * elemento `b`. Si no existe ninguna trayectoria entre `a` y `b`,
 * la lista será vacía.
 */
Lista*          grafica_dijkstra                 (Grafica*        grafica,
                                                  void*           a,
                                                  void*           b);

/**
 * Libera la memoria usada por la gráfica, pero no por sus
 * elementos.
 * @param grafica la gráfica de la cual queremos liberar su memoria.
 */
void            grafica_libera                   (Grafica*        grafica);

/**
 * Libera la memoria usada por la gráfica y sus elementos.
 * @param grafica la gráfica de la cual queremos liberar su memoria.
 */
void            grafica_libera_todo              (Grafica*        grafica);

/**
 * @brief Regresa el elemento de un vértice de gráfica.
 * @param vertice el vértice de gráfica del cual queremos su
 * elemento.
 * @return  el elemento del vértice de gráfica.
 */
void*           vertice_grafica_elemento         (VerticeGrafica* vertice);

/**
 * @brief Regresa un iterador para las aristas de un vértice.
 *
 * Regresa un @ref NodoLista que nos permite iterar las aristas del
 * vértice; el elemento de este NodoLista es la primera @ref
 * AristaGrafica del vértice recibido.
 *
 * @param vertice el vértice de gráfica del cual queremos iterar sus
 * aristas.
 * @return un iterador para las aristas del vértice. Si el vértice
 * no tiene vecinos, la función regresa `NULL`.
 */
NodoLista*      vertice_grafica_iterador_aristas (VerticeGrafica* vertice);

/**
 * @brief Regresa el color de un vértice de gráfica.
 * @param vertice el vértice de gráfica del cual queremos su color.
 * @return  el color del vértice de gráfica.
 */
Color           vertice_grafica_color            (VerticeGrafica* vertice);

/**
 * @brief Define el color de un vértice de gráfica.
 * @param vertice el vértice de gráfica del cual queremos definirle
 * su color.
 * @param color el nuevo color del vértice.
 */
void            vertice_grafica_define_color     (VerticeGrafica* vertice,
                                                  Color           color);

/**
 * @brief Regresa el vecino de una arista de gráfica.
 * @param arista la arista de gráfica de la cual queremos su vecino.
 * @return  el vecino de la arista de gráfica.
 */
VerticeGrafica* arista_grafica_vecino            (AristaGrafica*  arista);

/**
 * @brief Regresa el peso de una arista de gráfica.
 * @param arista la arista de gráfica de la cual queremos su peso.
 * @return  el peso de la arista de gráfica.
 */
double          arista_grafica_peso              (AristaGrafica*  arista);
