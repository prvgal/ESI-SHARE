
                /* Módulo Vehículos - Contiene toda la información referente al vehículo de cada usuario, si lo tiene.
                            Todos los datos pertinentes serán almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <string.h>
#include "vehiculo.h"

int main(){		//main provisional
	return 0;
}

   void cambiar_datos(vehiculo_inf vehiculo, FILE *veh_txt){
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
        escribir_fichero(vehiculo, veh_txt);
    }
    
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

    void pedir_plazas_veh(int plazas){

        printf("Indica el número total de plazas de las que dispone el vehículo: ");
        scanf("%i",&plazas);
        while(plazas>9||plazas<1){
            printf("Por favor, escribe un número válido de plazas de coche/furgoneta/etc... - ");
            scanf("%d",&plazas);
        }
    }

    void inserta_descripcion(char descripcion[CARACTERES]){

        printf("Escribe una pequeña descripción de tu vehículo (recuerda, 50 caracteres máximo) - marca, modelo, color, etc...");
        fflush(stdin);
        gets(descripcion);
        while(strlen(descripcion)>50){
    		printf("Introduzca una descripción más corta (o ninguna)");
    		fflush(stdin);
    		gets(descripcion);
		}
    }
    
    void introducir_datos(vehiculo_inf vehiculo, FILE *veh_txt){
    	int i, num_car;
    	
    	printf("Rellene el formulario a continuación, por favor: \n");
    	printf("		*) Matrícula: ");
    	do{
    		printf("		- La matrícula debe ser española (formato 0000AAA) -");
    		fflush(stdin);
    		gets(vehiculo.id_mat);
		}while(strlen(vehiculo.id_mat)>=8);
    
    	printf("\n		*) Número de plazas: ");
    	scanf("%d", vehiculo.num_plazas);
    	while(vehiculo.num_plazas>9){
    		printf("\n		Introduzca un número realista de plazas (0-9):");
    		scanf("%d", vehiculo.num_plazas);
		}
    
		printf("\n		*) Una breve descripción de tu coche (color, modelo y marca, etc... - máx. 50 caracteres): ");
		fflush(stdin);
    	gets(vehiculo.desc_veh);
    	while(strlen(vehiculo.desc_veh)>50){
    		printf("\n		Introduzca una descripción más corta (o ninguna)");
    		fflush(stdin);
    		gets(vehiculo.desc_veh);
		}
		//escribir_fichero(vehiculo, veh_txt);
	}
	
	void escribir_fichero(vehiculo_inf vehiculo, FILE *veh_txt){
        char guion[2]={'-','\0'};
        
        if((veh_txt=fopen("vehiculo.txt","w+"))==NULL){
        	printf("Error al guardar la información");
        	exit(1);
			}
		else{
           		fwrite(vehiculo.id_mat, sizeof(char), 7, veh_txt);
           		fwrite(guion,sizeof(char),1,veh_txt);
           		fwrite(vehiculo.id_usuario, sizeof(char), 4, veh_txt);
				fwrite(guion, sizeof(char),1,veh_txt);
				fprintf(veh_txt,"%i",vehiculo.num_plazas);
				fwrite(guion, sizeof(char),1,veh_txt);
				fwrite(vehiculo.desc_veh, sizeof(char), 50, veh_txt);
			}
     	fclose(veh_txt);
		}



