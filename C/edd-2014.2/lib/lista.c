#include <assert.h>
#include <stdlib.h>
#include "lista.h"

struct _Lista {
        NodoLista* cabeza;
        NodoLista* rabo;
        int        longitud;
};

struct _NodoLista {
        void*      elemento;
        NodoLista* anterior;
        NodoLista* siguiente;
};

static NodoLista*
nodo_lista_nuevo(void* elemento)
{
        NodoLista* nodo = NUEVO(NodoLista);
        assert(nodo != NULL);
        nodo->elemento = elemento;
        nodo->anterior = nodo->siguiente = NULL;
        return nodo;
}

Lista*
lista_nueva(void)
{
        Lista* lista = NUEVO(Lista);
        assert(lista != NULL);
        lista->rabo = lista->cabeza = NULL;
        lista->longitud = 0;
        return lista;
}

NodoLista*
lista_cabeza(Lista* lista)
{
        assert(lista != NULL);
        return lista->cabeza;
}

NodoLista*
lista_rabo(Lista* lista)
{
        assert(lista != NULL);
        return lista->rabo;
}

int
lista_longitud(Lista* lista)
{
        assert(lista != NULL);
        return lista->longitud;
}

void
lista_agrega_inicio(Lista* lista,
                    void*  elemento)
{
        assert(lista != NULL && elemento != NULL);
        NodoLista* nodo = nodo_lista_nuevo(elemento);
        lista->longitud++;
        if (lista->cabeza == NULL) {
                lista->cabeza = lista->rabo = nodo;
        } else {
                lista->cabeza->anterior = nodo;
                nodo->siguiente = lista->cabeza;
                lista->cabeza = nodo;
        }
}

void
lista_agrega_final(Lista* lista,
                   void*  elemento)
{
        assert(lista != NULL && elemento != NULL);
        NodoLista* nodo = nodo_lista_nuevo(elemento);
        lista->longitud++;
        if (lista->rabo == NULL) {
                lista->rabo = lista->cabeza = nodo;
        } else {
                lista->rabo->siguiente = nodo;
                nodo->anterior = lista->rabo;
                lista->rabo = nodo;
        }
}

void
lista_inserta_antes(Lista*     lista,
                    NodoLista* nodo,
                    void*      elemento)
{
        assert(lista != NULL && nodo != NULL && elemento != NULL);
        assert((nodo->anterior != NULL && nodo != lista->cabeza) ||
               (nodo->anterior == NULL && nodo == lista->cabeza));
        NodoLista* nuevo = nodo_lista_nuevo(elemento);
        if (nodo->anterior == NULL) {
                nodo->anterior = nuevo;
                nuevo->siguiente = nodo;
                lista->cabeza = nuevo;
        } else {
                nodo->anterior->siguiente = nuevo;
                nuevo->anterior = nodo->anterior;
                nodo->anterior = nuevo;
                nuevo->siguiente = nodo;
        }
        lista->longitud++;
}

void
lista_inserta_despues(Lista*     lista,
                      NodoLista* nodo,
                      void*      elemento)
{
        assert(lista != NULL && nodo != NULL && elemento != NULL);
        assert((nodo->siguiente != NULL && nodo != lista->rabo) ||
               (nodo->siguiente == NULL && nodo == lista->rabo));
        NodoLista* nuevo = nodo_lista_nuevo(elemento);
        if (nodo->siguiente == NULL) {
                nodo->siguiente = nuevo;
                nuevo->anterior = nodo;
                lista->rabo = nuevo;
        } else {
                nodo->siguiente->anterior = nuevo;
                nuevo->siguiente = nodo->siguiente;
                nodo->siguiente = nuevo;
                nuevo->anterior = nodo;
        }
        lista->longitud++;
}

static void
l_elimina_nodo(Lista*     lista,
               NodoLista* nodo)
{
        lista->longitud--;
        if (lista->cabeza == nodo && lista->rabo == nodo) {
                lista->cabeza = lista->rabo = NULL;
        } else if (nodo == lista->cabeza) {
                lista->cabeza = lista->cabeza->siguiente;
                lista->cabeza->anterior = NULL;
        } else if (nodo == lista->rabo) {
                lista->rabo = lista->rabo->anterior;
                lista->rabo->siguiente = NULL;
        } else {
                nodo->anterior->siguiente = nodo->siguiente;
                nodo->siguiente->anterior = nodo->anterior;
        }
        free(nodo);
}

void
lista_elimina(Lista*        lista,
              void*         elemento,
              func_compara  compara)
{
        assert(lista != NULL && elemento != NULL && compara != NULL);
        NodoLista* nodo = lista_busca(lista, elemento, compara);
        if (nodo == NULL)
                return;
        l_elimina_nodo(lista, nodo);
}

void*
lista_elimina_primero(Lista* lista)
{
        assert(lista != NULL && lista->cabeza != NULL);
        void* r = lista->cabeza->elemento;
        l_elimina_nodo(lista, lista->cabeza);
        return r;
}

void*
lista_elimina_ultimo(Lista* lista)
{
        assert(lista != NULL && lista->rabo != NULL);
        void* r = lista->rabo->elemento;
        l_elimina_nodo(lista, lista->rabo);
        return r;
}

void
lista_elimina_nodo(Lista*     lista,
                   NodoLista* nodo)
{
        assert(lista != NULL && nodo != NULL);
        l_elimina_nodo(lista, nodo);
}

NodoLista*
lista_busca(Lista*       lista,
            void*        elemento,
            func_compara compara)
{
        assert(lista != NULL);
        return nodo_lista_busca(lista->cabeza, elemento, compara);
}

NodoLista*
lista_dame(Lista* lista,
           int    indice)
{
        assert(lista != NULL && indice >= 0 && indice < lista->longitud);
        NodoLista* tmp = lista->cabeza;
        int c = 0;
        while (tmp != NULL) {
                if (c++ == indice)
                        return tmp;
                tmp = tmp->siguiente;
        }
        return NULL;
}

Lista*
lista_reversa(Lista* lista)
{
        assert(lista != NULL);
        Lista* reversa = lista_nueva();
        NodoLista* tmp = lista->cabeza;
        while (tmp != NULL) {
                lista_agrega_inicio(reversa, tmp->elemento);
                tmp = tmp->siguiente;
        }
        return reversa;
}

Lista*
lista_copia(Lista* lista)
{
        assert(lista != NULL);
        Lista* copia = lista_nueva();
        NodoLista* tmp = lista->cabeza;
        while (tmp != NULL) {
                lista_agrega_final(copia, tmp->elemento);
                tmp = tmp->siguiente;
        }
        return copia;
}

bool
lista_esta_ordenada(Lista*        lista,
                    func_compara  compara)
{
        assert(lista != NULL && compara != NULL);
        if (lista->cabeza == NULL)
                return true;
        NodoLista* a = lista->cabeza;
        NodoLista* b = a->siguiente;
        while (b != NULL) {
                if (compara(a->elemento, b->elemento) > 0)
                        return false;
                a = b;
                b = b->siguiente;
        }
        return true;
}

NodoLista*
lista_ordenada_busca(Lista*        lista,
                     void*         elemento,
                     func_compara  compara)
{
        assert(lista != NULL && elemento != NULL && compara != NULL);
        NodoLista* tmp = lista->cabeza;
        while (tmp != NULL && compara(tmp->elemento, elemento) < 0)
                tmp = tmp->siguiente;
        if (tmp != NULL && !compara(tmp->elemento, elemento))
                return tmp;
        return NULL;
}

static Lista*
lista_mezcla(Lista*       li,
             Lista*       ld,
             func_compara compara)
{
        Lista* l = lista_nueva();
        NodoLista* ni = li->cabeza;
        NodoLista* nd = ld->cabeza;
        while (ni != NULL && nd != NULL) {
                if (compara(ni->elemento, nd->elemento) < 0) {
                        lista_agrega_final(l, ni->elemento);
                        ni = ni->siguiente;
                } else {
                        lista_agrega_final(l, nd->elemento);
                        nd = nd->siguiente;
                }
        }
        while (ni != NULL) {
                lista_agrega_final(l, ni->elemento);
                ni = ni->siguiente;
        }
        while (nd != NULL) {
                lista_agrega_final(l, nd->elemento);
                nd = nd->siguiente;
        }
        return l;
}

static Lista*
lista_mergesort_aux(Lista*        lista,
                    func_compara  compara)
{
        if (lista->longitud < 2)
                return lista_copia(lista);
        Lista* li = lista_nueva();
        Lista* ld = lista_nueva();
        NodoLista* tmp = lista->cabeza;
        for (int i = 0; i < lista->longitud/2; i++) {
                lista_agrega_final(li, tmp->elemento);
                tmp = tmp->siguiente;
        }
        for (int i = lista->longitud/2; i < lista->longitud; i++) {
                lista_agrega_final(ld, tmp->elemento);
                tmp = tmp->siguiente;
        }
        Lista* oli = lista_mergesort_aux(li, compara);
        Lista* old = lista_mergesort_aux(ld, compara);
        Lista* r = lista_mezcla(oli, old, compara);
        lista_libera(li);
        lista_libera(ld);
        lista_libera(oli);
        lista_libera(old);
        return r;
}

Lista*
lista_mergesort(Lista*       lista,
                func_compara compara)
{
        assert(lista != NULL && compara != NULL);
        return lista_mergesort_aux(lista, compara);
}

static void
lista_libera_aux(Lista* lista,
                 bool   todo)
{
        assert(lista != NULL);
        NodoLista* tmp = lista->cabeza;
        while (tmp != NULL) {
                NodoLista* nodo = tmp;
                tmp = tmp->siguiente;
                if (todo)
                        free(nodo->elemento);
                free(nodo);
        }
}

void
lista_libera(Lista* lista)
{
        assert(lista != NULL);
        lista_libera_aux(lista, false);
}

void
lista_libera_todo(Lista* lista)
{
        assert(lista != NULL);
        lista_libera_aux(lista, true);
}

void*
nodo_lista_elemento(NodoLista* nodo)
{
        assert(nodo != NULL);
        return nodo->elemento;
}

NodoLista*
nodo_lista_anterior(NodoLista* nodo)
{
        assert(nodo != NULL);
        return nodo->anterior;
}

NodoLista*
nodo_lista_siguiente(NodoLista* nodo)
{
        assert(nodo != NULL);
        return nodo->siguiente;
}

NodoLista*
nodo_lista_busca(NodoLista*   nodo,
                 void*        elemento,
                 func_compara compara)
{
        assert(elemento != NULL && compara != NULL);
        NodoLista* tmp = nodo;
        while (tmp != NULL) {
                if (!compara(tmp->elemento, elemento))
                        return tmp;
                tmp = tmp->siguiente;
        }
        return NULL;
}
