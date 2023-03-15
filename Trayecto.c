#include <stdio.h>

int main() {
    encontrarUsuario("viajes.txt");
    copiarContenido("viajes.txt", "pasos.txt", 0, 7);

    return 0;
}

#include <stdio.h>

void copiarContenido(char* archivo_origen, char* archivo_destino, int inicio, int fin) {
    FILE *f_origen, *f_destino;
    char buffer[100];
    int tamano;

    f_origen = fopen(archivo_origen, "rb");
    if (f_origen == NULL) {
        printf("Error al abrir el archivo de origen\n");
        return;
    }

    f_destino = fopen(archivo_destino, "wb");
    if (f_destino == NULL) {
        printf("Error al abrir el archivo de destino\n");
        fclose(f_origen);
        return;
    }

    fseek(f_origen, inicio, SEEK_SET);
    tamano = fin - inicio;
    fread(buffer, tamano, 1, f_origen);
    fwrite(buffer, tamano, 1, f_destino);

    fclose(f_origen);
    fclose(f_destino);

    printf("Contenido copiado correctamente\n");
}


void encontrarUsuario(char* archivo_origen){

}
