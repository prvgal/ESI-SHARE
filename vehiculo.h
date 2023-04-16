#ifndef PRUEBA_VEHICULOS_H_INCLUDED
#define PRUEBA_VEHICULOS_H_INCLUDED

#include "vehiculo.h"
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


    //Precondici�n: El procedimiento recibe una estructura ya rellena de tipo vehiculo_inf, y un puntero a fichero en el que escribir.
    //Postcondici�n:  La informaci�n contenida en la estructura se habr� almacenado en el fichero.
    void escribir_fichero(vehiculo_inf, FILE *);

    //Precondici�n: El procedimiento recibe un vector de estructuras para captar los datos del fichero dado.
    //Postcondici�n: El procedimiento habr� le�do la informaci�n del fichero dado y la habr� guardado en el vector de estructuras dado.
    void leer_fichero_vehiculo(vehiculo_inf *, FILE *);

    //Precondici�n: Ninguna.
    //Postcondici�n: El administrador habr� elegido alguna de las opciones expuestas en un switch que permite: <1> Dar un veh�culo de alta <2> Dar un veh�culo de baja
    // <3> Listar todos los veh�culos <4> Modificar la informaci�n de un veh�culo <5> Volver al men� de administrador principal.
	void admin_veh();

	//Precondici�n:
    //Postcondici�n:
    void usuario();

    //Precondici�n: Recibe la ID del usuario que se est� registrando en el momento.
    //Postcondici�n: Se habr�n registrado los veh�culos que haya indicado el usuario al registrarse si es que tiene, se habr� continuado normalmente el registro en caso contrario.
    void menu_registro_vehiculo(tPerfil);

    //*******FUNCIONES PRIVADAS*******


    //Precondici�n: El procedimiento recibe una estructura de tipo vehiculo_inf.
    //Postcondici�n: El procedimiento habr� sido rellenada para a continuaci�n guardar la informaci�n en el fichero vehiculo.txt.
    static void introducir_datos_veh(vehiculo_inf);

    //Precondici�n: El usuario habr� creado su propia cuenta, de manera el dato l�gico "tienecoche" es igual a 1.
    //Postcondici�n: El usuario habr� cambiado alg�n dato acerca de su veh�culo.
    static void cambiar_datos_veh(vehiculo_inf);

    //Precondici�n: Recoge un vector de caracter o cadena de caracteres del campo id_mat del registro vehiculo, con lo que
    //debe estar habilitada la informaci�n del veh�culo.
    //Postcondici�n: La cadena vehiculo.matricula tendr� una matr�cula guardada.
    static void pedir_matricula(char []);

    //Precondici�n: Recibe la variable entera num_plazas, con lo que debe estar habilitada la informaci�n del veh�culo.
    //Postcondicion: El entero vehiculo.num_plazas ser� un n�mero entre 0 y 10.
    static void pedir_plazas_veh(int);

    //Precondici�n: Debe estar habilitada la informaci�n del veh�culo, concretamente el campo "desc_veh".
    //Postcondici�n: El usuario habr� introducido una breve descripci�n acerca de su veh�culo.
    static void inserta_descripcion(char []);

    //Precondici�n: Recibe una cadena de cualquier longitud, de manera que su contenido (que no espacio en memoria) se acortar� seg�n encuentre \n, es decir, queden espacios
	//libres.
	//Postcondici�n: La cadena dada habr� sido acortada, sustituyendo \n por \0.
    static void acortar_cadena(char []);

    //Precondici�n: Recibe una cadena (matr�cula) de longitud IDMAT, de manera que comprueba si es acorde al formato de matriculaci�n espa�ola (000AAA).
    //Postcondici�n: Devuelve 1 si la matr�cula es v�lida, 0 en caso contrario.
    static int comprobar_validez_mat(char []);

    //Precondici�n: Recibe una cadena (ID de usuario) de longitud IDUSU, de manera que comprueba si es acorde al formato 0000.
    //Postcondici�n: Devuelve 1 si la ID es v�lida, 0 en caso contrario.
    static int comprobar_validez_id(char []);

    //Precondici�n: Recibe la ID de un usuario (cadena) dada por un administrador para borrar su informaci�n de veh�culo/s.
    //Postcondici�n: El veh�culo/s asociado/s al usuario habr�/n sido borrado/s del listado en vehiculo.txt
    static void borrar_vehiculos(char [], int );

    //Precondici�n: Ninguna.
    //Postcondici�n: El administrador habr� introducido los datos necesarios para poder llamar a borrar_vehiculos y as� borrar los veh�culos deseados del listado.
    static void baja_vehiculo();

    //Precondici�n: Ninguna.
    //Postcondici�n: Se habr�n introducido uno o m�s nuevos veh�culos en el listado presente en el fichero vehiculo.txt, asociados a una ID dada por el administrador.
    static void alta_vehiculo();

    //Precondici�n: Debe existir el fichero vehiculo.txt.
    //Postcondici�n: Imprime por pantalla el contenido del fichero vehiculo.txt
    static void listar_vehiculos();

    //Precondici�n: Ninguna.
    //Postcondici�n: Busca y, si encuentra una l�nea del fichero vehiculo.txt coincidente con una matr�cula y un usuario pedidos en el procedimiento, modifica los datos de dicha l�nea a gusto del administrador.
    static void admin_modif_veh();

    //Precondici�n: Recibe una ID de usuario y una matr�cula (ambos cadenas) que han sido verificados previamente.
    //Postcondici�n: Busca y, si encuentra una l�nea del fichero vehiculo.txt coincidente con la matr�cula y el usuario, modifica los datos de dicha l�nea a gusto del administrador.
    static void buscar_modificar_vehiculo(char [], char []);

#endif // PRUEBA_VEHICULOS_H_INCLUDED
