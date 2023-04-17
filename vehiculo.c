
                /* M�dulo Veh�culos - Contiene toda la informaci�n referente al veh�culo de cada usuario, si lo tiene.
                            Todos los datos pertinentes ser�n almacenados en el fichero vehiculos.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "vehiculo.h"
#include "tipos.h"
#include "perfiles.h"
#include "Viajes.h"

   /*static void cambiar_datos_veh(vehiculo_inf vehiculo){
        int opcion, i=0;
        logico dato_camb=0;
        FILE *veh_txt;

        do{
        	system("cls");
       		printf("\n�Desea cambiar alg�n dato?\n\n");
        	printf("   *) Matricula - 1\n   *) N�mero de plazas - 2\n   *)Descripci�n del veh�culo - 3\n   *) Salir - 0\n\n");
        	if(scanf("%d",&opcion)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada v�lida, prueba con otra.\n");
        		opcion=-1;
        		i++;
				if(i>5)
					printf("\nVenga va, t� puedes, que no es tan complicado: pulsa 1, 2, 3 o 0 seg�n lo que necesites.\n");
			}
			else{
				switch(opcion){
               		case 1: pedir_matricula(vehiculo.id_mat); dato_camb=True; break;
               		case 2: pedir_plazas_veh(vehiculo.num_plazas); dato_camb=True; break;
               		case 3: inserta_descripcion(vehiculo.desc_veh); dato_camb=True; break;
               		case 0: break;
               		default: printf("\nPor favor, introduzca un n�mero v�lido.\n"); i++; if(i>5) printf("\nVenga va, t� puedes, que no es tan complicado: pulsa 1, 2, 3 o 0 seg�n lo que necesites."); break;
           		}
			}
		}while(opcion!=0);
        if(dato_camb==True)
        	escribir_fichero(vehiculo, veh_txt);
    }*/

    static void introducir_datos_veh(vehiculo_inf vehiculo){
		int i;
		FILE *veh_txt;

    	printf("\nRellene el formulario a continuaci�n, por favor: \n");

    	printf("		*) Matr�cula: ");
    	do{
    		printf("\n		- La matr�cula debe ser espa�ola (formato 0000AAA) - ");
    		fflush(stdin);
    		gets(vehiculo.id_mat);
    		i=comprobar_validez_mat(vehiculo.id_mat);
		}while(i!=1);

    	printf("\n		*) N�mero de plazas del veh�culo (sin contar el conductor): ");
    	scanf("%i", &vehiculo.num_plazas);
    	while(vehiculo.num_plazas>9||vehiculo.num_plazas<2){
    		printf("\n		Introduzca un n�mero realista de plazas (2-9):");
    		scanf("%i", &vehiculo.num_plazas);
		}

		printf("\n		*) Si deseas, incluye una breve descripci�n de tu coche (color, modelo y marca, etc... - m�x. 50 caracteres): ");
		fflush(stdin);
    	gets(vehiculo.desc_veh);
    	while(strlen(vehiculo.desc_veh)>50){
    		printf("\n		Introduzca una descripci�n m�s corta (o ninguna)");
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
        	printf("Error al guardar la informaci�n");
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
  	      	printf("Error al guardar la informaci�n");
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

        printf("Escribe una peque�a descripci�n de tu veh�culo (recuerda, 50 caracteres m�ximo) - marca, modelo, color, etc...");
        fflush(stdin);
        gets(descripcion);
        while(strlen(descripcion)>50){
    		printf("Introduzca una descripci�n m�s corta (o ninguna)");
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
			printf("Indica el n�mero total de plazas de las que dispone el veh�culo sin el conductor (introduzca un n�mero realista): ");
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

        printf("Indica la matr�cula de tu veh�culo: ");
        fflush(stdin);
        gets(matricula);
        do{
    		printf("Por favor, introduce una matr�cula espa�ola v�lida (sin espacios): ");
            fflush(stdin);
            gets(matricula);
            i=comprobar_validez_mat(matricula);
		}while(i!=1);
    }

	void admin_veh(){
		int op,i=0;

		do{
			printf("\n�Qu� desea hacer?\n <1> Dar un veh�culo de alta.\n <2> Dar un veh�culo de baja.\n <3> Lista de veh�culos\n <4> Modificar veh�culo.\n <5> Ver la informaci�n de un veh�culo.\n <0> Volver.\n Elija una opci�n: ");
			if(scanf("%i",&op)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada v�lida.");
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
					default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 seg�n lo que necesites.\n"); break;
				}
			}
		}while(op!=0);
	}

	void usuario_veh(tPerfil usuario){
        int op, i;

        system("cls");

        do{
			printf("\n�Qu� desea hacer?\n <1> Dar un veh�culo de alta.\n <2> Dar uno de sus veh�culos de baja.\n <3> Ver informaci�n de sus veh�culos.\n <4> Modificar informaci�n de alg�n veh�culo.\n <0> Volver.\n Elija una entrada: ");
			if(scanf("%i",&op)!=1){
				fflush(stdin);
				printf("Error: introduzca una entrada v�lida - ");
				op=-1;
			}
			else{
				switch(op){
					case 1:  usuario_alta_vehiculo(usuario.Id_usuario); break;
					case 2:  usuario_baja_vehiculo(usuario.Id_usuario); break;
					case 3:  usuario_listar_vehiculos(usuario.Id_usuario); break;
					case 4:  usuario_cambiar_informacion_vehiculo(usuario.Id_usuario); break;
					case 0:  break;
					default: printf("Introduzca una entrada dentro de la lista dada."); i++; if(i>5) printf("\nVenga, que no es complicado: introduce 1, 2, 3 o 4 seg�n lo que necesites.\n"); break;
				}
			}
		}while(op!=0);

	}

    static void usuario_alta_vehiculo(char idusuario[IDUSU]){
        vehiculo_inf vehiculo;
        int num_veh,i=0;

        strcpy(vehiculo.id_usuario,idusuario);

        printf("\n�Cu�ntos veh�culos quiere a�adir del usuario? - ");
        if(scanf("%d",&num_veh)!=1){
            fflush(stdin);
            printf("\nError: no has introducido una entrada v�lida, prueba con otra: ");
            num_veh=-1;
            i++;
            if(i>5)
                printf("\nVenga va, t� puedes, que no es tan complicado: introduce un n�mero que indique los coches a a�adir al registro.\n");
        }
        else
            for(i=0;i<num_veh;i++)
                introducir_datos_veh(vehiculo);
    }

	static void admin_alta_vehiculo(){
		vehiculo_inf veh;
		char id_aux[IDUSU];
		int i, num_veh;

        printf("\nIntroduzca la ID a la que pertenecer� el veh�culo: ");
		do{
            fflush(stdin);
            gets(id_aux);
            if(comprobar_validez_id(id_aux)==0)
                printf("\nIntroduzca una ID v�lida, por favor - ");
        }while(comprobar_validez_id(id_aux)!=1);

        strcpy(veh.id_usuario,id_aux);

        printf("�Cu�ntos veh�culos quiere a�adir del usuario? - ");
        if(scanf("%d",&num_veh)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada v�lida, prueba con otra.\n");
        		num_veh=-1;
        		i++;
				if(i>5)
					printf("\nVenga va, t� puedes, que no es tan complicado: introduce un n�mero que indique los coches a a�adir al registro.\n");
			}
			else
                for(i=0;i<num_veh;i++)
                    introducir_datos_veh(veh);
	}

    void admin_baja_vehiculo(){
        int i=0, num_veh;
        char id_aux[IDUSU];

        printf("\nIntroduzca la ID a la que pertenece el veh�culo: ");
		do{
            fflush(stdin);
            gets(id_aux);
            if(comprobar_validez_id(id_aux)==0)
                printf("\nIntroduzca una ID v�lida, por favor - ");
        }while(comprobar_validez_id(id_aux)!=1);

        printf("�Cu�ntos veh�culos quiere borrar del usuario? - ");
        if(scanf("%d",&num_veh)!=1){
        		fflush(stdin);
        		printf("\nError: no has introducido una entrada v�lida, prueba con otra.\n");
        		num_veh=-1;
        		i++;
				if(i>5)
					printf("\nVenga va, t� puedes, que no es tan complicado: introduce un n�mero que indique los coches a borrar.\n");
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

        // Leemos el fichero l�nea por l�nea
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
            printf("%d",v);
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
            printf("\nNo se encontr� el veh�culo indicado.");
        fclose(veh);
        return encontrado;
    }

    static void admin_modif_veh(){
        char mat[IDMAT], usu[IDUSU];

        do{
            printf("\nIntroduzca una ID v�lida a buscar: ");
            fflush(stdin);
            gets(usu);
        }while(comprobar_validez_id(usu)!=1);

        do{
            printf("\nAhora introduzca una matr�cula v�lida a buscar: ");
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
                // Copiamos la matricula y el usuario de la l�nea a variables temporales

                strncpy(matricula_actual, linea, 7);
                matricula_actual[7] = '\0';
                strncpy(usuario_actual, linea+8, 4);
                usuario_actual[4] = '\0';

                // Comparamos la primera y la segunda cadena de la l�nea con las cadenas dadas
                if (strcmp(usuario_actual, usuario)==0&&strcmp(matricula_actual, matricula)==0){
                    encontrado=True;
                    // Calcular la posici�n de la l�nea en el archivo
                    posicion=ftell(veh)-sizeof(linea);

                    // Mover la posici�n del archivo para escribir la nueva l�nea
                    fseek(veh, posicion,  SEEK_SET);
                    printf("\n");
                    introducir_datos_veh(vehiculo);
                }
            }
        }
        if(encontrado==False)
            printf("\nNo se encontr� el veh�culo indicado. Compruebe que el usuario y su matr�cula son correctos.\n");
        fclose(veh);
    }

    void menu_registro_vehiculo(tPerfil usuario){
        int op, i, num_veh;
        vehiculo_inf vehiculo[num_veh];

        do{
            printf("\n�Tiene planeado llevar y/o traer otra gente de la ESI?\n\n");
            printf("   <1> S�.\n   <2> No\n\n");
            if(scanf("%d",&op)!=1){
                fflush(stdin);
                printf("\nError: no has introducido una entrada v�lida, prueba con otra.\n");
                op=-1;
                i++;
                if(i>5)
                    printf("\nVenga va, t� puedes, que no es tan complicado: pulsa 1, o 2 seg�n lo que necesites.\n");
            }
            else{
                switch(op){
                    case 1: if(scanf("%d",&op)!=1){ fflush(stdin); printf("\nError: no has introducido una entrada v�lida, prueba con otra.\n");
                            op=-1; i++; if(i>5) printf("\nVenga va, t� puedes, que no es tan complicado: pulsa 1, 2, 3 o 0 seg�n lo que necesites.\n");} else{ for(i=0;i<num_veh;i++){
                            strcpy(vehiculo[i].id_usuario, usuario.Id_usuario); introducir_datos_veh(vehiculo[i]);}}
                    case 2: break;
                    default: printf("\nPor favor, introduzca un n�mero v�lido.\n"); i++; if(i>5) printf("\nVenga va, t� puedes, que no es tan complicado: pulsa 1 o 2 seg�n lo que necesites."); break;
                }
            }
        }while(op!=1&&op!=2);
    }

    static void listar_viajes(){
        char matricula[IDMAT];

        do{
            printf("\nIntroduzca una matr�cula v�lida a buscar: ");
            fflush(stdin);
            gets(matricula);
        }while(comprobar_validez_mat(matricula)!=1);

        listar_vehiculos_mat(matricula);
        viajes_veh(matricula);
    }
    static void viajes_veh(char matricula[IDMAT]){
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

    static void usuario_baja_vehiculo(char idusuario[IDUSU]){
        char matricula[IDMAT];

        do{
            printf("\nIntroduzca una matr�cula v�lida a buscar: ");
            fflush(stdin);
            gets(matricula);
        }while(comprobar_validez_mat(matricula)!=1);

        usuario_borrar_vehiculo(idusuario, matricula);
    }

    static void usuario_borrar_vehiculo(char usuario[IDUSU], char matricula[IDMAT]){
        FILE *file_temp;
        FILE *file_original;
        int i;
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

        // Leemos el fichero l�nea por l�nea
        char linea[MAX_LIN_FICHVEH];
        i=0;
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
            printf("\nEl veh�culo no se encuentra en el registro.");
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

        // Leemos el fichero l�nea por l�nea
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
            printf("\nNo existe ning�n veh�culo asociado a su cuenta.\n");
        fclose(file_original);
    }

    static void usuario_cambiar_informacion_vehiculo(char idusuario[IDUSU]){
        char matricula[IDMAT];

        do{
            printf("\nIntroduzca una matr�cula v�lida a buscar: ");
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

                // Movemos la posici�n del archivo para escribir la nueva l�nea
                fseek(archivo, posicion, SEEK_SET);
                introducir_datos_veh(veh);
            }
        }
    if(coincidencia==False)
        printf("\n El veh�culo indicado no se encuentra asociado a su cuenta.\n");
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

    void obtener_datos_vehiculo(char usu[IDUSU], viajes viaje){
        int num_veh;
        char mat[IDMAT];
        FILE *veh;
        char linea[MAX_LIN_FICHVEH];
        char mat_actual[IDMAT];
        char usu_actual[IDUSU];
        logico coincidencia=False;

        usuario_listar_vehiculos(usu);

            do{
                printf("\nIntroduzca la matr�cula del veh�culo que va a utilizar: ");
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
                        strcpy(viaje.matricula,mat_actual);
                        sscanf(linea, "%*[^0123456789]%d", &viaje.Nplazas);
                    }
                }
            }
            fclose(veh);
            if(coincidencia==False)
                printf("\nEl vehiculo indicado no figura en su cuenta.\n");
    }
