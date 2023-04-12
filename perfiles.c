#include "perfiles.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Precondición: Recibe la dirección de memoria donde se encuentra la primera posición del vector de estructuras de tipo tPerfil debe estar inicializada con antelación.
// Poscondición: Devuelve la posición donde se encuentra el usuario en el vector de estructuras de tipo tPerfil

int Inicio(tPerfil *infoper){
    int op, posUsuario;     // posUsuario contendrá la posición en el vector de estructuras donde se encuentre el usuario que ha iniciado sesión/registrado correctamente
    char usuario[MAX_U], contrasena[MAX_C];

    system("cls");
    ImprimirESISHARE();
    printf("\nBienvenido.");

    do{
        printf("\n#            LOG-IN            #\n");

        fflush(stdin);

        // Recogemos el usuario y la contraseña
        PreguntarUsuario(usuario);
        fflush(stdin);
        PreguntarContrasena(contrasena);

        // Validamos si el usuario, la contraseña, o ambas son correctas.
        if(!ValidarLogin(infoper, usuario, contrasena, &posUsuario)){
            system("cls");
            fprintf(stderr, "Error, el usuario o la contrasena son incorrectas\n"); // Mensjae de error si hay algo que no es correcto

            // Permitimos la opcion de seguir con el Inicio de Sesión, Registrarse o cerrar la aplicación.
            do{
                printf("\nNo tienes una cuenta o ha olvidad su contrasena?\n");
                printf("<1> Para seguir con el Inicio de Sesion.\n");
                printf("<2> Para Registrarse.\n");
                printf("<3> Para restablecer la contrasena\n");
                printf("<0> Para cerrar ESI-SHARE.\n");
                
                printf("\nIngrese el numero: ");

                if(scanf("%i", &op) != 1){
                    system("cls");
                    fflush(stdin);
                    fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
                } else{
                    switch(op){
                    case 0: exit(1); break;
                    case 1: posUsuario = Inicio(infoper); break;
                    case 2: posUsuario = SignUp(infoper); break;
                    case 3: posUsuario = RestablecerContrasena(infoper, usuario); break;
                    default: printf("\nIngrese un numero dentro del rango de opciones.\n"); break;
                    }
                }

            } while(op != 1 && op != 2 && op != 3);
        } 

        // Verificamos si está activo (1) o bloqueado (0) el usuario que desea Iniciar sesión. En caso de que se haya registrado, estará activado por defecto.
        if(infoper[posUsuario].estado == '0'){  
            fprintf(stderr, "\nError, el usuario se encuentra bloqueado.");
            exit(1);    // Si el usuario está bloqueado se cerrará la aplicación.
        } else{
            system("cls");
            printf("\nBienvenido/a %s.\n", infoper[posUsuario].Nomb_usuario);
        }

    } while(!ValidarLogin(infoper, infoper[posUsuario].Usuario, infoper[posUsuario].Contrasena, &posUsuario));

    return posUsuario;  // Devolvemos la posición del usuario en el vector para su uso en otras funciones y no perder qué usuario accedió iniciando sesión.
}

// Precondición: Debe haberse iniciado sesión o registrado con antelación. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación
// Poscondición: Dependiendo del tipo de perfil que tenga el usuario, desembocará a un menú u otro, en caso de ser administrador, se llama a MenuAdmin, en caso de no serlo, se llama a MenuUser

void Menu(tPerfil *infoper, int posUsua){
    // Según el inicio de sesión o registro, se verifica si el usuario con posición posUsua es admin o usuario corriente.
    // Esto es debido a que el usuario corriente no tiene el mismo menú que el administrador y viceversa.
    if(!strcmp(infoper[posUsua].Perfil_usuario, "administrador"))
        MenuAdmin(infoper, posUsua);
    else
        MenuUser(infoper, posUsua);
}

// Precondición: Debe haberse iniciado sesión o registrado con antelación. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en otro menú de configuración dependiendo de las opciones elegidas por el administrador.

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
        
        if(scanf("%i", &op) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            system("cls");
            ImprimirESISHARE();

            switch(op){
                case 0: exit(1); break;
                case 1: Usuarios(infoper); break;
                // case 2: Vehiculos(); break;
                // case 3: Viajes(); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}

// Precondición: Debe haberse iniciado sesión o registrado con antelación. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en otro menú de configuración dependiendo de las opciones elegidas por el usuario.

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

        if(scanf("%i", &op) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            system("cls");
            ImprimirESISHARE();

            switch(op){
                case 0: exit(1); break;
                case 1: Perfil(infoper, posUsua); break;
                // case 2: Vehiculos(); break;
                // case 3: Viajes(); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}

// Precondición: Debe haberse iniciado sesión o registrado y haber pasado por MenuUser anteriormente. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en diferentes opciones de configuración.

static void Perfil(tPerfil *infoper, int posUsua){
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
        
        if(scanf("%i", &op) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            system("cls");
            ImprimirESISHARE();

            switch(op){
                case 0: break;
                case 1: ModificarCamposUsuario(infoper, posUsua); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}


// Precondición: Debe haberse iniciado sesión o registrado y haber pasado por MenuAdmin anteriormente. Recibe la dirección de memoria del primer elemento del vector de estructuras tipo tPerfil
//               y un entero que se corresponde con la posición del usuario que inicio sesión o se registró con antelación..
// Poscondición: Menu de opcinoes que desembocará en diferentes opciones de configuración.

static void Usuarios(tPerfil *infoper){
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

        if(scanf("%i", &op) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            system("cls");
            ImprimirESISHARE();

            switch(op){
                case 0: break;
                case 1: ListarPerfiles(infoper); break;
                case 2: AltaUsuario(infoper); break;
                case 3: BajaUsuario(infoper); break;
                case 4: ModificarCamposAdmin(infoper); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}

// Precondición: 
// Poscondición: Imprime ESI-SHARE por pantalla.

void ImprimirESISHARE(void){
    printf("###################################\n");
    printf("#            ESI-SHARE            #\n");
    printf("###################################\n");
}


tPerfil *CrearListaDePerfiles(void){
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
    FILE *pf;
    char buffer[MAX_LIN_FICH];

    pf = fopen("Usuarios.txt", "r");

    if(pf == NULL){
        fprintf(pf, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(fgets(buffer, MAX_LIN_FICH, pf) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, 
                                                                     infoper[i].Localidad, infoper[i].Perfil_usuario, 
                                                                     infoper[i].Usuario, infoper[i].Contrasena, &infoper[i].estado);
        }
    }

    fclose(pf);
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
    infoper[numPerfiles].estado = '1';

    // menu_registro_vehiculo incluirlo.

    pf = fopen("Usuarios.txt", "a");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.");
        exit(1);
    }

    fprintf(pf, "\n%s-%s-%s-%s-%s-%s-%c", infoper[numPerfiles].Id_usuario, infoper[numPerfiles].Nomb_usuario,
                                          infoper[numPerfiles].Localidad, infoper[numPerfiles].Perfil_usuario,
                                          infoper[numPerfiles].Usuario, infoper[numPerfiles].Contrasena, 
                                          infoper[numPerfiles].estado);

    printf("\nBienvenido/a %s.\n", infoper[numPerfiles].Nomb_usuario);

    fclose(pf);

    return numPerfiles; // Devuelve la posición del vector donde debería encontrarse el usuario.
}

void AltaUsuario(tPerfil *infoper){
    SignUp(infoper);
}

void BajaUsuario(tPerfil *infoper){
    FILE *pf; 
    char id[ID];
    int i, j, pos, tamOriginal = LongitudVectorEstructuras(); 

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
        
        if(!ValidarID(infoper, id, &pos, tamOriginal))
            fprintf(stderr, "La ID no se encuentra disponible.\n");
        
        for(i = 0; i < tamOriginal; i++){
            if(!strcmp(infoper[i].Perfil_usuario, "administrador") && !strcmp(infoper[i].Id_usuario, id)){
                fprintf(stderr, "No se puede dar de baja a un admin.");

                for(j = 0; j < tamOriginal; j++){
                    if(j+1 == tamOriginal)
                        fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[j].Id_usuario, infoper[j].Nomb_usuario,
                                                            infoper[j].Localidad, infoper[j].Perfil_usuario,
                                                            infoper[j].Usuario, infoper[j].Contrasena, infoper[j].estado);
                    else
                        fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[j].Id_usuario, infoper[j].Nomb_usuario,
                                                              infoper[j].Localidad, infoper[j].Perfil_usuario,
                                                              infoper[j].Usuario, infoper[j].Contrasena, infoper[j].estado);

                    }

                exit(1);
            }
        }

    } while(!ValidarID(infoper, id, &pos, tamOriginal));

    system("cls");

    for(; pos < tamOriginal-1; pos++)
        infoper[pos]= infoper[pos+1];

    infoper = (tPerfil *)realloc(infoper, (tamOriginal-1)*sizeof(tPerfil));

    if(infoper == NULL){
        printf("Error en asignacion de memoria");
        exit(1);
    }

    // Regeneramos las IDs
    for(i = 0; i < tamOriginal-1; i++)
        GenerarID(infoper[i].Id_usuario, i+1, ID-1);
    
    // Reescribimos el archivo.
    for(i = 0; i < tamOriginal-1; i++){
        if(i+1 == tamOriginal-1)
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario,
                                                infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario,
                                                  infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    fclose(pf);
}


void ListarPerfiles(tPerfil *infoper){
    int i;

    printf("\nUsuarios registrados: \n");

    for(i = 0; i < LongitudVectorEstructuras(); i++)
        printf("%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, 
                                      infoper[i].Perfil_usuario, infoper[i].Contrasena ,infoper[i].estado);
    
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
        
        if(scanf("%i", &op) != 1){
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            switch(op){
                case 0: system("cls"); break;
                case 1: ObtenerNombreUsuario(infoper, infoper[pos].Nomb_usuario); break;
                case 2: ObtenerLocalidad(infoper[pos].Localidad); break;
                case 3: ObtenerUsuario(infoper, infoper[pos].Usuario); break;
                case 4: ObtenerContrasena(infoper[pos].Contrasena); break;
                default: printf("\nIngrese un numero dentro del rango de opciones.\n"); break;
            }
        }

    } while(op != 0);

    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(i+1 == LongitudVectorEstructuras())
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    fclose(pf);
}

void ModificarCamposAdmin(tPerfil *infoper){
    FILE *pf;
    char id[ID];
    int i, pos, aux;
    

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

    infoper[pos].estado = aux + '0';

    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(i+1 == LongitudVectorEstructuras())
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    fclose(pf);
}

int LongitudVectorEstructuras(void){
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

int RestablecerContrasena(tPerfil *infoper, char *user){
    int i, pos, fin = 0, seguro = 1;
    char nomUsua[MAX_N], nomLocal[MAX_L];

    system("cls");

    printf("\n########################################################\n");
    printf("#               Restablecer Contrasena                 #\n");
    printf("########################################################\n\n");

    printf("Para verificar si de verdad eres el usuario, deberas verificar dos preguntas de seguridad:\n");
    
    // Verificamos el nombre de usuario.
    printf("1. Nombre de usuario: ");
    fflush(stdin);
    fgets(nomUsua, MAX_N, stdin);
    EliminarSaltoLinea(nomUsua);

    printf("2. Nombre de su localidad: ");
    fflush(stdin);
    fgets(nomLocal, MAX_L, stdin);
    EliminarSaltoLinea(nomLocal);

    // Buscamos si el usuario introducido realmente existe en el registro.
    for(i = 0; i < LongitudVectorEstructuras() && !fin; i++){
        if(!strcmp(infoper[i].Usuario, user)){
            fin = 1;

            if(strcmp(infoper[i].Nomb_usuario, nomUsua) == 0 && strcmp(infoper[i].Localidad, nomLocal) == 0)    // Comprobamos si pasan las pruebas de seguridad
                seguro = 1;
            else
                seguro = 0;
                
        }
    }

    i -= 1; // Si sale del bucle con la condición de salida fin, la variable i valdrá 1 posición más de donde realmente se encuentra debido a la última iteración del bucle

    if(fin == 0 || seguro == 0){
        system("cls");
        ImprimirESISHARE();
        fprintf(stderr, "El usuario introducido no existe o no se pasaron las pruebas de seguridad.\n\n");

        int op;

        do{
            printf("<1> Para Registrarse.\n");
            printf("<0> Para salir de ESI-SHARE\n\n");

            printf("Ingrese una opcion: ");

            if(scanf("%i", &op) != 1){
                system("cls");
                fflush(stdin);
                fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
            } else{
                switch(op){
                    case 0: exit(1); break;
                    case 1: pos = SignUp(infoper); break;
                    default: fprintf(stderr, "La opcion no esta entre las opciones\n"); break;
                }
            }

        } while(op != 1);

    } else{
        FILE *pf;

        pf = fopen("Usuarios.txt", "r+");   // Abrimos el fihero.

        if(pf == NULL){ // Comprobamos si se ha abierto correctamente.
            fprintf(stderr, "Error en la apertura del fichero.\n");
            exit(1);
        }

        printf("A continuacion, podra restablecer su contrasena\n");

        pos = i;
        ObtenerContrasena(infoper[i].Contrasena);   // Preguntamos la contrasena

        for(i = 0; i < LongitudVectorEstructuras(); i++){
            if(i+1 == LongitudVectorEstructuras())  // Esta comprobación es para no tener un \n al final del archivo.
                fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                    infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
            else
                fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                      infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

        }

        fclose(pf);
    }

    return pos;
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
    } 
    
    if(strlen(nomUsuario) == 0){
        printf("El nombre de usuario no puede estar vacio.");
        LimpiarCadena(nomUsuario, MAX_N);
        ObtenerNombreUsuario(infoper, nomUsuario);
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
    int i = 0, fin = 0;
    char c, aux[MAX_U];

    printf("\nEscribe el usuario (maximo 5 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_U){
        aux[i] = c;
        i++;
    }

    aux[i] = '\0';

    if(strlen(aux) > MAX_U-1){
        printf("El usuario excede los 5 caracteres.");
        LimpiarCadena(aux, MAX_U);
        ObtenerUsuario(infoper, aux);
    } else if(strlen(aux) == 0){
        printf("El usuario no puede estar vacio.");
        LimpiarCadena(aux, MAX_U);
        ObtenerUsuario(infoper, aux);
    } else {
        for(i = 0; i < LongitudVectorEstructuras() && !fin; i++){
            if(!strcmp(infoper[i].Usuario, aux)){
                fin = 1;
                printf("El usuario ya se encuentra ocupado.");
                LimpiarCadena(aux, MAX_U);
                ObtenerUsuario(infoper, aux);
            }
        }
    }

    strcpy(usuario, aux);
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

void PreguntarUsuario(char *user){
    int i = 0;
    char c, usuario[MAX_U];

    printf("\nUsuario: ");
    fflush(stdin);
        
            // Recogemos los datos carácter a carácter para poder ir contando a su vez el numero de caracteres
    while((c = getchar()) != '\n' && i < MAX_U){
        usuario[i] = c;
        i++;
    }

    usuario[i] = '\0';

    if(strlen(usuario) > MAX_U-1){
        printf("\nEl usuario tiene de maximo 5 caracteres.\n");
        LimpiarCadena(usuario, MAX_U);
        PreguntarUsuario(usuario);
    }

    strcpy(user, usuario);
}

void PreguntarContrasena(char *password){
    int i = 0;
    char c, contrasena[MAX_C];

    printf("\nContrasena: ");
    fflush(stdin);
        
            // Recogemos los datos carácter a carácter para poder ir contando a su vez el numero de caracteres
    while((c = getchar()) != '\n' && i < MAX_C){
        contrasena[i] = c;
        i++;
    }

    contrasena[i] = '\0';

    if(strlen(contrasena) > MAX_C-1){
        printf("\nLa contrasena tiene de maximo 8 caracteres.\n");
        LimpiarCadena(contrasena, MAX_C);
        PreguntarContrasena(contrasena);
    }

    strcpy(password, contrasena);
}
