#include "tipos.h"
#include <string.h>

void EliminarSaltoLinea(char *cad){
    int longCad = strlen(cad);

    if(cad[longCad - 1] == '\n')
        cad[longCad - 1] = '\0';    

}