#include <string.h>
#include <stdio.h>

struct trayecto {
	char poblacion[20];
	int Id_viajes;
};



	FILE *fichero;

	struct trayecto trayecto;


	fichero = fopen("pasos.txt", "rb");

	if (fichero == NULL) {
		printf("Error: No se ha podido crear el fichero empleados.dat");
	} else {

		fread(&trayecto, sizeof(trayecto), 1, fichero);

		while (feof(fichero) == 0) {
			printf("\n\nPoblacion: %s", trayecto.poblacion);
			printf("\nId_viajes: %d", trayecto.Id_viajes);

			fread(&trayecto, sizeof(trayecto), 1, fichero);
		}


		fclose(fichero);
	}



typedef struct{
    int Id_viajes[6];
    char poblacion[20];
}trayecto;





	FILE *fichero;
	char poblacion[20];
	char *resultado;
	fichero = fopen("viajes.txt", "rt");
		resultado = fgets(poblacion, 20, fichero);
		while (resultado != NULL) {
			printf("%s", poblacion);
			resultado = fgets(poblacion, 20, fichero);
		}
		fclose(fichero);




		FILE *fichero;
	int Id_viajes[6];
	int *resultado;
	fichero = fopen("viajes.txt", "rt");
		resultado = fgets(Id_viajes, 6, fichero);
		while (resultado != NULL) {
			printf("%s", poblacion);
			resultado = fgets(Id_viajes, 6, fichero);
		}
		fclose(fichero);
