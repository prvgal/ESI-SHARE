#include "Viajes.h"
#include "perfiles.h"
#include "vehiculo.h"
#include "trayecto.h"

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
