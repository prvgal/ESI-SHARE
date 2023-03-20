#ifndef _PERFILES_
#define _PERFILES_

#include "tipos.h"

#define ID 4
#define MAX_N 21
#define MAX_L 21
#define MAX_U 6
#define MAX_C 9

typedef struct {
    char Id_usuario[ID];        // 4 digitos.
    char Nomb_usuario[MAX_N];   // 20 caracteres mas el \0. Nombre completo del usuario
    char Localidad[MAX_L];      // 20 caracteres mas el \0. Ubicación de donde sale el usuario con su vehículo compartido.
    logico Perfil_usuario;      // True para administrador y False para usuario.
    char Usuario[MAX_U];        // 5 caracteres mas el \0. Nombre de usuario para acceder al sistema
    char Contrasena[MAX_C];     // 8 caracteres mas el \0.
} tPerfiles;

/* FUNCIONES PUBLICAS */

/* Precondición: recibe un vector de estructuras tipo tPefiles el cual debe tener ¿¿un tamaño minimo?? */
/* Poscondición: almacena en infoper los datos de Usuarios.txt*/
void CargarPerfiles(tPerfiles *infoper);

/* Precondición: recibe un vector de estructuras de tipo tPerfiles. */
/* Poscondición: redimensiona el vector de estructuras tPerfiles para un nuevo elemento. */
void ReservarPerfil(tPerfiles *infoper);

/* Precondición: recibe un vector de estructuras de tipo tPerfiles el cual debe tener un tamaño mínimo. */
/* Poscondición: introduce en el vector de estructuras de tipo tPerfiles los valores necesarios. */
void RegistrarPerfil(tPerfiles *infoper);

/* Precondición: recibe un vector de estructuras tipo tPerfiles y una cadena de caracteres que debe contener la ID de usuario*/
/* Poscondición: imprime por pantalla todos los datos que hay en el registro */
void ListarRegistro(tPerfiles *infoper, char id[ID]);

/* Precondición: recibe un vector de estructuras de tipo tPerfiles el cual debe tener un tamaño mínimo y una cadena de caracteres (ID). */
/* Poscondición: modifica algún campo de la estructura indicado por el usuario. */
void ModificarCamposUsuario(tPerfiles *infoper, char id[ID]);

// void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles);

/* Precondición: recibe una cadena de caracteres(ID), el numeo de datos que haya almaecados y el numero de dígitos para el que se quiera generar la ID. */
/* Poscondición: inicializa la cadena de caracteres con una ID, por ejemplo, si es el usuario
                 18, en el vector id estará almacenado lo siguiente --> |0|0|1|8|. */
void GenerarID(char *id, int ndatos, int numDigitos);


/* FUNCIONES NO EXPORTABLES*/

/* Precondición: Recibe un vector de estructuras de tipo tPerfiles y un entero que indicará la posición del usuario en infoper. */
/* Poscondición: Cambia los datos almacenados de Nomb_usuario en la estructura infoper de la posición posUsuario. */
static void CambiarNombre(tPerfiles *infoper, int posUsuario);

/* Precondición: Recibe un vector de estructuras de tipo tPerfiles y un entero que indicará la posición del usuario en infoper. */
/* Poscondición: Cambia los datos almacenados de Localidad en la estructura infoper de la posición posUsuario. */
static void CambiarLocalidad(tPerfiles *infoper, int posUsuario);

/* Precondición: Recibe un vector de estructuras de tipo tPerfiles y un entero que indicará la posición del usuario en infoper. */
/* Poscondición: Cambia los datos almacenados de Usuario en la estructura infoper de la posición posUsuario. */
static void CambiarUsuarioAcceso(tPerfiles *infoper, int posUsuario);

/* Precondición: Recibe un vector de estructuras de tipo tPerfiles y un entero que indicará la posición del usuario en infoper. */
/* Poscondición: Cambia los datos almacenados de Contrasena en la estructura infoper de la posición posUsuario. */
static void CambiarContrasena(tPerfiles *infoper, int posUsuario);

/* Precondición: recibe un vector de estructuras ya inicializado y una cadena de caracteres (ID). */
/* Poscondición: devuelve la posición en la que se encuentra el usuario con ID (char id[ID]) dentro del vector de estructuras infoper */
static int PosicionUsuario(tPerfiles *infoper, char id[ID]);


#endif
