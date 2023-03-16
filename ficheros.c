#include "ficheros.h"

#include <stdio.h>

int LongitudVectorEstructuras(){
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
