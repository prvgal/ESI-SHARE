/* FALTA ADAPTARLO EN EL ARCHIVO DE HEADERS Y QUITAR EL MAIN, YA QUE ES UN MAIN TEMPORAL */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ID 5
#define MAX_N 21
#define MAX_L 21
#define MAX_PU 14
#define MAX_U 6
#define MAX_C 9
#define MAX_LIN_FICH 68

typedef struct {
    char Id_usuario[ID];        // 4 digitos.
    char Nomb_usuario[MAX_N];   // 20 caracteres mas el \0. Nombre completo del usuario
    char Localidad[MAX_L];      // 20 caracteres mas el \0. Ubicación de donde sale el usuario con su vehículo compartido.
    char Perfil_usuario[MAX_PU];      // True para administrador y False para usuario.
    char Usuario[MAX_U];        // 5 caracteres mas el \0. Nombre de usuario para acceder al sistema
    char Contrasena[MAX_C];
} tPerfil;

void Inicio(tPerfil *infoper, int *posUsua);
void Menu(tPerfil *infoper, int posUsua);
void MenuAdmin(tPerfil *infoper, int posUsua);
void MenuUser(tPerfil *infoper, int posUsua);
void Perfil(tPerfil *infoper, int posUsua);
void ImprimirESISHARE();

tPerfil *CrearListaDePerfiles();
void ReservarNuevoPerfil(tPerfil *infoper);
void CargarPerfiles(tPerfil *infoper);

int LogIn(tPerfil *infoper);
int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos);
int SignUp(tPerfil *infoper);

void ListarPerfiles(tPerfil *infoper);
void ModificarCamposUsuario(tPerfil *infoper, int pos);
int LongitudVectorEstructuras();
void EliminarSaltoLinea(char *cad);
void LimpiarCadena(char *cad);
void GenerarID(char *id, int num, int numDigitos);

void ObtenerNombreUsuario(char *nomUsuario);
void ObtenerLocalidad(char *nomLocalidad);
void ObtenerUsuario(char *usuario);
void ObtenerContrasena(char *contrasena);

int main(){
    int pos;
    tPerfil *info;

    info = CrearListaDePerfiles();
    CargarPerfiles(info);

    Inicio(info, &pos);

    Menu(info, pos);

    free(info);

    return 0;
}

void Inicio(tPerfil *infoper, int *posUsua){
    int op, pos;

    ImprimirESISHARE();
    printf("\nBienvenido.");

    do{
        printf("\n#            OPCIONES            #\n\n");
       
        printf("\n<1> Para Iniciar Sesion.\n");
        printf("<2> Para Registrarse.\n");
        printf("<0> Para cerrrar ESI-SHARE\n");
        printf("\nIngrese la opcion que desee: ");
        scanf("%i", &op);

        if(op == 0)
            exit(1);

        system("cls");
        ImprimirESISHARE();

        switch(op){
            case 1: pos = LogIn(infoper); break;
            case 2: pos = SignUp(infoper); break;
            default: printf("\nElige una de las opciones.\n");
        }

    } while(op != 1 && op != 2);

    *posUsua = pos;
}

void Menu(tPerfil *infoper, int posUsua){
    if(!strcmp(infoper[posUsua].Perfil_usuario, "administrador"))
        MenuAdmin(infoper, posUsua);
    else
        MenuUser(infoper, posUsua);
}

void MenuAdmin(tPerfil *infoper, int posUsua){
    int op;

    printf("\n###################################\n");
    printf("#               MENU              #\n");
    printf("###################################\n\n");

    printf("%s", infoper[posUsua].Perfil_usuario);

    do{
        printf("\n\n#            OPCIONES            #\n");
       
        printf("\n<1> Usuarios.\n");
        printf("<2> Vehiculos.\n");
        printf("<3> Viajes.\n");
        printf("<0> Para cerrar ESI-SHARE\n");
        printf("\nIngrese la opcion que desee: ");
        scanf("%i", &op);

        if(op == 0)
            exit(1);

        system("cls");
        ImprimirESISHARE();

        switch(op){
            // case 1: Usuarios(); break;
            // case 2: Vehiculos(); break;
            // case 3: Viajes(); break;
            default: printf("\nElige una de las opciones.\n");
        }

    } while(op != 0);

}

void MenuUser(tPerfil *infoper, int posUsua){
    int op;

    printf("\n###################################\n");
    printf("#               MENU              #\n");
    printf("###################################\n");

    printf("Usuario: %s", infoper[posUsua].Nomb_usuario);

    do{
        printf("\n\n#            OPCIONES            #\n");
       
        printf("\n<1> Perfil.\n");
        printf("<2> Vehiculos.\n");
        printf("<3> Viajes.\n");
        printf("<0> Para cerrar ESI-SHARE\n");

        printf("\nIngrese la opcion que desee: ");
        scanf("%i", &op);

        if(op == 0)
            exit(1);

        system("cls");
        ImprimirESISHARE();

        switch(op){
            case 1: Perfil(infoper, posUsua); break;
            // case 2: Vehiculos(); break;
            // case 3: Viajes(); break;
            default: printf("\nElige una de las opciones.\n");
        }

    } while(op != 0);
}

void Perfil(tPerfil *infoper, int posUsua){
    int op;

    printf("\n#######################################################\n");
    printf("#               Configuracion del Perfil              #\n");
    printf("#######################################################\n\n");

    printf("Usuario: %s.", infoper[posUsua].Nomb_usuario);

    do{
        printf("\n\n#            OPCIONES de Configuracion            #\n");
       
        printf("\n<1> Cambiar algun dato de la cuenta.\n");
        printf("<0> Para volver al menu.\n");
        printf("\nIngrese la opcion que desee: ");
        scanf("%i", &op);

        system("cls");
        ImprimirESISHARE();

        switch(op){
            case 0: break;
            case 1: ModificarCamposUsuario(infoper, posUsua); break;
            default: printf("\nElige una de las opciones.\n");
        }

    } while(op != 0);
}

void ImprimirESISHARE(){
    printf("###################################\n");
    printf("#            ESI-SHARE            #\n");
    printf("###################################\n");
}


tPerfil *CrearListaDePerfiles(){
    tPerfil *perfiles;

    perfiles = (tPerfil *)calloc(LongitudVectorEstructuras(), sizeof(tPerfil));

    if(perfiles == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }

    return perfiles;
}

void ReservarNuevoPerfil(tPerfil *infoper){
    if(LongitudVectorEstructuras() == 0)
        infoper = (tPerfil *)calloc(LongitudVectorEstructuras() + 1, sizeof(tPerfil));
    else
        infoper = (tPerfil *)realloc(infoper, (LongitudVectorEstructuras() + 1)*sizeof(tPerfil));

    if(infoper == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }
}

void CargarPerfiles(tPerfil *infoper){
    int i;
    char buffer[MAX_LIN_FICH];
    FILE *pf;

    pf = fopen("Usuarios.txt", "r");

    if(pf == NULL){
        fprintf(pf, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(fgets(buffer, MAX_LIN_FICH, pf) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%s", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, 
                                                               infoper[i].Perfil_usuario, infoper[i].Usuario, infoper[i].Contrasena);
        }
    }

    fclose(pf);
}



int LogIn(tPerfil *infoper){
    int posUsuario;
    char usuario[MAX_U], contrasena[MAX_C];

    do{
        printf("\n#            LOG-IN            #\n");

        printf("\nUsuario: ");
        fflush(stdin);
        fgets(usuario, MAX_U, stdin);

        printf("\nContrasena: ");
        fflush(stdin);
        fgets(contrasena, MAX_C, stdin);

        if(!ValidarLogin(infoper, usuario, contrasena, &posUsuario)){
            system("cls");
            ImprimirESISHARE();
            fprintf(stderr, "Error, el usuario o la contrasena son incorrectas\n");
        } else{
            system("cls");
            printf("\nBienvenido/a %s.\n", infoper[posUsuario].Nomb_usuario);
        }

    } while(!ValidarLogin(infoper, usuario, contrasena, &posUsuario));

    return posUsuario;  // Devuelve la posicion del usuario.
}

int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos){
    int i = 0, fin = 0, boole = 0;

    // Comprobemos primero los usuarios
    while(i < LongitudVectorEstructuras() && !fin){
        if(strncmp(infoper[i].Usuario, usuario, MAX_U-1) == 0 && strlen(usuario) == strlen(infoper[i].Usuario))
            fin = 1;

        i++;
    }

    i -= 1;

    // Luego, comprobamos la contraseña de ese usuario.
    if(strncmp(infoper[i].Contrasena, contrasena, MAX_C-1) == 0 && strlen(contrasena) == strlen(infoper[i].Contrasena))
        boole = 1;

    *pos = i;

    return boole;
}

int SignUp(tPerfil *infoper){
    FILE *pf;
    int numPerfiles = LongitudVectorEstructuras();

    ReservarNuevoPerfil(infoper);

    GenerarID(infoper[numPerfiles].Id_usuario, numPerfiles+1, ID-1);

    ObtenerNombreUsuario(infoper[numPerfiles].Nomb_usuario);

    ObtenerLocalidad(infoper[numPerfiles].Localidad);

    // El inicio de sesión será por defecto de tipo usuario, este campo solo lo podrá cambiar el administrador.
    strcpy(infoper[numPerfiles].Perfil_usuario, "usuario");

    ObtenerUsuario(infoper[numPerfiles].Usuario);

    ObtenerContrasena(infoper[numPerfiles].Contrasena);

    pf = fopen("Usuarios.txt", "a");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.");
        exit(1);
    }

    fprintf(pf, "\n%s-%s-%s-%s-%s-%s", infoper[numPerfiles].Id_usuario, infoper[numPerfiles].Nomb_usuario,
                                       infoper[numPerfiles].Localidad, infoper[numPerfiles].Perfil_usuario,
                                       infoper[numPerfiles].Usuario, infoper[numPerfiles].Contrasena);

    printf("\nBienvenido/a %s.\n", infoper[numPerfiles].Nomb_usuario);

    fclose(pf);

    return numPerfiles; // Devuelve la posición del vector donde debería encontrarse el usuario.
}


void ListarPerfiles(tPerfil *infoper){
    int i;

    printf("\nUsuarios registrados: ");

    for(i = 0; i < LongitudVectorEstructuras(); i++)
        printf("%s\n", infoper[i].Nomb_usuario);
    
    printf("Numero de usuarios %i totales.", i);
}

void ModificarCamposUsuario(tPerfil *infoper, int pos){
    int op;

    printf("Datos de su cuenta.\n");

    printf("\nNombre de usuario: %s\n", infoper[pos].Nomb_usuario);
    printf("\nNombre de la localidad: %s\n", infoper[pos].Localidad);
    printf("\nUsuario: %s\n", infoper[pos].Usuario);
    printf("\nContrasena: %s\n", infoper[pos].Contrasena);

    do{
        printf("\nQue desea cambiar?\n");
        printf("<1> Para cambiar el nombre de usuario.\n");
        printf("<2> Para cambiar el nombre de su localidad.\n");
        printf("<3> Para cambiar el usuario.\n");
        printf("<4> Para cambiar la contrasena.\n");
        printf("<0> Para no realizar ningun cambio y volver a la configuracion del perfil.\n");

        printf("\nIngrese el numero: ");
        scanf("%i", &op);

        switch(op){
            case 0: break;
            case 1: ObtenerNombreUsuario(infoper[pos].Nomb_usuario);
            case 2: ObtenerLocalidad(infoper[pos].Localidad);
            case 3: ObtenerUsuario(infoper[pos].Usuario);
            case 4: ObtenerContrasena(infoper[pos].Contrasena);
            default: printf("\nIngrese un numero dentro del rango de opciones.\n");
        }

    } while(op != 0);

    // FALTA QUE CAMBIE DICHOS CAMBIOS EN EL FICHERO
}

int LongitudVectorEstructuras(){
    // Sabemos que el fichero Usuarios.txt tendrá tantas líneas como la longitud del vector de estructuras infoper.
    char aux[MAX_LIN_FICH];   // MAX_LIN_FICH es el tamaño máximo que habrá en cada linea, incluyendo los guiones
    FILE *pf;
    int i = 1;

    pf = fopen("Usuarios.txt", "r");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.");
        exit(1);
    }

    while(!feof(pf)){
        fgets(aux, MAX_LIN_FICH, pf);
        i++;
    }

    rewind(pf); 
    fclose(pf);

    return i-1;
}

void EliminarSaltoLinea(char *cad){
    int len = strlen(cad);

    if(cad[len - 1] == '\n')
        cad[len - 1] = '\0';
}

void GenerarID(char *id, int num, int numDigitos){
    sprintf(id, "%0*d", numDigitos, num);
}



void ObtenerNombreUsuario(char *nomUsuario){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de usuario (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_N){
        nomUsuario[i] = c;
        i++;
    }

    nomUsuario[i] = '\0';

    if(strlen(nomUsuario) > MAX_N-1){
        printf("El nombre de usuario excede los 20 caracteres.");
        LimpiarCadena(nomUsuario);
        ObtenerNombreUsuario(nomUsuario);
    }

    if(strlen(nomUsuario) == 0){
        printf("El nombre de usuario no puede estar vacio.");
        LimpiarCadena(nomUsuario);
        ObtenerNombreUsuario(nomUsuario);
    } 
}

void ObtenerLocalidad(char *nomLocalidad){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de su localidad (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_L){
        nomLocalidad[i] = c;
        i++;
    }

    nomLocalidad[i] = '\0';

    if(strlen(nomLocalidad) > MAX_L-1){
        printf("El nombre de la localidad excede los 20 caracteres.");
        LimpiarCadena(nomLocalidad);
        ObtenerNombreUsuario(nomLocalidad);
    }

    if(strlen(nomLocalidad) == 0){
        printf("El nombre de la localidad no puede estar vacio.");
        LimpiarCadena(nomLocalidad);
        ObtenerNombreUsuario(nomLocalidad);
    } 
}

void ObtenerUsuario(char *usuario){
    int i = 0;
    char c;

    printf("\nEscribe el usuario (maximo 5 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_U){
        usuario[i] = c;
        i++;
    }

    usuario[i] = '\0';

    if(strlen(usuario) > MAX_U-1){
        printf("El usuario excede los 5 caracteres.");
        LimpiarCadena(usuario);
        ObtenerNombreUsuario(usuario);
    }

    if(strlen(usuario) == 0){
        printf("El usuario no puede estar vacio.");
        LimpiarCadena(usuario);
        ObtenerNombreUsuario(usuario);
    } 
}

void ObtenerContrasena(char *contrasena){
    int i = 0;
    char c;

    printf("\nEscribe la contrasena (maximo 8 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_C){
        contrasena[i] = c;
        i++;
    }

    contrasena[i] = '\0';

    if(strlen(contrasena) > MAX_C-1){
        printf("La contrasena excede los 8 caracteres.");
        LimpiarCadena(contrasena);
        ObtenerNombreUsuario(contrasena);
    }

    if(strlen(contrasena) == 0){
        printf("La contrasena no puede estar vacio.");
        LimpiarCadena(contrasena);
        ObtenerNombreUsuario(contrasena);
    } 
}

void LimpiarCadena(char *cad){
    unsigned int i;

    for(i = 0; i < strlen(cad); i++)
        cad[i] = '\0';
}
