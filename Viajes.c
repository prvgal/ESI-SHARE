
            /*Módulo de viaje: se guarda la ID única del viaje, la matrícula del vehículo, fecha y hora de inicio y llegada,
                        plazas libres, tipo de viaje, el importe y estado del viaje en el fichero Viajes.txt*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MATRICULA 8
#define HORA 6
#define TIPO 2

//Declaración de funciones
void generar_ID_viaje();
void introducir_fecha(int *hoy);
void horas(int hoy);
void plazas();

typedef struct{         //0 = Falso, 1 = Verdadero
    int abierto;
    int cerrado;
    int iniciado;
    int finalizado;
    int anulado;
} estado_viajes;

typedef struct{
    int ID;  //6 dígitos
    char matricula [MATRICULA];
    char fecha[11];
    char hora_inicio [HORA];   //Mínimo 06:00
    char hora_llegada [HORA];  //Máximo 22:30
    int Nplazas;     //Actualiza número de plazas
    char tipo [TIPO];  //I(Ida) o V(Vuelta)
    float importe;  //Entre 0 y 15 € por persona
    estado_viajes estado;  //Solo un estado activo al mismo tiempo
} viajes;

viajes *viaje;
int num = 0;

int main(){     //Main temporal para probar que funciona correctamente
    int hoy;

    if (num==0){
        viaje = (viajes*)malloc(sizeof(viajes));
        num = 1;
    }
    else
        viaje = (viajes*)realloc(viaje, (num+1)*sizeof(viajes));

    generar_ID_viaje();

    introducir_fecha(&hoy);

    horas(hoy);

    viaje[num].Nplazas = 4;

    plazas();

    free(viaje);
    return 0;
}

//Precondición: El usuario habrá elegido la opción de realizar un viaje
//Postcondición: Se le asigna una ID de 6 dígitos al viaje

void generar_ID_viaje(){
    int i, p = 0;
    do
    {
        srand(time(NULL));   //Inicializa la semilla del generador de números aleatorios
        viaje[num].ID = (rand() % (999999 - 100000 + 1)) + 100000;   //Genera un número aleatorio entre 0 y 999999

        for(i=0; i < num && p == 0; i++)    //Compara la ID generada con las otras existentes, si es igual a otra se genera una nueva
    {
        if(viaje[num].ID == viaje[i].ID){
            p = 1;
            printf("Hubo un error generando la ID del viaje.");
            printf("Generando una nueva ID...");
        }
    }
    } while (p==1);
    printf("ID del viaje generada correctamente.\n");
    printf("ID del viaje = %i\n", viaje[0].ID);
}

//Precondición: El usuario habrá elegido la opción de realizar un viaje
//Postcondición: El usuario habrá introducido una fecha del viaje válida
void introducir_fecha(int *hoy){
    int dia, mes, ano, dias_en_mes, fecha_valida = 0;   //Indica si la fecha introducida es válida
    *hoy = 0;

    time_t tiempo_actual;
    struct tm *fecha_actual;

    do {
        printf("Introduzca una fecha en el formato Dia/Mes/Ano: ");
        if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3) { //Si no se introducen los 3 números esperados con "/" separándolos
            while (getchar() != '\n');                  //se limpia el buffer de entrada
            printf("La fecha introducida no es valida. Por favor, intentelo de nuevo.\n");
            continue;
        }

        tiempo_actual = time(NULL);     //Para comprobar que la fecha introducida no es anterior a la actual
        fecha_actual = localtime(&tiempo_actual);

        if(dia == fecha_actual->tm_mday && mes == fecha_actual->tm_mon + 1 && ano == fecha_actual->tm_year + 1900){
            *hoy = 1;
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
        } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
            dias_en_mes = 30;
        }

        if (dia > dias_en_mes){
            printf("La fecha introducida no es valida, el mes %d tiene %d dias. Por favor, intentelo de nuevo.\n", mes, dias_en_mes);
            continue;
        }

        sprintf(viaje[num].fecha, "%02d/%02d/%04d", dia, mes, ano);  //Convierte la fecha a una cadena
        fecha_valida = 1;
    } while (!fecha_valida);

    printf("La fecha ingresada es: %s\n", viaje[num].fecha);
}

//Precondición: El usuario habrá elegido iniciar un viaje
//Postcondición: El usuario habrá introducido una hora de inicio y llegada válidas
void horas(int hoy){
    char entrada[6];
    int estado = 0, minutos_llegada, minutos_inicio, minutos_actual;

    time_t hora_actual = time(NULL);    //Obtiene la hora actual
    struct tm* hora_local = localtime(&hora_actual);    //Convierte a hora local
    
    minutos_actual = hora_local->tm_hour * 60 + hora_local->tm_min; //Convierte la hora local a minutos

    //Pide la hora de inicio
    while (estado == 0){
        printf("Introduzca la hora de inicio en formato hh:mm (24 horas): ");
        scanf("%5s", entrada);
        int horas, minutos;
        minutos_inicio = atoi(entrada+3) + atoi(entrada) * 60;
        if (sscanf(entrada, "%d:%d", &horas, &minutos) == 2 && minutos_inicio >= (6 * 60) && minutos_inicio <= (22 * 60 + 25) && minutos >= 0 && minutos < 60 && (hoy!=1 || minutos_inicio > minutos_actual)){ //Comprueba que la hora de inicio introducida es válida
            sprintf(viaje[num].hora_inicio, "%02d:%02d", horas, minutos);
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
            sprintf(viaje[num].hora_llegada, "%02d:%02d", horas, minutos);
            if (minutos_llegada >= minutos_inicio + 5) {
                estado = 1;
            } else{
                printf("La hora de llegada debe ser al menos 5 minutos mas tarde que la hora de inicio. Introduzca la hora de nuevo.\n");
            }
        } else{
            printf("La hora de llegada debe estar entre las 06:05 y las 22:30. Introduzca la hora de nuevo.\n");
        }
    }

    printf("La hora de inicio es %s\n", viaje[num].hora_inicio);
    printf("La hora de llegada es %s\n", viaje[num].hora_llegada);
}

//Precondición: El usuario habrá elegido unirse a un viaje
//Postcondición: Actualiza el número de plazas libres de un viaje
void plazas(){
    viaje[num].Nplazas -= 1;
    printf("Quedan %i plazas libres en el viaje %i", viaje[num].Nplazas, viaje[num].ID);
}
