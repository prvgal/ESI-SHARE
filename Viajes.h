#ifndef _VIAJES_H_
#define _VIAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "perfiles.h"

#define MAX_VIAJES 90
#define FECHA 11
#define MATRICULA 8
#define IMPORTE 7
#define TIPO 7
#define HORA 6

typedef struct{
    logico abierto;                 //Si Nplazas > 0 y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior, y no est� anulado
    logico cerrado;                 //Si Nplazas = 0 y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior, y no est� anulado
    logico iniciado;                //Si el viaje ha iniciado (la hora actual est� entre la hora de inicio y hora de llegada) y no se anula
    logico finalizado;              //Si el viaje ha finalizado (la hora actual es  mayor que la hora de llegada) y no ha sido anulado
    logico anulado;                 //Si el viaje ha sido anulado
} estado_viajes;

typedef struct{
    char i_d [7];                        //6 d�gitos
    char matricula [MATRICULA];     //Matr�cula de veh�cula usado para el viaje
    char fecha[FECHA];              //Formato dd/mm/aa
    char hora_inicio [HORA];        //Formato 24h - M�nimo 06:00
    char hora_llegada [HORA];       //Formato 24h - M�ximo 22:30
    int Nplazas;                    //N�mero de plazas disponibles
    char tipo [TIPO];               //Ida o Vuelta
    char importe [IMPORTE];         //Entre 0 y 15 � por persona
    estado_viajes estado;           //Solo un estado activo al mismo tiempo
    logico hoy;                     //Indica si la fecha introducida es hoy
    char anular;                    //Indica si quiere anular un viaje (S) o no (N)
    char usuviaje[ID];
} viajes;

//FUNCIONES PRIVADAS:

//Precondici�n: Recibe un vector de estructuras de tipo viajes y un entero que indicar� la posici�n del usuario en viaje
//Postcondici�n: Habr� introducido fecha en la estructura viaje de la posici�n posViaje

static void introducir_fecha(viajes *viaje, int posViaje);

/*Precondici�n: Recibe un vector de estructuras de tipo viajes y un entero que indicar� la posici�n del usuario en viaje*/
//Postcondici�n: Habr� introducido hora_inicio y hora_llegada en la estructura viaje de la posici�n posViaje

static void horas(viajes *viaje, int posViaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y un entero que indicar� la posici�n del usuario en viaje
//Postcondici�n: Actualiza el n�mero de plazas en la estructura viaje de la posici�n posViaje

static void plazas(viajes *viaje, int posViaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y un entero que indicar� la posici�n del usuario en viaje
//Postcondici�n: Habr� introducido el tipo de viaje en la estructura viaje de la posici�n posViaje: (I) Ida o (V) Vuelta

static void tipo(viajes *viaje, int posViaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y un entero que indicar� la posici�n del usuario en viaje
//Postcondicion: Habr� introducido el importe del viaje en la estructura viaje de la posici�n posViaje

static void importe(viajes *viaje, int posViaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Se actualizar� el estado de todos los viajes de la estructura activando (True) el estado en el que se encuentre el viaje y se desactivarando (False) el anterior si era diferente

static void estado(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondici�n: Se habr� podido modificar alg�n viaje del usuario

static viajes *modviaje(viajes *viaje, char viajeusu [5]);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Se habr� podido modificar cualquier viaje de la estructura

static viajes *modviajeAdmin(viajes *viaje);

//FUNCIONES P�BLICAS:

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Habr� imprimido en un fichero un nuevo viaje de la estructura viajes

void imprimirnuevoviaje(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Habr� imprimido en un fichero la estructura viajes

void imprimirviajes(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Habr� imprimido en un fichero la estructura viajes actualizada tras haber borrado uno

void imprimirviajesborrado(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Rellena la estructura viajes con el contenido del fichero Viajes.txt

void leerviajes(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Imprime por pantalla el contenido de cada posici�n de la estructura viajes

void listarviajes(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Imprime por pantalla los viajes que est�n en estado abierto

void listarviajesabiertos(viajes *viaje);

//Postcondici�n: Devuelve el n�mero de lineas que tiene el fichero

int numeroviajes(void);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Redimensiona la estructura igual al n�mero de viajes actuales del fichero Viajes.txt

viajes *reservarviajes(viajes *viaje);

//Postcondici�n: Crea una estructura de viajes

viajes *CrearListaViajes(void);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondici�n: Imprime por pantalla el men� de opciones del usuario

void menuviajesUsu(char viajeusu [5]);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondici�n: Imprime por pantalla el men� de opciones del administrador

void menuviajesAdmin(char viajeusu [5]);

//Precondici�n: Recibe un vector de estructras de tipo viajes
//Postcondici�n: Redimensiona la estructura a un tama�o m�s que el n�mero de viajes actuales del fichero Viajes.txt

viajes *reservarnuevoviaje(viajes *viaje);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondic�n: Habr� a�adido un viaje nuevo a la estructura viajes y lo habr� imprimido en el fichero Viajes.txt

viajes *publicarviaje(viajes *viaje, char viajeusu [5]);

/*Precondici�n: Recibe una cadena de caracteres que indica la ID del usuario que accede al programa,
una cadena de la estructura tPerfil que indicar� si est� accediendo un usuario o un administrador y un vector de estructuras de tipo viajes*/
//Postcondici�n: Lleva a la funci�n menuviajesUsu o menuviajesAdmin

void menuviajes(char viajeusu [5], char []);

//Precondici�n: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondici�n: Habr� imprimido por pantalla la lista de viajes que ha creado el usuario

int listartusviajes(viajes *viaje, char viajeusu [5]);

//Precondici�n: Recibe un vector de estructuras de tipo viajes
//Postcondici�n: Habr� dado la posibilidad a eliminar alg�n viaje a elecci�n del administrador

viajes *eliminarviaje(viajes *viaje);

#endif
