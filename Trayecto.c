#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "viajes.h"
#include "Trayecto.h"


void gestionar_trayecto(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n Elija una opción: \n \n   1. Agregar paradas \n   2. Modificar paradas \n   3. Borrar paradas \n   0. Cancelar \n");
        scanf("%i",&op);
        switch(op){
            case 1: inicio_trayecto(viaje);
            case 2: modificar_trayecto(viaje);
            case 3: borrar_trayecto(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void inicio_trayecto(viajes viaje){
     int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es el punto de partida de su viaje? \n\n");
        printf("1. El viaje inicia en la ESI\n 2. El viaje finaliza en la ESI\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: inicio_ESI(viaje);
            case 2: final_ESI(viaje);
            case 0: break;
        }
    }while(op!=0);
}


static void final_ESI(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es el punto de partida de su viaje? \n\n");
        printf("1. Cádiz\n 2. San Fernando\n 3. Jerez\n 4. Puerto de Santa María\n 5. Puerto Real\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_cadiz(viaje);
            case 2: ida_ESI_sanfer(viaje);
            case 3: ida_ESI_jerez(viaje);
            case 4: ida_ESI_puerto(viaje);
            case 5: ida_ESI_puertor(viaje);
            case 0: break;
        }
    }while(op!=0);
}


static void ida_ESI_cadiz(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es la siguiente parada de su viaje? \n\n");
        printf("1. Puerto Real\n 2. Fin\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_cadiz_puertor(viaje);
            case 2: ida_ESI_cadiz_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ida_ESI_cadiz_puertor(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Cádiz - Puerto Real - ESI\n");
}



static void ida_ESI_cadiz_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Cádiz\n");
}


static void ida_ESI_sanfer(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es la siguiente parada de su viaje? \n\n");
        printf("1. Cádiz\n 2. Puerto Real\n 3. Fin\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_sanfer_cadiz(viaje);
            case 2: ida_ESI_sanfer_puertor(viaje);
            case 3: ida_ESI_sanfer_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ida_ESI_sanfer_cadiz(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es la siguiente parada de su viaje? \n\n");
        printf("1. Puerto Real\n 2. Fin\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_sanfer_cadiz_puertor(viaje);
            case 2: ida_ESI_sanfer_cadiz_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ida_ESI_sanfer_cadiz_puertor(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: San Fernando - Cádiz - Puerto Real - ESI\n");
}



static void ida_ESI_sanfer_cadiz_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: San Fernando - Cádiz - ESI\n");
}



static void ida_ESI_sanfer_puertor(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: San Fernando - Puerto Real - ESI\n");
}



static void ida_ESI_sanfer_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: San Fernando - ESI\n");
}



static void ida_ESI_jerez(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es la siguiente parada de su viaje? \n\n");
        printf("1. Puerto de Santa María\n 2. Puerto Real\n 3. Fin\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_jerez_puerto(viaje);
            case 2: ida_ESI_jerez_puertor(viaje);
            case 3: ida_ESI_jerez_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ida_ESI_jerez_puerto(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es la siguiente parada de su viaje? \n\n");
        printf("1. Puerto Real\n 2. Fin\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_jerez_puerto_puertor_fin(viaje);
            case 2: ida_ESI_jerez_puertor_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ida_ESI_jerez_puerto_puertor_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Jerez - Puerto de Santa María - Puerto Real - ESI\n");
}




static void ida_ESI_jerez_puertor_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Jerez - Puerto de Santa María - ESI\n");
}



static void ida_ESI_jerez_puertor(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Jerez - Puerto Real - ESI\n");
}



static void ida_ESI_jerez_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Jerez - ESI\n");
}



static void ida_ESI_puerto(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es la siguiente parada de su viaje? \n\n");
        printf("1. Puerto Real\n 2. Fin\n 0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ida_ESI_puerto_puertor_fin(viaje);
            case 2: ida_ESI_puerto_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ida_ESI_puerto_puertor_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Puerto de Santa María - Puerto Real - ESI\n");
}



static void ida_ESI_puerto_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Puerto de Santa María - ESI\n");
}



static void ida_ESI_puertor(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: Puerto Real - ESI\n");
}

static void inicio_ESI(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál es su destino final? \n\n");
        printf("   1. Cádiz\n   2. Puerto Real\n   3. San Fernando\n   4. Jerez de la Frontera\n   5. Puerto de Santa María\n   0. Cancelar\n");
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


static void ESI_cadiz(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál será su siguiente parada? \n\n");
        printf("   1. Puerto Real\n   2. Fin\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_cadiz_puertor(viaje);
            case 2: ESI_cadiz_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}


static void ESI_cadiz_puertor(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real - Cádiz\n");
}



static void ESI_cadiz_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Cádiz\n");
}



static void ESI_puertoreal(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real\n");
}



static void ESI_sanfernando(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál será su siguiente parada? \n\n");
        printf("   1. Puerto Real\n   2. Cádiz\n   3. Fin\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_sanfer_puertor(viaje);
            case 2: ESI_sanfer_cadiz(viaje);
            case 3: ESI_sanfer_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ESI_sanfer_cadiz(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Cádiz - San Fernando\n");
}



static void ESI_sanfer_puertor(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál será su siguiente parada? \n\n");
        printf("   1. Cádiz\n   2. Fin\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_sanfer_cadiz_puerto(viaje);
            case 2: ESI_sanfer_puertor_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ESI_sanfer_cadiz_puerto(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Cádiz\n",viaje.ID);
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real - Cádiz - San Fernando\n");
}


static void ESI_sanfer_puertor_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real - San Fernando\n");
}



static void ESI_sanfer_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-San Fernando\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - San Fernando\n");
}


static void ESI_jerez(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál será su siguiente parada? \n\n");
        printf("   1. Puerto Real\n   2. Puerto de Santa María\n   3. Fin\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_jerez_puertor(viaje);
            case 2: ESI_jerez_puerto(viaje);
            case 3: ESI_jerez_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ESI_jerez_puertor(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál será su siguiente parada? \n\n");
        printf("   1. Puerto de Santa María\n   2. Fin\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_jerez_puertor_puerto_fin(viaje);
            case 2: ESI_jerez_puertor_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ESI_jerez_puertor_puerto_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real - Puerto de Santa María - Jerez\n");
}



static void ESI_jerez_puertor_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real - Jerez\n");
}




static void ESI_jerez_puerto(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto de Santa María - Jerez\n");
}



static ESI_jerez_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Jerez\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Jerez\n");
}



static void ESI_puertostamaria(viajes viaje){
    int op;
    do{
        setlocale(LC_ALL, "");
        printf("\n ¿Cuál será su siguiente parada? \n\n");
        printf("   1. Puerto de Santa María\n   2. Fin\n   0. Cancelar\n");
        scanf("%i",&op);
        switch(op){
            case 1: ESI_puerto_puertor_fin(viaje);
            case 2: ESI_puerto_fin(viaje);
            case 0: break;
        }
    }while(op!=0);
}



static void ESI_puerto_puertor_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fprintf(pasos,"%i-Puerto Real\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto Real - Puerto de Santa María\n");
}



static void ESI_puerto_fin(viajes viaje){
    FILE* pasos;
    pasos = fopen("Pasos.txt", "w");
    if (pasos != NULL) {
            fprintf(pasos,"%i-Puerto de Santa María\n",viaje.ID);
            fclose(pasos);
   }
   setlocale(LC_ALL, "");
   printf("Su ruta es: ESI - Puerto de Santa María\n");
}



static void modificar_trayecto(viajes viaje){
    borrar_trayecto(viaje);
    inicio_trayecto(viaje);
}



static void borrar_trayecto(viajes viaje){

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
