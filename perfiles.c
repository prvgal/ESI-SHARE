#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "perfiles.h"
#include "Viajes.h"
#include "vehiculo.h"

int Inicio(tPerfil *infoper){
    int op, posUsuario;     // posUsuario contendr� la posici�n en el vector de estructuras donde se encuentre el usuario que ha iniciado sesi�n/registrado correctamente
    char usuario[MAX_U], contrasena[MAX_C];

    system("cls");
    ImprimirESISHARE();
    printf("\nBienvenido.");

    do{
        printf("\n#            LOG-IN            #\n");

        fflush(stdin);

        // Recogemos el usuario y la contrase�a
        PreguntarUsuario(usuario);
        fflush(stdin);
        ObtenerContrasena(contrasena);

        // Validamos si el usuario, la contrase�a, o ambas son correctas.
        if(!ValidarLogin(infoper, usuario, contrasena, &posUsuario)){
            system("cls");
            fprintf(stderr, "Error, el usuario o la contrasena son incorrectas\n"); // Mensjae de error si hay algo que no es correcto

            // Permitimos la opcion de seguir con el Inicio de Sesi�n, Registrarse o cerrar la aplicaci�n.
            do{
                printf("\nNo tienes una cuenta o ha olvidad su contrasena?\n");
                printf("<1> Para seguir con el Inicio de Sesion.\n");
                printf("<2> Para Registrarse.\n");
                printf("<0> Para cerrar ESI-SHARE.\n");
                
                printf("\nIngrese el numero: ");

                if(scanf("%i", &op) != 1){      // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
                    system("cls");
                    fflush(stdin);
                    fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
                } else{
                    switch(op){
                    case 0: exit(1); break;
                    case 1: posUsuario = Inicio(infoper); break;
                    case 2: posUsuario = SignUp(infoper); break;
                    default: printf("\nIngrese un numero dentro del rango de opciones.\n"); break;
                    }
                }

            } while(op != 1 && op != 2 && op != 3);
        } 

        // Verificamos si est� activo (1) o bloqueado (0) el usuario que desea Iniciar sesi�n. En caso de que se haya registrado, estar� activado por defecto.
        if(infoper[posUsuario].estado == '0'){  
            fprintf(stderr, "\nError, el usuario se encuentra bloqueado.");
            exit(1);    // Si el usuario est� bloqueado se cerrar� la aplicaci�n.
        } else{
            system("cls");
            printf("\nBienvenido/a %s.\n", infoper[posUsuario].Nomb_usuario);
        }

    } while(!ValidarLogin(infoper, infoper[posUsuario].Usuario, infoper[posUsuario].Contrasena, &posUsuario));

    return posUsuario;  // Devolvemos la posici�n del usuario en el vector para su uso en otras funciones y no perder qu� usuario accedi� iniciando sesi�n.
}

void Menu(tPerfil *infoper, int posUsua){
    // Seg�n el inicio de sesi�n o registro, se verifica si el usuario con posici�n posUsua es admin o usuario corriente.
    // Esto es debido a que el usuario corriente no tiene el mismo men� que el administrador y viceversa.
    if(!strcmp(infoper[posUsua].Perfil_usuario, "administrador"))
        MenuAdmin(infoper, posUsua);
    else
        MenuUser(infoper, posUsua);
}

static void MenuAdmin(tPerfil *infoper, int posUsua){
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
        
        if(scanf("%i", &op) != 1){  // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
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
                case 3: menuviajes(infoper[posUsua].Id_usuario, infoper[posUsua].Perfil_usuario); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}

static void MenuUser(tPerfil *infoper, int posUsua){
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

        if(scanf("%i", &op) != 1){  // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
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
                case 3: menuviajes(infoper[posUsua].Id_usuario, infoper[posUsua].Perfil_usuario); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}

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
        
        if(scanf("%i", &op) != 1){  // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
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

        if(scanf("%i", &op) != 1){  // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            system("cls");
            ImprimirESISHARE();

            switch(op){
                case 0: break;
                case 1: ListarPerfiles(infoper); break;
                case 2: SignUp(infoper); break;
                case 3: BajaUsuario(infoper); break;
                case 4: ModificarCamposAdmin(infoper); break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);
}

static void ImprimirESISHARE(void){
    printf("###################################\n");
    printf("#            ESI-SHARE            #\n");
    printf("###################################\n");
}

tPerfil *CrearListaDePerfiles(void){
    tPerfil *perfiles;
    // Reservamos la memoria necesaria gracias a la funci�n LongitudVectorEstructuras()
    if(LongitudVectorEstructuras() == 0)
        perfiles = (tPerfil *)calloc(LongitudVectorEstructuras()+1, sizeof(tPerfil)); 
    else
        perfiles = (tPerfil *)calloc(LongitudVectorEstructuras(), sizeof(tPerfil));

    if(perfiles == NULL){   // Comprobamos si surge alg�n error en la asignaci�n
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }

    return perfiles;    // Devolvemos dicho vector.
}

static void ReservarNuevoPerfil(tPerfil *infoper){
    if(LongitudVectorEstructuras() == 0)    // Comprobaci�n del numero de usuarios para despu�s proceder con la reserva.
        infoper = (tPerfil *)calloc(LongitudVectorEstructuras() + 1, sizeof(tPerfil));
    else
        infoper = (tPerfil *)realloc(infoper, (LongitudVectorEstructuras() + 1)*sizeof(tPerfil));

    if(infoper == NULL){    // Comprobamos si surge alg�n error en la asignaci�n
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }
}

void CargarPerfiles(tPerfil *infoper){
    int i;
    char buffer[MAX_LIN_FICH];

    if(LongitudVectorEstructuras() != 0){    // Comprobamos si existe alg�n usuario en Usuarios.txt
        FILE *pf;

        pf = fopen("Usuarios.txt", "r");    // Abrimos el fichero en tipo lectura.

        if(pf == NULL){     // Comprobamos si su apertura es correcta.
            fprintf(pf, "Error en la apertura de archivos.\n");
            exit(1);
        }

        for(i = 0; i < LongitudVectorEstructuras(); i++){   // Recorremos el vector
        // Cogemos l�nea por l�nea, ya que sabemos que MAX_LIN_FICH es el m�ximo que ocupara cada l�nea de Usuarios.txt
        // Tras recoger una l�nea completa, eliminamos el \n y lo transformamos por un \0, y dicha cadena la metemos en los campos de infoper gracias a sscanf.
        if(fgets(buffer, MAX_LIN_FICH, pf) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, 
                                                                     infoper[i].Localidad, infoper[i].Perfil_usuario, 
                                                                     infoper[i].Usuario, infoper[i].Contrasena, &infoper[i].estado);
            }
        }

        fclose(pf); // Cerramos fichero.
    }
}

// Precondici�n: recibe una direcci�n de memoria a la primera posici�n del vector infoper, dos cadenas de caracteres y la direcci�n de memoria de la variable que almacenar� la posici�n del usuario
//               del cual queremos ver si existe o no.
// Poscondici�n: Devuelve 1 si se ha encontrado en el registro y 0 si no se ha encontrado

static int ValidarLogin(tPerfil *infoper, char usuario[MAX_U], char contrasena[MAX_C], int *pos){
    int i = 0, fin = 0, boole = 0;

    // Comprobemos primero los usuarios
    while(i < LongitudVectorEstructuras() && !fin){
        if(strncmp(infoper[i].Usuario, usuario, MAX_U-1) == 0 && strlen(usuario) == strlen(infoper[i].Usuario))
            fin = 1;

        i++;
    }

    i -= 1;

    // Luego, comprobamos la contrase�a de ese usuario.
    if(strncmp(infoper[i].Contrasena, contrasena, MAX_C-1) == 0 && strlen(contrasena) == strlen(infoper[i].Contrasena))
        boole = 1;

    *pos = i;   // El contenido de pos ahora valdr� i, es decir, donde encontramos el usuario.

    return boole;   // Devolvemos 1 o 0
}

static int SignUp(tPerfil *infoper){
    FILE *pf;
    int numPerfiles = LongitudVectorEstructuras();

    pf = fopen("Usuarios.txt", "a");

    if(pf == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.");
        exit(1);
    }

    ReservarNuevoPerfil(infoper);   // Reservamos un nuevo espacio de memoria

    GenerarID(infoper[numPerfiles].Id_usuario, numPerfiles+1, ID-1);    // Generamos la ID para un nuevo usuario

    ObtenerNombreUsuario(infoper[numPerfiles].Nomb_usuario);            // Preguntamos/Obtenemos el nombre de usuario

    ObtenerLocalidad(infoper[numPerfiles].Localidad);                   // Preguntamos/Obtenemos la localidad.

    // El inicio de sesi�n ser� por defecto de tipo usuario, este campo solo lo podr� cambiar el administrador.
    strcpy(infoper[numPerfiles].Perfil_usuario, "usuario"); 

    ObtenerUsuario(infoper, infoper[numPerfiles].Usuario);              // Preguntamos/Obtenemos el usuario

    ObtenerContrasena(infoper[numPerfiles].Contrasena);                 // Preguntamos/Obtenemos la localidad.

    // Por defecto el usuario estar� activo.
    infoper[numPerfiles].estado = '1';

    //mod reg veh

    // Imprimimos al final del fichero los nuevos datos.
    if(LongitudVectorEstructuras() == 0)
        fprintf(pf, "\n%s-%s-%s-%s-%s-%s-%c", infoper[numPerfiles].Id_usuario, infoper[numPerfiles].Nomb_usuario,
                                          infoper[numPerfiles].Localidad, infoper[numPerfiles].Perfil_usuario,
                                          infoper[numPerfiles].Usuario, infoper[numPerfiles].Contrasena, 
                                          infoper[numPerfiles].estado);
    else
        fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[numPerfiles].Id_usuario, infoper[numPerfiles].Nomb_usuario,
                                          infoper[numPerfiles].Localidad, infoper[numPerfiles].Perfil_usuario,
                                          infoper[numPerfiles].Usuario, infoper[numPerfiles].Contrasena, 
                                          infoper[numPerfiles].estado);

    printf("\nBienvenido/a %s.\n", infoper[numPerfiles].Nomb_usuario);

    fclose(pf); // Cerramos el fichero

    return numPerfiles; // Devuelve la posici�n del vector donde deber�a encontrarse el usuario.
}

static void BajaUsuario(tPerfil *infoper){
    FILE *pf; 
    char id[ID];
    int i, j, pos, tamOriginal = LongitudVectorEstructuras(); 

    printf("\n####################################################################\n");
    printf("#               Configuracion del Sistema de Bajas                 #\n");
    printf("####################################################################\n\n");
    
    ListarPerfiles(infoper);    // Listamos los perfiles con todos sus datos.

    pf = fopen("Usuarios.txt", "w");

    fclose(pf);  // Elminamos el contenido de Usuarios.txt para despu�s sobreescribirlo y no tener ning�n problema.

    pf = fopen("Usuarios.txt", "a");    // Lo abrimos nuevamente, esta vez en modo append

    if(pf == NULL){     // Comprobamos si su apertura es correcta
        fprintf(stderr, "Error en la apertura de archivos.");
        exit(1);
    }
    
    do{
        ObtenerID(infoper, id, tamOriginal); // Obtenemos la ID
        
        for(i = 0; i < tamOriginal; i++){
            // En caso de que la ID sea la de un admin, no se podr� dar de baja.
            if(!strcmp(infoper[i].Perfil_usuario, "administrador") && !strcmp(infoper[i].Id_usuario, id)){
                fprintf(stderr, "No se puede dar de baja a un admin.");     

                // Reescribimos en el fichero los datos.
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

    // Algoritmo para eliminar el usuario, se trata en sobreescribir de izquierda a derecha todos los datos.
    for(; pos < tamOriginal-1; pos++)
        infoper[pos]= infoper[pos+1];

    infoper = (tPerfil *)realloc(infoper, (tamOriginal-1)*sizeof(tPerfil)); // Realizamos un realloc a para una posici�n menos.

    if(infoper == NULL){    // Comprobamos si se reserv� bien la memoria
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

    fclose(pf);    // Cerramos el fichero
}

static void ListarPerfiles(tPerfil *infoper){
    int i;

    printf("\nUsuarios registrados: \n");

    // Recorremos el vector e imprimimos todos sus datos
    for(i = 0; i < LongitudVectorEstructuras(); i++)
        printf("%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, 
                                         infoper[i].Localidad, infoper[i].Perfil_usuario,   
                                         infoper[i].Usuario, infoper[i].Contrasena ,infoper[i].estado);
    
    printf("\nNumero de usuarios registrados en el sistema: %i.", i);
}


static void ModificarCamposUsuario(tPerfil *infoper, int pos){
    int i, op;
    FILE *pf;

    pf = fopen("Usuarios.txt", "r+");   // Abrimos Usuarios.txt para lectura/escritura

    if(pf == NULL){     // Comprobamos si se ha abierto correctamente
        fprintf(stderr, "Error al abrir el archivo.");
        exit(1);
    }

    // Imprimimos todos los datos que el usuario puede cambiar
    printf("\nDatos de su cuenta.\n");

    printf("\nNombre de usuario: %s\n", infoper[pos].Nomb_usuario);
    printf("\nNombre de la localidad: %s\n", infoper[pos].Localidad);
    printf("\nUsuario: %s\n", infoper[pos].Usuario);
    printf("\nContrasena: %s\n", infoper[pos].Contrasena);

    // Preguntamos qu� cambiar y en caso de no estar entre las opciones aparecer� un mensaje de error y volver� a preguntar de nuevo.
    do{
        printf("\nQue desea cambiar?\n");
        printf("<1> Para cambiar el nombre de usuario.\n");
        printf("<2> Para cambiar el nombre de su localidad.\n");
        printf("<3> Para cambiar el usuario.\n");
        printf("<4> Para cambiar la contrasena.\n");
        printf("<0> Para no realizar ningun cambio y volver a la configuracion del perfil.\n");
        
        printf("\nIngrese el numero: ");
        
        if(scanf("%i", &op) != 1){  // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
            system("cls");
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
        } else{
            switch(op){
                case 0: system("cls"); break;   
                case 1: ObtenerNombreUsuario(infoper[pos].Nomb_usuario); break;
                case 2: ObtenerLocalidad(infoper[pos].Localidad); break;
                case 3: ObtenerUsuario(infoper, infoper[pos].Usuario); break;
                case 4: ObtenerContrasena(infoper[pos].Contrasena); break;
                default: printf("\nIngrese un numero dentro del rango de opciones.\n"); break;
            }
        }

    } while(op != 0);

    // Reescribimos el fichero
    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(i+1 == LongitudVectorEstructuras())
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    fclose(pf);     // Cerramos el fichero
}


static void ModificarCamposAdmin(tPerfil *infoper){
    FILE *pf;
    char id[ID];
    int i, op, pos;
    
    pf = fopen("Usuarios.txt", "r+");   // Abrimos el fichero para lectura/escritura

    if(pf == NULL){     // Comprobamos si se ha abierto correctamente
        fprintf(stderr, "Error al abrir el archivo.");
        exit(1);
    }

    ListarPerfiles(infoper);    // Listamos los perfiles

    do{
        ObtenerID(infoper, id, LongitudVectorEstructuras()); // Preguntamos/Obtenemos la ID del usuario a cambiar sus datos

        pos = atoi(id) - 1;     // Pasamos la cadena a un numero.

        system("cls");
        printf("\nDatos del usuario con ID: %s\n", id);

        printf("\nNombre de usuario: %s.\n", infoper[pos].Nomb_usuario);
        printf("\nNombre de la localidad: %s.\n", infoper[pos].Localidad);
        printf("\nTipo de perfil: %s.\n", infoper[pos].Perfil_usuario);
        printf("\nUsuario: %s.\n", infoper[pos].Usuario);
        printf("\nContrasena: %s.\n", infoper[pos].Contrasena);
        printf("\nActivo (1) / bloqueado (0): %c.\n", infoper[pos].estado);

        if(!ValidarID(infoper, id, &pos, LongitudVectorEstructuras()))  // Si no se encuentra la ID, mensaje de error.
            fprintf(stderr, "La ID no se encuentra disponible.\n");
        else{
            // En el caso de encontrarse, preguntar� que es lo que desea cambiar, en caso de no estar en las opciones, tras un mensaje de error, vuelve a preguntar.
            printf("\nQue desea cambiar?\n");
            printf("\n<1> Para cambiar la ID.\n");
            printf("<2> Para cambiar el nombre de usuario.\n");
            printf("<3> Para cambiar el nombre de su localidad.\n");
            printf("<4> Para cambiar el usuario.\n");
            printf("<5> Para cambiar la contrasena.\n");
            printf("<6> Para activar/bloquear el usuario.\n");
            printf("<0> Para no realizar ningun cambio y volver a la configuracion del perfil.\n");
        
            printf("\nIngrese el numero: ");
        
            if(scanf("%i", &op) != 1){  // Con esta condici�n podemos evitar que el usuario haga una entrada err�nea.
                system("cls");
                fflush(stdin);
                fprintf(stderr, "\nEntrada no valida. Debe ser un numero.");
            } else{
                // Llamada a funciones para realizar dichos cambios
                switch(op){
                    case 0: system("cls"); break;
                    case 1: CambiarID(infoper[pos].Id_usuario); break;
                    case 2: ObtenerNombreUsuario(infoper[pos].Nomb_usuario); break;
                    case 3: ObtenerLocalidad(infoper[pos].Localidad); break;
                    case 4: ObtenerUsuario(infoper, infoper[pos].Usuario); break;
                    case 5: ObtenerContrasena(infoper[pos].Contrasena); break;
                    case 6: infoper[pos].estado = ObtenerEstado(); break;
                    default: printf("\nIngrese un numero dentro del rango de opciones.\n"); break;
                }

                system("cls");
            }
        }

    } while(!ValidarID(infoper, id, &pos, LongitudVectorEstructuras()));

    // Reescribimos el fichero para actualizar todos los cambios que han podido surgir.
    for(i = 0; i < LongitudVectorEstructuras(); i++){
        if(i+1 == LongitudVectorEstructuras())
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);
        else
            fprintf(pf, "%s-%s-%s-%s-%s-%s-%c\n", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, infoper[i].Perfil_usuario,
                                                  infoper[i].Usuario, infoper[i].Contrasena, infoper[i].estado);

    }

    fclose(pf);     // Cerramos el fichero.
}

static int LongitudVectorEstructuras(void){
    // Sabemos que el fichero Usuarios.txt tendr� tantas l�neas como la longitud del vector de estructuras infoper.
    char aux[MAX_LIN_FICH];   // MAX_LIN_FICH es el tama�o m�ximo que habr� en cada linea, incluyendo los guiones
    FILE *pf;
    int i = 0;

    pf = fopen("Usuarios.txt", "r");    // Abrimos el fichero en modo lectura.

    if(pf == NULL){     // Comprobamos su apertura.
        fprintf(stderr, "Error en la apertura del fichero.");
        exit(1);
    }

    // Hasta qeu no se llegue al fin de fichero, contamos linea a linea
    while(!feof(pf)){
        fgets(aux, MAX_LIN_FICH, pf);
        i++;
    }

    fclose(pf);     // Cerramos el fichero.

    return i;       // Devolvemos i, que es el numero de iteracines del bucle while que es a su vez el numero de lineas que contiene Usuarios.txt
}

void GenerarID(char *id, int num, int numDigitos){
    if(num >= 0 && numDigitos > 0)
        sprintf(id, "%0*d", numDigitos, num);   // Transformamos num en ID con el numero de d�gitos almacenados en numDigitos
    else
        fprintf(stderr, "La ID no puede ser negativa.");
}

static int ValidarID(tPerfil *infoper, char id[ID], int *posUsua, int tam){
    int i, boole = 0;

    for(i = 0; i < tam && !boole; i++){     // Recorremos el vector
        if(!strcmp(infoper[i].Id_usuario, id))  
            boole = 1;                      // 1 si lo hemos encontrado
    }

    *posUsua = i-1;     // Acutalizamos el contenido de posUsua, ya que la posici�n ser� donde ha encontrado la ID menos 1.

    return boole;       // Devolvemos
}

static void ObtenerNombreUsuario(char *nomUsuario){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de usuario (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_N){    // Recogemos caracter a caracter para controlar el tama�o de entrada
        nomUsuario[i] = c;
        i++;
    }

    nomUsuario[i] = '\0';           // A�adimos el \0 final

    // Comprobamos si el tama�o es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la funci�n
    if(strlen(nomUsuario) > MAX_N-1){
        printf("El nombre de usuario excede los 20 caracteres.");
        LimpiarCadena(nomUsuario, MAX_N);
        ObtenerNombreUsuario(nomUsuario);
    } 
    
    if(strlen(nomUsuario) == 0){
        printf("El nombre de usuario no puede estar vacio.");
        LimpiarCadena(nomUsuario, MAX_N);
        ObtenerNombreUsuario(nomUsuario);
    } 
}

static void ObtenerLocalidad(char *nomLocalidad){
    int i = 0;
    char c;

    printf("\nEscribe el nombre de su localidad (maximo 20 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_L){        // Recogemos caracter a caracter para controlar el tama�o de entrada
        nomLocalidad[i] = c;
        i++;
    }

    nomLocalidad[i] = '\0';         // A�adimos el \0 final

    // Comprobamos si el tama�o es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la funci�n
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

static void ObtenerUsuario(tPerfil *infoper, char *usuario){
    int i = 0, fin = 0;
    char c, aux[MAX_U];

    printf("\nEscribe el usuario (maximo 5 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_U){        // Recogemos caracter a caracter para controlar el tama�o de entrada
        aux[i] = c;
        i++;
    }

    aux[i] = '\0';         // A�adimos el \0 final

    // Comprobamos si el tama�o es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la funci�n
    if(strlen(aux) > MAX_U-1){
        printf("El usuario excede los 5 caracteres.");
        LimpiarCadena(aux, MAX_U);
        ObtenerUsuario(infoper, aux);
    } else if(strlen(aux) == 0){
        printf("El usuario no puede estar vacio.");
        LimpiarCadena(aux, MAX_U);
        ObtenerUsuario(infoper, aux);
    } else {    
        if(LongitudVectorEstructuras() != 0){
            // Si se han pasado las anteriores comprobaciones, hacemos una comprobaci�n final para verificar si el usuario se encuentra en el registro o no
            // en caso de encontrarse, entonces limpia la cadena y vuelve a llamar a la funci�n.
            for(i = 0; i < LongitudVectorEstructuras() && !fin; i++){
                if(!strcmp(infoper[i].Usuario, aux)){
                    fin = 1;
                    printf("El usuario ya se encuentra ocupado.");
                    LimpiarCadena(aux, MAX_U);
                    ObtenerUsuario(infoper, aux);
                }
            }
        }
        
    }

    strcpy(usuario, aux);       // Lo copiamos en user, para que ese valor est� almacenado donde el usuario lo haya puesto como parametro
}


static void ObtenerContrasena(char *contrasena){
    int i = 0;
    char c;

    printf("\nEscribe la contrasena (maximo 8 caracteres): ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < MAX_C){        // Recogemos caracter a caracter para controlar el tama�o de entrada
        contrasena[i] = c;
        i++;
    }

    contrasena[i] = '\0';       // A�adimos el \0 final

    // Comprobamos si el tama�o es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la funci�n
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

static void LimpiarCadena(char *cad, int tam){
    int i;

    for(i = 0; i < tam; i++)    // Recorremos la cadena e introducimos el \0 en cada posici�n.
        cad[i] = '\0';

}

static void PreguntarUsuario(char *user){
    int i = 0;
    char c, usuario[MAX_U];

    printf("\nUsuario (maximo 5 caracteres): ");
    fflush(stdin);
        
    while((c = getchar()) != '\n' && i < MAX_U){        // Recogemos caracter a caracter para controlar el tama�o de entrada
        usuario[i] = c;
        i++;
    }

    usuario[i] = '\0';      // A�adimos el \0 final

    // Comprobamos si el tama�o es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la funci�n
    if(strlen(usuario) > MAX_U-1){
        printf("\nEl usuario tiene de maximo 5 caracteres.\n");
        LimpiarCadena(usuario, MAX_U);
        PreguntarUsuario(usuario);
    }

    strcpy(user, usuario);  // Lo copiamos en user, para que ese valor est� almacenado donde el usuario lo haya puesto como parametro
}


static void ObtenerID(tPerfil *infoper, char *id, int tam){
    int i = 0, encontrado = 0, fin = 0;
    char c;

    printf("\nIndique la ID (primer campo de usuario) del usuario desea modificar: ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < ID){       // Recogemos caracter a caracter para controlar el tama�o de entrada
        id[i] = c;
        i++;
    }

    id[i] = '\0';       // A�adimos el \0 final

    for(i = 0; i < tam && !encontrado; i++){    // Recorremos el vector y buscamos si se encuentra o no
        if(!strcmp(id, infoper[i].Id_usuario))
            encontrado = 1;
    }

    for(i = 0; id[i] != '\0' && !fin; i++){
        if(isdigit((int) id[i]))    // Comprobamos si el formato es correcto
            encontrado = 1;
        else{
            encontrado = 0;  
            fin = 1; 
        }
    }

    // Si no se ha encontrado, limpiamos la cadena y volvemos a llamar a la funci�n
    if(!encontrado){
        printf("\nLa ID no se encuentra en el registro o no tiene 4 caracteres o el formato introducido es incorrecto.");
        LimpiarCadena(id, ID);
        ObtenerID(infoper, id, tam);
    }
}

static void CambiarID(char *id){
    int i = 0, encontrado = 0, fin = 0;
    char c;

    printf("\nIntroduzca la nueva ID: ");
    fflush(stdin);

    while((c = getchar()) != '\n' && i < ID){       // Recogemos caracter a caracter para controlar el tama�o de entrada
        id[i] = c;
        i++;
    }

    id[i] = '\0';   // A�adimos el \0 final

    for(i = 0; id[i] != '\0' && !fin; i++){
        if(isdigit((int) id[i]))
            encontrado = 1;
        else{
            encontrado = 0;  
            fin = 1; 
        }
    }

    // Comprobamos si el tama�o es correcto, en caso de no serlo, limpiamos la cadena y volvemos a llamar a la funci�n
    if(strlen(id) != ID-1 || !encontrado){
        printf("\nLa ID tiene 4 caracteres o el formato no es correcto.");
        LimpiarCadena(id, ID);
        CambiarID(id);
    }
}


static char ObtenerEstado(void){
    int aux;

    do{
        printf("\nEstado activo (1) / bloqueado (0): ");
        fflush(stdin);
        scanf("%i", &aux);

        if(aux != 1 && aux != 0)    // Comprobaci�n, no pueden haber datos distintos de 1 y 0
        fprintf(stderr, "\nEl estado debe ser activo (1) / bloqueado (0).");
    
    } while(aux != 1 && aux != 0);

    return (aux + '0'); // Transformamos el numero a cadena.
}
