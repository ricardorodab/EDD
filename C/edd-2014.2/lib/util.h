#pragma once

/**
 * @file util.h
 *
 * @brief Definciones de macros, tipos y prototipos de funciones
 * utilitarias.
 */

/**
 * @brief Asigna memoria suficiente para guardar una copia de un
 * tipo específico, y regresa la dirección a la misma.
 * @param tipo el tipo del que queremos memoria para guardar una
 * copia.
 */
#define NUEVO(tipo)          (malloc(sizeof(tipo)))

/**
 * @brief Asigna memoria suficiente para guardar *n* copias de un
 * tipo específico, y regresa la dirección a la misma.
 * @param tipo el tipo del que queremos memoria para guardar *n*
 * copias.
 * @param n el número de copias que queremos.
 */
#define ARREGLO(tipo, n)     (malloc(sizeof(tipo) * (n)))

/**
 * @brief Audiciona el apuntador a para que sea visto como un
 * arreglo de apuntadores anónimos.
 * @param a el arreglo que queremos ver como arreglo de apuntadores
 * anónimos.
 */
#define ARREGLO_ANONIMO(a)   ((void**)(a))

/**
 * @brief Regresa el máximo entre a y b.
 *
 * Si a o b no son valores numéricos, el resultado de la macro es no
 * definido.
 *
 * @param a el primer valor numérico.
 * @param b el segundo valor numérico.
 */
#define MAX(a, b)            ((a) > (b) ? (a) : (b))

/**
 * @brief Regresa el mínimo entre a y b.
 *
 * Si a o b no son valores numéricos, el resultado de la macro es no
 * definido.
 *
 * @param a el primer valor numérico.
 * @param b el segundo valor numérico.
 */
#define MIN(a, b)            ((a) < (b) ? (a) : (b))

/**
 * @brief Audiciona la función f para que sea vista como función de
 * comparación.
 * @param f la función que queremos ver como función de comparación.
 */
#define FUNC_COMPARA(f)      ((func_compara)f)

/**
 * @brief Audiciona la función f para que sea vista como función de
 * conversión a cadena.
 * @param f la función que queremos ver como función de conversión a
 * cadena.
 */
#define FUNC_A_CADENA(f)     ((func_a_cadena)f)

/**
 * @brief Audiciona la función f para que sea vista como función de
 * procesamiento.
 * @param f la función que queremos ver como función de
 * procesamiento.
 */
#define FUNC_PROCESA(f)      ((func_procesa)f)

/**
 * @brief Audiciona la función f para que sea vista como función de
 * huella digital.
 * @param f la función que queremos ver como función de huella
 * digital.
 */
#define FUNC_HUELLA(f)       ((func_huella)f)

/**
 * @brief Audiciona la función f para que sea vista como función de
 * índice.
 * @param f la función que queremos ver como función de índice.
 */
#define FUNC_INDICE(f)       ((func_huella)f)

/**
 * @brief Enumeración para colores.
 */
typedef enum {
        /** Ningún color. */
        COLOR_NINGUNO,
        /** Color negro. */
        COLOR_NEGRO,
        /** Color rojo. */
        COLOR_ROJO
} Color;

/**
 * @brief Definición de tipo para funciones de comparación.
 *
 * Las funciones de comparación deben regresar un valor menor,
 * igual, o mayor que cero si el objeto al que apunta a es menor,
 * igual o mayor que el objeto al que apunta b.
 */
typedef int    (*func_compara)       (const void* a,
                                      const void* b);

/**
 * @brief Definición de tipo para funciones de conversión a cadena.
 *
 * Las funciones de conversión a cadena deben regresar una cadena
 * que representa al objeto recibido. La cadena regresada deber ser
 * liberada por el usuario.
 */
typedef char*  (*func_a_cadena)      (const void* a);

/**
 * @brief Definición de tipo para funciones de procesamiento.
 *
 * Las funciones de procesamiento reciben el apuntador a un objeto
 * para procesarlo, y opcionalmente el apuntador a otro objeto con
 * datos secundarios.
 */
typedef void   (*func_procesa)       (const void* a,
                                      const void* datos);

/**
 * @brief Definición de tipo para funciones de huellas digitales.
 *
 * Las funciones de huellas digitales deben regresar una huella
 * digital de tipo entero del objeto al que a apunta.
 */
typedef int    (*func_huella)        (const void* a);

/**
 * @brief Definición de tipo para funciones de índice.
 *
 * Las funciones de índice deben regresar un apuntador al espacio en
 * memoria donde el índice del objeto existe.
 */
typedef int*   (*func_indice)        (const void* a);

/**
 * @brief intercambia dos elementos en un arreglo.
 *
 * Si `i` o `j` están fuera del rango del arreglo, el comportamiento
 * de esta función no está definido.
 *
 * @param a el arreglo de apuntadores donde están los elementos a
 * intercambiar.
 * @param i el índice del primer elemento.
 * @param j el índice del segundo elemento.
 */
void             intercambia         (void**      a,
                                      int         i,
                                      int         j);

/**
 * @brief Regresa un nuevo entero en memoria.
 * @param n el entero que guardaremos en la memoria asignada.
 * @return la dirección en memoria donde se guarda n. La memoria
 * debe ser liberada.
 */
int*             entero_nuevo        (int         n);

/**
 * @brief Compara dos apuntadores a enteros.

 * Compara dos apuntadores, suponiendo que apuntan a enteros en la
 * memoria. Si los apuntadores no apuntan a enteros, el resultado de
 * la función no está determinado.
 *
 * @param a el primer apuntador a un entero.
 * @param b el segundo apuntador a un entero.
 * @return un valor menor, igual, o mayor que cero, si el entero al
 * que apunta a es menor, igual o mayor que el entero al que apunta
 * b respectivamente.
 */
int              compara_enteros     (const void* a,
                                      const void* b);

/**
 * @brief Compara dos apuntadores.

 * Compara dos apuntadores para ver si apuntan a la misma dirección
 * en memoria.
 *
 * @param a el primer apuntador.
 * @param b el segundo apuntador.
 * @return 0, si ambos apuntadores apuntan a la misma dirección en
 * memoria, y un valor distinto de cero en otro caso.
 */
int              compara_apuntadores (const void* a,
                                      const void* b);

/**
 * @brief Convierte un entero a una cadena, que debe ser liberada.
 * @param n el entero del que queremos su representación en cadena.
 * @return la representación del entero en cadena, que debe ser
 * liberada.
 */
char*            entero_a_cadena     (int         n);

/**
 * @brief Convierte un aputnador a entero a una cadena, que debe ser
 * liberada.
 * @param n apuntador al entero del que queremos su representación
 * en cadena.
 * @return la representación del entero en cadena, que debe ser
 * liberada.
 */
char*            pentero_a_cadena   (void*        n);

/**
 * @brief Concatena una serie (terminada por `NULL`) de
 * cadenas.
 *
 * Esto en general **no funciona** con UTF-8, ya que una cadena
 * codificada con UTF-8 puede contener '\0' en medio, lo que esta
 * función interpretaría como el fin de cadena. Para ASCII y casos
 * específicos de UTF-8 donde sabemos que '\0' no aparece en medio,
 * la función trabaja de manera correcta.
 *
 * @param c la primera cadena.
 * @param ... el resto de las cadenas. La última de ellas **debe**
 * ser `NULL`.
 * @return la concatenación de todas las cadenas en la serie, que
 * debe ser liberada.
 */
char*            concatena_cadenas   (char*       c,
                                      ...);

/**
 * @brief Libera una serie (terminada por `NULL`) de cadenas.
 *
 * Por las mismas razones que concatena_cadenas(), esta función en
 * general **no funciona** para cadenas codificadas con UTF-8.
 *
 * @param c la primera cadena.
 * @param ... el resto de las cadenas. La última de ellas **debe**
 * ser `NULL`.
 */
void             libera_cadenas      (char*       c,
                                      ...);

/**
 * @brief Huella digital de Bob Jenkins para cadenas.
 * @param a la cadena de la cuál queremos la huella digital.
 * @return la huella digital de Bob Jenkis para la cadena.
 */
int              huella_cadena_bj    (const char* a);

/**
 * @brief Huella digital XOR para cadenas.
 * @param a la cadena de la cuál queremos la huella digital.
 * @return la huella digital XOR para la cadena.
 */
int              huella_cadena_xor   (const char* a);

/**
 * @brief Huella digital de glib para cadenas.
 * @param a la cadena de la cuál queremos la huella digital.
 * @return la huella digital de glib para la cadena.
 */
int              huella_cadena_glib  (const char* a);
