#include <stdio.h>
#include "perfiles.h"
#include <string.h>

/* Funciones públicas */

void LeerFicheroEnEstructura(tPerfiles *infoper, unsigned int numPerfiles){
    int i;
    FILE *f;

    f = fopen("Usuarios.txt", "r");

    if(f == NULL){
        fprintf(stderr, "Error en la apertura de ficheros.");
        exit(1);
    }

    for(i = 0; i < numPerfiles; i++){
        //Primer campo de la estructura
        fread()
    }
    
}


/* Funciones NO exportables */

static unsigned int NumeroDigitos(unsigned int num){
    int i = 0;

    while(num > 0){
        num /= 10;
        i++;
    }

    return i;
}