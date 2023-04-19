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
    char Localidad[MAX_L];      // 20 caracteres mas el \0. Ubicaci�n de donde sale el usuario con su veh�culo compartido.
    char Perfil_usuario[MAX_PU];    // 13 caracteres (administrador) incluyendo el \0. Verifica si el usuario es administrador o de tipo usuario
    char Usuario[MAX_U];        // 5 caracteres mas el \0. Nombre de usuario para acceder al sistema.
    char Contrasena[MAX_C];     // 8 caracteres mas el \0. 
    char estado;     // Dos posibles estados, activo (1) / bloqueado (0). 
} tPerfil;

/* FUNCIONES PUBLICAS */

// Precondici�n: Recibe la direcci�n de memoria donde se encuentra la primera posici�n del vector de estructuras de tipo tPerfil debe estar inicializada con antelaci�n.
// Poscondici�n: Devuelve la posici�n donde se encuentra el usuario en el vector de estructuras de tipo tPerfil
int Inicio(tPerfil *infoper);

// Precondici�n: Debe haberse iniciado sesi�n o registrado con antelaci�n. Recibe la direcci�n de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posici�n del usuario que inicio sesi�n o se registr� con antelaci�n
// Poscondici�n: Dependiendo del tipo de perfil que tenga el usuario, desembocar� a un men� u otro, en caso de ser administrador, se llama a MenuAdmin, en caso de no serlo, se llama a MenuUser
void Menu(tPerfil *infoper, int posUsua);

// Precondici�n: 
// Poscondici�n: Devuelve un vector de tipo tPerfil del tama�o equivalente al numero de usuarios guardados en Usuarios.txt
tPerfil *CrearListaDePerfiles(void);

// Precondici�n: Recibe un vector de estructuras tipo tPerfil, el cual, deber�a tener un tama�o m�nimo, en caso de no tenerlo, llama a SignUp para crear un nuevo usuario.
// Poscondici�n: carga toda la informaci�n de Usuarios.txt en el vector de estructuras de tipo tPefil.
void CargarPerfiles(tPerfil *infoper);

// Precondici�n: recibe una cadena de caraacteres y dos enteros, uno para el numero que queremos realizar la ID y el numero de d�gitos de esa ID.
// Poscondici�n: guarda en id una cadena de caracteres, por ejemplo, si num = 12 y numDigitos = 4, en id se encontrar� 0012
void GenerarID(char *id, int num, int numDigitos);


/* FUNCIONES NO EXPORTABLES */

// Precondici�n: Debe haberse iniciado sesi�n o registrado con antelaci�n. Recibe la direcci�n de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posici�n del usuario que inicio sesi�n o se registr� con antelaci�n..
// Poscondici�n: Menu de opcinoes que desembocar� en otro men� de configuraci�n dependiendo de las opciones elegidas por el administrador.
static void MenuAdmin(tPerfil *infoper, int posUsua);

// Precondici�n: Debe haberse iniciado sesi�n o registrado con antelaci�n. Recibe la direcci�n de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posici�n del usuario que inicio sesi�n o se registr� con antelaci�n..
// Poscondici�n: Menu de opcinoes que desembocar� en otro men� de configuraci�n dependiendo de las opciones elegidas por el usuario.
static void MenuUser(tPerfil *infoper, int posUsua);

// Precondici�n: Debe haberse iniciado sesi�n o registrado y haber pasado por MenuUser anteriormente. Recibe la direcci�n de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posici�n del usuario que inicio sesi�n o se registr� con antelaci�n..
// Poscondici�n: Menu de opcinoes que desembocar� en diferentes opciones de configuraci�n.
static void Perfil(tPerfil *infoper, int posUsua);

// Precondici�n: Debe haberse iniciado sesi�n o registrado y haber pasado por MenuAdmin anteriormente. Recibe la direcci�n de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posici�n del usuario que inicio sesi�n o se registr� con antelaci�n..
// Poscondici�n: Menu de opcinoes que desembocar� en diferentes opciones de configuraci�n.
static void Usuarios(tPerfil *infoper);

// Precondici�n: 
// Poscondici�n: Imprime ESI-SHARE por pantalla.
static void ImprimirESISHARE(void);

// Precondici�n: Recibe un vector de estructuras tipo tPerfil, el cual, debe estar inicializado o no.
// Poscondici�n: En caso de que en Usuarios.txt no se encuentre ningun usuario, esta funci�n reserva memoria para uno nuevo, en caso contrario, si se encuentran n usuarios,
//               reservar� memoria para n+1.
static void ReservarNuevoPerfil(tPerfil *infoper);

// Precondici�n: Recibe un vector de estructuras tipo tPerfil, el cual, deber�a tener un tama�o m�nimo, en caso de no tenerlo, llama a SignUp para crear un nuevo usuario.
// Poscondici�n: carga toda la informaci�n de Usuarios.txt en el vector de estructuras de tipo tPefil.
void CargarPerfiles(tPerfil *infoper);

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper, dos cadenas de caracteres y la direcci�n de memoria de la variable que almacenar� la posici�n del usuario
//               del cual queremos ver si existe o no.
// Poscondici�n: Devuelve 1 si se ha encontrado en el registro y 0 si no se ha encontrado
static int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos);

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper.
// Poscondici�n: a�ade en el vector de estructuras tPerfil un nuevo usuario e imprime en Usuarios.txt los datos de ese nuevo usuario.
static int SignUp(tPerfil *infoper);

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper.
// Poscondici�n: elimina tanto en el registro tPerfil tanto como en el fichero Usuarios.txt el usuario seleccionado.
static void BajaUsuario(tPerfil *infoper);

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper.
// Poscondici�n: Imprime por pantalla todos los usuarios con sus respectivos datos, y tambi�n el numero de usuarios registrados en el sistema.
static void ListarPerfiles(tPerfil *infoper);

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper y la posici�n del usuario que incio sesi�n al principio del programa.
// Poscondici�n: cambia tanto en el registro como en el fichero, los datos que puede cambiar un perfil de tipo usuario.
static void ModificarCamposUsuario(tPerfil *infoper, int pos);

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper.
// Poscondici�n: tras elegir qu� usuario cambiar datos, cambia tanto en el registro como en el fichero.
static void ModificarCamposAdmin(tPerfil *infoper);

// Precondici�n: 
// Poscondici�n: devuelve el numero de l�neas que tiene Usuarios.txt, que es a su vez el tama�o que corresponde al vector
static int LongitudVectorEstructuras(void);

// Precondici�n: recibe una cadena de caracteres y el tama�o de dicha cadena.
// Poscondici�n: limpia la cadena poniendo \0 en todas las posiciones de la cadena
static void LimpiarCadena(char *cad, int tam);

// Precondici�n: recibe un vector de estructuras tPerfil, una cadena de caracteres (ID), una direcci�n de memoria a la variable que contenga la posici�n del usuario
//               y una variable que contenga el tama�o del vector de estructuras tPerfil.
// Poscondici�n: Devuelve 1 si la ID es v�lida, es decir, si la ID se encuentra en el registro y 0 en caso contrario.
static int ValidarID(tPerfil *infoper, char id[ID], int *posUsua, int tam);

// Precondici�n: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondici�n: guarda en la cadena el nombre de usuario que se introduzca, con varios mensajes de error en caso de que no sea v�lida.
static void ObtenerNombreUsuario(char *nomUsuario);

// Precondici�n: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondici�n: guarda en la cadena la localidad que se introduzca, con varios mensajes de error en caso de que no sea v�lida.
static void ObtenerLocalidad(char *nomLocalidad);

// Precondici�n: recibe un vector de estructuras tPerfil y una cadena de caracteres, la cual no debe estar inicializada
// Poscondici�n: guarda en la cadena el usuario que se introduzca, con varios mensajes de error en caso de que no sea v�lida o se encuentre ya en el registro.
static void ObtenerUsuario(tPerfil *infoper, char *usuario);

// Precondici�n: recibe una cadena de caracteres, la cual no debe estar inicializada
// Poscondici�n: guarda en la cadena la contrase�a que se introduzca, con varios mensajes de error en caso de que no sea v�lida.
static void ObtenerContrasena(char *contrasena);

// Precondici�n: recibe un vector de estructuras tPerfil, una cadena de caracteres y el tama�o del vector de estructuras.
// Poscondici�n: pregunta y la ID, con mensajes de error en caso que no sea valido
static void ObtenerID(tPerfil *infoper, char *id, int tam);

// Precondici�n: recibe una cadena de caracteres.
// Poscondici�n: pregunta y obtiene el usuario, con mensajes de error en caso que no sea valido
static void PreguntarUsuario(char *user);

// Precondici�n: recibe una cadena de caracteres.
// Poscondici�n: pregunta y la ID, con mensajes de error en caso que no sea valido
static void CambiarID(char *id);

// Precondici�n: 
// Poscondici�n: Devuelve un char que contiene '1' pasa estar activo o '0' si pasa a estar bloqueados
static char ObtenerEstado(void);

#endif
