#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "arbolbinario.h"
#include "lista.h"

#define ES_NEGRO(a)      ((a) == NULL || (a)->color == COLOR_NEGRO)
#define ES_ROJO(a)       ((a) != NULL && (a)->color == COLOR_ROJO)
#define ES_IZQUIERDO(a)  ((a) != NULL && (a)->padre != NULL && \
                          (a)->padre->izquierdo == (a))
#define ES_DERECHO(a)    ((a) != NULL && (a)->padre != NULL && \
                          (a)->padre->derecho == (a))

typedef enum {
        ARBOL_BINARIO_ORDENADO,
        ARBOL_ROJINEGRO
} TipoArbol;

struct _ArbolBinario {
        NodoArbolBinario* raiz;
        TipoArbol         tipo;
        unsigned int      elementos;
        func_compara      compara;
};

struct _NodoArbolBinario {
        void*             elemento;
        NodoArbolBinario* padre;
        NodoArbolBinario* izquierdo;
        NodoArbolBinario* derecho;
        Color             color;
};

NodoArbolBinario*
arbol_binario_raiz(ArbolBinario* arbol)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

unsigned int
arbol_binario_elementos(ArbolBinario* arbol)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

unsigned int
arbol_binario_profundidad(ArbolBinario* arbol)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

void
arbol_binario_gira_izquierda(ArbolBinario*     arbol,
                             NodoArbolBinario* nodo)
{
        assert(arbol != NULL && nodo != NULL);
        // Aquí va su código.
}

void
arbol_binario_gira_derecha(ArbolBinario*     arbol,
                           NodoArbolBinario* nodo)
{
        assert(arbol != NULL && nodo != NULL);
        // Aquí va su código.
}

bool
arbol_binario_es_ordenado(ArbolBinario* arbol,
                          func_compara  compara)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

bool
arbol_binario_es_rojinegro(ArbolBinario* arbol)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

static char*
ab_espacios(int  n,
            int* rama) {
        int l = 0;
        for (int i = 0; i < n; i++)
                if (rama[i])
                         /* "│ " en utf-8 toma 5 bytes, 3 para "│ "
                            (0xe2, 0x94, 0x82), y 2 espacios. */
                        l += 5;
                else
                        l += 3;
        /* Espacio para el fin de cadena. */
        l++;
        char* s = ARREGLO(char, l);
        s[0] = '\0';
        for (int i = 0; i < n; i++)
                if (rama[i])
                        strcat(s, "│  ");
                else
                        strcat(s, "   ");
        return s;
}

static char*
nodo_a_cadena(NodoArbolBinario* nodo,
              func_a_cadena     a_cadena,
              int               nivel,
              int*              rama,
              int               p)
{
        char* s;
        char* n = a_cadena(nodo->elemento);
        switch (nodo->color) {
        case COLOR_ROJO:
                s = concatena_cadenas("R{", n, "}\n", NULL);
                break;
        case COLOR_NEGRO:
                s = concatena_cadenas("N{", n, "}\n", NULL);
                break;
        default:
                s = concatena_cadenas(n, "\n", NULL);
                break;
        }
        free(n);

        rama[nivel] = true;
        if (nodo->izquierdo != NULL && nodo->derecho != NULL) {
                char* e1 = ab_espacios(nivel, rama);
                char* tizq = nodo_a_cadena(nodo->izquierdo, a_cadena,
                                           nivel+1, rama, p);
                char* e2 = ab_espacios(nivel, rama);
                rama[nivel] = false;
                char* tder = nodo_a_cadena(nodo->derecho, a_cadena,
                                           nivel+1, rama, p);
                char* rms = concatena_cadenas(s,
                                              e1, "├─›", tizq,
                                              e2, "└─»", tder,
                                              NULL);
                libera_cadenas(s, e1, tizq, e2, tder, NULL);
                s = rms;
        } else if (nodo->izquierdo != NULL) {
                char* e = ab_espacios(nivel, rama);
                rama[nivel] = false;
                char* t = nodo_a_cadena(nodo->izquierdo, a_cadena,
                                        nivel+1, rama, p);
                char* rm = concatena_cadenas(s, e,
                                             "└─›", t, NULL);
                libera_cadenas(s, e, t, NULL);
                s = rm;
        } else if (nodo->derecho != NULL) {
                char* e = ab_espacios(nivel, rama);
                rama[nivel] = false;
                char* t = nodo_a_cadena(nodo->derecho, a_cadena,
                                        nivel+1, rama, p);
                char* rm = concatena_cadenas(s, e,
                                             "└─»", t, NULL);
                libera_cadenas(s, e, t, NULL);
                s = rm;
        }
        return s;
}

char*
arbol_binario_a_cadena(ArbolBinario* arbol,
                       func_a_cadena a_cadena)
{
        NodoArbolBinario* raiz = arbol_binario_raiz(arbol);
        if (raiz == NULL)
                return strdup("<vacío>");
        int p = arbol_binario_profundidad(arbol) + 1;
        int* rama = ARREGLO(int, p);
        for (int i = 0; i < p; i++)
            rama[i] = false;
        char* s = nodo_a_cadena(raiz, a_cadena, 0, rama, p);
        free(rama);
        return s;
}

void
arbol_binario_libera(ArbolBinario* arbol)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

void
arbol_binario_libera_todo(ArbolBinario* arbol)
{
        assert(arbol != NULL);
        // Aquí va su código.
}

ArbolBinario*
arbol_binario_ordenado_nuevo(func_compara compara)
{
        assert(compara != NULL);
        // Aquí va su código.
}

NodoArbolBinario*
arbol_binario_ordenado_agrega(ArbolBinario* arbol,
                              void*         elemento)
{
        assert(arbol != NULL && elemento != NULL &&
               (arbol->tipo == ARBOL_BINARIO_ORDENADO ||
                arbol->tipo == ARBOL_ROJINEGRO));
        // Aquí va su código.
}

NodoArbolBinario*
arbol_binario_ordenado_busca(ArbolBinario* arbol,
                             void*         elemento)
{
        assert(arbol != NULL && elemento != NULL &&
               (arbol->tipo == ARBOL_BINARIO_ORDENADO ||
                arbol->tipo == ARBOL_ROJINEGRO));
        // Aquí va su código.
}

void
arbol_binario_ordenado_elimina(ArbolBinario* arbol,
                               void*         elemento)
{
        assert(arbol != NULL && elemento != NULL &&
               (arbol->tipo == ARBOL_BINARIO_ORDENADO ||
                arbol->tipo == ARBOL_ROJINEGRO));
        // Aquí va su código.
}

ArbolBinario*
arbol_rojinegro_nuevo(func_compara compara)
{
        assert(compara != NULL);
        // Aquí va su código.
}

NodoArbolBinario*
arbol_rojinegro_agrega(ArbolBinario* arbol,
                       void*         elemento)
{
        assert(arbol != NULL && elemento != NULL &&
               arbol->tipo == ARBOL_ROJINEGRO);
        // Aquí va su código.
}

void
arbol_rojinegro_elimina(ArbolBinario* arbol,
                        void*         elemento)
{
        assert(arbol != NULL && elemento != NULL &&
               arbol->tipo == ARBOL_ROJINEGRO);
        // Aquí va su código.
}

void*
nodo_arbol_binario_elemento(NodoArbolBinario* nodo)
{
        assert(nodo != NULL);
        // Aquí va su código.
}

NodoArbolBinario*
nodo_arbol_binario_padre(NodoArbolBinario* nodo)
{
        assert(nodo != NULL);
        // Aquí va su código.
}

NodoArbolBinario*
nodo_arbol_binario_izquierdo(NodoArbolBinario* nodo)
{
        assert(nodo != NULL);
        // Aquí va su código.
}

NodoArbolBinario*
nodo_arbol_binario_derecho(NodoArbolBinario* nodo)
{
        assert(nodo != NULL);
        // Aquí va su código.
}

Color
nodo_arbol_binario_color(NodoArbolBinario* nodo)
{
        assert(nodo != NULL);
        // Aquí va su código.
}

