#ifndef TRAYECTO_H_INCLUDED
#define TRAYECTO_H_INCLUDED



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Crea un fichero llamado Pasos.txt donde guarda la ID de un viaje junto con sus respectivas paradas
void paradas_trayecto(viajes);



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite la elección entre: Agregar paradas, Modificar paradas, Borrar paradas o Cancelar
void gestionar_trayecto(viajes);



//precondición: Ninguna
//postcondición: Despliega un menú sin funcionalidad, meramente visual e ilustrativo
void eleccion_trayecto();


//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite al usuario modificar las paradas de su trayecto en caso de equivocación
void modificar_trayecto(viajes viaje);



//precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
//postcondición: Permite al usuario borrar su registro de trayecto del fichero Pasos.txt
void borrar_trayecto(viajes viaje);



#endif // TRAYECTO_H_INCLUDED
