#include <stdio.h>
#include "viajes.h"

void paradas(viajes viaje){
char c,poblacion[21];
FILE* pasos;
   pasos = fopen("Pasos.txt", "w");

    do{
        printf("Introduce una de las poblaciones de paso: \n");
        fflush(stdin);
        fgets(poblacion, 21, stdin);
        if (pasos != NULL) {
            fprintf(pasos,"%i-%c",viaje.ID,poblacion);
            fclose(pasos);
   }

        printf("¿Quiere añadir una nueva población? (s/n) \n");
        fflush(stdin);
        scanf("%c",c);
}while(c=='S'||c=='s');
}
