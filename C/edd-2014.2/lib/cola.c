#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "cola.h"

typedef struct _NodoCola NodoCola;

struct _NodoCola {
        void*     elemento;
        NodoCola* siguiente;
};

struct _Cola {
        NodoCola* primero;
        NodoCola* ultimo;
};

Cola*
cola_nueva()
{
        // Aquí va su código.
}

void
cola_mete(Cola* cola,
          void* elemento)
{
        assert(cola != NULL && elemento != NULL);
        // Aquí va su código.
}

void*
cola_saca(Cola* cola)
{
        assert(cola != NULL);
        // Aquí va su código.
}

bool
cola_es_vacia(Cola* cola)
{
        assert(cola != NULL);
        // Aquí va su código.
}

void
cola_libera(Cola* cola)
{
        assert(cola != NULL);
        // Aquí va su código.
}
