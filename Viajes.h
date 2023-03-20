#ifndef _VIAJES_H_
#define _VIAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"

#define MATRICULA 8
#define HORA 6

typedef struct{
    logico abierto;
    logico cerrado;
    logico iniciado;
    logico finalizado;
    logico anulado;
} estado_viajes;

typedef struct{
    int ID;                         //6 dígitos
    char matricula [MATRICULA];     //Matrícula de vehícula usado para el viaje
    char fecha[11];                 //Formato dd/mm/aa
    char hora_inicio [HORA];        //Formato 24h - Mínimo 06:00
    char hora_llegada [HORA];       //Formato 24h - Máximo 22:30
    int Nplazas;                    //Número de plazas disponibles
    char tipo;                      //I - Ida o V - Vuelta
    float importe;                  //Entre 0 y 15 € por persona
    estado_viajes estado;           //Solo un estado activo al mismo tiempo
} viajes;

//FUNCIONES PRIVADAS:

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Asigna una ID en la estructura viaje de la posición posUsuario

static void generar_ID_viaje(viajes *viaje, int posUsuario);

/*Precondición: Recibe un vector de estructuras de tipo viajes, un entero que indicará la posición del usuario en viaje
y la dirección de memoria a un puntero booleano que indicará si la fecha introducida es hoy*/
//Postcondición: Habrá introducido fecha en la estructura viaje de la posición posUsuario

static void introducir_fecha(viajes *viaje, int posUsuario, logico *hoy);

/*Precondición: Recibe un vector de estructuras de tipo viajes, un entero que indicará la posición del usuario en viaje
y un booleano que indicará si la fecha introducida es hoy*/
//Postcondición: Habrá introducido hora_inicio y hora_llegada en la estructura viaje de la posición posUsuario

static void horas(viajes *viaje, int posUsuario, logico hoy);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Actualiza el número de plazas en la estructura viaje de la posición posUsuario

static void plazas(viajes *viaje, int posUsuario);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicará la posición del usuario en viaje
//Postcondición: Habrá introducido el tipo de viaje en la estructura viaje de la posición posUsuario: (I) Ida o (V) Vuelta

static void tipo(viajes *viaje, int posUsuario);

#endif
