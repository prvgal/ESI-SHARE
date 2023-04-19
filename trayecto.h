#ifndef TRAYECTO_H_INCLUDED
#define TRAYECTO_H_INCLUDED
#include "viajes.h"
#include "perfiles.h"


//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero) y una localidad para el usuario en concreto (esta Localidad una cadena de 20 caracteres)
//postcondición: Permite la elección entre: Agregar paradas, Modificar paradas, Borrar paradas, listar viajes comunes al usuario o Cancelar
void gestionar_trayecto(char idt [7], tPerfil);



//precondición: Debe haberse generado una localidad para el usuario en concreto (esta Localidad una cadena de 20 caracteres)
//postcondición: Imprime por pantalla al usuario una lista con todos los viajes que pasen por su localidad con sus respectivas ID
void mostrar_paradas(char[]);



//*Nota*: Las siguientes funciones cuentan con la misma precondición y postcondición
//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Despliega un menú sin funcionalidad, meramente visual e ilustrativo
//********************************************************************************************************


void inicio_trayecto(char idt [7]);

static void final_ESI(char idt [7]);

static void ida_ESI_cadiz(char idt [7]);

static void ida_ESI_sanfer(char idt [7]);

static void ida_ESI_sanfer_cadiz(char idt [7]);

static void ida_ESI_sanfer_cadiz_fin(char idt [7]);

static void ida_ESI_jerez(char idt [7]);

static void ida_ESI_jerez_puerto(char idt [7]);

static void ida_ESI_puerto(char idt [7]);

static void inicio_ESI(char idt [7]);

static void ESI_cadiz(char idt [7]);

static void ESI_sanfernando(char idt [7]);

static void ESI_sanfer_puertor(char idt [7]);

static void ESI_jerez(char idt [7]);

static void ESI_jerez_puertor(char idt [7]);

static void ESI_puertostamaria(char idt [7]);


//********************************************************************************************************



//*Nota*: Las siguientes funciones cuentan con la misma precondición y postcondición
//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Imprime en el fichero Pasos.txt la ID del viaje y las paradas a las que el mismo está asociado e imprime la ruta paso a paso por pantalla al usuario
//********************************************************************************************************


static void ida_ESI_cadiz_puertor(char idt [7]);

static void ida_ESI_cadiz_fin(char idt [7]);

static void ida_ESI_sanfer_cadiz_puertor(char idt [7]);

static void ida_ESI_sanfer_cadiz_fin(char idt [7]);

static void ida_ESI_sanfer_puertor(char idt [7]);

static void ida_ESI_sanfer_fin(char idt [7]);

static void ida_ESI_jerez_puerto_puertor_fin(char idt [7]);

static void ida_ESI_jerez_puertor_fin(char idt [7]);

static void ida_ESI_jerez_puertor(char idt [7]);

static void ida_ESI_jerez_fin(char idt [7]);

static void ida_ESI_puerto_puertor_fin(char idt [7]);

static void ida_ESI_puerto_fin(char idt [7]);

static void ida_ESI_puertor(char idt [7]);

static void ESI_cadiz_puertor(char idt [7]);

static void ESI_cadiz_fin(char idt [7]);

static void ESI_puertoreal(char idt [7]);

static void ESI_sanfer_cadiz(char idt [7]);

static void ESI_sanfer_cadiz_puerto(char idt [7]);

static void ESI_sanfer_puertor_fin(char idt [7]);

static void ESI_sanfer_fin(char idt [7]);

static void ESI_jerez_puertor_puerto_fin(char idt [7]);

static void ESI_jerez_puertor_fin(char idt [7]);

static void ESI_jerez_puerto(char idt [7]);

static void ESI_jerez_fin(char idt [7]);

static void ESI_puerto_puertor_fin(char idt [7]);

static void ESI_puerto_fin(char idt [7]);


//********************************************************************************************************



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite al usuario modificar las paradas de su trayecto en caso de equivocación
static void modificar_trayecto(char idt [7]);



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite al usuario borrar su registro de trayecto del fichero Pasos.txt
static void borrar_trayecto(char idt [7]);



#endif // TRAYECTO_H_INCLUDED