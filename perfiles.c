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
    ReservarPerfil(infoper);

    unsigned int numPerfiles = LongitudVectorEstructuras(infoper);

    
}

// void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles)


/* Funciones NO exportables */

static void GenerarID(tPerfiles *infoper, char id[ID]){
    unsigned int ID_usuario = LongitudVectorEstructuras(infoper) + 1;
    int i = ID-1, temp1 = ID_usuario, temp2 = ID_usuario;     // temp1 contendrá la parte decimal y temp2 la parte entera
    
    for(; i >= 0; i--){
        temp2 %= 10;
        id[i] = temp2;
        temp1 = (unsigned int)floor(temp1/10);
        temp2 = temp1;
    } 
}

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

    rewind(fich);
    fclose(fich);

    return i;
}

/*static unsigned int LongitudVectorEstructuras(tPerfiles *infoper){
    unsigned int tamTotal, tamPrimerElem, longVec;

    tamTotal = sizeof(infoper);             // Numero de bytes que ocupa el vector.
    printf("%u\n", tamTotal);
    tamPrimerElem = sizeof(tPerfiles);     // Numero de bytes que ocupa el primer elemento del vector.
    printf("%u\n", tamPrimerElem);
    longVec = tamTotal/tamPrimerElem;       // Longitud del vector.
    printf("%u", longVec);

    return longVec;
}*/

static unsigned int NumeroDigitos(unsigned int num){
    unsigned int i = 0;

    while(num > 0){
        num /= 10;
        i++;
    }

    return i;
}
