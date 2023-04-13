#ifndef PRUEBA_VEHICULOS_H_INCLUDED
#define PRUEBA_VEHICULOS_H_INCLUDED

#include "vehiculo.h"
#include <stdio.h>
#include "perfiles.h"

#define CARACTERES 51
#define IDMAT 8
#define IDUSU 5
#define LONGVEC 5
#define MAX_LIN_FICHVEH 65

    typedef struct{
        char id_mat[IDMAT];
        char id_usuario[IDUSU];
        char desc_veh[CARACTERES];
        int num_plazas;
    }vehiculo_inf;

    //*******FUNCIONES PUBLICAS*******


    //Precondición: El usuario habrá creado su propia cuenta, de manera el dato lógico "tienecoche" es igual a 1.
    //Postcondición: El usuario habrá cambiado algún dato acerca de su vehículo.
    void cambiar_datos_veh(vehiculo_inf, FILE *);

    //Precondición: El procedimiento recibe una estructura de tipo vehiculo_inf.
    //Postcondición: El procedimiento habrá sido rellenada para a continuación guardar la información en el fichero vehiculo.txt.
    void introducir_datos_veh(vehiculo_inf, tPerfiles);

    //Precondición: El procedimiento recibe una estructura ya rellena de tipo vehiculo_inf, y un puntero a fichero en el que escribir.
    //Postcondición:  La información contenida en la estructura se habrá almacenado en el fichero.
    void escribir_fichero(vehiculo_inf, FILE *);

    //Precondición: El procedimiento recibe un vector de estructuras para captar los datos del fichero dado.
    //Postcondición: El procedimiento habrá leído la información del fichero dado y la habrá guardado en el vector de estructuras dado.
    void leer_fichero_vehiculo(vehiculo_inf *, FILE *);
    
    //Precondición: 
    //Postcondición:
	void admin_veh(tPerfiles);
	
	//Precondición: 
    //Postcondición:
    void usuario();
    
    //Precondición: 
    //Postcondición:
    void menu_registro_vehiculo(tPerfiles);

    //*******FUNCIONES PRIVADAS*******


    //Precondición: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la información del vehículo.
    //Postcondición: La cadena vehiculo.matricula tendrá una matrícula guardada.
    static void pedir_matricula(char []);

    //Precondición: Recibe la variable entera num_plazas, con lo que debe estar habilitada la información del vehículo.
    //Postcondicion: El entero vehiculo.num_plazas será un número entre 0 y 10.
    static void pedir_plazas_veh(int);

    //Precondición: Debe estar habilitada la información del vehículo, concretamente el campo "desc_veh".
    //Postcondición: El usuario habrá introducido una breve descripción acerca de su vehículo.
    static void inserta_descripcion(char []);

    //Precondición: Recibe una cadena de cualquier longitud, de manera que su contenido (que no espacio en memoria) se acortará según encuentre \n, es decir, queden espacios
	//libres.
	//Postcondición: La cadena dada habrá sido acortada, sustituyendo \n por \0.
    static void acortar_cadena(char []);
    
    //Precondición: Recibe una cadena (matrícula) de longitud IDMAT, de manera que comprueba si es acorde al formato de matriculación española (000AAA).
    //Postcondición: Devuelve 1 si la matrícula es válida, 0 en caso contrario.
    static int comprobar_validez_mat(char []);
    
    //Precondición:
    //Postcondición:
    static void bajavehiculo(vehiculo_inf);
    
    //Precondición: Recibe una ID (que debe ser de un usuario ya existente bajo comprobación del administrador).
    //Postcondición: Se habrá introducido un nuevo vehículo en el listado presente el fichero vehiculo.txt
    static void altavehiculo(tPerfiles);

#endif // PRUEBA_VEHICULOS_H_INCLUDED
