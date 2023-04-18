#include "Viajes.c"
#include "perfiles.c"

int main(){
	int pos;
    tPerfil *info;

    info = CrearListaDePerfiles();
    CargarPerfiles(info);

    pos = Inicio(info);

    Menu(info, pos);

    free(info);
    return 0;
}
