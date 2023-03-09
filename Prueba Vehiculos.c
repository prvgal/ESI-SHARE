
                /* M�dulo Veh�culos - Contiene toda la informaci�n referente al veh�culo de cada usuario, si lo tiene.
                            Todos los datos pertinentes ser�n almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define CARACTERES 51
#define IDMAT 8

    //vehiculo_inf - Registro que almacena toda la informaci�n pertinente a un veh�culo.
    typedef struct{
        char id_mat[IDMAT];
        int id_usuario;
        int num_plazas;
        char desc_veh[CARACTERES];
    }vehiculo_inf;

    FILE veh_txt;

    //Declaraci�n de funciones
    void cambiar_datos(vehiculo_inf);
    void pedir_matricula(char *);
    void pedir_plazas_veh(int);
    void inserta_descripcion(char *);


    //Precondici�n: El usuario habr� creado su propia cuenta, de manera el dato l�gico "tienecoche" es igual a 1.
    //Postcondici�n: El usuario habr� cambiado alg�n dato acerca de su veh�culo.
    void cambiar_datos(vehiculo_inf vehiculo){
        int opcion=-1;

        do{
        printf("�Desea cambiar alg�n dato?\n\n");
        printf("   *) Matricula - 1\n   *) N�mero de plazas - 2\n   *)Descripci�n del veh�culo - 3\n   *) Salir - 0\n");
        scanf("%d",&opcion);
            switch(opcion){
                case '1': pedir_matricula(vehiculo.id_mat); break;
                case '2': pedir_plazas_veh(vehiculo.num_plazas); break;
                case '3': inserta_descripcion(vehiculo.desc_veh); break;
                case '0': break;
            }
        }while(opcion!=0);
    }

    //Precondici�n: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la informaci�n del veh�culo.
    //Postcondici�n: La cadena vehiculo.matricula tendr� una matr�cula guardada.
    void pedir_matricula(char matricula[IDMAT]){
        int i;

        printf("Indica la matr�cula de tu veh�culo (formato 1234AAA): ");
        gets(matricula);
        for(i=0;i<8;i++){
            if(matricula[i]==' '||matricula[i]=='-'){
                printf("Por favor, introduce una matr�cula espa�ola v�lida (recuerda que no debe haber espacios al escribirla): ");
                fflush(stdin);
                gets(matricula);
                i=0;
            }
        }
        fflush(stdin);
    }

    //Precondici�n: Recibe la variable entera num_plazas, con lo que debe estar habilitada la informaci�n del veh�culo.
    //Postcondicion: El entero vehiculo.num_plazas ser� un n�mero entre 0 y 10.
    void pedir_plazas_veh(int plazas){

        printf("Indica el n�mero total de plazas de las que dispone el veh�culo: ");
        scanf("%i",&plazas);
        while(plazas>=10){
            printf("Por favor, escribe un n�mero v�lido de plazas de coche/furgoneta/etc... - ");
            scanf("%d",&plazas);
        }
    }

    //Precondici�n: Debe estar habilitada la informaci�n del veh�culo, concretamente el campo "desc_veh".
    //Postcondici�n: El usuario habr� introducido una breve descripci�n acerca de su veh�culo.
    void inserta_descripcion(char descripcion[CARACTERES]){

        printf("Escribe una peque�a descripci�n de tu veh�culo - color, alg�n detalle que veas importante, etc...");
        fflush(stdin);
        gets(descripcion);
    }

    //****************************************************************************************************************//
    void main(){
        vehiculo_inf v;
        cambiar_datos(v);
    }
    //****************************************************************************************************************//


