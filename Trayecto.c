#include <stdio.h>
#include "viajes.h"



void gestionar_trayecto(viajes viaje){
    int e;
    do{
        void eleccion_trayecto();
        scanf("%i",&e);
        switch(e){
            case 1: paradas_trayecto(viaje);
            case 2: modificar_trayecto(viaje);
            case 3: borrar_trayecto(viaje);
            case 0: break;
        }
    }while(e!=0);
}



void paradas_trayecto(viajes viaje){
char c,poblacion[21];
FILE* pasos;
   pasos = fopen("Pasos.txt", "w");

    do{
        printf("Introduce una de las poblaciones de paso: \n");
        fflush(stdin);
        fgets(poblacion, 21, stdin);
        if (pasos != NULL) {
            fprintf(pasos,"%i-%c \n",viaje.ID,poblacion);
            fclose(pasos);
   }

        printf("¿Quiere añadir una nueva población? (s/n) \n");
        fflush(stdin);
        scanf("%c",c);
}while(c=='S'||c=='s');
}

void eleccion_trayecto(){
    printf("Elija una opcion: \n   1. Agregar paradas \n   2. Modificar paradas \n   3. Borrar paradas \n   0. Cancelar \n")
}



void modificar_trayecto(viajes viaje){
}



void borrar_trayecto(viajes viaje){
}
