#ifndef PRUEBA_VEHICULOS_H_INCLUDED
#define PRUEBA_VEHICULOS_H_INCLUDED

#include <string.h>
#include "tipos.h"

#define CARACTERES 51
#define IDMAT 8

    typedef struct{
        char id_mat[IDMAT]; //
        int id_usuario;
        int num_plazas;
        char desc_veh[CARACTERES];
    }vehiculo_inf;


    //*******FUNCIONES PUBLICAS*******


    //Precondici�n: El usuario habr� creado su propia cuenta, de manera el dato l�gico "tienecoche" es igual a 1.
    //Postcondici�n: El usuario habr� cambiado alg�n dato acerca de su veh�culo.
    void cambiar_datos(vehiculo_inf);

    //Precondici�n: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la informaci�n del veh�culo.
    //Postcondici�n: La cadena vehiculo.matricula tendr� una matr�cula guardada.
    void pedir_matricula(char *);

    //Precondici�n: Recibe la variable entera num_plazas, con lo que debe estar habilitada la informaci�n del veh�culo.
    //Postcondicion: El entero vehiculo.num_plazas ser� un n�mero entre 0 y 10.
    void pedir_plazas_veh(int);

    //Precondici�n: Debe estar habilitada la informaci�n del veh�culo, concretamente el campo "desc_veh".
    //Postcondici�n: El usuario habr� introducido una breve descripci�n acerca de su veh�culo.
    void inserta_descripcion(char *);


#endif // PRUEBA_VEHICULOS_H_INCLUDED
