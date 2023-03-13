#ifndef __PERFILES__
#define __PERFILES__

#include "tipos.h"

#define ID 4
#define MAX_N 21
#define MAX_L 21
#define MAX_U 6
#define MAX_C 9
#define MAX_LIN_FICH 67

typedef struct {
    unsigned int Id_usuario[ID];    // 4 digitos.
    char Nomb_usuario[MAX_N];   // 20 caracteres mas el \0. Nombre completo del usuario
    char Localidad[MAX_L];      // 20 caracteres mas el \0. Ubicación de donde sale el usuario con su vehículo compartido.
    logico Perfil_usuario;      //True para administrador y False para usuario.
    char Usuario[MAX_U];        // 5 caracteres mas el \0. Nombre de usuario para acceder al sistema
    char Contrasena[MAX_C];     // 8 caracteres mas el \0.
} tPerfiles;

/* FUNCIONES PUBLICAS */

/* Precondición: recibe un vector de estructuras de tipo tPerfiles el cual debe tener un tamaño mínimo. */
/* Poscondición: redimensiona el vector de estructuras tPerfiles para un nuevo elemento. */
void ReservarPerfil(tPerfiles *infoper);

/* Precondición: recibe un vector de estructuras de tipo tPerfiles el cual debe tener un tamaño mínimo. */
/* Poscondición: introduce en el vector de estructuras de tipo tPerfiles los valores necesarios. */
void RegistrarPerfil(tPerfiles *infoper);

/* Precondición: recibe un vector de estructuras de tipo tPerfiles el cual debe tener un tamaño mínimo. */
/* Poscondición: modifica algún campo de la estructura indicado por el usuario. */
void ModificarCampo(tPerfiles *infoper);

// void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles);



/* FUNCIONES NO EXPORTABLES*/

/* Precondición: recibe un vector de estructuras y un vector de enteros sin signo. */
/* Poscondición: inicializa el vector de enteros sin signo con una ID, por ejemplo, si es el usuario
                 18, en el vector id estará almacenado lo siguiente --> |0|0|1|8|. */
static void GenerarID(tPerfiles *infoper, unsigned int id[ID]);

/* Precondición: recibe un vector de estructuras. */
/* Poscondición: devuelve un entero sin signo que indica el la longitud n de una estructura. */
static unsigned int LongitudVectorEstructuras(tPerfiles *infoper);


#endif 
