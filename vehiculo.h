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


    //Precondición: El usuario habrá creado su propia cuenta, de manera el dato lógico "tienecoche" es igual a 1.
    //Postcondición: El usuario habrá cambiado algún dato acerca de su vehículo.
    void cambiar_datos(vehiculo_inf);

    //Precondición: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la información del vehículo.
    //Postcondición: La cadena vehiculo.matricula tendrá una matrícula guardada.
    void pedir_matricula(char *);

    //Precondición: Recibe la variable entera num_plazas, con lo que debe estar habilitada la información del vehículo.
    //Postcondicion: El entero vehiculo.num_plazas será un número entre 0 y 10.
    void pedir_plazas_veh(int);

    //Precondición: Debe estar habilitada la información del vehículo, concretamente el campo "desc_veh".
    //Postcondición: El usuario habrá introducido una breve descripción acerca de su vehículo.
    void inserta_descripcion(char *);

    /*void leer_fichero(FILE, vehiculo_inf);*/

#endif // PRUEBA_VEHICULOS_H_INCLUDED
