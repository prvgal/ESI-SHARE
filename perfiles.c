#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char estado;     // Dos posibles estados, activo (1) /bloqueado (0). 
} tPerfil;

void Inicio(tPerfil *infoper, int *posUsua);
void Menu(tPerfil *infoper, int posUsua);
void MenuAdmin(tPerfil *infoper, int posUsua);
void MenuUser(tPerfil *infoper, int posUsua);
void Perfil(tPerfil *infoper, int posUsua);
void Usuarios(tPerfil *infoper);
void ImprimirESISHARE();

tPerfil *CrearListaDePerfiles();
void ReservarNuevoPerfil(tPerfil *infoper);
void CargarPerfiles(tPerfil *infoper);

int LogIn(tPerfil *infoper);
int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos);
int SignUp(tPerfil *infoper);
void AltaUsuario(tPerfil *infoper);
void BajaUsuario(tPerfil *infoper);

void ListarPerfiles(tPerfil *infoper);
void ModificarCamposUsuario(tPerfil *infoper, int pos);
void ModificarCamposAdmin(tPerfil *infoper);
int LongitudVectorEstructuras();
void EliminarSaltoLinea(char *cad);
void LimpiarCadena(char *cad, int tam);
void GenerarID(char *id, int num, int numDigitos);
int ValidarID(tPerfil *infoper, char id[ID], int *posUsua, int tam);

void ObtenerNombreUsuario(tPerfil *infoper, char *nomUsuario);
void ObtenerLocalidad(char *nomLocalidad);
void ObtenerUsuario(tPerfil *infoper, char *usuario);
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
            case 1: Usuarios(infoper); break;
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

void Usuarios(tPerfil *infoper){
    int op;

    printf("\n##################################################################\n");
    printf("#               Configuracion del Sistema de Usuarios              #\n");
    printf("####################################################################\n\n");

    do{
        printf("\n\n#            OPCIONES de Configuracion            #\n");
       
        printf("\n<1> Listar usuarios del sistema.\n");
        printf("<2> Para dar de alta a un usuario.\n");
        printf("<3> Para dar de baja a un usuario.\n");
        printf("<4> Para modificar datos de algun usuario.\n");
        printf("<0> Para volver al menu.\n");
        printf("\nIngrese la opcion que desee: ");
        scanf("%i", &op);

        system("cls");
        ImprimirESISHARE();

        switch(op){
            case 0: break;
            case 1: ListarPerfiles(infoper); break;
            //case 2: AltaUsuario(infoper, posUsua); break;
            case 3: BajaUsuario(infoper); break;
            case 4: ModificarCamposAdmin(infoper); break;
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
            sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, 
                                                                     infoper[i].Perfil_usuario, infoper[i].Usuario, infoper[i].Contrasena,
                                                                     &infoper[i].estado);
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
            if(infoper[posUsuario].estado == '0'){  // Verificamos si está activo.
                fprintf(stderr, "\nError, el usuario se encuentra bloqueado.");
                exit(1);
            } else{
                system("cls");
                printf("\nBienvenido/a %s.\n", infoper[posUsuario].Nomb_usuario);
            }
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

    ObtenerNombreUsuario(infoper, infoper[numPerfiles].Nomb_usuario);

    ObtenerLocalidad(infoper[numPerfiles].Localidad);

    // El inicio de sesión será por defecto de tipo usuario, este campo solo lo podrá cambiar el administrador.
    strcpy(infoper[numPerfiles].Perfil_usuario, "usuario");

    ObtenerUsuario(infoper, infoper[numPerfiles].Usuario);

    ObtenerContrasena(infoper[numPerfiles].Contrasena);

    // Por defecto el usuario estará activo.
    infoper[numPerfiles].estado = 1;

    pf = fopen("Usuarios.txt", "a");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.");
        exit(1);
    }

    fprintf(pf, "\n%s-%s-%s-%s-%s-%s-%c", infoper[numPerfiles].Id_usuario, infoper[numPerfiles].Nomb_usuario,
                                       infoper[numPerfiles].Localidad, infoper[numPerfiles].Perfil_usuario,
                                       infoper[numPerfiles].Usuario, infoper[numPerfiles].Contrasena, infoper[numPerfiles].estado);

    printf("\nBienvenido/a %s.\n", infoper[numPerfiles].Nomb_usuario);

    fclose(pf);

    return numPerfiles; // Devuelve la posición del vector donde debería encontrarse el usuario.
}

//void AltaUsuario(tPerfil *infoper, int pos){

//}

void BajaUsuario(tPerfil *infoper){
    FILE *pf; 
    int i, pos, tamOriginal = LongitudVectorEstructuras(); 
    char id[ID];

    printf("\n####################################################################\n");
    printf("#               Configuracion del Sistema de Bajas                 #\n");
    printf("####################################################################\n\n");
    
    ListarPerfiles(infoper);

    pf = fopen("Usuarios.txt", "w");

    fclose(pf);  // Elminamos su contenido

    pf = fopen("Usuarios.txt", "a");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.");
        exit(1);
    }
    
    do{
        printf("\nIndique la ID (primer campo de usuario) del usuario que desea dar de baja: ");
        fflush(stdin);
        fgets(id, ID, stdin);
        
        if(!ValidarID((infoper), id, &pos, tamOriginal))
            fprintf(stderr, "La ID no se encuentra disponible.\n");
        
        for(i = 0; i < tamOriginal; i++){
            if(!strcmp((infoper)[i].Perfil_usuario, "administrador") && !strcmp((infoper)[i].Id_usuario, id)){
                fprintf(stderr, "No se puede dar de baja a un admin.");
                exit(1);
            }
        }

    } while(!ValidarID((infoper), id, &pos, tamOriginal));

    system("cls");

    for(; pos < tamOriginal-1; pos++)
        (infoper)[pos]= (infoper)[pos+1];

    infoper = (tPerfil *)realloc(infoper, (tamOriginal-1)*sizeof(tPerfil));

    if(infoper == NULL){
        printf("Error en asignacion de memoria");
        exit(1);
    }

    // Regeneramos las IDs
    for(i = 0; i < tamOriginal-1; i++)
        GenerarID((infoper)[i].Id_usuario, i+1, ID-1);
    
    // Reescribimos el archivo.
    for(i = 0; i < tamOriginal-1; i++){
        if(i+1 == tamOriginal-1)
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", (infoper)[i].Id_usuario, (infoper)[i].Nomb_usuario,
                                                (infoper)[i].Localidad, (infoper)[i].Perfil_usuario,
                                                (infoper)[i].Usuario, (infoper)[i].Contrasena, (infoper)[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", (infoper)[i].Id_usuario, (infoper)[i].Nomb_usuario,
                                                  (infoper)[i].Localidad, (infoper)[i].Perfil_usuario,
                                                  (infoper)[i].Usuario, (infoper)[i].Contrasena, (infoper)[i].estado);

    }

    fclose(pf);
}


void ListarPerfiles(tPerfil *infoper){
    int i;

    printf("\nUsuarios registrados: \n");

    for(i = 0; i < LongitudVectorEstructuras(); i++)
        printf("%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario, infoper[i].Contrasena ,infoper[i].estado);
    
    printf("\nNumero de usuarios registrados en el sistema: %i.", i);
}

void ModificarCamposUsuario(tPerfil *infoper, int pos){
    int i, op;
    FILE *pf;

    pf = fopen("Usuarios.txt", "r+");

    if(pf == NULL){
        fprintf(stderr, "Error al abrir el archivo.");
        exit(1);
    }

    printf("\nDatos de su cuenta.\n");

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
            case 0: system("cls"); break;
            case 1: ObtenerNombreUsuario(infoper, infoper[pos].Nomb_usuario); break;
            case 2: ObtenerLocalidad(infoper[pos].Localidad); break;
            case 3: ObtenerUsuario(infoper, infoper[pos].Usuario); break;
            case 4: ObtenerContrasena(infoper[pos].Contrasena); break;
            default: printf("\nIngrese un numero dentro del rango de opciones.\n");
        }

    } while(op != 0);

    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(i+1 == LongitudVectorEstructuras())
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario,
                                                infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario,
                                                  infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    rewind(pf);

    fclose(pf);
}

void ModificarCamposAdmin(tPerfil *infoper){
    FILE *pf;
    int i, pos, aux;
    char id[ID], estadoPerfil[2];

    pf = fopen("Usuarios.txt", "r+");

    if(pf == NULL){
        fprintf(stderr, "Error al abrir el archivo.");
        exit(1);
    }

    ListarPerfiles(infoper);

    do{
        printf("\nIndique la ID (primer campo de usuario) del usuario que desea cambiar su actividad: ");
        fflush(stdin);
        fgets(id, ID, stdin);
        
        if(!ValidarID(infoper, id, &pos, LongitudVectorEstructuras()))
            fprintf(stderr, "La ID no se encuentra disponible.\n");
        else{
            do{
                printf("\nEstado activo (1) / bloqueado (0): ");
                fflush(stdin);
                scanf("%i", &aux);

                if(aux != 1 && aux != 0)
                    fprintf(stderr, "\nEl estado debe ser activo (1) / bloqueado (0).");
    
            } while(aux != 1 && aux != 0);

            system("cls");
        }

    } while(!ValidarID(infoper, id, &pos, LongitudVectorEstructuras()));

    sprintf(estadoPerfil, "%i", aux);

    infoper[pos].estado = estadoPerfil[0];

    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(i+1 == LongitudVectorEstructuras())
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario,
                                                infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario,
                                                  infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    rewind(pf);

    fclose(pf);
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


int ValidarID(tPerfil *infoper, char id[ID], int *posUsua, int tam){
    int i, boole = 0;

    for(i = 0; i < tam && !boole; i++){
        if(!strcmp(infoper[i].Id_usuario, id))
            boole = 1;
    }

    *posUsua = i-1;

    return boole;
}


void ObtenerNombreUsuario(tPerfil *infoper, char *nomUsuario){
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
        LimpiarCadena(nomUsuario, MAX_N);
        ObtenerNombreUsuario(infoper, nomUsuario);
    } else if(strlen(nomUsuario) == 0){
        printf("El nombre de usuario no puede estar vacio.");
        LimpiarCadena(nomUsuario, MAX_N);
        ObtenerNombreUsuario(infoper, nomUsuario);
    } else {
        for(i = 0; i < LongitudVectorEstructuras(); i++){
            if(!strcmp(infoper[i].Nomb_usuario, nomUsuario)){
                printf("El nombre de usuario ya se encuentra ocupado.");
                LimpiarCadena(nomUsuario, MAX_N);
                ObtenerNombreUsuario(infoper, nomUsuario);
            }
        }
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
        LimpiarCadena(nomLocalidad, MAX_L);
        ObtenerLocalidad(nomLocalidad);
    }

    if(strlen(nomLocalidad) == 0){
        printf("El nombre de la localidad no puede estar vacio.");
        LimpiarCadena(nomLocalidad, MAX_L);
        ObtenerLocalidad(nomLocalidad);
    }
}

void ObtenerUsuario(tPerfil *infoper, char *usuario){
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
        LimpiarCadena(usuario, MAX_U);
        ObtenerUsuario(infoper, usuario);
    }

    if(strlen(usuario) == 0){
        printf("El usuario no puede estar vacio.");
        LimpiarCadena(usuario, MAX_U);
        ObtenerUsuario(infoper, usuario);
    } else {
        for(i = 0; i < LongitudVectorEstructuras(); i++){
            if(!strcmp(infoper[i].Usuario, usuario)){
                printf("El usuario ya se encuentra ocupado.");
                LimpiarCadena(usuario, MAX_U);
                ObtenerNombreUsuario(infoper, usuario);
            }
        }
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
        LimpiarCadena(contrasena, MAX_C);
        ObtenerContrasena(contrasena);
    }

    if(strlen(contrasena) == 0){
        printf("La contrasena no puede estar vacio.");
        LimpiarCadena(contrasena, MAX_C);
        ObtenerContrasena(contrasena);
    } 
}



void LimpiarCadena(char *cad, int tam){
    int i;

    for(i = 0; i < tam; i++)
        cad[i] = '\0';
    
}
