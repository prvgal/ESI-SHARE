#include "tipos.h"
#include <string.h>

void EliminarSaltoLinea(char *cad){
    int longCad = strlen(cad);

    if(cad[longCad - 1] == '\n')
        cad[longCad - 1] = '\0';    

}

logico vectores_iguales(int longitud1, int longitud2, int vec1[],int vec2[]) {
		int i, valor_vec1, valor_vec2;
		
		if (longitud1!=longitud2){
			return False;
	  	}
  		for (i=0;i<longitud1;i++){
  			
			if (vec1[i]!=vec2[i]) {
				return False;  
  			}
  		}
 	 return True;
	}