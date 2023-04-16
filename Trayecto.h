#ifndef TRAYECTO_H_INCLUDED
#define TRAYECTO_H_INCLUDED
#include "viajes.h"


//precondici?n: Debe haberse generado una ID para un viaje (esta ID ser?a de tipo entero)
//postcondici?n: Permite la elecci?n entre: Agregar paradas, Modificar paradas, Borrar paradas o Cancelar
void gestionar_trayecto(viajes);



//*Nota*: Las siguientes funciones cuentan con la misma precondici?n y postcondici?n
//precondici?n: Debe haberse generado una ID para un viaje (esta ID ser?a de tipo entero)
//postcondici?n: Despliega un men? sin funcionalidad, meramente visual e ilustrativo
//********************************************************************************************************


static void inicio_trayecto(viajes);

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



//*Nota*: Las siguientes funciones cuentan con la misma precondici?n y postcondici?n
//precondici?n: Debe haberse generado una ID para un viaje (esta ID ser?a de tipo entero)
//postcondici?n: Imprime en el fichero Pasos.txt la ID del viaje y las paradas a las que el mismo est? asociado e imprime la ruta paso a paso por pantalla al usuario
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



//precondici?n: Debe haberse generado una ID para un viaje (esta ID ser?a de tipo entero)
//postcondici?n: Permite al usuario modificar las paradas de su trayecto en caso de equivocaci?n
static void modificar_trayecto(viajes);



//precondici?n: Debe haberse generado una ID para un viaje (esta ID ser?a de tipo entero)
//postcondici?n: Permite al usuario borrar su registro de trayecto del fichero Pasos.txt
static void borrar_trayecto(viajes);



#endif // TRAYECTO_H_INCLUDED
