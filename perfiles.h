#ifndef _PERFILES_H_
#define _PERFILES_H_

#define ID 5
#define MAX_N 21
#define MAX_L 21
#define MAX_PU 14
#define MAX_U 6
#define MAX_C 9
#define MAX_E 10
#define MAX_LIN_FICH 70

typedef struct {
    char Id_usuario[ID];        // 4 digitos.
    char Nomb_usuario[MAX_N];   // 20 caracteres mas el \0. Nombre completo del usuario
    char Localidad[MAX_L];      // 20 caracteres mas el \0. Ubicación de donde sale el usuario con su vehículo compartido.
    char Perfil_usuario[MAX_PU];    // 13 caracteres (administrador) incluyendo el \0. Verifica si el usuario es administrador o de tipo usuario
    char Usuario[MAX_U];        // 5 caracteres mas el \0. Nombre de usuario para acceder al sistema.
    char Contrasena[MAX_C];     // 8 caracteres mas el \0. 
    char estado;     // Dos posibles estados, activo (1) / bloqueado (0). 
} tPerfil;

/* FUNCIONES PUBLICAS */

// Precondición: Recibe la dirección de memoria donde se encuentra la primera posición del vector de estructuras de tipo tPerfil debe estar inicializada con antelación.
// Poscondición: Devuelve la posición donde se encuentra el usuario en el vector de estructuras de tipo tPerfil
int Inicio(tPerfil *infoper);

// Precondición: Debe haberse iniciado sesión o registrado con antelación. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación
// Poscondición: Dependiendo del tipo de perfil que tenga el usuario, desembocará a un menú u otro, en caso de ser administrador, se llama a MenuAdmin, en caso de no serlo, se llama a MenuUser
void Menu(tPerfil *infoper, int posUsua);

// Precondición: Nada.
// Poscondición: Devuelve un vector de tipo tPerfil del tamaño equivalente al numero de usuarios guardados en Usuarios.txt
tPerfil *CrearListaDePerfiles(void);

// Precondición: Recibe un vector de estructuras tipo tPerfil, el cual, deberá tener un tamaño mínimo, en caso de no tenerlo, llama a SignUp para crear un nuevo usuario.
// Poscondición: carga toda la información de Usuarios.txt en el vector de estructuras de tipo tPefil.
void CargarPerfiles(tPerfil *infoper);

// Precondición: recibe una cadena de caraacteres y dos enteros, uno para el numero que queremos realizar la ID y el numero de dígitos de esa ID.
// Poscondición: guarda en id una cadena de caracteres, por ejemplo, si num = 12 y numDigitos = 4, en id se encontrará 0012
void GenerarID(char *id, int num, int numDigitos);


/* FUNCIONES NO EXPORTABLES */

// Precondición: Debe haberse iniciado sesión o registrado con antelación. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en otro menú de configuración dependiendo de las opciones elegidas por el administrador.
static void MenuAdmin(tPerfil *infoper, int posUsua);

// Precondición: Debe haberse iniciado sesión o registrado con antelación. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en otro menú de configuración dependiendo de las opciones elegidas por el usuario.
static void MenuUser(tPerfil *infoper, int posUsua);

// Precondición: Debe haberse iniciado sesión o registrado y haber pasado por MenuUser anteriormente. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en diferentes opciones de configuración.
static void Perfil(tPerfil *infoper, int posUsua);

// Precondición: Debe haberse iniciado sesión o registrado y haber pasado por MenuAdmin anteriormente. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en diferentes opciones de configuración.
static void Usuarios(tPerfil *infoper);

// Precondición: Nada.
// Poscondición: Imprime ESI-SHARE por pantalla.
static void ImprimirESISHARE(void);

// Precondición: Recibe un vector de estructuras tipo tPerfil, el cual, debe estar inicializado o no.
// Poscondición: En caso de que en Usuarios.txt no se encuentre ningun usuario, esta función reserva memoria para uno nuevo, en caso contrario, si se encuentran n usuarios,
//               reservará memoria para n+1.
static void ReservarNuevoPerfil(tPerfil *infoper);

// Precondición: Recibe un vector de estructuras tipo tPerfil, el cual, deberá tener un tamaño mínimo, en caso de no tenerlo, llama a SignUp para crear un nuevo usuario.
// Poscondición: carga toda la información de Usuarios.txt en el vector de estructuras de tipo tPefil.
void CargarPerfiles(tPerfil *infoper);

// Precondición: recibe una dirección de memoria a la primera posición del vector infoper, dos cadenas de caracteres y la dirección de memoria de la variable que almacenará la posición del usuario
//               del cual queremos ver si existe o no.
// Poscondición: Devuelve 1 si se ha encontrado en el registro y 0 si no se ha encontrado
static int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos);

// Precondición: recibe una dirección de memoria a la primera posición del vector infoper.
// Poscondición: añade en el vector de estructuras tPerfil un nuevo usuario e imprime en Usuarios.txt los datos de ese nuevo usuario.
static int SignUp(tPerfil *infoper);

// Precondición: recibe una dirección de memoria a la primera posición del vector infoper.
// Poscondición: elimina tanto en el registro tPerfil tanto como en el fichero Usuarios.txt el usuario seleccionado.
static void BajaUsuario(tPerfil *infoper);

// Precondición: recibe una dirección de memoria a la primera posición del vector infoper.
// Poscondición: Imprime por pantalla todos los usuarios con sus respectivos datos, y también el numero de usuarios registrados en el sistema.
static void ListarPerfiles(tPerfil *infoper);

// Precondición: recibe una dirección de memoria a la primera posición del vector infoper y la posición del usuario que incio sesión al principio del programa.
// Poscondición: cambia tanto en el registro como en el fichero, los datos que puede cambiar un perfil de tipo usuario.
static void ModificarCamposUsuario(tPerfil *infoper, int pos);

// Precondición: recibe una dirección de memoria a la primera posición del vector infoper.
// Poscondición: tras elegir qué usuario cambiar datos, cambia tanto en el registro como en el fichero.
static void ModificarCamposAdmin(tPerfil *infoper);

// Precondición: Nada.
// Poscondición: devuelve el numero de líneas que tiene Usuarios.txt, que es a su vez el tamaño que corresponde al vector
static int LongitudVectorEstructuras(void);

// Precondición: recibe una cadena de caracteres y el tamaño de dicha cadena.
// Poscondición: limpia la cadena poniendo \0 en todas las posiciones de la cadena
static void LimpiarCadena(char *cad, int tam);

// Precondición: recibe un vector de estructuras tPerfil, una cadena de caracteres (ID), una dirección de memoria a la variable que contenga la posición del usuario
//               y una variable que contenga el tamaño del vector de estructuras tPerfil.
// Poscondición: Devuelve 1 si la ID es válida, es decir, si la ID se encuentra en el registro y 0 en caso contrario.
static int ValidarID(tPerfil *infoper, char id[ID], int *posUsua, int tam);

// Precondición: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea válida.
static void ObtenerNombreUsuario(char *nomUsuario);

// Precondición: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena la localidad que se introduzca, con varios mensajes de error en caso de que no sea válida.
static void ObtenerLocalidad(char *nomLocalidad);

// Precondición: recibe un vector de estructuras tPerfil y una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena el usuario que se introduzca, con varios mensajes de error en caso de que no sea válida o se encuentre ya en el registro.
static void ObtenerUsuario(tPerfil *infoper, char *usuario);

// Precondición: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondición: guarda en la cadena la contraseña que se introduzca, con varios mensajes de error en caso de que no sea válida.
static void ObtenerContrasena(char *contrasena);

// Precondición: recibe un vector de estructuras tPerfil, una cadena de caracteres y el tamaño del vector de estructuras.
// Poscondición: pregunta y la ID, con mensajes de error en caso que no sea valido
static void ObtenerID(tPerfil *infoper, char *id, int tam);

// Precondición: recibe una cadena de caracteres.
// Poscondición: pregunta y obtiene el usuario, con mensajes de error en caso que no sea valido
static void PreguntarUsuario(char *user);

// Precondición: recibe una cadena de caracteres.
// Poscondición: pregunta y la ID, con mensajes de error en caso que no sea valido
static void CambiarID(char *id);

// Precondición: Nada.
// Poscondición: Devuelve un char que contiene '1' pasa estar activo o '0' si pasa a estar bloqueados
static char ObtenerEstado(void);

#endif