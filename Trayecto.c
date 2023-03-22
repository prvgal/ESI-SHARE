#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "viajes.h"



void gestionar_trayecto(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n Elija una opción: \n \n   1. Agregar paradas \n   2. Modificar paradas \n   3. Borrar paradas \n   0. Cancelar \n");
        scanf("%i",&op);
        switch(op){
            case 1: inicio_trayecto();
            case 2: modificar_trayecto(viaje);
            case 3: borrar_trayecto(viaje);
            case 0: break;
        }
    }while(op!=0);
}



void inicio_trayecto(){
     int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es el punto de partida de su viaje? \n\n");
        printf("1. El viaje inicia en la ESI\n 2. El viaje finaliza en la ESI\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: inicio_ESI();
            case 2: final_ESI();
            case 0: break;
        }
    }while(op!=0);
}


void inicio_ESI(){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es su destino final? \n\n");
        printf("   1. Cádiz\n   2. Puerto Real\n   3. San Fernando\n   4. Jerez de la Frontera\n   5. Puerto se Santa María\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_cadiz(viaje);
            case 2: ESI_puertoreal(viaje);
            case 3: ESI_sanfernando(viaje);
            case 4: ESI_jerez(viaje);
            case 5: ESI_puertostamaria(viaje);
            case 0: break;
        }
    }while(op!=0);
}


void ESI_cadiz(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Eleja una de las siguientes opciones? \n\n");
        printf("   1. Ruta más corta\n   2. Ruta personalizada\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_cadiz_corta(viaje);
            case 2: ESI_cadiz_pers(viaje);
            case 0: break;
        }
    }while(op!=0);
}


void ESI_cadiz_corta(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su rura es: Puerto Real - Cádiz");
}

/*
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
*/







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
    setlocale(LC_ALL, "");
    printf("Paradas borradas correctamene \n");
}
