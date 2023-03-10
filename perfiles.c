#include "perfiles.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Funciones públicas */

void CargarPerfiles();

void ReservarPerfil(tPerfiles *infoper){
    unsigned int numPerfiles = LongitudVectorEstructuras(infoper);

    infoper = (tPerfiles *)realloc(infoper, (numPerfiles + 1)*sizeof(tPerfiles));

    if(infoper == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }
}

void RegistrarPerfil(tPerfiles *infoper){
    unsigned int numPerfiles = LongitudVectorEstructuras(infoper) + 1, id[ID];

    ReservarPerfil(infoper);

    GenerarID(infoper, infoper[numPerfiles].Id_usuario);

    printf("\nNombre de usuario: ");
    fflush(stdin);
    fgets(infoper[numPerfiles].Nomb_usuario, MAX_N, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Nomb_usuario);

    printf("\n%s, indique el nombre de la localidad en la que resida: ", infoper[numPerfiles].Nomb_usuario);
    fflush(stdin);
    fgets(infoper[numPerfiles].Localidad, MAX_L, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Localidad);

    infoper[numPerfiles].Perfil_usuario = False;

    printf("\n%s, indique el nombre de usuario para acceder al sistema: ", infoper[numPerfiles].Nomb_usuario);
    fflush(stdin);
    fgets(infoper[numPerfiles].Usuario, MAX_U, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Usuario);

    printf("\nContrasena para %s: ", infoper[numPerfiles].Usuario);
    fflush(stdin);
    fgets(infoper[numPerfiles].Contrasena, MAX_C, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Contrasena);
}

void ListarRegistro(tPerfiles *infoper, unsigned int id[ID]){
    int pos = PosicionUsuario(infoper, id);
    char c;

    printf("\nUSER: %s", infoper[pos].Usuario);
    printf("\nNombre de usuario: %s", infoper[pos].Nomb_usuario);
    printf("\nLocalidad: %s", infoper[pos].Localidad);
    printf("\nContrasena: %s", infoper[pos].Contrasena);
    
    if(infoper[pos].Perfil_usuario == True)
        printf("\nTipo de usuario: Administrador.");
    else
        printf("\nTipo de usuario: Usuario.");

    printf("\nDesea cambiar algun dato? (S para modificar, cualquiera para no modificar) ");
    scanf("%c", &c);

    if(infoper[pos].Perfil_usuario == True)
        (c == 'S')?ModificarCamposAdmin(infoper, id):printf("No se modificaran datos.\n");
    else
        (c == 'S')?ModificarCamposUsuario(infoper, id):printf("No se modificaran datos.\n");

}

void ModificarCamposUsuario(tPerfiles *infoper, unsigned int id[ID]){
    int op;
    unsigned int pos = PosicionUsuario(infoper, id);

    puts("Que campo desea modificar? ");

    do{
        printf("\n<1> Nombre de usuario. <2> Localidad. <3> Usuario de acceso. <4> Contrasena. <0> Salir");
        scanf("%i", &op);

        switch(op){
            case 0: break;
            case 1: CambiarNombre(infoper, pos); break;
            case 2: CambiarLocalidad(infoper, pos); break;
            case 3: CambiarUsuarioAcceso(infoper, pos); break;
            case 4: CambiarContrasena(infoper, pos); break;
            default: printf("\nPor favor, introduzca un numero que este en las opciones.\n");
        }
        
    } while(op < 0 || op > 4);   
}

// void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles)


/* Funciones NO exportables */

static void CambiarNombre(tPerfiles *infoper, unsigned int posUsuario){
    char c, copia[MAX_N];

    strcpy(copia, infoper[posUsuario].Nomb_usuario);

    printf("\nIntroduzca el nuevo nombre: ");
    fflush(stdin);
    fgets(infoper[posUsuario].Nomb_usuario, MAX_N, stdin);
    EliminarSaltoLinea(infoper[posUsuario].Nomb_usuario);

    printf("\nNuevo nombre: %s.\n", infoper[posUsuario].Nomb_usuario);

    printf("Desea mantener cambios? (S/n) ");
    scanf("%c", &c);

    do{
        if(c == 'n'){
            strcpy(infoper[posUsuario].Nomb_usuario, copia);
            puts("Se cancelaron los cambios.");
        } else if(c != 'S' || c != 'n')
            puts("Introduzca o S (Si) o N (No)");
        else
            puts("Se ha cambiado el nombre de usuario.");

    } while(c != 'S' || c != 'n');
}

static void CambiarLocalidad(tPerfiles *infoper, unsigned int posUsuario){
    char c, copia[MAX_N];

    strcpy(copia, infoper[posUsuario].Localidad);

    printf("\nIntroduzca la nueva localidad: ");
    fflush(stdin);
    fgets(infoper[posUsuario].Localidad, MAX_N, stdin);
    EliminarSaltoLinea(infoper[posUsuario].Localidad);

    printf("\nNueva localidad: %s.\n", infoper[posUsuario].Localidad);

    printf("Desea mantener cambios? (S/n) ");
    scanf("%c", &c);

    do{
        if(c == 'n'){
            strcpy(infoper[posUsuario].Localidad, copia);
            puts("Se cancelaron los cambios.");
        } else if(c != 'S' || c != 'n')
            puts("Introduzca o S (Si) o N (No)");
        else
            puts("Se ha cambiado la localidad.");

    } while(c != 'S' || c != 'n');
}

static void CambiarUsuarioAcceso(tPerfiles *infoper, unsigned int posUsuario){
    char c, copia[MAX_N];

    strcpy(copia, infoper[posUsuario].Usuario);

    printf("\nIntroduzca el nuevo nombre de acceso: ");
    fflush(stdin);
    fgets(infoper[posUsuario].Usuario, MAX_N, stdin);
    EliminarSaltoLinea(infoper[posUsuario].Usuario);

    printf("\nNuevo nombre de acceso: %s.\n", infoper[posUsuario].Usuario);

    printf("Desea mantener cambios? (S/n) ");
    scanf("%c", &c);

    do{
        if(c == 'n'){
            strcpy(infoper[posUsuario].Usuario, copia);
            puts("Se cancelaron los cambios.");
        } else if(c != 'S' || c != 'n')
            puts("Introduzca o S (Si) o N (No)");
        else
            puts("Se ha cambiado el nombre de acceso.");

    } while(c != 'S' || c != 'n');
}

static void CambiarContrasena(tPerfiles *infoper, unsigned int posUsuario){
    char c, copia[MAX_N];

    strcpy(copia, infoper[posUsuario].Contrasena);

    printf("\nIntroduzca la nueva contrasena: ");
    fflush(stdin);
    fgets(infoper[posUsuario].Contrasena, MAX_N, stdin);
    EliminarSaltoLinea(infoper[posUsuario].Contrasena);

    printf("\nNueva contrasena: %s.\n", infoper[posUsuario].Contrasena);

    printf("Desea mantener cambios? (S/n) ");
    scanf("%c", &c);

    do{
        if(c == 'n'){
            strcpy(infoper[posUsuario].Contrasena, copia);
            puts("Se cancelaron los cambios.");
        } else if(c != 'S' || c != 'n')
            puts("Introduzca o S (Si) o N (No)");
        else
            puts("Se ha cambiado la contrasena.");

    } while(c != 'S' || c != 'n');
}

static unsigned int PosicionUsuario(tPerfiles *infoper, unsigned int id[ID]){
    int i, fin = 0, npos = LongitudVectorEstructuras(infoper);

    for(i = 0; i < npos && !fin; i++){
        if(!strcmp(infoper[i].Id_usuario, id))
            fin = 1;
    }

    return i;
}

static void GenerarID(tPerfiles *infoper, unsigned int id[ID]){
    int i = ID-1, aux1 = LongitudVectorEstructuras(infoper) + 1, aux2 = aux1;     // aux1 contendrá la parte decimal y aux2 la parte entera
    
    for(; i >= 0; i--){
        aux2 %= 10;
        id[i] = aux2;
        aux1 = (unsigned int)floor(aux1/10);  // Aproximación a la baja, es decir, si el numero es 3,8, en aux1 se guradará 3
        aux2 = aux1;
    } 
}

// static ¿ void ? ObtenerID(){}

static unsigned int LongitudVectorEstructuras(tPerfiles *infoper){
    // Sabemos que el fichero Usuarios.txt tendrá tantas líneas como la longitud del vector de estructuras infoper.
    char aux[MAX_LIN_FICH];   // MAX_LIN_FICH es el tamaño máximo que habrá en cada linea, incluyendo los guiones
    FILE *fich;
    unsigned int i = 1;

    fich = fopen("Usuarios.txt", "r");

    if(fich == NULL){
        fprintf(stderr, "Error en la apertura del fichero.");
        exit(1);
    }

    while(!feof(fich)){
        fgets(aux, MAX_LIN_FICH, fich);
        i++;
    }

    // Falta eliminar la última linea que se crea al ver las lineas del fichero

    rewind(fich); 
    fclose(fich);

    return i;
}

