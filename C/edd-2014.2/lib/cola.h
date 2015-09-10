#pragma once

/**
 * @file cola.h
 *
 * @brief Prototipos de funciones para la estrutura Cola.
 *
 * Las colas implementan una estructura *FIFO*: *Firt-In/First-Out*;
 * el primer elemento en ser metido, es el último en ser sacado.
 *
 * Por ejemplo:
 *
@code{.c}
Cola* cola = cola_nueva();
for (int i = 0; i < 10; i++)
        cola_mete(cola, entero_nuevo(i));
while (!cola_es_vacia(cola)) {
        int* n = cola_saca(cola);
        printf("%d, ", *n);
        free(n);
}
printf("\n");
cola_libera(cola);
@endcode
 *
 * Imprimiría lo siguiente en consola: `0, 1, 2, 3, 4, 5, 6, 7, 8, 9, `.
 */

#include <stdbool.h>

/**
 * @brief Estructura para colas.
 *
 * La estructura @ref Cola es opaca; sus miembros no deben ser
 * accesados directamente.
 */
typedef struct _Cola Cola;

/**
 * @brief Crea una nueva cola.
 *
 * @return la nueva cola, que debe ser liberada por el usuario.
 */
Cola*   cola_nueva      (void);

/**
 * @brief Mete un elemento a una cola.
 *
 * @param cola la cola a la que se le meterá un elemento.
 * @param elemento el elemento a meter en la cola.
 */
void    cola_mete       (Cola* cola,
                         void* elemento);

/**
 * @brief Saca un elemento de una cola.
 *
 * @param cola la cola a la que se le sacará un elemento.
 * @return el primer elemento que se metió en la cola que no haya
 *         sido sacado.
 */
void*   cola_saca       (Cola* cola);

/**
 * @brief Nos dice si una cola es vacía.
 *
 * @param cola la cola que queremos saber si está vacía.
 * @return `true` si la cola está vacía, `false` en otro caso.
 */
bool    cola_es_vacia   (Cola* cola);

/**
 * @brief Libera la memoria usada por una cola.
 *
 * La función libera la memoria usada por la cola, no la que
 * utilizan sus elementos.
 *
 * @param cola la cola a liberar.
 */
void    cola_libera     (Cola* cola);
