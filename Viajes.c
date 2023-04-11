
            /*Módulo de viaje: se guarda la ID única del viaje, la matrícula del vehículo, fecha y hora de inicio y llegada,
                        plazas libres, tipo de viaje, el importe y estado del viaje en el fichero Viajes.txt*/

#include "Viajes.h"
#include "tipos.h"

viajes *viaje;
int posViaje = 0;
int numvector = 0;
int Iplazas = 4;

int main(){     //Main temporal para probar que funciona correctamente

    if (numvector == 0){

        viaje = (viajes*)malloc(sizeof(viajes));

        numvector = 1;
    }
    else{

        viaje = (viajes*)realloc(viaje, (numvector + 1)*sizeof(viajes));
        
        numvector += 1;
    }

    strcpy(viaje[posViaje].matricula, "8291JDK");

    generar_ID_viaje(viaje, posViaje);

    introducir_fecha(viaje, posViaje);

    horas(viaje, posViaje);

    viaje[posViaje].Nplazas = Iplazas;

    plazas(viaje, posViaje);

    tipo(viaje, posViaje);

    importe(viaje, posViaje);

    estado(viaje, posViaje);

    modviaje(viaje, posViaje);

    imprimirviajes(viaje);

    free(viaje);
    return 0;
}

static void generar_ID_viaje(viajes *viaje, int posViaje){
    int i, p = 0;

    do

    {
        srand(time(NULL));   //Inicializa la semilla del generador de números aleatorios
        viaje[posViaje].ID = (rand() % (999999 - 100000 + 1)) + 100000;   //Genera un número aleatorio entre 0 y 999999

        for(i=0; i < posViaje && p == 0; i++)    //Compara la ID generada con las otras existentes, si es igual a otra se genera una nueva
    {
        if(viaje[posViaje].ID == viaje[i].ID){
            p = 1;
            printf("Hubo un error generando la ID del viaje.");
            printf("Generando una nueva ID...");
        }
    }

    } while (p==1);

    printf("ID del viaje generada correctamente.\n");
    printf("ID del viaje = %i\n", viaje[posViaje].ID);
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

        if (ano > 2024 || mes < 1 || mes > 12 || dia < 1){ //Se comprueba que el día, mes y año sean válidos
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

        printf("Quedan %i plazas libres en el viaje %i\n", viaje[posViaje].Nplazas, viaje[posViaje].ID);
    }
    else
    printf("No quedan plazas en el viaje %i\n", viaje[posViaje].ID);
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

static void estado(viajes *viaje, int posViaje){
    int minutos_llegada, minutos_inicio, minutos_actual, dia, mes, ano, hora, minuto;
    char anular;

    time_t fecha_actual = time(NULL);
    struct tm* fecha_local = localtime(&fecha_actual);
    
    minutos_actual = fecha_local->tm_hour * 60 + fecha_local->tm_min; //Convierte la hora local a minutos

    sscanf(viaje[posViaje].fecha, "%d/%d/%d", &dia, &mes, &ano);

    if(dia == fecha_local->tm_mday && mes == fecha_local->tm_mon + 1 && ano == fecha_local->tm_year + 1900){
        viaje[posViaje].hoy = True;
    }
    else
        viaje[posViaje].hoy = False;

    sscanf(viaje[posViaje].hora_inicio, "%d:%d", &hora, &minuto);

    minutos_inicio = hora*60 + minuto;

    sscanf(viaje[posViaje].hora_llegada, "%d:%d", &hora, &minuto);

    minutos_llegada = hora*60 + minuto;

    if(viaje[posViaje].Nplazas > 0 &&
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[posViaje].hoy == True && minutos_actual < minutos_inicio))){

        viaje[posViaje].estado.abierto = True;            //Abierto
        viaje[posViaje].estado.cerrado = False;
        viaje[posViaje].estado.iniciado = False;
        viaje[posViaje].estado.finalizado = False;
        viaje[posViaje].estado.anulado = False;
    }

    if(viaje[posViaje].Nplazas == 0 && 
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[posViaje].hoy == True && minutos_actual < minutos_inicio))){

        viaje[posViaje].estado.abierto = False;
        viaje[posViaje].estado.cerrado = True;            //Cerrado
        viaje[posViaje].estado.iniciado = False;
        viaje[posViaje].estado.finalizado = False;
        viaje[posViaje].estado.anulado = False;
    }

    if(viaje[posViaje].hoy == True && minutos_actual >= minutos_inicio && minutos_actual < minutos_llegada + 60){

        viaje[posViaje].estado.abierto = False;
        viaje[posViaje].estado.cerrado = False;
        viaje[posViaje].estado.iniciado = True;           //Iniciado
        viaje[posViaje].estado.finalizado = False;
        viaje[posViaje].estado.anulado = False;
    }

    if(((ano < fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes < fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia < fecha_local->tm_mday)) ||
    (viaje[posViaje].hoy == True && minutos_actual >= minutos_llegada + 60))){

        viaje[posViaje].estado.abierto = False;
        viaje[posViaje].estado.cerrado = False;
        viaje[posViaje].estado.iniciado = False;
        viaje[posViaje].estado.finalizado = True;        //Finalizado
        viaje[posViaje].estado.anulado = False;
    }

    do
    {
        fflush(stdin);
        printf("Desea anular el viaje %i? (S/N): ", viaje[posViaje].ID);
        scanf("%c", &anular);
    } while (anular != 'S' && anular != 'N');

    if(anular == 'S'){
        viaje[posViaje].estado.abierto = False;
        viaje[posViaje].estado.cerrado = False;
        viaje[posViaje].estado.iniciado = False;
        viaje[posViaje].estado.finalizado = False;
        viaje[posViaje].estado.anulado = True;            //Anulado
    }

    printf("El estado abierto esta a %i\n", viaje[posViaje].estado.abierto);
    printf("El estado cerrado esta a %i\n", viaje[posViaje].estado.cerrado);
    printf("El estado iniciado esta a %i\n", viaje[posViaje].estado.iniciado);
    printf("El estado finalizado esta a %i\n", viaje[posViaje].estado.finalizado);
    printf("El estado anulado esta a %i\n", viaje[posViaje].estado.anulado);
}

static void modviaje(viajes *viaje, int posViaje){
    int op;

    if(viaje[posViaje].Nplazas == Iplazas){
        do
        {
            printf("Seleccione que desea modificar del viaje con ID %i:\n (1) Fecha\n (2) Hora\n (3) Tipo\n (4) Importe\n", viaje[posViaje].ID);
            scanf("%i", &op);
        } while (op != 1 && op != 2 && op != 3 && op != 4);
        
        switch (op)
        {
        case 1:
            introducir_fecha(viaje, posViaje);
            break;
        
        case 2:
            horas(viaje, posViaje);
            break;
        
        case 3:
            tipo(viaje, posViaje);
            break;
        
        case 4:
            importe(viaje, posViaje);
        }
    }
    else
        printf("Hay al menos una plaza ocupada, para modificar un viaje no debe haber ninguna plaza ocupada.\n");
}

static void imprimirviajes(viajes *viaje){
    int i;
    char aux [11];

    FILE *vf;
    vf = fopen("Viajes.txt", "a");

    if(vf == NULL){
        fprintf(stderr, "Error en la apertura de archivos.\n");
        exit(1);
    }

    for(i = 0; i <= posViaje; i++){
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
        fprintf(vf, "%i-%s-%s-%s-%s-%i-%s-%s-%s\n", viaje[i].ID, viaje[i].matricula, viaje[i].fecha,
                                                viaje[i].hora_inicio, viaje[i].hora_llegada, viaje[i].Nplazas,
                                                viaje[i].tipo, viaje[i].importe, aux);
    }
    fclose(vf);
}
