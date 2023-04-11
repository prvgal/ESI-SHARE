
            /*Módulo de viaje: se guarda la ID única del viaje, la matrícula del vehículo, fecha y hora de inicio y llegada,
                        plazas libres, tipo de viaje, el importe y estado del viaje en el fichero Viajes.txt*/

#include "Viajes.h"
#include "tipos.h"

viajes *viaje;
int posUsuario = 0;
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

    generar_ID_viaje(viaje, posUsuario);

    introducir_fecha(viaje, posUsuario);

    horas(viaje, posUsuario);

    viaje[posUsuario].Nplazas = Iplazas;

    plazas(viaje, posUsuario);

    tipo(viaje, posUsuario);

    importe(viaje, posUsuario);

    estado(viaje, posUsuario);

    free(viaje);
    return 0;
}

static void generar_ID_viaje(viajes *viaje, int posUsuario){
    int i, p = 0;

    do

    {
        srand(time(NULL));   //Inicializa la semilla del generador de números aleatorios
        viaje[posUsuario].ID = (rand() % (999999 - 100000 + 1)) + 100000;   //Genera un número aleatorio entre 0 y 999999

        for(i=0; i < posUsuario && p == 0; i++)    //Compara la ID generada con las otras existentes, si es igual a otra se genera una nueva
    {
        if(viaje[posUsuario].ID == viaje[i].ID){
            p = 1;
            printf("Hubo un error generando la ID del viaje.");
            printf("Generando una nueva ID...");
        }
    }

    } while (p==1);

    printf("ID del viaje generada correctamente.\n");
    printf("ID del viaje = %i\n", viaje[posUsuario].ID);
}

static void introducir_fecha(viajes *viaje, int posUsuario){
    int dia, mes, ano, dias_en_mes, fecha_valida = 0;   //Indica si la fecha introducida es válida

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

        if(dia == fecha_actual->tm_mday && mes == fecha_actual->tm_mon + 1 && ano == fecha_actual->tm_year + 1900){
            viaje[posUsuario].hoy = True;
        }
        else
            viaje[posUsuario].hoy = False;

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

        sprintf(viaje[posUsuario].fecha, "%02d/%02d/%04d", dia, mes, ano);  //Convierte la fecha a una cadena

        fecha_valida = 1;

    } while (!fecha_valida);

    printf("La fecha introducida es: %s\n", viaje[posUsuario].fecha);
}

static void horas(viajes *viaje, int posUsuario){
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

        if (sscanf(entrada, "%d:%d", &horas, &minutos) == 2 && minutos_inicio >= (6 * 60) && minutos_inicio <= (22 * 60 + 25) && minutos >= 0 && minutos < 60 && (viaje[posUsuario].hoy!=True || minutos_inicio > minutos_actual)){ //Comprueba que la hora de inicio introducida es válida
            sprintf(viaje[posUsuario].hora_inicio, "%02d:%02d", horas, minutos);

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
            sprintf(viaje[posUsuario].hora_llegada, "%02d:%02d", horas, minutos);

            if (minutos_llegada >= minutos_inicio + 5){
                estado = 1;

            } else{
                printf("La hora de llegada debe ser al menos 5 minutos mas tarde que la hora de inicio. Introduzca la hora de nuevo.\n");
            }

        } else{
            printf("La hora de llegada debe estar entre las 06:05 y las 22:30. Introduzca la hora de nuevo.\n");
        }
    }

    printf("La hora de inicio es %s\n", viaje[posUsuario].hora_inicio);
    printf("La hora de llegada es %s\n", viaje[posUsuario].hora_llegada);
}

static void plazas(viajes *viaje, int posUsuario){
    if(viaje[posUsuario].Nplazas != 0){
        viaje[posUsuario].Nplazas -= 1;

        printf("Quedan %i plazas libres en el viaje %i\n", viaje[posUsuario].Nplazas, viaje[posUsuario].ID);
    }
    else
    printf("No quedan plazas en el viaje %i\n", viaje[posUsuario].ID);
}

static void tipo(viajes *viaje, int posUsuario){
    do
    {
        printf("Introduce (I) si el viaje es de ida o (V) vuelta:\n");
    
        fflush(stdin);
    
        scanf("%c", &viaje[posUsuario].tipo);
    } while (viaje[posUsuario].tipo != 'I' && viaje[posUsuario].tipo != 'V');

    printf("Seleccionado viaje tipo %c\n", viaje[posUsuario].tipo);
}

static void importe(viajes *viaje, int posUsuario){
    do
    {
        printf("Introduce el importe del viaje (0-15 euros): ");
        scanf("%f", &viaje[posUsuario].importe);
    } while (viaje[posUsuario].importe < 0 || viaje[posUsuario].importe > 15);
    
    printf("El importe introducido es de %.2f euros\n", viaje[posUsuario].importe);
}

static void estado(viajes *viaje, int posUsuario){
    int minutos_llegada, minutos_inicio, minutos_actual, dia, mes, ano, hora, minuto;
    char anular;

    time_t fecha_actual = time(NULL);
    struct tm* fecha_local = localtime(&fecha_actual);
    
    minutos_actual = fecha_local->tm_hour * 60 + fecha_local->tm_min; //Convierte la hora local a minutos

    sscanf(viaje[posUsuario].fecha, "%d/%d/%d", &dia, &mes, &ano);

    if(dia == fecha_local->tm_mday && mes == fecha_local->tm_mon + 1 && ano == fecha_local->tm_year + 1900){
        viaje[posUsuario].hoy = True;
    }
    else
        viaje[posUsuario].hoy = False;

    sscanf(viaje[posUsuario].hora_inicio, "%d:%d", &hora, &minuto);

    minutos_inicio = hora*60 + minuto;

    sscanf(viaje[posUsuario].hora_llegada, "%d:%d", &hora, &minuto);

    minutos_llegada = hora*60 + minuto;

    if(viaje[posUsuario].Nplazas > 0 &&
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[posUsuario].hoy == True && minutos_actual < minutos_inicio))){

        viaje[posUsuario].estado.abierto = True;            //Abierto
        viaje[posUsuario].estado.cerrado = False;
        viaje[posUsuario].estado.iniciado = False;
        viaje[posUsuario].estado.finalizado = False;
        viaje[posUsuario].estado.anulado = False;
    }

    if(viaje[posUsuario].Nplazas == 0 && 
    ((ano > fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes > fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia > fecha_local->tm_mday)) ||
    (viaje[posUsuario].hoy == True && minutos_actual < minutos_inicio))){

        viaje[posUsuario].estado.abierto = False;
        viaje[posUsuario].estado.cerrado = True;            //Cerrado
        viaje[posUsuario].estado.iniciado = False;
        viaje[posUsuario].estado.finalizado = False;
        viaje[posUsuario].estado.anulado = False;
    }

    if(viaje[posUsuario].hoy == True && minutos_actual >= minutos_inicio && minutos_actual <= minutos_llegada){

        viaje[posUsuario].estado.abierto = False;
        viaje[posUsuario].estado.cerrado = False;
        viaje[posUsuario].estado.iniciado = True;           //Iniciado
        viaje[posUsuario].estado.finalizado = False;
        viaje[posUsuario].estado.anulado = False;
    }

    if(((ano < fecha_local->tm_year + 1900 || (ano == fecha_local->tm_year + 1900 && mes < fecha_local->tm_mon + 1) || (ano == fecha_local->tm_year + 1900 && mes == fecha_local->tm_mon + 1 && dia < fecha_local->tm_mday)) ||
    (viaje[posUsuario].hoy == True && minutos_actual > minutos_llegada))){

        viaje[posUsuario].estado.abierto = False;
        viaje[posUsuario].estado.cerrado = False;
        viaje[posUsuario].estado.iniciado = False;
        viaje[posUsuario].estado.finalizado = True;        //Finalizado
        viaje[posUsuario].estado.anulado = False;
    }

    do
    {
        fflush(stdin);
        printf("Desea anular el viaje %i? (S/N): ", viaje[posUsuario].ID);
        scanf("%c", &anular);
    } while (anular != 'S' && anular != 'N');

    if(anular == 'S'){
        viaje[posUsuario].estado.abierto = False;
        viaje[posUsuario].estado.cerrado = False;
        viaje[posUsuario].estado.iniciado = False;
        viaje[posUsuario].estado.finalizado = False;
        viaje[posUsuario].estado.anulado = True;            //Anulado
    }

    printf("El estado abierto esta a %i\n", viaje[posUsuario].estado.abierto);
    printf("El estado cerrado esta a %i\n", viaje[posUsuario].estado.cerrado);
    printf("El estado iniciado esta a %i\n", viaje[posUsuario].estado.iniciado);
    printf("El estado finalizado esta a %i\n", viaje[posUsuario].estado.finalizado);
    printf("El estado anulado esta a %i\n", viaje[posUsuario].estado.anulado);
}
