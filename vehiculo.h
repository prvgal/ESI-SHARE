#ifndef PRUEBA_VEHICULOS_H_INCLUDED
#define PRUEBA_VEHICULOS_H_INCLUDED

#include "vehiculo.h"
#include "tipos.h"
#include "perfiles.h"
#include "Viajes.h"

#define CARACTERES 51
#define IDMAT 8
#define IDUSU 5

#define MAX_LIN_FICHVEH 66
#define MAX_LIN_FICHVIAJE 60

    typedef struct{
        char id_mat[IDMAT];         //Matr�cula del veh�culo
        char id_usuario[IDUSU];     //ID de usuario asociado al veh�culo
        char desc_veh[CARACTERES];  //Breve descripci�n del veh�culo
        int num_plazas;             //N�mero de plazas de las que dispone el veh�culo
    }vehiculo_inf;

    //*******FUNCIONES PUBLICAS*******


    //Precondici�n: El procedimiento recibe una estructura ya rellena de tipo vehiculo_inf, y un puntero a fichero en el que escribir.
    //Postcondici�n:  La informaci�n contenida en la estructura se habr� almacenado en el fichero.
    void escribir_fichero(vehiculo_inf, FILE *);

    //Precondici�n: El procedimiento recibe un vector de estructuras para captar los datos del fichero dado.
    //Postcondici�n: El procedimiento habr� le�do la informaci�n del fichero dado y la habr� guardado en el vector de estructuras dado.
    void leer_fichero_vehiculo(int , vehiculo_inf *, FILE *);

    //Precondici�n: Ninguna.
    //Postcondici�n: El administrador habr� elegido alguna de las opciones expuestas en un switch que permite: <1> Dar un veh�culo de alta <2> Dar un veh�culo de baja
    // <3> Listar todos los veh�culos <4> Modificar la informaci�n de un veh�culo <5> Volver al men� de administrador principal.
	void admin_veh();

	//Precondici�n: Recibe una variable estructura tipo tPerfil.
    //Postcondici�n: El usuario habr� realizado alguna acci�n entre: <1> Dar un veh�culo de alta <2> Dar uno de sus veh�culos de baja <3> Ver informaci�n de sus veh�culos <4> Modificar informaci�n de alg�n veh�culo
    //<0> Volver al men� principal.
    void usuario_veh(tPerfil);

    //Precondici�n: Recibe la ID del usuario que se est� registrando en el momento.
    //Postcondici�n: Se habr�n registrado los veh�culos que haya indicado el usuario al registrarse si es que tiene, se habr� continuado normalmente el registro en caso contrario.
    void menu_registro_vehiculo(tPerfil);

    //Precondici�n: Recibe la ID del usuario que est�  registrado en el momento, as� como una estructura de tipo viajes con alg�n dato b�sico.
    //Postcondici�n: Guarda en la estructura el n�mero de plazas y la matr�cula de alguno de los veh�culos del usuario, si tiene. Indica que el usuario no tiene veh�culos registrados en su cuenta en caso contrario.
    void proc_jose(char [], viajes);

    //*******FUNCIONES PRIVADAS*******


    //Precondici�n: El procedimiento recibe una estructura de tipo vehiculo_inf.
    //Postcondici�n: El procedimiento habr� sido rellenada para a continuaci�n guardar la informaci�n en el fichero vehiculo.txt.
    static void introducir_datos_veh(vehiculo_inf);

    //Precondici�n: El usuario habr� creado su propia cuenta, de manera el dato l�gico "tienecoche" es igual a 1.
    //Postcondici�n: El usuario habr� cambiado alg�n dato acerca de su veh�culo.
    //static void cambiar_datos_veh(vehiculo_inf);

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
    static void admin_borrar_vehiculos(char [], int );

    //Precondici�n: Ninguna.
    //Postcondici�n: El administrador habr� introducido los datos necesarios para poder llamar a borrar_vehiculos y as� borrar los veh�culos deseados del listado.
    static void admin_baja_vehiculo();

    //Precondici�n: Ninguna.
    //Postcondici�n: Se habr�n introducido uno o m�s nuevos veh�culos en el listado presente en el fichero vehiculo.txt, asociados a una ID dada por el administrador.
    static void admin_alta_vehiculo();

    //Precondici�n: Debe existir el fichero vehiculo.txt.
    //Postcondici�n: Imprime por pantalla el contenido del fichero vehiculo.txt
    static void listar_vehiculos();

    //Precondici�n: Recibe un matr�cula con la que comparar los veh�culos del fichero vehiculo.txt.
    //Postcondici�n: Imprime por pantalla el vehiculo del fichero vehiculo.txt que coincida con la matricula dada, si lo encuentra. Devuelve True en tal caso, y False en el contrario.
    static logico listar_vehiculos_mat(char []);

    //Precondici�n: Ninguna.
    //Postcondici�n: Busca y, si encuentra una l�nea del fichero vehiculo.txt coincidente con una matr�cula y un usuario pedidos en el procedimiento, modifica los datos de dicha l�nea a gusto del administrador.
    static void admin_modif_veh();

    //Precondici�n: Recibe una ID de usuario y una matr�cula (ambos cadenas) que han sido verificados previamente.
    //Postcondici�n: Busca y, si encuentra una l�nea del fichero vehiculo.txt coincidente con la matr�cula y el usuario, modifica los datos de dicha l�nea a gusto del administrador.
    static void admin_buscar_modificar_vehiculo(char [], char []);

    //Precondici�n: Recibe una matr�cula dada por el administrador.
    //Postcondici�n: Busca y, si encuentra una l�nea del fichero Viajes.txt coincidente con la matr�cula dada y tenga la etiqueta de "finalizado", imprime los datos de dicha l�nea por pantalla hasta que termine el fichero.
    static void viajes_veh(char []);

    //Precondici�n: Ninguna.
    //Postcondici�n: El procedimiento habr� pedido al usuario una matr�cula para buscar y, en caso afirmativo, habr� impreso por pantalla todos los viajes finalizados en los que figure el veh�culo con esa matr�cula.
    static void listar_viajes();

    //Precondici�n: Recibe la ID del usuario que est� en el perfil en el momento.
    //Postcondici�n: El procedimiento habr� realizado alguna de las tareas: <1> Dar un veh�culo de alta <2> Dar uno de sus veh�culo de baja <3> Modificar informaci�n de alg�n veh�culo. <4> Ver informaci�n de sus veh�culos.
    //<0> Volver al men� anterior.
    static void usuario_alta_vehiculo(char []);

    //Precondici�n: Recibe la ID del usuario que est� en el perfil en el momento, as� como una matr�cula dada por el usuario.
    //Postcondici�n: El procedimiento habr� borrado del registro el veh�culo con la matr�cula dada (s�lo si es suyo), no hace nada en caso contrario.
    static void usuario_borrar_vehiculo(char [], char []);

    //Precondici�n: Recibe la ID del usuario que est� en el perfil en el momento.
    //Postcondici�n: El procedimiento habr� borrado del registro el veh�culo con la matr�cula dada dentro del mismo (s�lo si es suyo), no hace nada en caso contrario.
    static void usuario_baja_vehiculo(char []);

    //Precondici�n: Recibe la ID del usuario que est� en el perfil en el momento.
    //Postcondici�n: El procedimiento habr� impreso la informaci�n de los veh�culos que el usuario tenga dados de alta.
    static void usuario_listar_vehiculos(char []);

    //Precondici�n: Recibe una matr�cula e ID de usuario (cadenas) con las que buscar en el fichero vehiculo.txt
    //Postcondici�n: El procedimiento habr� modificado la informaci�n ligada a la matr�cula recibida.
    static void usuario_modificar_vehiculo(char [], char []);

    //Precondici�n: Recibe la ID del usuario que est� en el perfil en el momento.
    //Postcondici�n: El procedimiento habr� recibido una matr�cula y con ella habr� llamado al procedimiento usuario_modificar_vehiculo, cambiando la informaci�n ligada a la matr�cula recibida.
    static void usuario_cambiar_informacion_vehiculo(char []);

    //Precondici�n: Recibe la ID del usuario que est� en el perfil en el momento.
    //Postcondici�n: Devuelve el n�mero de veh�culos asociados a la ID recibida.
    static int contar_vehiculos(char []);

#endif // PRUEBA_VEHICULOS_H_INCLUDED
