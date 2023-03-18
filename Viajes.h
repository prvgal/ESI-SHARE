#ifndef _VIAJES_H_
#define _VIAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"

#define MATRICULA 8
#define HORA 6
#define TIPO 2

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

#endif
