#ifndef _VIAJES_H_
#define _VIAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tipos.h"

#define FECHA 11
#define MATRICULA 8
#define IMPORTE 7
#define TIPO 7
#define HORA 6

typedef struct{
    logico abierto;                 //Si Nplazas > 0 y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior, y no está anulado
    logico cerrado;                 //Si Nplazas = 0 y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior, y no está anulado
    logico iniciado;                //Si el viaje ha iniciado (la hora actual está entre la hora de inicio y hora de llegada) y no se anula
    logico finalizado;              //Si el viaje ha finalizado (la hora actual es  mayor que la hora de llegada) y no ha sido anulado
    logico anulado;                 //Si el viaje ha sido anulado
} estado_viajes;

typedef struct{
    int ID;                         //6 dígitos
    char matricula [MATRICULA];     //Matrícula de vehícula usado para el viaje
    char fecha[FECHA];              //Formato dd/mm/aa
    char hora_inicio [HORA];        //Formato 24h - Mínimo 06:00
    char hora_llegada [HORA];       //Formato 24h - Máximo 22:30
    int Nplazas;                    //Número de plazas disponibles
    char tipo [TIPO];               //Ida o Vuelta
    char importe [IMPORTE];         //Entre 0 y 15 € por persona
    estado_viajes estado;           //Solo un estado activo al mismo tiempo
    logico hoy;                     //Indica si la fecha introducida es hoy
} viajes;

//FUNCIONES PRIVADAS:

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Asigna una ID en la estructura viaje de la posición posViaje

static void generar_ID_viaje(viajes *viaje, int posViaje);

/*Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje*/
//Postcondición: Habrá introducido fecha en la estructura viaje de la posición posViaje

static void introducir_fecha(viajes *viaje, int posViaje);

/*Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje*/
//Postcondición: Habrá introducido hora_inicio y hora_llegada en la estructura viaje de la posición posViaje

static void horas(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Actualiza el número de plazas en la estructura viaje de la posición posViaje

static void plazas(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Habrá introducido el tipo de viaje en la estructura viaje de la posición posViaje: (I) Ida o (V) Vuelta

static void tipo(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondicion: Habrá introducido el importe del viaje en la estructura viaje de la posición posViaje

static void importe(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Se activará (True) el estado en el que se encuentre el viaje y se desactivará (False) el anterior si era diferente

static void estado(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Se habrá modificado algo en la estructura
static void modviaje(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Habrá imprimido en un fichero la estructura viaje
static void imprimirviajes(viajes *viaje);

#endif
