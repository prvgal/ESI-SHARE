
            /*Módulo de viaje: se guarda la ID única del viaje, la matrícula del vehículo, fecha y hora de inicio y llegada,
                        plazas libres, tipo de viaje, el importe y estado del viaje en el fichero Viajes.txt*/

#include "Viajes.h"
#include "tipos.h"
//#include "perfiles.h"
//#include "vehiculo.h"

int posViaje;
int Iplazas = 3;

int main(){     //Main temporal para probar que funciona correctamente
    char viajeusu [5];

    strcpy(viajeusu, "0001");

    viajes *viaje;
    viaje = CrearListaViajes();

    viaje = menuviajesAdmin(viaje, viajeusu);

    free(viaje);
    return 0;
}

static void generar_ID_viaje(viajes *viaje, int posViaje){
    int aux;

    srand(time(NULL));   //Inicializa la semilla del generador de números aleatorios
    aux = (rand() % (999999 - 100000 + 1)) + 100000;   //Genera un número aleatorio entre 0 y 999999

    sprintf((viaje[posViaje].i_d), "%d", aux);

    printf("ID del viaje generada correctamente.\n");
    printf("ID del viaje = %s\n", viaje[posViaje].i_d);
}

static void introducir_fecha(viajes *viaje, int posViaje){
    int dia, mes, ano, dias_en_mes, hora_actual, fecha_valida = 0;   //Indica si la fecha introducida es válida

    time_t tiempo_actual;
    struct tm *fecha_actual;

    do {
        printf("Introduzca una fecha en el formato Dia/Mes/Ano: ");

        if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3){ //Si no se introducen los 3 números esperados con "/" separándolos

            while (getchar() != '\n');                  //se limpia el buffer de entrada
            printf("La fecha introducida no es valida. Por favor, intentelo de nuevo.\n");

            continue;
        }

        tiempo_actual = time(NULL);     //Para comprobar que la fecha introducida no es anterior a la actual
        fecha_actual = localtime(&tiempo_actual);

        hora_actual = fecha_actual->tm_hour * 60 + fecha_actual->tm_min;

        if(dia == fecha_actual->tm_mday && mes == fecha_actual->tm_mon + 1 && ano == fecha_actual->tm_year + 1900){
            viaje[posViaje].hoy = True;
        }
        else
            viaje[posViaje].hoy = False;

        if(viaje[posViaje].hoy == True && hora_actual >= (22*60 + 25)){
            printf("No es posible crear un viaje para hoy. Por favor, introduzca otra fecha.\n");

            continue;
        }

        if (ano < fecha_actual->tm_year + 1900 || (ano == fecha_actual->tm_year + 1900 && mes < fecha_actual->tm_mon + 1) || (ano == fecha_actual->tm_year + 1900 && mes == fecha_actual->tm_mon + 1 && dia < fecha_actual->tm_mday)){
            printf("La fecha introducida no puede ser anterior a la fecha actual. Por favor, intentelo de nuevo.\n");

            continue;
        }

        if (ano > fecha_actual->tm_year + 1901 || mes < 1 || mes > 12 || dia < 1){ //Se comprueba que el día, mes y año sean válidos
            printf("La fecha introducida no es valida. Por favor, intentelo de nuevo.\n");

            continue;
        }

        dias_en_mes = 31;   //Se establece el valor por defecto de días en el mes

        //Se calcula el número de días del mes introducido
        if (mes == 2){
            dias_en_mes = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) ? 29 : 28;

        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11){

            dias_en_mes = 30;
        }

        if (dia > dias_en_mes){
            printf("La fecha introducida no es valida, el mes %d tiene %d dias. Por favor, intentelo de nuevo.\n", mes, dias_en_mes);

            continue;
        }

        sprintf(viaje[posViaje].fecha, "%02d/%02d/%04d", dia, mes, ano);  //Convierte la fecha a una cadena

        fecha_valida = 1;

    } while (!fecha_valida);

    printf("La fecha introducida es: %s\n", viaje[posViaje].fecha);
}

static void horas(viajes *viaje, int posViaje){
    char entrada[6];
    int estado = 0, minutos_llegada, minutos_inicio, minutos_actual;

    time_t hora_actual = time(NULL);                    //Obtiene la hora actual
    struct tm* hora_local = localtime(&hora_actual);    //Convierte a hora local

    minutos_actual = hora_local->tm_hour * 60 + hora_local->tm_min; //Convierte la hora local a minutos

    //Pide la hora de inicio
    while (estado == 0){
        printf("Introduzca la hora de inicio en formato hh:mm (24 horas): ");
        scanf("%5s", entrada);

        int horas, minutos;

        minutos_inicio = atoi(entrada+3) + atoi(entrada) * 60;

        if (sscanf(entrada, "%d:%d", &horas, &minutos) == 2 && minutos_inicio >= (6 * 60) && minutos_inicio <= (22 * 60 + 25) && minutos >= 0 && minutos < 60 && (viaje[posViaje].hoy!=True || minutos_inicio > minutos_actual)){ //Comprueba que la hora de inicio introducida es válida
            sprintf(viaje[posViaje].hora_inicio, "%02d:%02d", horas, minutos);

            estado = 1;

        } else{
            printf("La hora de inicio debe estar entre las 06:00 y las 22:25 y debe ser anterior a la actual si el viaje es hoy. Introduzca la hora de nuevo.\n");
        }
    }

    estado = 0;

    //Pide la hora de llegada
    while (estado == 0){
        printf("Introduzca la hora de llegada en formato hh:mm (24 horas): ");
        scanf("%5s", entrada);

        int horas, minutos;

        minutos_llegada = atoi(entrada+3) + atoi(entrada) * 60;

        if (sscanf(entrada, "%d:%d", &horas, &minutos) == 2 && minutos_llegada >= (6 * 60) && minutos >= 0 && minutos < 60 && minutos_llegada <= (22 * 60 + 30)){   //Comprueba que la hora de llegada introducida es válida
            sprintf(viaje[posViaje].hora_llegada, "%02d:%02d", horas, minutos);

            if (minutos_llegada >= minutos_inicio + 5){
                estado = 1;

            } else{
                printf("La hora de llegada debe ser al menos 5 minutos mas tarde que la hora de inicio. Introduzca la hora de nuevo.\n");
            }

        } else{
            printf("La hora de llegada debe estar entre las 06:05 y las 22:30. Introduzca la hora de nuevo.\n");
        }
    }

    printf("La hora de inicio es %s\n", viaje[posViaje].hora_inicio);
    printf("La hora de llegada es %s\n", viaje[posViaje].hora_llegada);
}

static void plazas(viajes *viaje, int posViaje){
    if(viaje[posViaje].Nplazas != 0){
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
        fgets(viaje[posViaje].tipo, sizeof(viaje[posViaje].tipo), stdin);

        viaje[posViaje].tipo[strcspn(viaje[posViaje].tipo, "\n")] = '\0';

    } while (strcmp(viaje[posViaje].tipo, "ida") != 0 && strcmp(viaje[posViaje].tipo, "vuelta") != 0);

    printf("Seleccionaste viaje tipo %s\n", viaje[posViaje].tipo);
}

static void importe(viajes *viaje, int posViaje){
    float aux;

    do
    {
        printf("Introduce el importe del viaje (0-15 euros): ");
        scanf("%f", &aux);
    } while (aux < 0 || aux > 15);

    sprintf(viaje[posViaje].importe, "%.2f€", aux);

    printf("El importe introducido es de %.2f euros\n", aux);
}

static void estado(viajes *viaje){
    int minutos_llegada, minutos_inicio, minutos_actual, dia, mes, ano, hora, minuto, i;

    time_t fecha_actual = time(NULL);
    struct tm* fecha_local = localtime(&fecha_actual);

    minutos_actual = fecha_local->tm_hour * 60 + fecha_local->tm_min; //Convierte la hora local a minutos

    for(i = 0; i < numeroviajes(); i++){

    sscanf(viaje[i].fecha, "%d/%d/%d", &dia, &mes, &ano);

    if(dia == fecha_local->tm_mday && mes == fecha_local->tm_mon + 1 && ano == fecha_local->tm_year + 1900){
        viaje[i].hoy = True;
    }
    else
        viaje[i].hoy = False;

    sscanf(viaje[i].hora_inicio, "%d:%d", &hora, &minuto);

    minutos_inicio = hora*60 + minuto;

    sscanf(viaje[i].hora_llegada, "%d:%d", &hora, &minuto);

    minutos_llegada = hora*60 + minuto;

    if(viaje[i].Nplazas > 0 &&
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[i].hoy == True && minutos_actual < minutos_inicio))){

        viaje[i].estado.abierto = True;            //Abierto
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = False;
    }

    if(viaje[i].Nplazas == 0 &&
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[i].hoy == True && minutos_actual < minutos_inicio))){

        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = True;            //Cerrado
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = False;
    }

    if(viaje[i].hoy == True && minutos_actual >= minutos_inicio && minutos_actual < minutos_llegada + 60){

        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = True;           //Iniciado
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = False;
    }

    if(((ano < fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes < fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia < fecha_local->tm_mday)) ||
    (viaje[i].hoy == True && minutos_actual >= minutos_llegada + 60))){

        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = True;        //Finalizado
        viaje[i].estado.anulado = False;
    }

    if(viaje[i].anular == 'S'){
        viaje[i].estado.abierto = False;
        viaje[i].estado.cerrado = False;
        viaje[i].estado.iniciado = False;
        viaje[i].estado.finalizado = False;
        viaje[i].estado.anulado = True;            //Anulado
    }
    }
}

int listartusviajes(viajes *viaje, char viajeusu [5]){
    int i, j = 0;
    char aux [11];

    for(i = 0; i < numeroviajes(); i++){
        if(strcmp(viajeusu, viaje[i].usuviaje) == 0){
            if(viaje[i].estado.abierto == 1){
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

    return j;
}

static viajes *modviaje(viajes *viaje, char viajeusu [5]){
    int op, i, j, k = 0;
    char aux [7];

    if(numeroviajes() == 0)
        printf("No hay ningun viaje.\n");
    else{
        do{
            j = listartusviajes(viaje, viajeusu);

            if(j == 0){
                printf("\nNo has publicado ningun viaje aun.\n");
                return viaje;
            }

            printf("\nIntroduzca la ID del viaje que quieres modificar: ");
            
            fflush(stdin);
            fgets(aux, 7, stdin);
            aux[strcspn(aux, "\n")] = '\0';

            for(i = 0; i < numeroviajes() && k == 0; i++){
                if(strcmp(viajeusu, viaje[i].usuviaje) == 0){
                    if(strcmp(viaje[i].i_d, aux) == 0){
                        k = 1;
                    }
                }
            }
        } while (k == 0);

        printf("\n%i", viaje[i-1].Nplazas);
        printf("%i\n", Iplazas);

        if(viaje[i-1].Nplazas == Iplazas){
        if(viaje[i-1].anular == 'S'){
            printf("\nEste viaje ha sido anulado.\n");
        } else{

        do{
        printf("\nSeleccione que desea modificar del viaje con ID %s:\n (1) Fecha\n (2) Hora\n (3) Tipo\n (4) Importe\n (5) Anular viaje\n (0) Salir\n\n", viaje[i-1].i_d);

        if(scanf("%i", &op) != 1){
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
            estado(viaje);
            if(viaje[i-1].estado.finalizado == 1)
                printf("El viaje no se puede anular porque ya ha finalizado.\n");
            else{
                viaje[i-1].anular = 'S';
                printf("\nViaje anulado\n");
            }
        }
        case 0: break;
        default: printf("Elige una de las opciones.\n"); break;
        }
    }
    } while (op != 0);

        }
    } else{
        printf("\nPara modificar un viaje no debe haber ninguna plaza ocupada.\n");
    }

    estado(viaje);
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
            listarviajes(viaje);
            printf("\nSelecciona cual viaje quieres modificar o si quiere salir (0): ");

            if(scanf("%i", &i) != 1){
            fflush(stdin);
            fprintf(stderr, "Entrada no valida. Debe ser un numero.\n");
        }
        } while (i < 0 || i > numeroviajes());

        if(i == 0){
            return viaje;
        }

        printf("\nSeleccione que desea modificar del viaje con ID %s:\n (1) Fecha\n (2) Hora\n (3) Tipo\n (4) Importe\n (5) Anular viaje\n (0) Salir\n\n", viaje[i-1].i_d);

        if(scanf("%i", &op) != 1){
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
        case 0: break;
        default: printf("Elige una de las opciones.\n"); break;
        }
    }
    } while (op != 0);

    estado(viaje);
    }

    return viaje;
}

void imprimirnuevoviaje(viajes *viaje){
    int i, tamoriginal = numeroviajes();
    char aux [11];

    FILE *vf;

    vf = fopen("Viajes.txt", "w");

    fclose(vf);

    vf = fopen("Viajes.txt", "a");

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < tamoriginal + 1; i++){
        if(viaje[i].estado.abierto == 1){
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
        if(tamoriginal + 1 == i + 1){
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
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

void imprimirviajes(viajes *viaje){
    int i, tamoriginal = numeroviajes();
    char aux [11];

    FILE *vf;

    vf = fopen("Viajes.txt", "w");

    fclose(vf);

    vf = fopen("Viajes.txt", "a");

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < tamoriginal; i++){
        if(viaje[i].estado.abierto == 1){
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
        if(tamoriginal == i + 1){
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
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

void imprimirviajesborrado(viajes *viaje){
    int i, tamoriginal = numeroviajes() - 1;
    char aux [11];

    FILE *vf;

    vf = fopen("Viajes.txt", "w");

    fclose(vf);

    vf = fopen("Viajes.txt", "a");

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < tamoriginal; i++){
        if(viaje[i].estado.abierto == 1){
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
        if(tamoriginal == i + 1){
            fprintf(vf, "%s-%s-%s-%s-%s-%i-%s-%s-%s-%s", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
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

void leerviajes(viajes *viaje){
    int i;
    char aux[11];

    FILE *vf;
    char buff[MAX_VIAJES];

    vf = fopen("Viajes.txt", "r");

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i < numeroviajes(); i++){
        if(fgets(buff, MAX_VIAJES, vf) != NULL){
            buff[strcspn(buff, "\n")] = '\0';
            sscanf(buff, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%i-%[^-]-%[^-]-%[^-]-%[^-]", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, &viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
        }

        if(strcmp(aux, "abierto") == 0){
            viaje[i].estado.abierto = True;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "cerrado") == 0){
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = True;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "iniciado") == 0){
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = True;
            viaje[i].estado.finalizado = False;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "finalizado") == 0){
            viaje[i].estado.abierto = False;
            viaje[i].estado.cerrado = False;
            viaje[i].estado.iniciado = False;
            viaje[i].estado.finalizado = True;
            viaje[i].estado.anulado = False;
            continue;
        }
        if(strcmp(aux, "anulado") == 0){
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

void listarviajes(viajes *viaje){
    int i;
    char aux[11];

    printf("\nLista de todos los viajes:\n\n");

    for(i = 0; i < numeroviajes(); i++){
        if(viaje[i].estado.abierto == 1){
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
        printf("<%i> %s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", i+1, viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
}

void listarviajesabiertos(viajes *viaje){
    int i;
    char aux[11];

    printf("\nViajes abiertos:\n\n");

    for(i = 0; i < numeroviajes(); i++){
        if(viaje[i].estado.abierto == 1){
            strcpy(aux, "abierto");
        }
        if(viaje[i].estado.cerrado == 1){
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
        printf("%s-%s-%s-%s-%s-%i-%s-%s-%s-%s\n", viaje[i].i_d, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux, viaje[i].usuviaje);
    }
}

int numeroviajes(void){
    char aux[MAX_VIAJES];
    FILE *vf;
    int i = 0;

    vf = fopen("Viajes.txt", "r");

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura del fichero.\n");
        exit(1);
    }

    while(fgets(aux, MAX_VIAJES, vf) != NULL){
        i++;
    }

    rewind(vf);
    fclose(vf);

    return i;
}

viajes *CrearListaViajes(void){
    viajes *viaje;

    if(numeroviajes() == 0)
        viaje = (viajes *)calloc(1, sizeof(viajes));
    else
        viaje = (viajes *)calloc(numeroviajes(), sizeof(viajes));

    if(viaje == NULL){
        fprintf(stderr, "Error en asignacion de memoria\n");
        exit(1);
    }

    return viaje;
}

viajes *reservarnuevoviaje(viajes *viaje){

    viaje = (viajes *)realloc(viaje, (numeroviajes() + 1)*sizeof(viajes));

    if(viaje == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }

    return viaje;
}

viajes *reservarviajes(viajes *viaje){

    if(numeroviajes() != 0)
        viaje = (viajes *)realloc(viaje, (numeroviajes())*sizeof(viajes));

    if(viaje == NULL){
        fprintf(stderr, "Error en la asignacion de memoria.\n");
        exit(1);
    }

    return viaje;
}

viajes *menuviajesUsu(viajes *viaje, char viajeusu [5]){
    int op;

    system("cls");

    viaje = reservarviajes(viaje);
    leerviajes(viaje);

    do{
    printf("\n########################################\n");
    printf("#              MENU VIAJES              #\n");
    printf("########################################\n\n");

    estado(viaje);
    imprimirviajes(viaje);
    listarviajesabiertos(viaje);

    printf("\nSeleccione que desea hacer:\n\n");
    printf("<1> Unirse a un viaje.\n");
    printf("<2> Publicar un nuevo viaje.\n");
    printf("<3> Editar un viaje.\n");
    printf("<0> Volver al menu principal.\n\n");

    if(scanf("%i", &op) != 1){
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

    } while(op != 0);

    return viaje;
}

viajes *menuviajesAdmin(viajes *viaje, char viajeusu [5]){
    int op;

    system("cls");

    viaje = reservarviajes(viaje);
    leerviajes(viaje);

    do{
    printf("\n#######################################################\n");
    printf("#              MENU VIAJES (ADMINISTRADOR)            #\n");
    printf("#######################################################\n\n");

    estado(viaje);
    imprimirviajes(viaje);

    printf("\nSeleccione que desea hacer:\n\n");
    printf("<1> Listar viajes.\n");
    printf("<2> Publicar un nuevo viaje.\n");
    printf("<3> Editar un viaje.\n");
    printf("<4> Eliminar un viaje.\n");
    printf("<0> Volver al menu principal.\n\n");

    if(scanf("%i", &op) != 1){
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

    } while(op != 0);

    return viaje;
}

viajes *eliminarviaje(viajes *viaje){
    int op, i;
    system("cls");
    if(numeroviajes() == 0)
        printf("\nNo hay ningun viaje.\n\n");
    else{
        listarviajes(viaje);

    printf("\n\nIntroduce cual viaje quiere eliminar o cualquier otro numero para salir: ");

    if(scanf("%i", &op) != 1){
            fflush(stdin);
            fprintf(stderr, "\nEntrada no valida. Debe ser un numero.\n");
        } else{
            if(op < 1 || op > numeroviajes()){
                return viaje;
            }
            for(i = op-1; i+1 <= numeroviajes(); i++){
                strcpy(viaje[i].i_d, viaje[i+1].i_d);
                strcpy(viaje[i].matricula, viaje[i+1].matricula);
                strcpy(viaje[i].fecha, viaje[i+1].fecha);
                strcpy(viaje[i].hora_inicio, viaje[i+1].hora_inicio);
                strcpy(viaje[i].hora_llegada, viaje[i+1].hora_llegada);
                viaje[i].Nplazas = viaje[i+1].Nplazas;
                strcpy(viaje[i].tipo, viaje[i+1].tipo);
                strcpy(viaje[i].importe, viaje[i+1].importe);
                viaje[i].estado.abierto = viaje[i+1].estado.abierto;
                viaje[i].estado.cerrado = viaje[i+1].estado.cerrado;
                viaje[i].estado.iniciado = viaje[i+1].estado.iniciado;
                viaje[i].estado.finalizado = viaje[i+1].estado.finalizado;
                viaje[i].estado.anulado = viaje[i+1].estado.anulado;
                viaje[i].hoy = viaje[i+1].hoy;
                viaje[i].anular = viaje[i+1].anular;
                strcpy(viaje[i].usuviaje, viaje[i+1].usuviaje);
            }

            viaje = (viajes *)realloc(viaje, (numeroviajes() - 1)*sizeof(viajes));
            imprimirviajesborrado(viaje);
            printf("\nViaje borrado.\n");
        }
    }
    return viaje;
}

viajes *publicarviaje(viajes *viaje, char viajeusu [5]){
    //if(contar_vehiculos(viajeusu) > 0){
        viaje = reservarnuevoviaje(viaje);

        int posViaje = numeroviajes();

        printf("Seleccione el vehículo con el que se va a realizar el viaje:\n\n");

        //obtener_datos_vehiculo(viajeusu, viaje[posViaje]);

        //usuario_listar_vehiculos(viajeusu);

        strcpy(viaje[posViaje].matricula, "8291JDK");

        strcpy(viaje[posViaje].usuviaje, viajeusu);

        leerviajes(viaje);

        generar_ID_viaje(viaje, posViaje);

        introducir_fecha(viaje, posViaje);

        horas(viaje, posViaje);

        viaje[posViaje].Nplazas = Iplazas;

        plazas(viaje, posViaje);

        tipo(viaje, posViaje);

        importe(viaje, posViaje);

        estado(viaje);

        imprimirnuevoviaje(viaje);

        listarviajes(viaje);
    /*}
    else
        printf("No puedes publicar un viaje porque no tienes ningún vehículo registrado.\n");*/
    return viaje;
}
/*
void menuviajes(char viajeusu [5], char tipousuario[MAX_PU], viajes *viaje){
    static int auxi = 0;

    if(auxi == 0){
        viaje = CrearListaViajes();
        auxi = 1;
    }

    if(tipousuario == 'usuario')
        viaje = menuviajesUsu(viaje, viajeusu);
    else
        viaje = menuviajesAdmin(viaje, viajeusu);
}
*/
