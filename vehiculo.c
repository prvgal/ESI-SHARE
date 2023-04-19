
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


    static void introducir_datos_veh(vehiculo_inf vehiculo){
		int i;

    	printf("\nRellene el formulario a continuación, por favor: \n");

    	printf("		*) Matrícula: ");
    	do{
    		printf("\n		- La matrícula debe ser española (formato 0000AAA) - ");
    		fflush(stdin);
    		gets(vehiculo.id_mat);
    		i=comprobar_validez_mat(vehiculo.id_mat);
		}while(i!=1);

    	printf("\n		*) Número de plazas del vehículo (sin contar el conductor): ");
    	scanf("%i", &vehiculo.num_plazas);
    	while(vehiculo.num_plazas>9||vehiculo.num_plazas<1){
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
		escribir_fichero(vehiculo);
	}

	static void escribir_fichero(vehiculo_inf vehiculo){
        char guion[2]={'-','\0'};
        FILE *veh_txt;

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

	static void acortar_cadena(char cadena[]){
		int i, len = (int) strlen(cadena);
		for(i=0; i<len; i++){
    			if(cadena[i]=='\n')
    				cadena[i]='\0';
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
            }
        }

        return 1; // Agregamos una llave de cierre adicional para cerrar la función correctamente
    }


	static int comprobar_validez_id(char id_aux[]){
		int i;
		vehiculo_inf vehiculo;

		if (strlen(id_aux)!=IDUSU-1)
			return 0;

        strcpy(vehiculo.id_usuario, id_aux);

		for(i=0;i<IDUSU-1;i++){
			if(vehiculo.id_usuario[i]!=1&&vehiculo.id_usuario[i]!=2&&vehiculo.id_usuario[i]!=3&&vehiculo.id_usuario[i]!=4&&
				vehiculo.id_usuario[i]!=5&&vehiculo.id_usuario[i]!=6&&vehiculo.id_usuario[i]!=7&&vehiculo.id_usuario[i]!=8&&
				vehiculo.id_usuario[i]!=9&&vehiculo.id_usuario[i]!=0)
				return 0;
		}
		return 1;
	}

	void admin_veh(){
		int op,i=0;

		do{
			printf("\n¿Qué desea hacer?\n <1> Dar un vehículo de alta.\n <2> Dar un vehículo de baja.\n <3> Lista de vehículos\n <4> Modificar vehículo.\n <5> Ver la información de un vehículo.\n <0> Volver.\n Elija una opción: ");
			if(scanf("%i",&op)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada válida.");
				op=-1;
			}
			else{
				switch(op){
					case 1: admin_alta_vehiculo(); break;
					case 2: admin_baja_vehiculo(); break;
					case 3: printf("\n"); listar_vehiculos(); break;
					case 4: admin_modif_veh(); break;
					case 5: listar_viajes(); break;
					case 0: break;
					default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 según lo que necesites.\n"); break;
				}
			}
		}while(op!=0);
	}

	void usuario_veh(tPerfil usuario){
        int op, i;

        system("cls");

        do{
			printf("\n¿Qué desea hacer?\n <1> Dar un vehículo de alta.\n <2> Dar uno de sus vehículos de baja.\n <3> Ver información de sus vehículos.\n <4> Modificar información de algún vehículo.\n <0> Volver.\n Elija una entrada: ");
			if(scanf("%i",&op)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada válida - ");
				op=-1;
			}
			else{
				switch(op){
					case 1:  usuario_alta_vehiculo(usuario.Id_usuario); break;
					case 2:  usuario_baja_vehiculo(usuario.Id_usuario); break;
					case 3:  usuario_listar_vehiculos(usuario.Id_usuario); break;
					case 4:  usuario_cambiar_informacion_vehiculo(usuario.Id_usuario); break;
					case 0:  break;
					default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 según lo que necesites.\n"); break;
				}
			}
		}while(op!=0);

	}

    static void usuario_alta_vehiculo(char idusuario[IDUSU]){
        vehiculo_inf vehiculo;
        int num_veh,i=0;

        strcpy(vehiculo.id_usuario,idusuario);

        printf("\n¿Cuántos vehículos quiere añadir del usuario? - ");
        if(scanf("%d",&num_veh)!=1){
            fflush(stdin);
            printf("\nError: no has introducido una entrada válida, prueba con otra: ");
            num_veh=-1;
            i++;
            if(i>5)
                printf("\nVenga va, tú puedes, que no es tan complicado: introduce un número que indique los coches a añadir al registro.\n");
        }
        else
            for(i=0;i<num_veh;i++)
                introducir_datos_veh(vehiculo);
    }

	static void admin_alta_vehiculo(){
		vehiculo_inf veh;
		char id_aux[IDUSU];
		int i, num_veh;

        printf("\nIntroduzca la ID a la que pertenecerá el vehículo: ");
		do{
            fflush(stdin);
            gets(id_aux);
            if(comprobar_validez_id(id_aux)==0)
                printf("\nIntroduzca una ID válida, por favor - ");
        }while(comprobar_validez_id(id_aux)!=1);

        strcpy(veh.id_usuario,id_aux);

        printf("¿Cuántos vehículos quiere añadir del usuario? - ");
        if(scanf("%d",&num_veh)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada válida, prueba con otra.\n");
        		num_veh=-1;
        		i++;
				if(i>5)
					printf("\nVenga va, tú puedes, que no es tan complicado: introduce un número que indique los coches a añadir al registro.\n");
			}
			else
                for(i=0;i<num_veh;i++)
                    introducir_datos_veh(veh);
	}

    void admin_baja_vehiculo(){
        int i=0, num_veh;
        char id_aux[IDUSU];

        printf("\nIntroduzca la ID a la que pertenece el vehículo: ");
		do{
            fflush(stdin);
            gets(id_aux);
            if(comprobar_validez_id(id_aux)==0)
                printf("\nIntroduzca una ID válida, por favor - ");
        }while(comprobar_validez_id(id_aux)!=1);

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
                admin_borrar_vehiculos(id_aux, num_veh);
    }

    static void admin_borrar_vehiculos(char cadena_a_borrar[], int num_veh){
        FILE *file_temp;
        FILE *file_original;
        int i=0;
        logico encontrado=False;
        char segunda_cadena[IDUSU];

        // Abrimos el archivo original en modo lectura y escritura
        if ((file_original=fopen("vehiculo.txt", "r+"))==NULL){
            printf("Error al abrir el archivo vehiculo.txt.\n");
            exit(0);
        }

        // Ahora abrimos el archivo temporal en modo escritura
        if ((file_temp=fopen("vehiculo_temp.txt", "w"))==NULL){
            printf("Error al abrir vehiculo_temp.\n");
            fclose(file_original);
            exit(0);
        }

        // Leemos el fichero línea por línea
        char linea[MAX_LIN_FICHVEH];
        while (fgets(linea, sizeof(linea), file_original) != NULL){
            // Obtenemos la segunda cadena

            strncpy(segunda_cadena, linea+8, 4);
            segunda_cadena[4] = '\0'; //Nos aseguramos de que la segunda cadena termine con '\0'
            // Comprobamos si hay coincidencia
            if (strcmp(segunda_cadena, cadena_a_borrar)!=0)
                fputs(linea, file_temp);
            else{
                encontrado=True;
                i++;
                if(i>num_veh)
                    fputs(linea,file_temp);
            }
        }
        if(encontrado==False){
            printf("\nEl usuario dado no figura en el registro.\n");
            fclose(file_original);
            fclose(file_temp);
        }
        else{
            fclose(file_original);
            fclose(file_temp);
            remove("vehiculo.txt");
            int v=rename("vehiculo_temp.txt", "vehiculo.txt");
        }
    }

    static void listar_vehiculos(){
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];

        if((veh=fopen("vehiculo.txt","r"))==NULL)
            printf("\nError al abrir el fichero vehiculo.txt\n");
        else{
            while(fgets(linea,sizeof(linea),veh)!=NULL)
                printf("%s",linea);
        }
        fclose(veh);
    }

    static logico listar_vehiculos_mat(char mat[IDMAT]){
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];
        char matricula_actual[IDMAT];
        logico encontrado=False;

        if((veh=fopen("vehiculo.txt","r"))==NULL)
            printf("\nError al abrir el fichero vehiculo.txt\n");
        else{
            while(fgets(linea,sizeof(linea),veh)!=NULL&&encontrado==False){
                strncpy(matricula_actual, linea+8, 4);
                matricula_actual[4] = '\0';

                if(strcmp(matricula_actual,mat)==0){
                    encontrado=True;
                    printf("%s",linea);
                }
            }
        }
        if(encontrado==False)
            printf("\nNo se encontró el vehículo indicado.");
        fclose(veh);
        return encontrado;
    }

    static void admin_modif_veh(){
        char mat[IDMAT], usu[IDUSU];

        do{
            printf("\nIntroduzca una ID válida a buscar: ");
            fflush(stdin);
            gets(usu);
        }while(comprobar_validez_id(usu)!=1);

        do{
            printf("\nAhora introduzca una matrícula válida a buscar: ");
            fflush(stdin);
            gets(mat);
        }while(comprobar_validez_mat(mat)!=1);

        admin_buscar_modificar_vehiculo(mat, usu);
    }

    static void admin_buscar_modificar_vehiculo(char matricula[IDMAT], char usuario[IDUSU]){
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];
        vehiculo_inf vehiculo;
        int posicion;
        logico encontrado=False;
        char usuario_actual[IDUSU];
        char matricula_actual[IDMAT];

        strcpy(vehiculo.id_usuario, usuario );
        strcpy(vehiculo.id_mat, matricula);

        if((veh=fopen("vehiculo.txt","r+"))==NULL){
            printf("\nError al abrir el fichero vehiculo.txt\n");
            exit(1);
        }
        else{
            while (fgets(linea, sizeof(linea), veh)!=NULL){
                // Copiamos la matricula y el usuario de la línea a variables temporales

                strncpy(matricula_actual, linea, 7);
                matricula_actual[7] = '\0';
                strncpy(usuario_actual, linea+8, 4);
                usuario_actual[4] = '\0';

                // Comparamos la primera y la segunda cadena de la línea con las cadenas dadas
                if (strcmp(usuario_actual, usuario)==0&&strcmp(matricula_actual, matricula)==0){
                    encontrado=True;
                    // Calcular la posición de la línea en el archivo
                    posicion=ftell(veh)-sizeof(linea);

                    // Mover la posición del archivo para escribir la nueva línea
                    fseek(veh, posicion,  SEEK_SET);
                    printf("\n");
                    introducir_datos_veh(vehiculo);
                }
            }
        }
        if(encontrado==False)
            printf("\nNo se encontró el vehículo indicado. Compruebe que el usuario y su matrícula son correctos.\n");
        fclose(veh);
    }

    void menu_registro_vehiculo(char usuario[ID]){
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
                            strcpy(vehiculo[i].id_usuario, usuario); introducir_datos_veh(vehiculo[i]);}}
                    case 2: break;
                    default: printf("\nPor favor, introduzca un número válido.\n"); i++; if(i>5) printf("\nVenga va, tú puedes, que no es tan complicado: pulsa 1 o 2 según lo que necesites."); break;
                }
            }
        }while(op!=1&&op!=2);
    }

    static void listar_viajes(){
        char matricula[IDMAT];

        do{
            printf("\nIntroduzca una matrícula válida a buscar: ");
            fflush(stdin);
            gets(matricula);
        }while(comprobar_validez_mat(matricula)!=1);

        listar_vehiculos_mat(matricula);
        viajes_veh(matricula);
    }
    static void viajes_veh(char matricula[IDMAT]){
        FILE *viaj;
        char linea[MAX_LIN_FICHVIAJE];
        viajes viaje;
        logico coincidencia=False;

        if((viaj=fopen("Viajes.txt","r+"))==NULL){
            printf("\nError al abrir el fichero Viajes.txt\n");
            exit(1);
        }
        else{
            while(fgets(linea, sizeof(linea), viaj)!=NULL){
                sscanf(linea, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%d-%[^-]-%[^-]-%[^-]-%d-%c", viaje.i_d, viaje.matricula, viaje.fecha, viaje.hora_inicio, viaje.hora_llegada, &viaje.Nplazas, viaje.tipo,
                                                                                            viaje.importe, viaje.estado, viaje.hoy, &viaje.anular);
                if(strcmp(viaje.matricula,matricula)==0){
                    printf("%s - %s - %s - %s - %s - %d - %s - %s - %s - %c", viaje.i_d, viaje.matricula, viaje.fecha, viaje.hora_inicio, viaje.hora_llegada, &viaje.Nplazas, viaje.tipo, viaje.importe,
                                                                                viaje.estado, viaje.anular);
                    coincidencia=True;
                }
            }
        }
        if(coincidencia==False)
            printf("\nEl vehículo dado no figura en ningún viaje.\n");
        fclose(viaj);
    }

    static void usuario_baja_vehiculo(char idusuario[IDUSU]){
        char matricula[IDMAT];

        do{
            printf("\nIntroduzca una matrícula válida a buscar: ");
            fflush(stdin);
            gets(matricula);
        }while(comprobar_validez_mat(matricula)!=1);

        usuario_borrar_vehiculo(idusuario, matricula);
    }

    static void usuario_borrar_vehiculo(char usuario[IDUSU], char matricula[IDMAT]){
        FILE *file_temp;
        FILE *file_original;
        logico coincidencia=0;

        // Abrimos el archivo original en modo lectura y escritura
        if ((file_original=fopen("vehiculo.txt", "r+"))==NULL){
            printf("Error al abrir el archivo original.\n");
            exit(0);
        }

        // Ahora abrimos el archivo temporal en modo escritura
        if ((file_temp=fopen("vehiculo_temp.txt", "w"))==NULL){
            printf("Error al abrir el archivo temporal.\n");
            fclose(file_original);
            exit(0);
        }

        // Leemos el fichero línea por línea
        char linea[MAX_LIN_FICHVEH];
        while (fgets(linea, sizeof(linea), file_original) != NULL){
            // Obtenemos las cadenas
            char matricula_actual[IDMAT];
            strncpy(matricula_actual,linea,7);
            char usuario_actual[IDUSU];
            strncpy(usuario_actual, linea+8, 4);
            usuario_actual[4] = '\0'; //Nos aseguramos de que la segunda cadena termine con '\0'

            // Comprobamos si hay coincidencia
            if (strcmp(usuario_actual, usuario)==0&&strcmp(matricula_actual,matricula)==0){
                coincidencia=1;
            }
            else
                fputs(linea, file_temp);
        }
        if(coincidencia==0)
            printf("\nEl vehículo no se encuentra en el registro.");
        fclose(file_original);
        fclose(file_temp);

        remove("vehiculo_temp.txt");
    }

     void usuario_listar_vehiculos(char usuario[IDUSU]){
        FILE *file_original;
        logico coincidencia=0;

        // Abrimos el archivo original en modo lectura
        if ((file_original=fopen("vehiculo.txt", "r"))==NULL){
            printf("Error al abrir el archivo original.\n");
            exit(0);
        }

        // Leemos el fichero línea por línea
        char linea[MAX_LIN_FICHVEH];
        while (fgets(linea, sizeof(linea), file_original) != NULL){
            // Obtenemos las cadenas
            char matricula_actual[IDMAT];
            strncpy(matricula_actual,linea,7);
            char usuario_actual[IDUSU];
            strncpy(usuario_actual, linea+8, 4);
            usuario_actual[4] = '\0'; //Nos aseguramos de que la segunda cadena termine con '\0'

            // Comprobamos si hay coincidencia
            if (strcmp(usuario_actual, usuario)==0){
                coincidencia=1;
                printf("%s",linea);
            }
        }
        if(coincidencia==0)
            printf("\nNo existe ningún vehículo asociado a su cuenta.\n");
        fclose(file_original);
    }

    static void usuario_cambiar_informacion_vehiculo(char idusuario[IDUSU]){
        char matricula[IDMAT];

        do{
            printf("\nIntroduzca una matrícula válida a buscar: ");
            fflush(stdin);
            gets(matricula);
        }while(comprobar_validez_mat(matricula)!=1);

        usuario_modificar_vehiculo(idusuario,matricula);
    }

    static void usuario_modificar_vehiculo(char idusuario[IDUSU], char matricula[IDMAT]){
       FILE* archivo;
       int posicion;
       vehiculo_inf veh;
       logico coincidencia=False;
       char matricula_actual[IDMAT];
       char usuario_actual[IDUSU];

        if ((archivo = fopen("vehiculo.txt", "r+"))==NULL){
            printf("Error al abrir el archivo.\n");
            exit(1);
        }

        char linea[MAX_LIN_FICHVEH];
        while (fgets(linea, sizeof(linea), archivo)!=NULL){

            strncpy(matricula_actual, linea, 7);
            matricula_actual[7] = '\0';

            strncpy(usuario_actual, linea+8, 4);
            usuario_actual[4] = '\0';

            if (strcmp(matricula_actual, matricula)==0&&strcmp(usuario_actual, idusuario)==0){
                coincidencia=True;
                posicion=ftell(archivo)-sizeof(linea);

                // Movemos la posición del archivo para escribir la nueva línea
                fseek(archivo, posicion, SEEK_SET);
                introducir_datos_veh(veh);
            }
        }
    if(coincidencia==False)
        printf("\n El vehículo indicado no se encuentra asociado a su cuenta.\n");
    fclose(archivo);
    }

    int contar_vehiculos(char idusu[IDUSU]){
        FILE *file_original;
        char usuario_actual[IDUSU];
        int i;

        // Abrimos el archivo original en modo lectura y escritura
        if ((file_original=fopen("vehiculo.txt", "r+"))==NULL){
            printf("Error al abrir el archivo original.\n");
            exit(0);
        }

        else{
            char linea[MAX_LIN_FICHVEH];
            i=0;
            while (fgets(linea, sizeof(linea), file_original) != NULL){
                strncpy(usuario_actual, linea+8, 4);
                usuario_actual[4] = '\0'; //Nos aseguramos de que la segunda cadena termine con '\0'
                if(strcmp(usuario_actual, idusu)==0){
                    i++;
                }
            }
        }
        fclose(file_original);
        return i;
    }

    viajes *obtener_matricula_vehiculo(char usu[IDUSU], viajes *viaje, int posViaje){
        char mat[IDMAT];
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];
        char mat_actual[IDMAT];
        char usu_actual[IDUSU];
        logico coincidencia=False;

        usuario_listar_vehiculos(usu);

            do{
                printf("\nIntroduzca la matrícula del vehículo que va a utilizar: ");
                fflush(stdin);
                gets(mat);
            }while(comprobar_validez_mat(mat)!=1);

            if((veh=fopen("vehiculo.txt","r"))==NULL)
                printf("\nError al abrir el fichero vehiculo.txt\n");

            else{
                while(fgets(linea,sizeof(linea),veh)!=NULL){
                    strncpy(usu_actual,linea+8,4);
                    usu_actual[4]='\0';

                    strncpy(mat_actual, linea, 7);
                    mat_actual[7] = '\0';

                    if(strcmp(mat_actual,mat)==0&&strcmp(usu_actual,usu)==0){
                        coincidencia=True;
                        strcpy(viaje[posViaje].matricula,mat_actual);
                    }
                }
            }
            fclose(veh);
            if(coincidencia==False)
                printf("\nEl vehiculo indicado no figura en su cuenta.\n");
            
            return viaje;
    }

viajes *obtener_plazas_vehiculo(viajes *viaje, int posViaje, char mat_actual[IDMAT]){
        
        typedef struct {
    char matricula[IDMAT];
    char Idv[IDUSU];
    int plazas;
    char nombre[CARACTERES];
} Vehiculo;

    Vehiculo *vehiculos;
    vehiculos = (Vehiculo*)calloc(numerovehiculos(), sizeof(Vehiculo));

        FILE *veh;
        int i = 0;
        int j;

        if((veh=fopen("vehiculo.txt","r"))==NULL)
                printf("\nError al abrir el fichero vehiculo.txt\n");

            else{

    while (!feof(veh)) {
        fscanf(veh, "%[^-]-%[^-]-%d-%[^\n]\n", vehiculos[i].matricula, vehiculos[i].Idv, &vehiculos[i].plazas, vehiculos[i].nombre);
        i++;
    }

    fclose(veh);

    for (j = 0; j < i; j++) {
        if (strcmp(mat_actual, vehiculos[j].matricula) == 0) {
            viaje[posViaje].Iplazas = vehiculos[j].plazas;
            break;
        }
    }

        fclose(veh);
            }

        free(vehiculos);
        return viaje;
    }

    static int numerovehiculos(void){
    char aux[MAX_LIN_FICHVEH];   //Se usa para llegar al final de cada linea
    FILE *vf;
    int i = 0;

    vf = fopen("vehiculo.txt", "r");  //Abre el fichero en modo lectura

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    while(fgets(aux, MAX_LIN_FICHVEH, vf) != NULL){  //Lee cada linea y suma 1 a la variable i
        i++;
    }

    rewind(vf);
    fclose(vf);

    return i;   //Devuelve el número de lineas del fichero Viajes.txt
}