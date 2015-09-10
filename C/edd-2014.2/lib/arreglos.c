#include <stdlib.h>
#include <stdbool.h>

#include "arreglos.h"

bool
arreglos_esta_ordenado (void**       arreglo,
                        int          n,
                        func_compara compara)
{
        assert(arreglo != NULL && compara != NULL);
        // Aquí va su código.
}

int
arreglos_busqueda_binaria(void**       arreglo,
                          int          n,
                          void*        elemento,
                          func_compara compara)
{
        assert(arreglo != NULL && elemento != NULL && compara != NULL);
        // Aquí va su código.
}

void
arreglos_selectionsort(void**       arreglo,
                       int          n,
                       func_compara compara)
{
        assert(arreglo != NULL && compara != NULL);
        // Aquí va su código.
}

void
arreglos_quicksort(void**       arreglo,
                   int          n,
                   func_compara compara)
{
        assert(arreglo != NULL && compara != NULL);
        // Aquí va su código.
}
