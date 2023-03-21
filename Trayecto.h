#ifndef TRAYECTO_H_INCLUDED
#define TRAYECTO_H_INCLUDED



//precondici�n: Debe haberse generado una ID para un viaje (esta ID ser�a de tipo entero)
//postcondici�n: Crea un fichero llamado Pasos.txt donde guarda la ID de un viaje junto con sus respectivas paradas
void paradas_trayecto(viajes);



//precondici�n: Debe haberse generado una ID para un viaje (esta ID ser�a de tipo entero)
//postcondici�n: Permite la elecci�n entre: Agregar paradas, Modificar paradas, Borrar paradas o Cancelar
void gestionar_trayecto(viajes);



//precondici�n: Ninguna
//postcondici�n: Despliega un men� sin funcionalidad, meramente visual e ilustrativo
void eleccion_trayecto();


//precondici�n: Debe haberse generado una ID para un viaje (esta ID ser�a de tipo entero)
//postcondici�n: Permite al usuario modificar las paradas de su trayecto en caso de equivocaci�n
void modificar_trayecto(viajes viaje);



//precondici�n: Debe haberse generado una ID para un viaje (esta ID ser�a de tipo entero)
//postcondici�n: Permite al usuario borrar su registro de trayecto del fichero Pasos.txt
void borrar_trayecto(viajes viaje);



#endif // TRAYECTO_H_INCLUDED
