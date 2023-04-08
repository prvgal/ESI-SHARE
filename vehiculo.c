
                /* Módulo Vehículos - Contiene toda la información referente al vehículo de cada usuario, si lo tiene.
                            Todos los datos pertinentes serán almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "vehiculo.h"
#include "tipos.h"

   void cambiar_datos_veh(vehiculo_inf vehiculo, FILE *veh_txt){
        int opcion, i=0;
        logico dato_camb=0;

        do{
        	system("cls");
       		printf("\n¿Desea cambiar algún dato?\n\n");
        	printf("   *) Matricula - 1\n   *) Número de plazas - 2\n   *)Descripción del vehículo - 3\n   *) Salir - 0\n\n");
        	if(scanf("%d",&opcion)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada válida, prueba con otra.\n");
        		opcion=-1;
        		i++; 
				if(i>5) 
					printf("\nVenga va, tú puedes, que no es tan complicado: pulsa 1, 2, 3 o 0 según lo que necesites.\n");
			}	
			else{
				switch(opcion){
               		case 1: pedir_matricula(vehiculo.id_mat); dato_camb=True; break;
               		case 2: pedir_plazas_veh(vehiculo.num_plazas); dato_camb=True; break;
               		case 3: inserta_descripcion(vehiculo.desc_veh); dato_camb=True; break;
               		case 0: break;
               		default: printf("\nPor favor, introduzca un número válido.\n"); i++; if(i>5) printf("\nVenga va, tú puedes, que no es tan complicado: pulsa 1, 2, 3 o 0 según lo que necesites."); break;
           		}
			}   
		}while(opcion!=0);     			
        if(dato_camb==True)
        	escribir_fichero(vehiculo, veh_txt);
    }

    void introducir_datos_veh(vehiculo_inf vehiculo, FILE *veh_txt){
		int i;
		
    	printf("Rellene el formulario a continuación, por favor: \n");
    	
    	printf("		*) Matrícula: ");
    	do{
    		printf("\n		- La matrícula debe ser española (formato 0000AAA) - ");
    		fflush(stdin);
    		gets(vehiculo.id_mat);
    		i=comprobar_validez_mat(vehiculo.id_mat);
		}while(i!=1);
		
    	printf("\n		*) Número de plazas del vehículo (sin contar el conductor): ");
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

	void escribir_fichero(vehiculo_inf vehiculo, FILE *veh_txt){
        char guion[2]={'-','\0'};
		int i;
		
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

	void leer_fichero_vehiculo(vehiculo_inf vehiculo[LONGVEC], FILE *veh_txt){
		int i;
		char buf[1024];

		if((veh_txt=fopen("vehiculo.txt","r"))==NULL){
  	      	printf("Error al guardar la información");
		}

		else{
			for(i=0;i<LONGVEC;i++){
				if(fgets(buf, 1024, veh_txt)!=NULL){
					buf[strcspn(buf,"\n")]='\0';
					sscanf(buf,"%[^-]-%[^-]-%d-%[^\0]",vehiculo[i].id_mat, vehiculo[i].id_usuario, &vehiculo[i].num_plazas, vehiculo[i].desc_veh);
				}
			}
		}
		fclose(veh_txt);
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

	static void acortar_cadena(char cadena[]){
		int i;
		for(i=0;i<strlen(cadena);i++){
    			if(cadena[i]=='\n')
    				cadena[i]='\0';
			}
	}
	
	static void pedir_plazas_veh(int plazas){
    	plazas=-1;
		while(plazas<1||plazas>9){
			printf("Indica el número total de plazas de las que dispone el vehículo sin el conductor (introduzca un número realista): ");
        	scanf("%i",&plazas);
		}
    }

	static int comprobar_validez_mat(char matricula[]){
		int i;
		
		if(strlen(matricula)!=IDMAT-1){
			return 0;
		}

		for(i=0;i<IDMAT-1;i++){
			if(i<4){
				if(matricula[i]!='1'&&matricula[i]!='2'&&matricula[i]!='3'&&matricula[i]!='4'&&matricula[i]!='5'&&matricula[i]!='6'&&matricula[i]!='7'&&matricula[i]!='8'
				&&matricula[i]!='9'&&matricula[i]!='0'){
					return 0;
				}		
			}
			else{
				if(matricula[i]!='A'&&matricula[i]!='B'&&matricula[i]!='C'&&matricula[i]!='D'&&matricula[i]!='E'&&matricula[i]!='F'&&matricula[i]!='G'&&matricula[i]!='H'&&matricula[i]!='I'&&matricula[i]!='J'
				&&matricula[i]!='K'&&matricula[i]!='L'&&matricula[i]!='M'&&matricula[i]!='N'&&matricula[i]!='O'&&matricula[i]!='P'&&matricula[i]!='Q'&&matricula[i]!='R'&&matricula[i]!='S'&&matricula[i]!='T'
				&&matricula[i]!='U'&&matricula[i]!='V'&&matricula[i]!='W'&&matricula[i]!='X'&&matricula[i]!='Y'&&matricula[i]!='Z'){
					return 0;
				}
				return 1;
			}
		}		
	
	}

	static void pedir_matricula(char *matricula){
        int i;

        printf("Indica la matrícula de tu vehículo: ");
        fflush(stdin);
        gets(matricula);
        do{
    		printf("Por favor, introduce una matrícula española válida (sin espacios): ");
            fflush(stdin);
            gets(matricula);
            i=comprobar_validez_mat(matricula);
		}while(i!=1);
    }
