#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{
    int TareaID; //Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

void limpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {}
}
Nodo *ListaVacia();
Nodo *CrearNodo(Tarea dato);
void InsertarNodo(Nodo **start, Nodo *nodo);
void ListarNodos(Nodo *start);
Nodo *BuscarTareaPorID(Nodo *start, int id);

int main() {
    srand(time(NULL));
    Nodo *TareasPendientes;
    Nodo *TareasRealizadas;
    Tarea tarea;
    int id = 1000;
    char opcion;
    char buff[100];

    //Inicializo los nodos cabecera
    TareasPendientes = ListaVacia();
    TareasRealizadas = ListaVacia();

    //Solicitar tareas pendientes
    do {
        tarea.TareaID = id;
        printf("==TAREA %d==\n", id);
        printf("Ingrese la descripcion: ");
        gets(buff);
        int tamDesc = strlen(buff);
        tarea.Descripcion = (char *)malloc(tamDesc * sizeof(char) + 1);
        strcpy(tarea.Descripcion, buff);

        int duracion = (rand() % 100) + 10;
        tarea.Duracion = duracion;
        printf("Duracion de la tarea: %d\n", tarea.Duracion);

        InsertarNodo(&TareasPendientes, CrearNodo(tarea));
        printf("===========\n");

        printf("Desea seguir ingresando tareas pendientes? Y/N: ");
        scanf("%c", &opcion);
        limpiarBuffer();
        id++;
    }while(opcion == 'Y' || opcion == 'y');

    //Elegir tareas realizadas
    do {
        int idBuscada;
        printf("Ingrese el ID de la tarea que fue realizada: ");
        scanf("%d", &idBuscada);
        Nodo *buscada;
        buscada = (Nodo *)malloc(sizeof(Nodo)); //necesario?
        buscada = BuscarTareaPorID(TareasPendientes, idBuscada);
        if(buscada == NULL) {
            printf("No se pudo encontrar esa tarea: ");
        } else {
            InsertarNodo(&TareasRealizadas, buscada);
        }

        printf("Desea seguir ingresando tareas realizadas? Y/N: ");
        scanf(" %c", &opcion);
        if(opcion == 'N' || opcion == 'n') { // preguntar
            free(buscada);
        }

    }while(opcion == 'Y' || opcion == 'y');

    //Listar tareas pendientes y realizadas
    printf("==TAREAS PENDIENTES==\n");
    ListarNodos(TareasPendientes);
    printf("==TAREAS REALIZADAS==\n");
    ListarNodos(TareasRealizadas);

    //Consultar tareas pendientes/realizadas por id o palabra clave

    return 0;
}

Nodo *ListaVacia() {
    return NULL;
}

Nodo *CrearNodo(Tarea dato) {
    Nodo *nodoN = (Nodo *)malloc(sizeof(Nodo));
    nodoN->T = dato;
    nodoN->Siguiente = NULL;

    return nodoN;
}

void InsertarNodo(Nodo **start, Nodo *nodo) {
    nodo->Siguiente = *start;
    *start  = nodo;
}

void ListarNodos(Nodo *start) {
    while(start != NULL) {
        printf("==TAREA %d==\n", start->T.TareaID);
        printf("Descripcion: ");
        puts(start->T.Descripcion);
        
        printf("Duracion: %d\n", start->T.Duracion);

        start = start->Siguiente;
    }
}

Nodo *BuscarTareaPorID(Nodo *start, int id) {
    while(start != NULL) {
        if(start->T.TareaID == id) {
            return start;
        }
        start = start->Siguiente;
    }
    return NULL;
}