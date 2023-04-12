#ifndef _PERFILES_
#define _PERFILES_

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

int Inicio(tPerfil *infoper);
void Menu(tPerfil *infoper, int posUsua);
void MenuAdmin(tPerfil *infoper, int posUsua);
void MenuUser(tPerfil *infoper, int posUsua);
static void Perfil(tPerfil *infoper, int posUsua);
static void Usuarios(tPerfil *infoper);
void ImprimirESISHARE(void);

tPerfil *CrearListaDePerfiles(void);
void ReservarNuevoPerfil(tPerfil *infoper);
void CargarPerfiles(tPerfil *infoper);

int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos);
int SignUp(tPerfil *infoper);
void AltaUsuario(tPerfil *infoper);
void BajaUsuario(tPerfil *infoper);

void ListarPerfiles(tPerfil *infoper);
void ModificarCamposUsuario(tPerfil *infoper, int pos);
void ModificarCamposAdmin(tPerfil *infoper);
int LongitudVectorEstructuras(void);
void EliminarSaltoLinea(char *cad);
void LimpiarCadena(char *cad, int tam);
void GenerarID(char *id, int num, int numDigitos);
int ValidarID(tPerfil *infoper, char id[ID], int *posUsua, int tam);
int RestablecerContrasena(tPerfil *infoper, char *user);

void ObtenerNombreUsuario(tPerfil *infoper, char *nomUsuario);
void ObtenerLocalidad(char *nomLocalidad);
void ObtenerUsuario(tPerfil *infoper, char *usuario);
void ObtenerContrasena(char *contrasena);

void PreguntarUsuario(char *user);
void PreguntarContrasena(char *password);


#endif
