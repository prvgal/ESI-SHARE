
                /* Módulo Vehículos - Contiene toda la información referente al vehículo de cada usuario, si lo tiene.
                            Todos los datos pertinentes serán almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "vehiculo.h"
#include "tipos.h"
#include "perfiles.h"

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

    void introducir_datos_veh(vehiculo_inf vehiculo, tPerfiles usu){
		int i;
		FILE *veh_txt;
		
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

	int comprobar_validez_id(char ID[]){
		int i;
		
		if (strlen(ID)!=IDUSU)
			return 0;
		for(i=0;i++;i<IDUSU){
			if(vehiculo.id_usuario[i]!=1&&vehiculo.id_usuario[i]!=2&&vehiculo.id_usuario[i]!=3&&vehiculo.id_usuario[i]!=4&&
				vehiculo.id_usuario[i]!=5&&vehiculo.id_usuario[i]!=6&&vehiculo.id_usuario[i]!=7&&vehiculo.id_usuario[i]!=8&&
				vehiculo.id_usuario[i]!=9&&vehiculo.id_usuario[i]!=0)
				return 0;
		}
		return 1;
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
    
    void menu_registro_vehiculo(tPerfiles usuario){
		vehiculo_inf veh;
		int S_N;
		
		do{
			printf("¿Tiene planeado llevar a gente en coche?\n \n<1>Sí\n<2> No\n\n");
			if(scanf("%i",&S_N)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada válida");
				S_N=-1;
			}
			else{
				switch(S_N){
					case 1: introducir_datos_veh(veh, usuario); 
					case 2: break;
					default: printf("\nIntroduzca 1 o 2 según tenga coche y vaya a traer y llevar gente de la ESI"); break;
				}
			}
		}while(S_N!=1&&S_N!=2);
	}

	void admin_veh(tPerfiles usu){
		int op,i=0;
		
		do{
			printf("¿Qué desea hacer?\n <1> Dar un vehículo de alta.\n <2> Dar un vehículo de baja.\n <3> Lista de vehículos\n <4> Modificar vehículo.\n <0> Salir.");
			if(scanf("%i",&op)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada válida.");
				op=-1;
			}
			else{
				switch(op){
					case 1: alta_vehiculo(); break;
					case 2: baja_vehiculo_admin(); break;
					case 3: break;
					case 4: break;
					case 0: exit(1); break;
					default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 según lo que necesites.\n"); break;
				}
			}
		}while(op!=1&&op!=2&&op!=3&&op!=4);
	}
	
	void usuario_veh(){
		
		
	}
	
	static void alta_vehiculo(){
		vehiculo_inf veh;
		char ID[IDUSU];
	
		do{
			printf("\n\nIntroduzca la ID a la que pertenecerá el vehículo: ");
			gets(ID);
			if(comprobar_validez_id(ID)==0)
				printf("\nIntroduzca una ID válida.");
		}while(comprobar_validez_id(ID)!=1);
		
		strcpy(veh.id_usuario,ID);
		introducir_datos_veh(veh);
	}
	
	static void baja_vehiculo_admin(vehiculo_inf *vehiculo){
		FILE *pf; 
    	char mat[IDMAT];
    	int i, j, pos, tamOriginal = LongitudVectorEstructurasVehiculo(); 

	    printf("\n####################################################################\n");
	    printf("#          Configuracion del Sistema de Bajas de Vehículo            #\n");
	    printf("####################################################################\n\n");
	    
	    Listar_vehiculos(vehiculo);
	
	    pf = fopen("vehiculo.txt", "w");
	
	    fclose(pf);  // Elminamos su contenido
	
	    pf = fopen("vehiculo.txt", "a");
	
	    if(pf == NULL){
	        fprintf(stderr, "Error en la apertura de archivos.");
	        exit(1);
	    }
	    
	    do{
	        printf("\nIndique la ID del usuario que desea dar de baja: ");
	        fflush(stdin);
	        fgets(id, ID, stdin);
	        
	        if(!ValidarID(vehiculo, id, &pos, tamOriginal))
	            fprintf(stderr, "La ID no se encuentra disponible.\n");
	        
	        for(i = 0; i < tamOriginal; i++){
	
	                for(j = 0; j < tamOriginal; j++){
	                    if(j+1 == tamOriginal)
	                        fprintf(pf, "%s-%s-%i-%s", vehiculo[i].id_mat, vehiculo[i].id_usuario, vehiculo[i].num_plazas, vehiculo[i].desc_veh);
	                    else
	                        fprintf(pf, "%s-%s-%i-%s", vehiculo[i].id_mat, vehiculo[i].id_usuario, vehiculo[i].num_plazas, vehiculo[i].desc_veh);
	
	                    }
	                exit(1);
	            }
	        }
	
	    } while(!validar_id_veh(vehiculo, id, &pos, tamOriginal));
	
	    system("cls");
	
	    for(; pos < tamOriginal-1; pos++)
	        vehiculo[pos]= vehiculo[pos+1];
	
	    infoper = (vehiculo_inf *)realloc(vehiculo, (tamOriginal-1)*sizeof(vehiculo_inf));
	
	    if( == NULL){
	        printf("Error en asignacion de memoria");
	        exit(1);
	    }
	
	    // Regeneramos las IDs
	    for(i = 0; i < tamOriginal-1; i++)
	        GenerarID(vhiculo[i].id_usuario, i+1, ID-1);    
	   
	    // Reescribimos el archivo.
	    for(i = 0; i < tamOriginal-1; i++){
	        if(i+1 == tamOriginal-1)
	            fprintf(pf, "%s-%s-%i-%s", vehiculo[i].id_mat, vehiculo[i].id_usuario, vehiculo[i].num_plazas, vehiculo[i].desc_veh);
	        else
	            fprintf(pf, "%s-%s-%i-%s\n", vehiculo[i].id_mat, vehiculo[i].id_usuario, vehiculo[i].num_plazas, vehiculo[i].desc_veh);
	
	    }
	
	    fclose(pf);
	}

	static int LongitudVectorEstructurasVehiculo(){
	    // Sabemos que el fichero vehiculo.txt tendrá tantas líneas como la longitud del vector de estructuras infoper.
	    char aux[MAX_LIN_FICHVEH];   // MAX_LIN_FICHVEH es el tamaño máximo que habrá en cada linea, incluyendo los guiones
	    FILE *fich;
	    int i = 1;
	
	    fich = fopen("vehiculo.txt", "r");
	
	    if(fich == NULL){
	        fprintf(stderr, "Error en la apertura del fichero.");
	        exit(1);
	    }
	
	    while(!feof(fich)){
	        fgets(aux, MAX_LIN_FICHVEH, fich);
	        i++;
	    }
	
	    rewind(fich); 
	    fclose(fich);
	
	    return i;
	}
		
	static int validar_id_veh(vehiculo_inf *vehiculo, char id[ID], int *pos_usu, int tam){
	    int i, boole = 0;
	
	    for(i = 0; i < tam && !boole; i++){
	        if(!strcmp(vehiculo[i].id_usuario, id))
	            boole = 1;
	    }
	
	    *pos_usu = i-1;
	
	    return boole;