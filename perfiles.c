#include "perfiles.h"
#include "ficheros.h"
#include "tipos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Funciones públicas */

/* FUNCIÓN CON PROBLEMAS, SI NO LE METO UN INTRO AL PRINCIPIO, LA PRIMERA ID QUE RECOGE COGE SOLO 3 DÍGITOS*/
void CargarPerfiles(tPerfiles *infoper){
    int i;
    FILE *pf;

    pf = fopen("Usuarios.txt", "r");

    if(pf == NULL){
        fprintf(pf, "Error en la apertura de ficheros.\n");
        exit(1);
    }

    for(i = 0; i < LongitudVectorEstructuras(); i++)
        fscanf(pf, "%*c%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]", infoper[i].Id_usuario, infoper[i].Nomb_usuario, infoper[i].Localidad, 
                                                              infoper[i].Perfil_usuario, infoper[i].Usuario, infoper[i].Contrasena);
}

void ReservarPerfil(tPerfiles *infoper){
    int numPerfiles = LongitudVectorEstructuras();

    if(numPerfiles == 0)
        infoper = (tPerfiles *)calloc(numPerfiles + 1, sizeof(tPerfiles));
    else
        infoper = (tPerfiles *)realloc(infoper, (numPerfiles + 1)*sizeof(tPerfiles));

    if(infoper == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.");
        exit(1);
    }
}

void RegistrarPerfil(tPerfiles *infoper){
    int numPerfiles = LongitudVectorEstructuras();

    ReservarPerfil(infoper);

    GenerarID(infoper[numPerfiles].Id_usuario, numPerfiles, ID);

    printf("\nNombre de usuario: ");
    fflush(stdin);
    fgets(infoper[numPerfiles].Nomb_usuario, MAX_N, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Nomb_usuario);

    printf("\n%s, indique el nombre de la localidad en la que resida: ", infoper[numPerfiles].Nomb_usuario);
    fflush(stdin);
    fgets(infoper[numPerfiles].Localidad, MAX_L, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Localidad);

    // ADMINISTRADOR O USUARIO???

    printf("\n%s, indique el nombre de usuario para acceder al sistema: ", infoper[numPerfiles].Nomb_usuario);
    fflush(stdin);
    fgets(infoper[numPerfiles].Usuario, MAX_U, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Usuario);

    printf("\nContrasena para %s: ", infoper[numPerfiles].Usuario);
    fflush(stdin);
    fgets(infoper[numPerfiles].Contrasena, MAX_C, stdin);
    EliminarSaltoLinea(infoper[numPerfiles].Contrasena);
}

void ListarRegistro(tPerfiles *infoper, char id[ID]){
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

void ModificarCamposUsuario(tPerfiles *infoper, char id[ID]){
    int op;
    int pos = PosicionUsuario(infoper, id);

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

void GenerarID(char *id, int num, int numDigitos){
    int i = numDigitos-1, aux1 = num, aux2 = aux1;     // aux1 contendrá la parte decimal y aux2 la parte entera

    for(; i >= 0; i--){
        aux2 %= 10;
        id[i] = aux2;
        aux1 = (int)floor(aux1/10);  // Aproximación a la baja, es decir, si el numero es 3,8, en aux1 se guradará 3
        aux2 = aux1;
    }

    id[numDigitos] = '/0';
}

void ImprimirID(char *id, int numDigitos){
    int i;

    for(i = 0; i < numDigitos; i++)
        printf("%i", id[i]);
}

/* Funciones NO exportables */

static void CambiarNombre(tPerfiles *infoper, int posUsuario){
    char c, copia[MAX_N];

    strcpy(copia, infoper[posUsuario].Nomb_usuario);

    printf("\nIntroduzca el nuevo nombre: ");
    fflush(stdin);
    fgets(infoper[posUsuario].Nomb_usuario, MAX_N, stdin);
    EliminarSaltoLinea(infoper[posUsuario].Nomb_usuario);

    printf("\nNuevo nombre: %s.\n", infoper[posUsuario].Nomb_usuario);

    printf("Desea mantener cambios? (S/n) ");
    fflush(stdin);
    scanf("%c", &c);

    do{
        if(c == 'n'){
            strcpy(infoper[posUsuario].Nomb_usuario, copia);
            puts("Se cancelaron los cambios.");
        } else if(c == 'S')
            puts("Se ha cambiado el nombre de usuario.");
        else{
            puts("Introduzca o S (Si) o N (No) ");
            fflush(stdin);
            scanf("%c", &c);
        }
    } while(c != 'S' && c != 'n');

    // Se debe llamar a una función para que cambie esos cambios también en el fichero.
}

static void CambiarLocalidad(tPerfiles *infoper, int posUsuario){
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
        } else if(c == 'S')
            puts("Se ha cambiado la localidad.");
        else{
            puts("Introduzca o S (Si) o N (No) ");
            fflush(stdin);
            scanf("%c", &c);
        }
    } while(c != 'S' && c != 'n');

    // Se debe llamar a una función para que cambie esos cambios también en el fichero.
}

static void CambiarUsuarioAcceso(tPerfiles *infoper, int posUsuario){
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
        } else if(c == 'S')
            puts("Se ha cambiado el nombre de acceso.");
        else{
            puts("Introduzca o S (Si) o N (No) ");
            fflush(stdin);
            scanf("%c", &c);
        }
    } while(c != 'S' && c != 'n');

    // Se debe llamar a una función para que cambie esos cambios también en el fichero.
}

static void CambiarContrasena(tPerfiles *infoper, int posUsuario){
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
        } else if(c == 'S')
            puts("Se ha cambiado la contrasena.");
        else{
            puts("Introduzca o S (Si) o N (No) ");
            fflush(stdin);
            scanf("%c", &c);
        }
    } while(c != 'S' && c != 'n');

    // Se debe llamar a una función para que cambie esos cambios también en el fichero.
}

static int PosicionUsuario(tPerfiles *infoper, char id[ID]){
    int i, fin = 0, npos = LongitudVectorEstructuras();

    for(i = 0; i < npos && !fin; i++){
        if(!strcmp(infoper[i].Id_usuario, id))
            fin = 1;
    }

    return i-1; // El bucle for hará que i contenga un valor más de lo que realmente buscabamos.
}
