#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "util.h"
#include "lista.h"

#define BLOQUE 256

typedef unsigned char byte;

void
intercambia(void** a,
            int    i,
            int    j)
{
        void* t = a[i];
        a[i] = a[j];
        a[j] = t;
}

int*
entero_nuevo(int n)
{
        int* r = NUEVO(int);
        *r = n;
        return r;
}

int
compara_enteros(const void* a,
                const void* b)
{
        int aa = *((int*)a);
        int bb = *((int*)b);
        return aa - bb;
}

int
compara_apuntadores(const void* a,
                    const void* b)
{
        return a != b;
}

char*
entero_a_cadena(int n)
{
        char bloque[BLOQUE];
        sprintf(bloque, "%d", n);
        char* s = strdup(bloque);
        return s;
}

char*
pentero_a_cadena(void* n)
{
        return entero_a_cadena(*((int*)n));
}

char*
concatena_cadenas(char* c,
                  ...) {
        int longitud = 0;
        va_list ap;

        Lista* l = lista_nueva();

        va_start(ap, c);

        char* cad = c;

        while (cad != NULL) {
                longitud += strlen(cad);
                lista_agrega_final(l, cad);
                cad = va_arg(ap, char*);
        }

        va_end(ap);

        longitud++;

        char* r = ARREGLO(char, longitud);
        r[0] = '\0';

        LISTA_PARA_CADA(char*, str, l, strcat(r, str));

        lista_libera(l);

        return r;
}

void
libera_cadenas(char* c,
               ...) {
        va_list ap;

        va_start(ap, c);

        char* cad = c;

        while (cad != NULL) {
                free(cad);
                cad = va_arg(ap, char*);
        }

        va_end(ap);
}


#define mezcla_bj(a,b,c)                  \
{                                         \
        a -= b; a -= c; a ^= (c >> 13);   \
        b -= c; b -= a; b ^= (a << 8);    \
        c -= a; c -= b; c ^= (b >> 13);   \
        a -= b; a -= c; a ^= (c >> 12);   \
        b -= c; b -= a; b ^= (a << 16);   \
        c -= a; c -= b; c ^= (b >> 5);    \
        a -= b; a -= c; a ^= (c >> 3);    \
        b -= c; b -= a; b ^= (a << 10);   \
        c -= a; c -= b; c ^= (b >> 15);   \
}

static int
huella_bj(const byte* k,
          int         n)
{
        /* Guardamos estas variables en registros, para rapidez. */
        register unsigned int a, b, c, l;

        /* Estado interno. */
        l = (unsigned int)n;
        a = b = 0x9e3779b9;  /* "Golden ratio"; es arbitrario. */
        c = 0xffffffff;      /* Valor inicial. */

        /* Dividimos la llave en 3 enteros (grupos de 4 bytes), y
           los mezclamos. Hacemos esto mientras tengamos grupos de 3
           enteros disponibles en la llave. */
        while (l >= 12) {
                a += (k[0] + (k[1] << 8) + (k[2]  << 16) + (k[3]  << 24));
                b += (k[4] + (k[5] << 8) + (k[6]  << 16) + (k[7]  << 24));
                c += (k[8] + (k[9] << 8) + (k[10] << 16) + (k[11] << 24));
                mezcla_bj(a, b, c);
                k += 12;
                l -= 12;
        }

        /* El switch lidia con los últimos 11 bytes. */
        c += n;
        switch (l) {
                /* No hay breaks; se ejecutan los casos desde el
                   primero encontrado hasta el último. */
        case 11: c += (k[10] << 24);
        case 10: c += (k[9]  << 16);
        case  9: c += (k[8]  <<  8);
                /* El primer byte de c se reserva para la
                   longitud. */
        case  8: b += (k[7]  << 24);
        case  7: b += (k[6]  << 16);
        case  6: b += (k[5]  <<  8);
        case  5: b += k[4];
        case  4: a += (k[3]  << 24);
        case  3: a += (k[2]  << 16);
        case  2: a += (k[1]  <<  8);
        case  1: a += k[0];
                /* Caso 0: Nada que hacer, se acabaron los bytes. */
        }

        /* Mezclamos una última vez. */
        mezcla_bj(a, b, c);
        return (int)c;
}

static int
huella_xor(const byte* k,
           int         n)
{
        unsigned int m = (unsigned int)n;
        if ((n & 3) != 0) /* n no es múltiplo de 4. */
                m = n + 4 - (n & 3);
        byte* t = ARREGLO(char, m);
        for (int i = 0; i < m - n; i++)
                t[i] = '\0';
        for (int i = m - n; i < m; i++)
                t[i] = k[i - m + n];
	unsigned int h = 0;
	for (int i = 0; i < m; i += 4) {
                /* Combinamos cuatro caracteres en un entero. */
                unsigned int a = (unsigned int)t[i]   << 24;
		unsigned int b = (unsigned int)t[i+1] << 16;
                unsigned int c = (unsigned int)t[i+2] << 8;
                unsigned int d = (unsigned int)t[i+3]; /* << 0 */
                int abcd = a | b | c | d;
                /* Hacemos XOR sobre lo que ya llevábamos. */
                h ^= abcd;
	}
        free(t);
        return (int)h;
}

static int
huella_glib(const byte* k,
            int         n)
{
        int h = 5381; /* Arbitrario. */
        for (int i = 0; i < n; i++) {
                /* Le regresamos el signo al byte. */
                char c = (char)k[i];
                h = h * 33 + c;
        }
        return h;
}

int
huella_cadena_bj(const char* a)
{
        int n = strlen(a) + 1;
        return huella_bj((byte*)a, n);
}

int
huella_cadena_xor(const char* a)
{
        int n = strlen(a) + 1;
        return huella_xor((byte*)a, n);
}

int
huella_cadena_glib(const char* a)
{
        int n = strlen(a) + 1;
        return huella_glib((byte*)a, n);
}
