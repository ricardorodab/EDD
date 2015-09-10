#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "util.h"
#include "grafica.h"
#include "lista.h"
#include "monticulominimo.h"

struct _VerticeGrafica {
        void*  elemento;
        Lista* aristas;
        Color  color;
        // No hay accesores para estos campos.
        double distancia;
        int    indice;
};

struct _AristaGrafica {
        VerticeGrafica* vecino;
        double          peso;
};

struct _Grafica {
        Lista*       vertices;
        func_compara compara;
};

Grafica*
grafica_nueva(func_compara compara)
{
        assert(compara != NULL);
        // Aquí va su código.
}

void
grafica_agrega(Grafica* grafica,
               void*    elemento)
{
        assert(grafica != NULL && elemento != NULL);
        // Aquí va su código.
}

void
grafica_conecta(Grafica* grafica,
                void*    a,
                void*    b,
                double peso)
{
        assert(grafica != NULL && a != NULL && b != NULL && peso > 0.0);
        // Aquí va su código.
}

void
grafica_elimina(Grafica* grafica,
                void*    elemento)
{
        assert(grafica != NULL && elemento != NULL);
        // Aquí va su código.
}

void
grafica_desconecta(Grafica* grafica,
                   void*    a,
                   void*    b)
{
        assert(grafica != NULL && a != NULL && b != NULL);
        // Aquí va su código.
}

VerticeGrafica*
grafica_vertice(Grafica* grafica,
                void*    elemento)
{
        assert(grafica != NULL && elemento != NULL);
        // Aquí va su código.
}

Lista*
grafica_vertices(Grafica* grafica)
{
        assert(grafica != NULL);
        // Aquí va su código.
}

bool
grafica_estan_conectados(Grafica* grafica,
                         void*    a,
                         void*    b)
{
        assert(grafica != NULL && a != NULL && b != NULL);
        // Aquí va su código.
}

double
grafica_peso(Grafica* grafica,
             void*    a,
             void*    b)
{
        assert(grafica != NULL && a != NULL && b != NULL);
        // Aquí va su código.
}

bool
grafica_contiene(Grafica* grafica,
                 void*    elemento)
{
        assert(grafica != NULL && elemento != NULL);
        // Aquí va su código.
}

void
grafica_itera_bfs(Grafica*     grafica,
                  void*        elemento,
                  func_procesa procesa,
                  void*        datos)
{
        assert(grafica != NULL && elemento != NULL && procesa != NULL);
        // Aquí va su código.
}

void
grafica_itera_dfs(Grafica*     grafica,
                  void*        elemento,
                  func_procesa procesa,
                  void*        datos)
{
        assert(grafica != NULL && elemento != NULL && procesa != NULL);
        // Aquí va su código.
}

Lista*
grafica_trayectoria_minima(Grafica* grafica,
                           void*    a,
                           void*    b)
{
        assert(grafica != NULL && a != NULL && b != NULL);
        // Aquí va su código.
}

Lista*
grafica_dijkstra(Grafica* grafica,
                 void*    a,
                 void*    b)
{
        assert(grafica != NULL && a != NULL && b != NULL);
        // Aquí va su código.
}

void
grafica_libera(Grafica* grafica)
{
        assert(grafica != NULL);
        // Aquí va su código.
}

void
grafica_libera_todo(Grafica* grafica)
{
        assert(grafica != NULL);
        // Aquí va su código.
}

void*
vertice_grafica_elemento(VerticeGrafica* vertice)
{
        assert(vertice != NULL);
        // Aquí va su código.
}

NodoLista*
vertice_grafica_iterador_aristas(VerticeGrafica* vertice)
{
        assert(vertice != NULL);
        // Aquí va su código.
}

Color
vertice_grafica_color(VerticeGrafica* vertice)
{
        assert(vertice != NULL);
        // Aquí va su código.
}

void
vertice_grafica_define_color(VerticeGrafica* vertice,
                             Color           color)
{
        assert(vertice != NULL);
        // Aquí va su código.
}

VerticeGrafica*
arista_grafica_vecino(AristaGrafica* arista)
{
        assert(arista != NULL);
        // Aquí va su código.
}

double
arista_grafica_peso(AristaGrafica* arista)
{
        assert(arista != NULL);
        // Aquí va su código.
}
