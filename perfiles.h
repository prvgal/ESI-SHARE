#ifndef __PERFILES__
#define __PERFILES__

#include "tipos.h"

#define MAX_N 21
#define MAX_L 21
#define MAX_P 14
#define MAX_U 6
#define MAX_C 9

typedef struct {
    unsigned int Id_usuario;    // 4 digitos.
    char Nomb_usuario[MAX_N];   // 20 caracteres mas el \0. Nombre completo del usuario
    char Localidad[MAX_L];      // 20 caracteres mas el \0. Ubicación de donde sale el usuario con su vehículo compartido.
    logico Perfil_usuario;      //True para administrador y False para usuario.
    char Usuario[MAX_U];        // 5 caracteres mas el \0. Nombre de usuario para acceder al sistema
    char Contrasena[MAX_C];     // 8 caracteres mas el \0.
} tPerfiles;

/* FUNCIONES PUBLICAS */

/* Precondición: */
/* Poscondición: */

void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles);

/* FUNCIONES NO EXPORTABLES*/

/* Precondición: recibe un entero sin signo. */
/* Poscondición: devuelve el numero de digitos que tiene el numero. */

static unsigned int NumeroDigitos(unsigned int num);

#endif 