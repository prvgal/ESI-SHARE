#ifndef _VIAJES_H_
#define _VIAJES_H_

#define MAX_VIAJES 90
#define FECHA 11
#define MATRICULA 8
#define IMPORTE 7
#define TIPO 7
#define HORA 6

typedef struct{
    logico abierto;                 //Si Nplazas > 0 y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior, y no esta anulado
    logico cerrado;                 //Si Nplazas = 0 y la fecha del viaje es posterior que la actual o igual que la actual pero con hora posterior, y no esta anulado
    logico iniciado;                //Si el viaje ha iniciado (la hora actual esta entre la hora de inicio y hora de llegada) y no se anula
    logico finalizado;              //Si el viaje ha finalizado (la hora actual es  mayor que la hora de llegada) y no ha sido anulado
    logico anulado;                 //Si el viaje ha sido anulado
} estado_viajes;

typedef struct{
    char i_d [7];                   //6 digitos
    char matricula [MATRICULA];     //Matricula de vehicula usado para el viaje
    char fecha[FECHA];              //Formato dd/mm/aa
    char hora_inicio [HORA];        //Formato 24h - Minimo 06:00
    char hora_llegada [HORA];       //Formato 24h - Maximo 22:30
    int Nplazas;                    //Número de plazas disponibles
    char tipo [TIPO];               //Ida o Vuelta
    char importe [IMPORTE];         //Entre 0 y 15 € por persona
    estado_viajes estado;           //Solo un estado activo al mismo tiempo
    logico hoy;                     //Indica si la fecha introducida es hoy
    char anular;                    //Indica si quiere anular un viaje (S) o no (N)
    char usuviaje[ID];              //Indica la ID del usuario que ha creado el viaje
} viajes;

//FUNCIONES PRIVADAS:

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicara la posición del usuario en viaje
//Postcondición: Habrá introducido fecha en la estructura viaje de la posición posViaje

static void introducir_fecha(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicara la posición del usuario en viaje
//Postcondición: Habra introducido hora_inicio y hora_llegada en la estructura viaje de la posición posViaje

static void horas(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicara la posición del usuario en viaje
//Postcondición: Actualiza el número de plazas en la estructura viaje de la posición posViaje

static void plazas(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicara la posición del usuario en viaje
//Postcondición: Habra introducido el tipo de viaje en la estructura viaje de la posición posViaje: (I) Ida o (V) Vuelta

static void tipo(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y un entero que indicara la posición del usuario en viaje
//Postcondicion: Habra introducido el importe del viaje en la estructura viaje de la posición posViaje

static void importe(viajes *viaje, int posViaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Se actualizara el estado de todos los viajes de la estructura activando (True) el estado en el que se encuentre el viaje y se desactivarando (False) el anterior si era diferente

static void estado(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondición: Se habra podido modificar algún viaje del usuario

static viajes *modviaje(viajes *viaje, char viajeusu [5]);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Se habra podido modificar cualquier viaje de la estructura

static viajes *modviajeAdmin(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondición: Habra imprimido por pantalla la lista de viajes que ha creado el usuario

static int listartusviajes(viajes *viaje, char viajeusu [5]);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Habra dado la posibilidad a eliminar algún viaje a elección del administrador

static viajes *eliminarviaje(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Habra imprimido en un fichero un nuevo viaje de la estructura viajes

static void imprimirnuevoviaje(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Habra imprimido en un fichero la estructura viajes actualizada tras haber borrado uno

static void imprimirviajesborrado(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Rellena la estructura viajes con el contenido del fichero Viajes.txt

static void leerviajes(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Imprime por pantalla el contenido de cada posición de la estructura viajes

static void listarviajes(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Imprime por pantalla los viajes que estan en estado abierto

static void listarviajesabiertos(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Habra imprimido en un fichero la estructura viajes

static void imprimirviajes(viajes *viaje);

//Precondición: Ninguna
//Postcondición: Devuelve el número de lineas que tiene el fichero

static int numeroviajes(void);

//Precondición: Recibe un vector de estructuras de tipo viajes
//Postcondición: Redimensiona la estructura igual al número de viajes actuales del fichero Viajes.txt

static viajes *reservarviajes(viajes *viaje);

//Precondición: Recibe un vector de estructras de tipo viajes
//Postcondición: Redimensiona la estructura a un tamano mas que el número de viajes actuales del fichero Viajes.txt

static viajes *reservarnuevoviaje(viajes *viaje);

//Precondición: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondicón: Habra anadido un viaje nuevo a la estructura viajes y lo habra imprimido en el fichero Viajes.txt

static viajes *publicarviaje(viajes *viaje, char viajeusu [5]);

//Precondición: Ninguna
//Postcondición: Crea una estructura de viajes

static viajes *CrearListaViajes(void);

//Precondición: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondición: Imprime por pantalla el menú de opciones del usuario

static void menuviajesUsu(char viajeusu [5]);

//Precondición: Recibe un vector de estructuras de tipo viajes y una cadena de caracteres que indica la ID del usuario que accede al programa
//Postcondición: Imprime por pantalla el menú de opciones del administrador

static void menuviajesAdmin(char viajeusu [5]);

//FUNCIONES PUBLICAS:

/*Precondición: Recibe una cadena de caracteres que indica la ID del usuario que accede al programa y
una cadena de la estructura tPerfil que indicara si esta accediendo un usuario o un administrador*/
//Postcondición: Lleva a la función menuviajesUsu o menuviajesAdmin

void menuviajes(char viajeusu [5], char []);

#endif
