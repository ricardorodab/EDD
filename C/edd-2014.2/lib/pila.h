#pragma once

/**
 * @file pila.h
 *
 * @brief Prototipos de funciones para la estrutura Pila.
 *
 * Las pilas implementan una estructura *FILO*: *First-In/Last-Out*;
 * el primer elemento en ser metido, es el último en ser sacado.
 *
 * Por ejemplo:
 *
@code{.c}
Pila* pila = pila_nueva();
for (int i = 0; i < 10; i++)
        pila_mete(pila, entero_nuevo(i));
while (!pila_es_vacia(pila)) {
        int* n = pila_saca(pila);
        printf("%d, ", *n);
        free(n);
}
printf("\n");
pila_libera(pila);
@endcode
 *
 * Imprimiría lo siguiente en consola: `9, 8, 7, 6, 5, 4, 3, 2, 1, 0, `.
 */

#include <stdbool.h>

/**
 * @brief Estructura para pilas.
 *
 * La estructura @ref Pila es opaca; sus miembros no deben ser
 * accesados directamente.
 */
typedef struct _Pila Pila;

/**
 * @brief Crea una nueva pila.
 *
 * @return la nueva pila, que debe ser liberada por el usuario.
 */
Pila*   pila_nueva      (void);

/**
 * @brief Mete un elemento a una pila.
 *
 * @param pila la pila a la que se le meterá un elemento.
 * @param elemento el elemento a meter en la pila.
 */
void    pila_mete       (Pila* pila,
                         void* elemento);

/**
 * @brief Saca un elemento de una pila.
 *
 * @param pila la pila a la que se le sacará un elemento.
 * @return el primer elemento que se metió en la pila que no haya
 *         sido sacado.
 */
void*   pila_saca       (Pila* pila);

/**
 * @brief Nos dice si una pila es vacía.
 *
 * @param pila la pila que queremos saber si está vacía.
 * @return `true` si la pila está vacía, `false` en otro caso.
 */
bool    pila_es_vacia   (Pila* pila);

/**
 * @brief Libera la memoria usada por una pila.
 *
 * La función libera la memoria usada por la pila, no la que
 * utilizan sus elementos.
 *
 * @param pila la pila a liberar.
 */
void    pila_libera     (Pila* pila);
