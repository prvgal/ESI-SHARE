#ifndef PRUEBA_VEHICULOS_H_INCLUDED
#define PRUEBA_VEHICULOS_H_INCLUDED

#include "vehiculo.h"
#include "perfiles.h"

#define CARACTERES 51
#define IDMAT 8
#define IDUSU 5

#define MAX_LIN_FICHVEH 66
#define MAX_LIN_FICHVIAJE 60

    typedef struct{
        char id_mat[IDMAT];         //Matrícula del vehículo
        char id_usuario[IDUSU];     //ID de usuario asociado al vehículo
        char desc_veh[CARACTERES];  //Breve descripción del vehículo
        int num_plazas;             //Número de plazas de las que dispone el vehículo
    }vehiculo_inf;

    //*******FUNCIONES PUBLICAS*******


    //Precondición: El procedimiento recibe una estructura ya rellena de tipo vehiculo_inf, y un puntero a fichero en el que escribir.
    //Postcondición:  La información contenida en la estructura se habrá almacenado en el fichero.
    void escribir_fichero(vehiculo_inf, FILE *);

    //Precondición: El procedimiento recibe un vector de estructuras para captar los datos del fichero dado.
    //Postcondición: El procedimiento habrá leído la información del fichero dado y la habrá guardado en el vector de estructuras dado.
    void leer_fichero_vehiculo(int , vehiculo_inf *, FILE *);

    //Precondición: Ninguna.
    //Postcondición: El administrador habrá elegido alguna de las opciones expuestas en un switch que permite: <1> Dar un vehículo de alta <2> Dar un vehículo de baja
    // <3> Listar todos los vehículos <4> Modificar la información de un vehículo <5> Volver al menú de administrador principal.
	void admin_veh();

	//Precondición:
    //Postcondición:
    void usuario_veh();

    //Precondición: Recibe la ID del usuario que se esté registrando en el momento.
    //Postcondición: Se habrán registrado los vehículos que haya indicado el usuario al registrarse si es que tiene, se habrá continuado normalmente el registro en caso contrario.
    void menu_registro_vehiculo(tPerfil);

    //*******FUNCIONES PRIVADAS*******


    //Precondición: El procedimiento recibe una estructura de tipo vehiculo_inf.
    //Postcondición: El procedimiento habrá sido rellenada para a continuación guardar la información en el fichero vehiculo.txt.
    static void introducir_datos_veh(vehiculo_inf);

    //Precondición: El usuario habrá creado su propia cuenta, de manera el dato lógico "tienecoche" es igual a 1.
    //Postcondición: El usuario habrá cambiado algún dato acerca de su vehículo.
    static void cambiar_datos_veh(vehiculo_inf);

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

    //Precondición: Recibe una cadena (ID de usuario) de longitud IDUSU, de manera que comprueba si es acorde al formato 0000.
    //Postcondición: Devuelve 1 si la ID es válida, 0 en caso contrario.
    static int comprobar_validez_id(char []);

    //Precondición: Recibe la ID de un usuario (cadena) dada por un administrador para borrar su información de vehículo/s.
    //Postcondición: El vehículo/s asociado/s al usuario habrá/n sido borrado/s del listado en vehiculo.txt
    static void borrar_vehiculos(char [], int );

    //Precondición: Ninguna.
    //Postcondición: El administrador habrá introducido los datos necesarios para poder llamar a borrar_vehiculos y así borrar los vehículos deseados del listado.
    static void baja_vehiculo();

    //Precondición: Ninguna.
    //Postcondición: Se habrán introducido uno o más nuevos vehículos en el listado presente en el fichero vehiculo.txt, asociados a una ID dada por el administrador.
    static void alta_vehiculo();

    //Precondición: Debe existir el fichero vehiculo.txt.
    //Postcondición: Imprime por pantalla el contenido del fichero vehiculo.txt
    static void listar_vehiculos();

    //Precondición: Ninguna.
    //Postcondición: Busca y, si encuentra una línea del fichero vehiculo.txt coincidente con una matrícula y un usuario pedidos en el procedimiento, modifica los datos de dicha línea a gusto del administrador.
    static void admin_modif_veh();

    //Precondición: Recibe una ID de usuario y una matrícula (ambos cadenas) que han sido verificados previamente.
    //Postcondición: Busca y, si encuentra una línea del fichero vehiculo.txt coincidente con la matrícula y el usuario, modifica los datos de dicha línea a gusto del administrador.
    static void buscar_modificar_vehiculo(char [], char []);

    //Precondición: Recibe una matrícula dada por el administrador.
    //Postcondición: Busca y, si encuentra una línea del fichero Viajes.txt coincidente con la matrícula dada y tenga la etiqueta de "finalizado", imprime los datos de dicha línea por pantalla hasta que termine el fichero.
    static void listar_viajes(char []);


#endif // PRUEBA_VEHICULOS_H_INCLUDED
