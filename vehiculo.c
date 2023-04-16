
                /* Módulo Vehículos - Contiene toda la información referente al vehículo de cada usuario, si lo tiene.
                            Todos los datos pertinentes serán almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "vehiculo.h"
#include "tipos.h"
#include "perfiles.h"
#include "Viajes.h"

   static void cambiar_datos_veh(vehiculo_inf vehiculo){
        int opcion, i=0;
        logico dato_camb=0;
        FILE *veh_txt;

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

    static void introducir_datos_veh(vehiculo_inf vehiculo){
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

	void leer_fichero_vehiculo(int veces, vehiculo_inf vehiculo[veces], FILE *veh_txt){
		int i;
		char buf[1024];

		if((veh_txt=fopen("vehiculo.txt","r"))==NULL){
  	      	printf("Error al guardar la información");
		}

		else{
			for(i=0;i<veces;i++){
				if(fgets(buf, 1024, veh_txt)!=NULL){
					buf[strcspn(buf,"\n")]='\0';
					sscanf(buf,"%[^-]-%[^-]-%d-%[^\n]",vehiculo[i].id_mat, vehiculo[i].id_usuario, &vehiculo[i].num_plazas, vehiculo[i].desc_veh);
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

	static int comprobar_validez_id(char id_aux[]){
		int i;
		vehiculo_inf vehiculo;

		if (strlen(id_aux)!=IDUSU-1)
			return 0;

        strcpy(vehiculo.id_usuario, id_aux);

		for(i=0;i++;i<IDUSU-1){
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

	void admin_veh(){
		int op,i=0;

		do{
			printf("\n¿Qué desea hacer?\n <1> Dar un vehículo de alta.\n <2> Dar un vehículo de baja.\n <3> Lista de vehículos\n <4> Modificar vehículo.\n <5> Ver información de un vehículo.\n <0> Volver.");
			if(scanf("%i",&op)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada válida.");
				op=-1;
			}
			else{
				switch(op){
					case 1: alta_vehiculo(); break;
					case 2: baja_vehiculo(); break;
					case 3: listar_vehiculos(); break;
					case 4: admin_modif_veh(); break;
					case 5: break;
					case 0: break;
					default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 según lo que necesites.\n"); break;
				}
			}
		}while(op!=1&&op!=2&&op!=3&&op!=4&&op!=5&&op!=0);
	}

	void usuario_veh(){

	}

	static void alta_vehiculo(){
		vehiculo_inf veh;
		char id_aux[IDUSU];
		int i, num_veh;

        printf("\n\nIntroduzca la ID a la que pertenecerá el vehículo: ");
		do{
            fflush(stdin);
            gets(id_aux);
            if(comprobar_validez_id(id_aux)==0)
                printf("\nIntroduzca una ID válida, por favor - ");
        }while(comprobar_validez_id(id_aux)!=1);

        strcpy(veh.id_usuario,id_aux);

        printf("¿Cuántos vehículos quiere borrar del usuario? - ");
        if(scanf("%d",&num_veh)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada válida, prueba con otra.\n");
        		num_veh=-1;
        		i++;
				if(i>5)
					printf("\nVenga va, tú puedes, que no es tan complicado: introduce un número que indique los coches a borrar.\n");
			}
			else
                for(i=0;i<num_veh;i++)
                    introducir_datos_veh(veh);
	}

    void baja_vehiculo(){
        int i=0, num_veh;
        char id_aux[IDUSU];

        do{
            printf("\nIntroduzca una ID de usuario válida: ");
            gets(id_aux);
        }while(comprobar_validez_id(id_aux)!=1);

        printf("¿Cuántos vehículos quiere borrar del usuario?");
        if(scanf("%d",&num_veh)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada válida, prueba con otra.\n");
        		num_veh=-1;
        		i++;
				if(i>5)
					printf("\nVenga va, tú puedes, que no es tan complicado: introduce un número que indique los coches a borrar.\n");
			}
			else
                borrar_vehiculos(id_aux, num_veh);
    }

    static void borrar_vehiculos(char cadena_a_borrar[], int num_veh){
        FILE *file_temp;
        FILE *file_original;
        int i;

        const char* archivo_original = "archivo.txt";
        const char* archivo_temporal = "archivo_temp.txt";

        // Abrimos el archivo original en modo lectura y escritura
        if ((file_original=fopen(archivo_original, "r+"))==NULL){
            printf("Error al abrir el archivo original.\n");
            exit(0);
        }

        // Ahora abrimos el archivo temporal en modo escritura
        if ((file_temp=fopen(archivo_temporal, "w"))==NULL){
            printf("Error al abrir el archivo temporal.\n");
            fclose(file_original);
            exit(0);
        }

        // Leemos el fichero línea por línea
        char linea[MAX_LIN_FICHVEH];
        i=0;
        while (fgets(linea, sizeof(linea), file_original) != NULL){
            // Obtenemos la segunda cadena
            char segunda_cadena[IDUSU];
            strncpy(segunda_cadena, linea+8, 4);
            segunda_cadena[4] = '\0'; //Nos aseguramos de que la segunda cadena termine con '\0'

            // Comprobamos si hay coincidencia
            if (strcmp(segunda_cadena, cadena_a_borrar)!=0&&i<num_veh){
                fputs(linea, file_temp);
                i++;
            }
        }

        fclose(file_original);
        fclose(file_temp);

        if (remove(archivo_original)!=0){
            printf("Error al eliminar el archivo original.\n");
            exit(0);
        }

        if (rename(archivo_temporal, archivo_original)!=0){
            printf("Error al renombrar el archivo temporal.\n");
            exit(0);
        }

        printf("Línea borrada exitosamente.\n");
    }

    static void listar_vehiculos(){
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];

        if((veh=fopen("vehiculo.txt","r"))==NULL)
            printf("\nError al abrir el fichero vehiculo.txt\n");
        else
            while(fgets(linea,sizeof(linea),veh)!=NULL)
                printf("%s",linea);
        fclose(veh);
    }

    static void admin_modif_veh(){
        char mat[IDMAT], usu[IDUSU];

        do{
            printf("\nIntroduzca una ID válida a buscar: ");
            gets(usu);
        }while(comprobar_validez_id(usu)!=1);

        do{
            printf("\nAhora introduzca una matrícula válida a buscar: ");
            gets(mat);
        }while(comprobar_validez_mat(mat)!=1);

        buscar_modificar_vehiculo(mat, usu);
    }

    static void buscar_modificar_vehiculo(char matricula[IDMAT], char usuario[IDUSU]){
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];
        vehiculo_inf vehiculo;
        int posicion;

        strcpy(vehiculo.id_usuario, usuario );
        strcpy(vehiculo.id_mat, matricula);

        if((veh=fopen("vehiculo.txt","r+"))==NULL){
            printf("\nError al abrir el fichero vehiculo.txt\n");
            exit(1);
        }
        else{
            while (fgets(linea, sizeof(linea), veh)!=NULL){
                // Copiamos la matricula y el usuario de la línea a variables temporales
                char usuario_actual[IDUSU];
                char matricula_actual[IDMAT];
                strncpy(matricula_actual, linea, 4);
                matricula_actual[4] = '\0';
                strncpy(usuario_actual, linea+8, 4);
                usuario_actual[4] = '\0';


                // Comparamos la primera y la segunda cadena de la línea con las cadenas dadas
                if (strcmp(usuario_actual, usuario)==0&&strcmp(matricula_actual, matricula)==0){
                    // Calcular la posición de la línea en el archivo
                    posicion=ftell(veh) - sizeof(linea);

                    // Mover la posición del archivo para escribir la nueva línea
                    fseek(veh, posicion, SEEK_SET);

                    cambiar_datos_veh(vehiculo);
                }
            }
        }
        fclose(veh);
    }

    void menu_registro_vehiculo(tPerfil usuario){
        int op, i, num_veh;
        vehiculo_inf vehiculo[num_veh];

        do{
            printf("\n¿Tiene planeado llevar y/o traer otra gente de la ESI?\n\n");
            printf("   <1> Sí.\n   <2> No\n\n");
            if(scanf("%d",&op)!=1){
                fflush(stdin);
                printf("\nError: no has introducido una entrada válida, prueba con otra.\n");
                op=-1;
                i++;
                if(i>5)
                    printf("\nVenga va, tú puedes, que no es tan complicado: pulsa 1, o 2 según lo que necesites.\n");
            }
            else{
                switch(op){
                    case 1: if(scanf("%d",&op)!=1){ fflush(stdin); printf("\nError: no has introducido una entrada válida, prueba con otra.\n");
                            op=-1; i++; if(i>5) printf("\nVenga va, tú puedes, que no es tan complicado: pulsa 1, 2, 3 o 0 según lo que necesites.\n");} else{ for(i=0;i<num_veh;i++){
                            strcpy(vehiculo[i].id_usuario, usuario.Id_usuario); introducir_datos_veh(vehiculo[i]);}}
                    case 2: break;
                    default: printf("\nPor favor, introduzca un número válido.\n"); i++; if(i>5) printf("\nVenga va, tú puedes, que no es tan complicado: pulsa 1 o 2 según lo que necesites."); break;
                }
            }
        }while(op!=1&&op!=2);
    }

    static void listar_viajes(char matricula[IDMAT]){
        FILE *viaj;
        int aux_id;
        char linea[MAX_LIN_FICHVIAJE];
        viajes viaje;

        if((viaj=fopen("Viajes.txt","r+"))==NULL){
            printf("\nError al abrir el fichero Viajes.txt\n");
            exit(1);
        }
        else{
            while(fgets(linea, sizeof(linea), viaj)!=NULL){
                sscanf(linea, "%d-%[^-]-%[^-]-%[^-]-%[^-]-%d-%[^-]-%[^-]-%[^-]-%[^-]-%c", &viaje.i_d, viaje.matricula, viaje.fecha, viaje.hora_inicio, viaje.hora_llegada, &viaje.Nplazas, viaje.tipo,
                                                                                            viaje.importe, viaje.estado, viaje.hoy, &viaje.anular);
                if(strcmp(viaje.matricula,matricula)==0&&viaje.estado.finalizado==True){
                    printf("%d - %s - %s - %s - %s - %d - %s - %s - %s - %c", &viaje.i_d, viaje.matricula, viaje.fecha, viaje.hora_inicio, viaje.hora_llegada, &viaje.Nplazas, viaje.tipo, viaje.importe,
                                                                                viaje.estado, viaje.anular);
                }
            }
        }
        fclose(viaj);
    }
