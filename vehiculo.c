
                /* Módulo Vehículos - Contiene toda la información referente al vehículo de cada usuario, si lo tiene.
                            Todos los datos pertinentes serán almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <string.h>
#include "vehiculo.h"
#include "tipos.h"

	int main(){
		FILE *f;
		vehiculo_inf vehiculo[3];
		
		leer_fichero_vehiculo(vehiculo,f);
		return 0;
	}

   void cambiar_datos(vehiculo_inf vehiculo, FILE *veh_txt){
        int opcion=-1;

        do{
        printf("¿Desea cambiar algún dato?\n\n");
        printf("   *) Matricula - 1\n   *) Número de plazas - 2\n   *)Descripción del vehículo - 3\n   *) Salir - 0\n\n");
        scanf("%d",&opcion);
            switch(opcion){
                case 1: pedir_matricula(vehiculo.id_mat); break;
                case 2: pedir_plazas_veh(vehiculo.num_plazas); break;
                case 3: inserta_descripcion(vehiculo.desc_veh); break;
                case 0: break;
            }
        }while(opcion!=0);
        escribir_fichero(vehiculo, veh_txt);
    }

    static void pedir_matricula(char matricula[IDMAT]){
        int i;

        printf("Indica la matrícula de tu vehículo: ");
        fflush(stdin);
        gets(matricula);
        for(i=0;i<8;i++){
            if(matricula[i]==' '||matricula[i]=='-'){
                printf("Por favor, introduce una matrícula española válida (recuerda que no debe haber espacios al escribirla): ");
                fflush(stdin);
                gets(matricula);
            }
        }
        fflush(stdin);
    }

    static void pedir_plazas_veh(int plazas){
    	plazas=-1;
		while(plazas<1||plazas>9){
			printf("Indica el número total de plazas de las que dispone el vehículo (introduzca un número realista): ");
        	scanf("%i",&plazas);
		}
    }

    static void inserta_descripcion(char descripcion[CARACTERES]){

        printf("Escribe una pequeña descripción de tu vehículo (recuerda, 50 caracteres máximo) - marca, modelo, color, etc...");
        fflush(stdin);
        gets(descripcion);
        while(strlen(descripcion)>50){
    		printf("Introduzca una descripción más corta (o ninguna)");
    		fflush(stdin);
    		gets(descripcion);
		}
		acortar_cadena(descripcion);
    }

    void introducir_datos(vehiculo_inf vehiculo, FILE *veh_txt){
    	int i, num_car;

    	printf("Rellene el formulario a continuación, por favor: \n");
    	printf("		*) Matrícula: ");
    	do{
    		printf("\n		- La matrícula debe ser española (formato 0000AAA) - ");
    		fflush(stdin);
    		gets(vehiculo.id_mat);
		}while(strlen(vehiculo.id_mat)>=8||strlen(vehiculo.id_mat)<7);

    	printf("\n		*) Número de plazas disponibles (sin contar el conductor): ");
    	scanf("%i", &vehiculo.num_plazas);
    	while(vehiculo.num_plazas>9||vehiculo.num_plazas<2){
    		printf("\n		Introduzca un número realista de plazas (2-9):");
    		scanf("%i", &vehiculo.num_plazas);
		}

		printf("\n		*) Si deseas, incluye una breve descripción de tu coche (color, modelo y marca, etc... - máx. 50 caracteres): ");
		fflush(stdin);
    	gets(vehiculo.desc_veh);
    	while(strlen(vehiculo.desc_veh)>50){
    		printf("\n		Introduzca una descripción más corta (o ninguna)");
    		fflush(stdin);
    		gets(vehiculo.desc_veh);
		}
		acortar_cadena(vehiculo.desc_veh);
		escribir_fichero(vehiculo, veh_txt);
	}

	static void acortar_cadena(char cadena[]){
		int i,longitud;
		for(i=0;i<strlen(cadena);i++){
    			if(cadena[i]=='\n')
    				cadena[i]=='\0';
			}
	}

	void escribir_fichero(vehiculo_inf vehiculo, FILE *veh_txt){
        char guion[2]={'-','\0'};

        if((veh_txt=fopen("vehiculo.txt","a+"))==NULL){
        	printf("Error al guardar la información");
			}
		else{
           		fwrite(vehiculo.id_mat, sizeof(char), 7, veh_txt);
           		fflush(veh_txt);
           		fwrite(guion,sizeof(char),1,veh_txt);
           		fflush(veh_txt);
           		fwrite(vehiculo.id_usuario, sizeof(char), 4, veh_txt);
           		fflush(veh_txt);
				fwrite(guion, sizeof(char),1,veh_txt);
				fflush(veh_txt);
				fprintf(veh_txt,"%i",vehiculo.num_plazas);
				fflush(veh_txt);
				fwrite(guion, sizeof(char),1,veh_txt);
				fflush(veh_txt);
				fwrite(vehiculo.desc_veh, sizeof(char), strlen(vehiculo.desc_veh), veh_txt);
				fflush(veh_txt);
				fprintf(veh_txt,"\n");
			}
	     	fclose(veh_txt);
		}

	void leer_fichero_vehiculo(vehiculo_inf vehiculo[5], FILE *veh_txt){
		int i;

		if((veh_txt=fopen("vehiculo.txt","r"))==NULL){
  	      	printf("Error al guardar la información");
		}

		else{
			for(i=0;i<1;i++){
				fscanf(veh_txt,"%[^-]-%[^-]-%[^-]-%[^\n]",vehiculo[i].id_mat, vehiculo[i].id_usuario, vehiculo[i].num_plazas, vehiculo[i].desc_veh);
				printf("\nRegistro: %s - %s - %d - %s",vehiculo[i].id_mat, vehiculo[i].id_usuario, vehiculo[i].num_plazas, vehiculo[i].desc_veh);
			}
		}
		fclose(veh_txt);
	}	