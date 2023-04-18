```c
static void borrar_trayecto(viajes viaje){

    FILE *pasos, *pasosaux;
    char linea_borrar[100], linea[100];
    int ID;
    pasos = fopen("Pasos.txt", "r");                    //(1)
    pasosaux = fopen("PasosAux.txt", "w");              //(2)

    while ((fscanf(pasos, "%[^-]", &ID))!=EOF) {        //(3)
        if (ID == viaje.ID) {                           //(4)
            fgets(linea, 100, pasos);                   //(5)
            strcpy(linea_borrar, linea);                //(6)
        } else {                                        //(7)
            fputs(linea, pasosaux);                     //(8)
        }                                               //(9)
    }                                                   //(10)

    fclose(pasos);                                      //(11)
    fclose(pasosaux);                                   //(12)

    remove("Pasos.txt");                                //(13)
    rename("PasosAux.txt", "Pasos.txt");                //(14)
    setlocale(LC_ALL, "");                              //(15)
    printf("Paradas borradas correctamene \n");         //(16)
}                                   
```


##### **Precondición:** Debe haberse generado una ID para un viaje (esta ID sería de tipo entero) y una localidad para el usuario en concreto (esta Localidad una cadena de 20 caracteres)
##### **postcondición:** Permite la elección entre: Agregar paradas, Modificar paradas, Borrar paradas, listar viajes comunes al usuario o Cancelar
*void gestionar_trayecto(viajes);*


##### **Precondición:** Debe haberse generado una localidad para el usuario en concreto (esta Localidad una cadena de 20 caracteres)
##### **Postcondición:** Imprime por pantalla al usuario una lista con todos los viajes que pasen por su localidad con sus respectivas ID
*mostrar_paradas(viajes, tPerfil);*


#### *Nota*: Las siguientes funciones cuentan con la misma precondición y postcondición
##### **Precondición:** Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
##### **Postcondición:** Despliega un menú sin funcionalidad, meramente visual e ilustrativo
# ***********************************************************************************************


*void inicio_trayecto(viajes);*

*static void final_ESI(viajes);*

*static void ida_ESI_cadiz(viajes);*

*static void ida_ESI_sanfer(viajes);*

*static void ida_ESI_sanfer_cadiz(viajes);*

*static void ida_ESI_sanfer_cadiz_fin(viajes);*

*static void ida_ESI_jerez(viajes);*

*static void ida_ESI_jerez_puerto(viajes);*

*static void ida_ESI_puerto(viajes);*

*static void inicio_ESI(viajes);*

*static void ESI_cadiz(viajes);*

*static void ESI_sanfernando(viajes);*

*static void ESI_sanfer_puertor(viajes);*

*static void ESI_jerez(viajes);*

*static void ESI_jerez_puertor(viajes);*

*static void ESI_puertostamaria(viajes);*


# ***********************************************************************************************



#### *Nota*: Las siguientes funciones cuentan con la misma precondición y postcondición
##### **Precondición:** Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
##### **Postcondición:** Imprime en el fichero Pasos.txt la ID del viaje y las paradas a las que el mismo está asociado e imprime la ruta paso a paso por pantalla al usuario
# ***********************************************************************************************


*static void ida_ESI_cadiz_puertor(viajes);*

*static void ida_ESI_cadiz_fin(viajes);*

*static void ida_ESI_sanfer_cadiz_puertor(viajes);*

*static void ida_ESI_sanfer_cadiz_fin(viajes);*

*static void ida_ESI_sanfer_puertor(viajes);*

*static void ida_ESI_sanfer_fin(viajes);*

*static void ida_ESI_jerez_puerto_puertor_fin(viajes);*

*static void ida_ESI_jerez_puertor_fin(viajes);*

*static void ida_ESI_jerez_puertor(viajes);*

*static void ida_ESI_jerez_fin(viajes);*

*static void ida_ESI_puerto_puertor_fin(viajes);*

*static void ida_ESI_puerto_fin(viajes);*

*static void ida_ESI_puertor(viajes);*

*static void ESI_cadiz_puertor(viajes);*

*static void ESI_cadiz_fin(viajes);*

*static void ESI_puertoreal(viajes);*

*static void ESI_sanfer_cadiz(viajes);*

*static void ESI_sanfer_cadiz_puerto(viajes);*

*static void ESI_sanfer_puertor_fin(viajes);*

*static void ESI_sanfer_fin(viajes);*

*static void ESI_jerez_puertor_puerto_fin(viajes);*

*static void ESI_jerez_puertor_fin(viajes);*

*static void ESI_jerez_puerto(viajes);*

*static void ESI_jerez_fin(viajes);*

*static void ESI_puerto_puertor_fin(viajes);*

*static void ESI_puerto_fin(viajes);*


# ***********************************************************************************************



##### Precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
##### Postcondición: Permite al usuario modificar las paradas de su trayecto en caso de equivocación
*static void modificar_trayecto(viajes);*



##### Precondición: Debe haberse generado una ID para un viaje (esta ID sería de tipo entero)
##### Postcondición: Permite al usuario borrar su registro de trayecto del fichero Pasos.txt
*static void borrar_trayecto(viajes);*