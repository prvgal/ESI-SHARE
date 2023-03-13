#include "perfiles.h"

#include <stdio.h>
#include <stdlib.h>
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

void ModificarCampo(tPerfiles *infoper){
    int op;
    

    puts("Que campo desea modificar? ");

    do{
        printf("\n<1> Nombre de usuario. <2> Localidad. <3> Usuario de acceso. <4> Contrasena.");
        scanf("%i", &op);

        if(op < 1 || op > 4)
            puts("Por favor, introduzca uno de los campos mencionados.");
    } while(op < 1 || op > 4);

    switch(op){
        case 1: CambiarNombre(); break;
        case 2: CambiarLocalidad(); break;
        case 3: CambiarUsuarioAcceso(); break;
        case 4: CambiarContrasena(); break;
    }
}

// void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles)


/* Funciones NO exportables */

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
