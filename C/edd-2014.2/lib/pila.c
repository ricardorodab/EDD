#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "pila.h"

typedef struct _NodoPila NodoPila;

struct _NodoPila {
        void*     elemento;
        NodoPila* anterior;
};

struct _Pila {
        NodoPila* primero;
        NodoPila* ultimo;
};

Pila*
pila_nueva()
{
        // Aquí va su código.
}

void
pila_mete(Pila* pila,
          void* elemento)
{
        assert(pila != NULL && elemento != NULL);
        // Aquí va su código.
}

void*
pila_saca(Pila* pila)
{
        assert(pila != NULL);
        // Aquí va su código.
}

bool
pila_es_vacia(Pila* pila)
{
        assert(pila != NULL);
        // Aquí va su código.
}

void
pila_libera(Pila* pila)
{
        assert(pila != NULL);
        // Aquí va su código.
}
