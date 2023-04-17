#ifndef TRAYECTO_H_INCLUDED
#define TRAYECTO_H_INCLUDED
#include "viajes.h"
#include "perfiles.h"


//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero) y una localidad para el usuario en concreto (esta Localidad una cadena de 20 caracteres)
//postcondición: Permite la elección entre: Agregar paradas, Modificar paradas, Borrar paradas o Cancelar
void gestionar_trayecto(viajes, tPerfil);



//precondición: Debe haberse generado una localidad para el usuario en concreto (esta Localidad una cadena de 20 caracteres)
//postcondición: Imprime por pantalla al usuario una lista con todos los viajes que pasen por su localidad con sus respectivas ID
void mostrar_paradas(tPerfil);



//*Nota*: Las siguientes funciones cuentan con la misma precondición y postcondición
//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Despliega un menú sin funcionalidad, meramente visual e ilustrativo
//********************************************************************************************************


void inicio_trayecto(viajes);

static void final_ESI(viajes);

static void ida_ESI_cadiz(viajes);

static void ida_ESI_sanfer(viajes);

static void ida_ESI_sanfer_cadiz(viajes);

static void ida_ESI_sanfer_cadiz_fin(viajes);

static void ida_ESI_jerez(viajes);

static void ida_ESI_jerez_puerto(viajes);

static void ida_ESI_puerto(viajes);

static void inicio_ESI(viajes);

static void ESI_cadiz(viajes);

static void ESI_sanfernando(viajes);

static void ESI_sanfer_puertor(viajes);

static void ESI_jerez(viajes);

static void ESI_jerez_puertor(viajes);

static void ESI_puertostamaria(viajes);


//********************************************************************************************************



//*Nota*: Las siguientes funciones cuentan con la misma precondición y postcondición
//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Imprime en el fichero Pasos.txt la ID del viaje y las paradas a las que el mismo está asociado e imprime la ruta paso a paso por pantalla al usuario
//********************************************************************************************************


static void ida_ESI_cadiz_puertor(viajes);

static void ida_ESI_cadiz_fin(viajes);

static void ida_ESI_sanfer_cadiz_puertor(viajes);

static void ida_ESI_sanfer_cadiz_fin(viajes);

static void ida_ESI_sanfer_puertor(viajes);

static void ida_ESI_sanfer_fin(viajes);

static void ida_ESI_jerez_puerto_puertor_fin(viajes);

static void ida_ESI_jerez_puertor_fin(viajes);

static void ida_ESI_jerez_puertor(viajes);

static void ida_ESI_jerez_fin(viajes);

static void ida_ESI_puerto_puertor_fin(viajes);

static void ida_ESI_puerto_fin(viajes);

static void ida_ESI_puertor(viajes);

static void ESI_cadiz_puertor(viajes);

static void ESI_cadiz_fin(viajes);

static void ESI_puertoreal(viajes);

static void ESI_sanfer_cadiz(viajes);

static void ESI_sanfer_cadiz_puerto(viajes);

static void ESI_sanfer_puertor_fin(viajes);

static void ESI_sanfer_fin(viajes);

static void ESI_jerez_puertor_puerto_fin(viajes);

static void ESI_jerez_puertor_fin(viajes);

static void ESI_jerez_puerto(viajes);

static void ESI_jerez_fin(viajes);

static void ESI_puerto_puertor_fin(viajes);

static void ESI_puerto_fin(viajes);


//********************************************************************************************************



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite al usuario modificar las paradas de su trayecto en caso de equivocación
static void modificar_trayecto(viajes);



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite al usuario borrar su registro de trayecto del fichero Pasos.txt
static void borrar_trayecto(viajes);



#endif // TRAYECTO_H_INCLUDED
