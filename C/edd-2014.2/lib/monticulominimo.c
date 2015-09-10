#include <assert.h>
#include <stdlib.h>
#include "monticulominimo.h"

#define N 100

struct _MonticuloMinimo {
        void**       arbol;
        int          n;
        int          ultimo;
        func_compara compara;
        func_indice  indice;
};

MonticuloMinimo*
monticulo_minimo_nuevo(func_compara compara,
                       func_indice  indice)
{
        assert(compara != NULL && indice != NULL);
        // Aquí va su código.
}

MonticuloMinimo*
monticulo_minimo_nuevo_de_lista(Lista*       lista,
                                func_compara compara,
                                func_indice  indice)
{
        assert(lista != NULL && compara != NULL && indice != NULL);
        // Aquí va su código.
}

void
monticulo_minimo_agrega(MonticuloMinimo* monticulo,
                        void*            elemento)
{
        assert(monticulo != NULL && elemento != NULL);
        // Aquí va su código.
}

void*
monticulo_minimo_elimina(MonticuloMinimo* monticulo)
{
        assert(monticulo != NULL && monticulo->ultimo != -1);
        // Aquí va su código.
}

bool
monticulo_minimo_es_vacio(MonticuloMinimo* monticulo)
{
        assert(monticulo != NULL);
        // Aquí va su código.
}

void
monticulo_minimo_reordena(MonticuloMinimo* monticulo,
                          void*            elemento)
{
        assert(monticulo != NULL && elemento != NULL);
        // Aquí va su código.
}

int
monticulo_minimo_ultimo(MonticuloMinimo* monticulo)
{
        assert(monticulo != NULL);
        // Aquí va su código.
}

void*
monticulo_minimo_dame(MonticuloMinimo* monticulo,
                      int              indice)
{
        assert(monticulo != NULL && indice >= 0 &&
               indice <= monticulo->ultimo);
        // Aquí va su código.
}

void
monticulo_minimo_libera(MonticuloMinimo* monticulo)
{
        assert(monticulo != NULL);
        // Aquí va su código.
}

void
monticulo_minimo_libera_todo(MonticuloMinimo* monticulo)
{
        assert(monticulo != NULL);
        // Aquí va su código.
}
