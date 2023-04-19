                /*Modulo de viaje: se guarda la ID unica del viaje, la matricula del vehiculo, fecha y hora de inicio y llegada,
                  plazas libres, tipo de viaje, el importe, el estado del viaje y la ID del creador en el fichero Viajes.txt*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tipos.h"
#include "perfiles.h"
#include "Viajes.h"
#include "tipos.h"
#include "vehiculo.h"

static void introducir_fecha(viajes *viaje, int posViaje){
    int dia, mes, ano, dias_en_mes, hora_actual, fecha_valida = 0;   //Indica si la fecha introducida es válida

    time_t tiempo_actual;
    struct tm *fecha_actual;

    do {
        printf("Introduzca una fecha en el formato Dia/Mes/Ano: ");

        if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3){ //Si no se introducen los 3 numeros esperados con "/" separándolos*

            while (getchar() != '\n');                  //*se limpia el buffer de entrada y se vuelve a iniciar el bucle
            printf("La fecha introducida no es valida. Por favor, intentelo de nuevo.\n");

            continue;
        }

        tiempo_actual = time(NULL);     //Para comprobar que la fecha introducida no es anterior a la actual
        fecha_actual = localtime(&tiempo_actual);

        hora_actual = fecha_actual->tm_hour * 60 + fecha_actual->tm_min;    //Se pasa la hora actual a minutos

        if(dia == fecha_actual->tm_mday && mes == fecha_actual->tm_mon + 1 && ano == fecha_actual->tm_year + 1900){ //Si la fecha introducida es hoy, se activará a 1 en la estructra
            viaje[posViaje].hoy = True;
        }
        else
            viaje[posViaje].hoy = False;

        if(viaje[posViaje].hoy == True && hora_actual >= (22*60 + 25)){ //Si se crea un viaje para hoy a más de las 22:25 se reinicia el bucle
            printf("No es posible crear un viaje para hoy. Por favor, introduzca otra fecha.\n");

            continue;
        }

        //Se comprueba que la fecha introducida no sea anterior a la actual, y si lo es se reinicia el bucle
        if (ano < fecha_actual->tm_year + 1900 || (ano == fecha_actual->tm_year + 1900 && mes < fecha_actual->tm_mon + 1) || (ano == fecha_actual->tm_year + 1900 && mes == fecha_actual->tm_mon + 1 && dia < fecha_actual->tm_mday)){
            printf("La fecha introducida no puede ser anterior a la fecha actual. Por favor, intentelo de nuevo.\n");

            continue;
        }

        if (ano > fecha_actual->tm_year + 1901 || mes < 1 || mes > 12 || dia < 1){ //Se comprueba que el dia, mes y año sean válidos, sino se reinicia el bucle
            printf("La fecha introducida no es valida. Por favor, intentelo de nuevo.\n");

            continue;
        }

        dias_en_mes = 31;   //Se establece el valor por defecto de dias en el mes

        //Se calcula el número de dias del mes introducido
        if (mes == 2){
            dias_en_mes = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) ? 29 : 28;

        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11){

            dias_en_mes = 30;
        }

        if (dia > dias_en_mes){ //Si el el número de dias introducido supera a los dias del mes introducido se reinicia el bucle
            printf("La fecha introducida no es valida, el mes %d tiene %d dias. Por favor, intentelo de nuevo.\n", mes, dias_en_mes);

            continue;
        }

        sprintf(viaje[posViaje].fecha, "%02d/%02d/%04d", dia, mes, ano);  //Convierte la fecha a una cadena

        fecha_valida = 1;   //Indica que la fecha introducida es válida y permite salir del bucle

    } while (!fecha_valida);

    printf("\nLa fecha introducida es: %s\n", viaje[posViaje].fecha);
}

static void horas(viajes *viaje, int posViaje){
    char entrada[6];
    int estado = 0, minutos_llegada, minutos_inicio, minutos_actual;    //El estado permanecerá a 0 hasta que se introduzca una hora válida

    time_t hora_actual = time(NULL);                    //Obtiene la hora actual
    struct tm* hora_local = localtime(&hora_actual);    //Convierte a hora local

    minutos_actual = hora_local->tm_hour * 60 + hora_local->tm_min; //Convierte la hora local a minutos

    //Pide la hora de inicio
    while (estado == 0){
        printf("Introduzca la hora de inicio en formato hh:mm (24 horas): ");
        scanf("%5s", entrada);  //Pide un string de 5 caracteres

        int horas, minutos;

        minutos_inicio = atoi(entrada+3) + atoi(entrada) * 60;  //Convierte la hora introducida a minutos

        //Si la hora introducida y su formato son correctos la variable estado se activará a 1, permitiendo salir del bucle
        if (sscanf(entrada, "%d:%d", &horas, &minutos) == 2 && minutos_inicio >= (6 * 60) && minutos_inicio <= (22 * 60 + 25) && minutos >= 0 && minutos < 60 && (viaje[posViaje].hoy!=True || minutos_inicio > minutos_actual)){ //Comprueba que la hora de inicio introducida es v�lida
            sprintf(viaje[posViaje].hora_inicio, "%02d:%02d", horas, minutos);

            estado = 1;

        } else{
            printf("La hora de inicio debe estar entre las 06:00 y las 22:25 y debe ser anterior a la actual si el viaje es hoy. Introduzca la hora de nuevo.\n");
        }
    }

    estado = 0; //Se establece a 0 para pedir la hora de llegada

    //Pide la hora de llegada
    while (estado == 0){
        printf("Introduzca la hora de llegada en formato hh:mm (24 horas): ");
        scanf("%5s", entrada);  //Pide un string de 5 caracteres

        int horas, minutos;

        minutos_llegada = atoi(entrada+3) + atoi(entrada) * 60; //Convierte la hora introducida a minutos

        //Se comprueba que la hora introducida y su formato son correctos
        if (sscanf(entrada, "%d:%d", &horas, &minutos) == 2 && minutos_llegada >= (6 * 60) && minutos >= 0 && minutos < 60 && minutos_llegada <= (22 * 60 + 30)){   //Comprueba que la hora de llegada introducida es v�lida
            sprintf(viaje[posViaje].hora_llegada, "%02d:%02d", horas, minutos);

            if (minutos_llegada >= minutos_inicio + 5){ //La hora de llegada debe de ser mínimo 5 minutos más tarde que la de inicio
                estado = 1;

            } else{
                printf("La hora de llegada debe ser al menos 5 minutos mas tarde que la hora de inicio. Introduzca la hora de nuevo.\n");
            }

        } else{
            printf("La hora de llegada debe estar entre las 06:05 y las 22:30. Introduzca la hora de nuevo.\n");
        }
    }

    printf("\nLa hora de inicio introducida es %s\n", viaje[posViaje].hora_inicio);
    printf("La hora de llegada introducida es %s\n\n", viaje[posViaje].hora_llegada);
}

static void plazas(viajes *viaje, int posViaje){
    if(viaje[posViaje].Nplazas != 0){   //Si el número de plazas no es 0, se actualizará a una menos
        viaje[posViaje].Nplazas -= 1;

        printf("Quedan %i plazas libres en el viaje %s\n", viaje[posViaje].Nplazas, viaje[posViaje].i_d);
    }
    else
    printf("No quedan plazas en el viaje %s\n", viaje[posViaje].i_d);
}

static void tipo(viajes *viaje, int posViaje){

    do {
        printf("Introduce 'ida' o 'vuelta': ");
        fflush(stdin);
        fgets(viaje[posViaje].tipo, sizeof(viaje[posViaje].tipo), stdin);   //Obtiene la string tipo para la estructura viaje de la posición posViaje

        viaje[posViaje].tipo[strcspn(viaje[posViaje].tipo, "\n")] = '\0';   //Sustituye el \n final por \0

    } while (strcmp(viaje[posViaje].tipo, "ida") != 0 && strcmp(viaje[posViaje].tipo, "vuelta") != 0);  //Comprueba si la string introducida es "ida" o "vuelta"

    printf("Seleccionaste viaje tipo %s\n", viaje[posViaje].tipo);
}

static void importe(viajes *viaje, int posViaje){
    float aux;

    do
    {
        printf("Introduce el importe del viaje (0-15 euros): ");
        scanf("%f", &aux);
    } while (aux < 0 || aux > 15);  //Si el importe es menor que 0 o mayor que 15 es inválido

    sprintf(viaje[posViaje].importe, "%.2f€", aux); //Convierte el número introducido a un string que dice la cantidad de euros con 2 decimales

    printf("\nEl importe introducido es de %.2f euros\n\n", aux);
}

static void estado(viajes *viaje){
    int minutos_llegada, minutos_inicio, minutos_actual, dia, mes, ano, hora, minuto, i;

    time_t fecha_actual = time(NULL);
    struct tm* fecha_local = localtime(&fecha_actual);  //Obtiene los datos locales

    minutos_actual = fecha_local->tm_hour * 60 + fecha_local->tm_min; //Convierte la hora local a minutos

    for(i = 0; i < numeroviajes(); i++){    //Se actualiza el estado de cada viaje

    sscanf(viaje[i].fecha, "%d/%d/%d", &dia, &mes, &ano);   //Convierte la cadena de caracteres "fecha" a dia, mes y año

    if(dia == fecha_local->tm_mday && mes == fecha_local->tm_mon + 1 && ano == fecha_local->tm_year + 1900){    //Comprueba si el dia de la fecha es hoy
        viaje[i].hoy = True;
    }
    else
        viaje[i].hoy = False;

    sscanf(viaje[i].hora_inicio, "%d:%d", &hora, &minuto);  //Convierte la cadena de caracteres "hora_inicio" a hora y minutos

    minutos_inicio = hora*60 + minuto;  //Convierte la hora de inicio a minutos

    sscanf(viaje[i].hora_llegada, "%d:%d", &hora, &minuto); //Convierte la cadena de caracteres "hora_llegada" a hora y minutos

    minutos_llegada = hora*60 + minuto; //Convierte la hora de llegada a minutos

    if(viaje[i].Nplazas > 0 &&
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[i].hoy == True && minutos_actual < minutos_inicio))){    //Si hay plazas disponibles y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior,
                                                                    //el estado del viaje quedará abierto
        viaje[i].estado.abierto = True;            //Abierto
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = False;
    }

    if(viaje[i].Nplazas == 0 &&
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[i].hoy == True && minutos_actual < minutos_inicio))){    //Si no hay plazas disponibles y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior,
                                                                    //el estado del viaje quedará cerrado
        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = True;            //Cerrado
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = False;
    }

    //Si la hora actual esta entre la hora de inicio y hora de llegada el estado del viaje quedará iniciado
    if(viaje[i].hoy == True && minutos_actual >= minutos_inicio && minutos_actual < minutos_llegada + 60){

        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = True;           //Iniciado
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = False;
    }

    if(((ano < fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes < fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia < fecha_local->tm_mday)) ||
    (viaje[i].hoy == True && minutos_actual >= minutos_llegada + 60))){ //Si la hora actual es mayor que la hora de llegada, el estado del viaje quedará iniciado

        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = True;        //Finalizado
        viaje[i].estado.anulado = False;
    }

    if(viaje[i].anular == 'S'){ //El viaje se anulará si el usuario lo decide
        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = True;            //Anulado
    }
    }
}

static int listartusviajes(viajes *viaje, char viajeusu [5]){
    int i, j = 0;
    char aux [11];

    for(i = 0; i < numeroviajes(); i++){    //Recorre todos los viajes de la estructura
        if(strcmp(viajeusu, viaje[i].usuviaje) == 0){   //Si el usuario con el que se accede es el dueño de un viaje, este se imprimirá por pantalla
            if(viaje[i].estado.abierto == 1){   //Se imprime por pantalla el nombre del estado que esté activo
                strcpy(aux, "abierto");
            }
            if(viaje[i].estado.cerrado == 1){
                        strcpy(aux, "cerrado");
            }
            if(viaje[i].estado.iniciado == 1){
                        strcpy(aux, "iniciado");
            }
            if(viaje[i].estado.finalizado == 1){
                        strcpy(aux, "finalizado");
            }
            if(viaje[i].estado.anulado == 1){
                        strcpy(aux, "anulado");
            }
            printf("<%i> %s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", j+1, viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
            j++;
        }
    }

    return j;   //Devuelve j que será el número de viajes que tiene un usuario
}

static viajes *modviaje(viajes *viaje, char viajeusu [5]){
    int op, i, j, k = 0;
    char aux [7];

    if(numeroviajes() == 0) //Comprueba que haya algún viaje
        printf("No hay ningun viaje.\n");
    else{
        do{
            j = listartusviajes(viaje, viajeusu);   //Si el usuario ha creado algún viaje, estos se imprimirán por pantalla

            if(j == 0){
                printf("\nNo has publicado ningun viaje aun.\n");
                return viaje;
            }

            printf("\nIntroduzca la ID del viaje que quieres modificar: ");
            
            fflush(stdin);
            fgets(aux, 7, stdin);   //Obtiene la ID del viaje que quiere modificar
            aux[strcspn(aux, "\n")] = '\0'; //Sustituye \n por \0

            for(i = 0; i < numeroviajes() && k == 0; i++){  //Llega a la posición de la estructura perteneciente a la ID del viaje introducido
                if(strcmp(viajeusu, viaje[i].usuviaje) == 0){
                    if(strcmp(viaje[i].i_d, aux) == 0){
                        k = 1;
                    }
                }
            }
        } while (k == 0);

        if(viaje[i-1].Nplazas == viaje[i-1].Iplazas){  //Si hay alguna plaza ocupada no se puede modificar el viaje
        if(viaje[i-1].anular == 'S'){   //Si el viaje ha sido anulado no se puede modificar
            printf("\nEste viaje ha sido anulado.\n");
        } else{

        do{
        printf("\nSeleccione que desea modificar del viaje con ID %s:\n (1) Fecha\n (2) Hora\n (3) Tipo\n (4) Importe\n (5) Anular viaje\n (0) Salir\n\n", viaje[i-1].i_d);

        if(scanf("%i", &op) != 1){
            fflush(stdin);
            fprintf(stderr, "Entrada no valida. Debe ser un numero.\n");
        } else{

        switch (op) //Según el número introducido, podrá modificar los diferentes campos del viaje
        {
        case 1: {
            introducir_fecha(viaje, i-1);
            break;
        }
        case 2: {
            horas(viaje, i-1);
            break;
        }
        case 3: {
            tipo(viaje, i-1);
            break;
        }
        case 4: {
            importe(viaje, i-1);
            break;
        }
        case 5: {
            estado(viaje);
            if(viaje[i-1].estado.finalizado == 1)   //Si el viaje ha finalizado no se puede anular
                printf("El viaje no se puede anular porque ya ha finalizado.\n");
            else{
                viaje[i-1].anular = 'S';
                printf("\nViaje anulado\n");
            }
        }
        case 0: break;  //Si introduce 0 cancela la acción de modificar el viaje seleccionado
        default: printf("Elige una de las opciones.\n"); break;
        }
    }
    } while (op != 0);  //Mientras que el número introducido no sea 0, podrá seguir modificando viajes

        }
    } else{
        printf("\nPara modificar un viaje no debe haber ninguna plaza ocupada.\n");
    }

    estado(viaje);  //Actualiza los estados
    }

    return viaje;
}


static viajes *modviajeAdmin(viajes *viaje){
    int op, i;

    if(numeroviajes() == 0)
        printf("No hay ningun viaje.\n");
    else{
        do
    {
        do
        {
            listarviajes(viaje);    //Imprime todos los viajes por pantalla
            printf("\nSelecciona cual viaje quieres modificar o si quiere salir (0): ");

            if(scanf("%i", &i) != 1){
            fflush(stdin);
            fprintf(stderr, "Entrada no valida. Debe ser un numero.\n");
        }
        } while (i < 0 || i > numeroviajes());  //Si el número no está en el rango de viajes ni es 0 se repite el bucle

        if(i == 0){ //Si se introduce 0 sale de la función
            return viaje;
        }

        printf("\nSeleccione que desea modificar del viaje con ID %s:\n (1) Fecha\n (2) Hora\n (3) Tipo\n (4) Importe\n (5) Anular viaje\n (0) Salir\n\n", viaje[i-1].i_d);

        if(scanf("%i", &op) != 1){  //Da a elegir cual campo del viaje seleccionado modificar
            fflush(stdin);
            fprintf(stderr, "Entrada no valida. Debe ser un numero.\n");
        } else{

        switch (op)
        {
        case 1: {
            introducir_fecha(viaje, i-1);
            break;
        }
        case 2: {
            horas(viaje, i-1);
            break;
        }
        case 3: {
            tipo(viaje, i-1);
            break;
        }
        case 4: {
            importe(viaje, i-1);
            break;
        }
        case 5: {
            viaje[i-1].anular = 'S';
            printf("\nViaje anulado.\n");
        }
        case 0: break;  //Si introduce 0 cancela la acción de modificar el viaje seleccionado
        default: printf("Elige una de las opciones.\n"); break;
        }
    }
    } while (op != 0);  //Mientras que el número introducido no sea 0 no saldrá de la función

    estado(viaje);
    }

    return viaje;
}

static void imprimirnuevoviaje(viajes *viaje){
    int i, tamoriginal = numeroviajes();    //Guarda cuántas lineas hay en Viajes.txt
    char aux [11];

    FILE *vf;

    vf = fopen("Viajes.txt", "w");  //Borra el contenido del fichero

    fclose(vf);

    vf = fopen("Viajes.txt", "a");  //Lo abre para escribirlo de nuevo

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < tamoriginal + 1; i++){   //Se prepara para escribir los viajes que había más uno adicional
        if(viaje[i].estado.abierto == 1){   //Se transforma el valor numérico de los estados a la cadena de caracteres que se imprimirá en el fichero
            strcpy(aux, "abierto");
        }
        if(viaje[i].estado.cerrado == 1){
            strcpy(aux, "cerrado");
        }
        if(viaje[i].estado.iniciado == 1){
            strcpy(aux, "iniciado");
        }
        if(viaje[i].estado.finalizado == 1){
            strcpy(aux, "finalizado");
        }
        if(viaje[i].estado.anulado == 1){
            strcpy(aux, "anulado");
        }
        if(tamoriginal + 1 == i + 1){   //El último viaje en imprimir irá sin salto de linea
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,  //Se imprimen separados por guiones
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
        }
        else
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
    fclose(vf);
}

static void imprimirviajes(viajes *viaje){
    int i, tamoriginal = numeroviajes();    //Se guarda el número de lineas del fichero Viajes.txt
    char aux [11];

    FILE *vf;

    vf = fopen("Viajes.txt", "w");  //Borra el contenido del fichero

    fclose(vf);

    vf = fopen("Viajes.txt", "a");  //Lo abre para escribirlo de nuevo

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < tamoriginal; i++){   //Vuelve a escribir el contenido actualizándolo
        if(viaje[i].estado.abierto == 1){   //Convierte el valor numérico de los estados a una cadena de caracteres que se imprimirá en el fichero Viajes.txt
            strcpy(aux, "abierto");
        }
        if(viaje[i].estado.cerrado == 1){
            strcpy(aux, "cerrado");
        }
        if(viaje[i].estado.iniciado == 1){
            strcpy(aux, "iniciado");
        }
        if(viaje[i].estado.finalizado == 1){
            strcpy(aux, "finalizado");
        }
        if(viaje[i].estado.anulado == 1){
            strcpy(aux, "anulado");
        }
        if(tamoriginal == i + 1){   //El último viaje en imprimir no tendrá salto de linea
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,  //Se imprimen separados por guiones
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
        }
        else
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
    fclose(vf);
}

static void imprimirviajesborrado(viajes *viaje){
    int i, tamoriginal = numeroviajes() - 1;    //Guarda un número menos de lineas del fichero Viajes.txt
    char aux [11];

    FILE *vf;

    vf = fopen("Viajes.txt", "w");  //Borra el contenido del fichero

    fclose(vf);

    vf = fopen("Viajes.txt", "a");  //Se prepara para escribir de nuevo el contenido

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < tamoriginal; i++){   //Se prepara para escribir los viajes que había a excepción del borrado
        if(viaje[i].estado.abierto == 1){   //Convierte el valor numérico de los estados a una cadena de caracteres que se imprimirá en el fichero Viajes.txt
            strcpy(aux, "abierto");
        }
        if(viaje[i].estado.cerrado == 1){
            strcpy(aux, "cerrado");
        }
        if(viaje[i].estado.iniciado == 1){
            strcpy(aux, "iniciado");
        }
        if(viaje[i].estado.finalizado == 1){
            strcpy(aux, "finalizado");
        }
        if(viaje[i].estado.anulado == 1){
            strcpy(aux, "anulado");
        }
        if(tamoriginal == i + 1){   //El último viaje en imprimir no tendrá salto de linea
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,  //Se imprimen separados por guiones
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
        }
        else
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
    fclose(vf);
}

static void leerviajes(viajes *viaje){
    int i;
    char aux[11];

    FILE *vf;
    char buff[MAX_VIAJES];  //Se crea un buffer de tamaño mayor que una posición de la estructura para que recorra la linea entera del fichero Viajes.txt

    vf = fopen("Viajes.txt", "r");  //Se abre en modo lectura

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < numeroviajes(); i++){    //Recorre el número de lineas que haya en el fichero
        if(fgets(buff, MAX_VIAJES, vf) != NULL){    //Guarda en la estructura el contenido del fichero hasta que llega al final
            buff[strcspn(buff, "\n")] = '\0';   //Convierte los \n en \0
            sscanf(buff, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%i-%[^-]-%[^-]-%[^-]-%[^-]", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,  //Recoge los campos separados por guiones
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, &viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
        }

        if(strcmp(aux, "abierto") == 0){    //Compara la cadena de caracteres auxiliar con la que se ha obtenido la string del fichero con el estado y lo establece a True y False al resto
            viaje[i].estado.abierto = True;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "cerrado") == 0){    //Compara la cadena de caracteres auxiliar con la que se ha obtenido la string del fichero con el estado y lo establece a True y False al resto
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = True;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "iniciado") == 0){   //Compara la cadena de caracteres auxiliar con la que se ha obtenido la string del fichero con el estado y lo establece a True y False al resto
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = True;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "finalizado") == 0){ //Compara la cadena de caracteres auxiliar con la que se ha obtenido la string del fichero con el estado y lo establece a True y False al resto
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = True;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "anulado") == 0){    //Compara la cadena de caracteres auxiliar con la que se ha obtenido la string del fichero con el estado y lo establece a True y False al resto
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = True;
            continue;
        }
    }
    fclose(vf);
}

static void listarviajes(viajes *viaje){
    int i;
    char aux[11];

    printf("\nLista de todos los viajes:\n\n");

    for(i = 0; i < numeroviajes(); i++){    //Imprime por pantalla el número de viajes que haya en el fichero Viajes.txt
        if(viaje[i].estado.abierto == 1){   //Convierte el estado de valor numérico a string
            strcpy(aux, "abierto");
        }
        if(viaje[i].estado.cerrado == 1){
            strcpy(aux, "cerrado");
        }
        if(viaje[i].estado.iniciado == 1){
            strcpy(aux, "iniciado");
        }
        if(viaje[i].estado.finalizado == 1){
            strcpy(aux, "finalizado");
        }
        if(viaje[i].estado.anulado == 1){
            strcpy(aux, "anulado");
        }
        printf("<%i> %s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", i+1, viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,   //Imprime la estructura por pantalla separando los campos con guiones
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
}

static void listarviajesabiertos(viajes *viaje){
    int i;
    char aux[11];

    printf("\nViajes abiertos:\n\n");

    for(i = 0; i < numeroviajes(); i++){    //Imprime por pantalla el número de viajes abiertos que haya en el fichero Viajes.txt
        if(viaje[i].estado.abierto == 1){   //Solo en el caso de que el viaje esté abierto se imprimirá por pantalla
            strcpy(aux, "abierto");
        }
        if(viaje[i].estado.cerrado == 1){   //Si no lo está seguirá con el bucle
            continue;
        }
        if(viaje[i].estado.iniciado == 1){
            continue;
        }
        if(viaje[i].estado.finalizado == 1){
            continue;
        }
        if(viaje[i].estado.anulado == 1){
            continue;
        }
        printf("%s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha, //Imprime la estructura por pantalla separando los campos con guiones
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
}

static int numeroviajes(void){
    char aux[MAX_VIAJES];   //Se usa para llegar al final de cada linea
    FILE *vf;
    int i = 0;

    vf = fopen("Viajes.txt", "r");  //Abre el fichero en modo lectura

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    while(fgets(aux, MAX_VIAJES, vf) != NULL){  //Lee cada linea y suma 1 a la variable i
        i++;
    }

    rewind(vf);
    fclose(vf);

    return i;   //Devuelve el número de lineas del fichero Viajes.txt
}

static viajes *CrearListaViajes(void){
    viajes *viaje;

    if(numeroviajes() == 0) //Si no hay ningún viaje en el fichero Viajes.txt se reserva memoria para una estructura
        viaje = (viajes *)calloc(1, sizeof(viajes));
    else
        viaje = (viajes *)calloc(numeroviajes(), sizeof(viajes));   //Si hay varios viajes se reservará para tantos viajes como haya

    if(viaje == NULL){
        fprintf(stderr, "Error en asignacion de memoria\n");
        exit(1);
    }

    return viaje;
}

static viajes *reservarnuevoviaje(viajes *viaje){

    viaje = (viajes *)realloc(viaje, (numeroviajes() + 1)*sizeof(viajes));  //Redimensiona la estructura para un viaje adicional del número de viajes del fichero Viajes.txt

    if(viaje == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }

    return viaje;
}

static viajes *reservarviajes(viajes *viaje){

    if(numeroviajes() != 0) //Sólo si existe algún viaje en el fichero Viajes.txt se redimensionará la estructura para tantos como haya
        viaje = (viajes *)realloc(viaje, (numeroviajes())*sizeof(viajes));

    if(viaje == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }

    return viaje;
}

static void menuviajesUsu(char viajeusu [5]){
    int op;
	viajes *viaje;
	
	viaje = CrearListaViajes(); //Reserva memoria por primera vez
	
    system("cls");  //Limpia la pantalla

    viaje = reservarviajes(viaje);  //Reserva memoria para tantos viajes como haya en el fichero Viajes.txt
    leerviajes(viaje);  //Lee los datos de la estructura en el fichero Viajes.txt

    do{
    printf("\n########################################\n");
    printf("#              MENU VIAJES              #\n");
    printf("########################################\n\n");

    estado(viaje);  //Actualiza el estado de los viajes
    imprimirviajes(viaje);  //Actualiza los viajes en el fichero
    listarviajesabiertos(viaje);    //Imprime por pantalla la lista de los viajes abiertos

    printf("\nSeleccione que desea hacer:\n\n");
    printf("<1> Unirse a un viaje.\n");
    printf("<2> Publicar un nuevo viaje.\n");
    printf("<3> Editar un viaje.\n");
    printf("<0> Volver al menu principal.\n\n");

    if(scanf("%i", &op) != 1){  //Introduce un número para elegir que hacer
            fflush(stdin);
            fprintf(stderr, "Entrada no valida. Debe ser un numero.\n");
        } else{

            switch(op){
                //case 1: MenuUser(infoper, posViajes); break;
                case 2: viaje = publicarviaje(viaje, viajeusu); break;
                case 3: viaje = modviaje(viaje, viajeusu); break;
                case 0: break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);   //Se repite hasta que el usuario introduzca 0

    free(viaje);    //Se libera la memoria de la estructura viaje
}

static void menuviajesAdmin(char viajeusu [5]){
    int op;
	viajes *viaje;
	
	viaje = CrearListaViajes(); //Reserva memoria por primera vez
	
    system("cls");  //Limpia la pantalla

    viaje = reservarviajes(viaje);  //Reserva memoria para tantos viajes como haya en el fichero Viajes.txt
    leerviajes(viaje);  //Lee los datos de la estructura en el fichero Viajes.txt

    do{
    printf("\n#######################################################\n");
    printf("#              MENU VIAJES (ADMINISTRADOR)            #\n");
    printf("#######################################################\n\n");

    estado(viaje);  //Actualiza el estado del viaje
    imprimirviajes(viaje);  //Actualiza los viajes en el fichero Viajes.txt

    printf("\nSeleccione que desea hacer:\n\n");
    printf("<1> Listar viajes.\n");
    printf("<2> Publicar un nuevo viaje.\n");
    printf("<3> Editar un viaje.\n");
    printf("<4> Eliminar un viaje.\n");
    printf("<0> Volver al menu principal.\n\n");

    if(scanf("%i", &op) != 1){  //Introduce un número para elegir que hacer
            fflush(stdin);
            fprintf(stderr, "Entrada no valida. Debe ser un numero.\n");
        } else{

            switch(op){
                case 1: listarviajes(viaje); break;
                case 2: viaje = publicarviaje(viaje, viajeusu); break;
                case 3: viaje = modviajeAdmin(viaje); break;
                case 4: viaje = eliminarviaje(viaje); break;
                case 0: break;
                default: printf("\nElige una de las opciones.\n"); break;
            }
        }

    } while(op != 0);   //Se repite hasta que introduzca 0

    free(viaje);    //Se libera la memoria de la estructura viaje
}

static viajes *eliminarviaje(viajes *viaje){
    int op, i;
    system("cls");  //Limpia la pantalla
    if(numeroviajes() == 0) //Si el número de viajes del fichero Viajes.txt es 0 no se puede eliminar ningún viaje
        printf("\nNo hay ningun viaje.\n\n");
    else{
        listarviajes(viaje);    //Imprime todos los viajes de la estructura por pantalla

    printf("\n\nIntroduce cual viaje quiere eliminar o cualquier otro numero para salir: ");

    if(scanf("%i", &op) != 1){
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.\n");
        } else{
            if(op < 1 || op > numeroviajes()){  //Si introduce cualquiera otro número que no sea uno de los viajes, vuelve al menú
                return viaje;
            }

            for(i = op-1; i < numeroviajes(); i++)  //Desplaza una posición superior del viaje elegido a uno inferior, quedando el último libre*
                viaje[i] = viaje[i+1];

            viaje = (viajes *)realloc(viaje, (numeroviajes() - 1)*sizeof(viajes));  //*El cual se eliminará redimensionando la estructura a un viaje menos
            imprimirviajesborrado(viaje);   //Imprime la estructura en el fichero con un viaje menos
            printf("\nViaje borrado.\n");
        }
    }

    return viaje;
}

static viajes *publicarviaje(viajes *viaje, char viajeusu [5]){
    if(contar_vehiculos(viajeusu) > 0){ //Si el usuario no tiene ningún vehículo registrado no puede iniciar un viaje
        viaje = reservarnuevoviaje(viaje);  //Se reserva memoria para un nuevo viaje

        int posViaje = numeroviajes();  //Se calcula la posición en la estructura del nuevo viaje

        viaje[posViaje].Iplazas = 4;

        viaje = obtener_matricula_vehiculo(viajeusu, viaje, posViaje);  //Obtiene la matrícula y plazas del vehículo

        viaje = obtener_plazas_vehiculo(viaje, posViaje, viaje[posViaje].matricula);

        strcpy(viaje[posViaje].usuviaje, viajeusu); //Copia la ID del usuario actual a la estructura

        leerviajes(viaje);  //Lee los viajes del fichero Viajes.txt

        GenerarID(viaje[posViaje].i_d, numeroviajes()+1, 6);    //Guarda la ID del viaje nuevo

        introducir_fecha(viaje, posViaje);

        horas(viaje, posViaje);

        viaje[posViaje].Nplazas = viaje[posViaje].Iplazas;

        tipo(viaje, posViaje);

        importe(viaje, posViaje);

        estado(viaje);

        imprimirnuevoviaje(viaje);  //Se imprime el nuevo viaje en el fichero Viajes.txt    
    }
    else
        printf("No puedes publicar un viaje porque no tienes ning�n veh�culo registrado.\n");

    return viaje;
}

void menuviajes(char viajeusu [5], char tipousuario[MAX_PU]){
    if(!strcmp(tipousuario, "usuario")) //Si la cadena de caracteres recibida es "usuario" se ejecutará el menuviajesUsu, sino el menuviajesAdmin
        menuviajesUsu(viajeusu);
    else
        menuviajesAdmin(viajeusu);
}
