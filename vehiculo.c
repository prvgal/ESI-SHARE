
                /* Módulo Vehículos - Contiene toda la información referente al vehículo de cada usuario, si lo tiene.
                            Todos los datos pertinentes serán almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "vehiculo.h"
#define CARACTERES 51
#define IDMAT 8

    //vehiculo_inf - Registro que almacena toda la información pertinente a un vehículo.
    typedef struct{
        char id_mat[IDMAT];
        int id_usuario;
        int num_plazas;
        char desc_veh[CARACTERES];
    }vehiculo_inf;

    FILE veh_txt;

    //Declaración de funciones
    void cambiar_datos(vehiculo_inf);
    void pedir_matricula(char *);
    void pedir_plazas_veh(int);
    void inserta_descripcion(char *);


    //Precondición: El usuario habrá creado su propia cuenta, de manera el dato lógico "tienecoche" es igual a 1.
    //Postcondición: El usuario habrá cambiado algún dato acerca de su vehículo.
    void cambiar_datos(vehiculo_inf vehiculo){
        int opcion=-1;

        do{
        printf("¿Desea cambiar algún dato?\n\n");
        printf("   *) Matricula - 1\n   *) Número de plazas - 2\n   *)Descripción del vehículo - 3\n   *) Salir - 0\n");
        scanf("%d",&opcion);
            switch(opcion){
                case '1': pedir_matricula(vehiculo.id_mat); break;
                case '2': pedir_plazas_veh(vehiculo.num_plazas); break;
                case '3': inserta_descripcion(vehiculo.desc_veh); break;
                case '0': break;
            }
        }while(opcion!=0);
    }

    //Precondición: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la información del vehículo.
    //Postcondición: La cadena vehiculo.matricula tendrá una matrícula guardada.
    void pedir_matricula(char matricula[IDMAT]){
        int i;

        printf("Indica la matrícula de tu vehículo (formato 1234AAA): ");
        gets(matricula);
        for(i=0;i<8;i++){
            if(matricula[i]==' '||matricula[i]=='-'){
                printf("Por favor, introduce una matrícula española válida (recuerda que no debe haber espacios al escribirla): ");
                fflush(stdin);
                gets(matricula);
                i=0;
            }
        }
        fflush(stdin);
    }

    //Precondición: Recibe la variable entera num_plazas, con lo que debe estar habilitada la información del vehículo.
    //Postcondicion: El entero vehiculo.num_plazas será un número entre 0 y 10.
    void pedir_plazas_veh(int plazas){

        printf("Indica el número total de plazas de las que dispone el vehículo: ");
        scanf("%i",&plazas);
        while(plazas>=10){
            printf("Por favor, escribe un número válido de plazas de coche/furgoneta/etc... - ");
            scanf("%d",&plazas);
        }
    }

    //Precondición: Debe estar habilitada la información del vehículo, concretamente el campo "desc_veh".
    //Postcondición: El usuario habrá introducido una breve descripción acerca de su vehículo.
    void inserta_descripcion(char descripcion[CARACTERES]){

        printf("Escribe una pequeña descripción de tu vehículo - color, algún detalle que veas importante, etc...");
        fflush(stdin);
        gets(descripcion);
    }

    //****************************************************************************************************************//
    void main(){
        vehiculo_inf v;
        cambiar_datos(v);
    }
    //****************************************************************************************************************//


