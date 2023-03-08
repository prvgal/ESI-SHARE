#ifndef __TIPOS__
#define __TIPOS__

/* Enumeramos False como cero y True como uno para poder usar booleanos */

typedef enum {
    False = 0,
    True = 1
} logico;

/* Precondición: Recibe una cadena de caracteres. */
/* Poscondición: Cambia el \n por el \0 para que no haya ningún salto de linea al ser la cadena introducida por el buffer. */

void EliminarSaltoLinea(char *cad);

#endif
