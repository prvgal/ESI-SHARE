#include <stdio.h>
#include "viajes.h"



void gestionar_trayecto(viajes viaje){
    int eleccion;
    do{
        void eleccion_trayecto();
        scanf("%i",&eleccion);
        switch(eleccion){
            case 1: paradas_trayecto(viaje);
            case 2: modificar_trayecto(viaje);
            case 3: borrar_trayecto(viaje);
            case 0: break;
        }
    }while(eleccion!=0);
}



void paradas_trayecto(viajes viaje){
char c,poblacion[21];
FILE* pasos;
    pasos = fopen("Pasos.txt", "w");

    do{
        printf("Introduzca una de las poblaciones de paso: \n");
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
    printf("\n Elija una opcion: \n   1. Agregar paradas \n   2. Modificar paradas \n   3. Borrar paradas \n   0. Cancelar \n");
}



void modificar_trayecto(viajes viaje){
    borrar_trayecto(viaje);
    paradas_trayecto(viaje);
}



void borrar_trayecto(viajes viaje){

    FILE *pasos, *pasosaux;
    char ID[6], linea_borrar[100], linea[100];
    int i=0;
    pasos = fopen("Pasos.txt", "r");
    pasosaux = fopen("PasosAux.txt", "w");

    while (fgets(ID, 6, pasos)!=NULL) {
        i++;
        if (ID == viaje.ID) {
            fgets(linea, 100, pasos);
            strcpy(linea_borrar, linea);
        } else {
            fputs(linea, pasosaux);
        }
    }

    fclose(pasos);
    fclose(pasosaux);

    remove("Pasos.txt");
    rename("PasosAux.txt", "Pasos.txt");

    printf("Paradas borradas correctamene \n");
}
