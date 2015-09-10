#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lista.h"
#include "diccionario.h"

#define N 64

typedef struct _Entrada Entrada;

struct _Diccionario {
        int          mascara;
        int          total;
        func_huella  huella;
        func_compara compara;
        Lista**      arreglo;
};

struct _Entrada {
        void* llave;
        void* valor;
};

Diccionario*
diccionario_nuevo(int          n,
                  func_huella  huella,
                  func_compara compara)
{
        assert(huella != NULL && compara != NULL);
        // Aquí va su código.
}

void
diccionario_agrega(Diccionario* diccionario,
                   void*        llave,
                   void*        valor)
{
        assert(diccionario != NULL && llave != NULL && valor != NULL);
        // Aquí va su código.
}

void*
diccionario_dame(Diccionario* diccionario,
                 void*        llave)
{
        assert(diccionario != NULL && llave != NULL);
        // Aquí va su código.
}

void
diccionario_elimina(Diccionario* diccionario,
                    void*        llave)
{
        assert(diccionario != NULL && llave != NULL);
        // Aquí va su código.
}

bool
diccionario_tiene_llave(Diccionario* diccionario,
                        void*        llave)
{
        assert(diccionario != NULL && llave != NULL);
        // Aquí va su código.
}

Lista*
diccionario_llaves(Diccionario* diccionario)
{
        assert(diccionario != NULL);
        // Aquí va su código.
}

Lista*
diccionario_elementos(Diccionario* diccionario)
{
        assert(diccionario != NULL);
        // Aquí va su código.
}

void
diccionario_colisiones(Diccionario* diccionario,
                       int*         maximo,
                       int*         total)
{
        assert(diccionario != NULL);
        // Aquí va su código.
}

double
diccionario_carga(Diccionario* diccionario)
{
        assert(diccionario != NULL);
        // Aquí va su código.
}

int
diccionario_total(Diccionario* diccionario)
{
        assert(diccionario != NULL);
        // Aquí va su código.
}

void
diccionario_libera(Diccionario* diccionario,
                   bool         llaves,
                   bool         valores)
{
        assert(diccionario != NULL);
        // Aquí va su código.
}
