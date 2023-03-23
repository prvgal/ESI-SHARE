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

// Precondición: Recibe dos vectores, así como la longitud de cada uno de ellos.
// Postcondición: Devuelve el valor lógico True si el contenido de los vectores es el mismo, False en caso contrario.
logico vectores_iguales(int, int, int *,int *);

#endif
