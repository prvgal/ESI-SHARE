#ifndef PRUEBA_VEHICULOS_H_INCLUDED
#define PRUEBA_VEHICULOS_H_INCLUDED

#include <string.h>
#include "tipos.h"
#include <stdlib.h>
#include <stdio.h>

#define CARACTERES 51
#define IDMAT 8
#define IDUSU 5

    typedef struct{
        char id_mat[IDMAT]; 
        char id_usuario[IDUSU];
        char desc_veh[CARACTERES];
        int num_plazas;
    }vehiculo_inf;

    //*******FUNCIONES PUBLICAS*******


    //Precondición: El usuario habrá creado su propia cuenta, de manera el dato lógico "tienecoche" es igual a 1.
    //Postcondición: El usuario habrá cambiado algún dato acerca de su vehículo.
    void cambiar_datos(vehiculo_inf, FILE *);

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
    
    //Precondición: La función recibe una estructura de tipo vehiculo_inf.
    //Postcondición: La función habrá sido rellenada para a continuación guardar la información en el fichero vehiculo.txt.
    void introducir_datos(vehiculo_inf, FILE *);
    
    //Precondición: La función recibe una estructura ya rellena de tipo vehiculo_inf, y un puntero a fichero en el que escribir.
    //Postcondición:  La información contenida en la estructura se habrá almacenado en el fichero.
    void escribir_fichero(vehiculo_inf, FILE *);
    
    
    //*******FUNCIONES PRIVADAS*******
    
    
    //Precondición: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la información del vehículo.
    //Postcondición: La cadena vehiculo.matricula tendrá una matrícula guardada.
    void pedir_matricula(char [IDMAT]);
    
    //Precondición: Recibe la variable entera num_plazas, con lo que debe estar habilitada la información del vehículo.
    //Postcondicion: El entero vehiculo.num_plazas será un número entre 0 y 10.
    void pedir_plazas_veh(int);
    
    //Precondición: Debe estar habilitada la información del vehículo, concretamente el campo "desc_veh".
    //Postcondición: El usuario habrá introducido una breve descripción acerca de su vehículo.
    void inserta_descripcion(char [CARACTERES]);
    
    //Precondición: Recibe una cadena de cualquier longitud, de manera que se acortará según encuentre \n, es decir, queden espacios 
	//libres.
	//Postcondición: La cadena dada habrá sido acortada, sustituyendo \n por \0.
    void acortar_cadena(char []);

#endif // PRUEBA_VEHICULOS_H_INCLUDED