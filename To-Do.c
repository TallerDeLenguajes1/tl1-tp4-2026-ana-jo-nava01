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
Nodo *EliminarNodo(Nodo **start, int id);
void ListarNodos(Nodo **start);
Nodo *BuscarTareaPorID(Nodo **start, int id);
int BuscarPorPalabraClave(Nodo **start, char buff[]);

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

    printf("==TAREAS PENDIENTES==\n");
    ListarNodos(&TareasPendientes);

    //Elegir tareas realizadas
    do {
        int idBuscada;
        printf("Ingrese el ID de la tarea que fue realizada: ");
        scanf("%d", &idBuscada);
        Nodo *buscada = BuscarTareaPorID(&TareasPendientes, idBuscada);
        if(buscada == NULL) {
            printf("No se pudo encontrar esa tarea: ");
        } else {
            Nodo *eliminado = EliminarNodo(&TareasPendientes, idBuscada);
            InsertarNodo(&TareasRealizadas, buscada);
        }

        printf("Desea seguir ingresando tareas realizadas? Y/N: ");
        scanf(" %c", &opcion);

    }while(opcion == 'Y' || opcion == 'y');

    //Listar tareas pendientes y realizadas
    printf("==TAREAS PENDIENTES==\n");
    ListarNodos(&TareasPendientes);
    printf("==TAREAS REALIZADAS==\n");
    ListarNodos(&TareasRealizadas);

    //Consultar tareas pendientes/realizadas por id o palabra clave
    printf("Ingrese la palabra clave: ");
    scanf("%s", buff);
    if(BuscarPorPalabraClave(&TareasPendientes, buff) == 0) {
        printf("No hubo coincidencias para tareas pendientes.\n");
    }
    if(BuscarPorPalabraClave(&TareasRealizadas, buff) == 0) {
        printf("No hubo coincidencias para tareas realizadas.\n");
    }

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

void ListarNodos(Nodo **start) {
    Nodo *aux = (*start);
    while(aux != NULL) {
        printf("==TAREA %d==\n", aux->T.TareaID);
        printf("Descripcion: ");
        puts(aux->T.Descripcion);
        
        printf("Duracion: %d\n", aux->T.Duracion);

        aux = aux->Siguiente;
    }
    printf("\n\n");
}

Nodo *EliminarNodo(Nodo **start, int id) {
    Nodo *aux = (*start);
    Nodo *ant = NULL;
    while (aux != NULL && aux->T.TareaID != id) {
        ant = aux;
        aux = aux->Siguiente;
    }
    if(aux != NULL) {
        if(aux == (*start)) {
            (*start) = aux->Siguiente;
        } else {
            ant->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
    }
    return(aux);
}

Nodo *BuscarTareaPorID(Nodo **start, int id) {
    Nodo *aux = (*start);
    while(aux && aux->T.TareaID != id) {
        aux = aux->Siguiente;
    }
    return aux;
}

int BuscarPorPalabraClave(Nodo **start, char buff[]) {
    int coincidencia = 0;
    Nodo *aux = (*start);
    while(aux != NULL) {
        if(strstr(aux->T.Descripcion, buff) != NULL) {
            printf("- Tarea %d -\n", aux->T.TareaID);
            printf("Descripcion: ");
            puts(aux->T.Descripcion);
            coincidencia = 1;
        }

        aux = aux->Siguiente;
    }

    return coincidencia;
}
