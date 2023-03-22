#ifndef __FICHEROS__
#define __FICHEROS__

#define MAX_LIN_FICH 67


/* Precondición: . */
/* Poscondición: devuelve un entero que indica el la longitud n de una estructura. */
int LongitudVectorEstructuras();

/* Precondición: recibe como parametros la dirección de un fichero, y una cadena de caracteres. */
/* Poscondición: carga la Id_Usuario en la cadena. */
void CargarID(FILE *ptrf, char *cad, int numDigitos);

/* Precondición: recibe como parametros la dirección de un fichero, y una cadena de caracteres. */
/* Poscondición: carga el nombre de usuario en la cadena. */
void CargarNombreUsuario(FILE *ptrf, char *cad);

/* Precondición: recibe como parametros la dirección de un fichero, y una cadena de caracteres. */
/* Poscondición: carga la localidad del usuario en la cadena. */
void CargarLocalidad(FILE *ptrf, char *cad);

/* Precondición: recibe como parametros la dirección de un fichero, y una cadena de caracteres. */
/* Poscondición: carga el perfil de usuario en la cadena. */
void CargarPerfilUsuario(FILE *ptrf, char *cad);

/* Precondición: recibe como parametros la dirección de un fichero, y una cadena de caracteres. */
/* Poscondición: carga el usuario en la cadena. */
void CargarUsuario(FILE *ptrf, char *cad);

/* Precondición: recibe como parametros la dirección de un fichero, y una cadena de caracteres. */
/* Poscondición: carga la contraseña del usuario en la cadena. */
void CargarContrasena(FILE *ptrf, char *cad);

/*
            Funciones a crear:
1. CambiarNombreEnFichero
2. CambiarLocalidadEnFichero
3. CambiarUsuarioAccesoEnFichero
4. CambiarContrasenaEnFichero

*/

#endif
