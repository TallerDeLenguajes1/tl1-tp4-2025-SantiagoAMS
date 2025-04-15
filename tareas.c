#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID; //[1000, ... )
    char *Descripcion;
    int Duracion; // [10, 100]
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

typedef Nodo *Lista;

void CrearLista(Lista *l);
void InsertarAlInicio(Lista *l, Tarea t);
void InsertarAlFinal(Lista *l, Tarea t);
void DesalojarMemoria(Lista *l);
void Listar(Lista l);

#define MIN_ID 1000

int main()
{

    int id = MIN_ID, duracion;
    char opc = ' ', buffer[128];
    char *pDesc;

    Lista pendientes, realizadas;
    CrearLista(&pendientes);
    CrearLista(&realizadas);

    while (1)
    {
        printf("\n----- Tarea N %d -----", (1 + id - MIN_ID));
        printf("\n  Nombre:\n>   ");
        gets(buffer);
        pDesc = malloc(sizeof(char) * strlen(buffer));
        strcpy(pDesc, buffer);

        printf("  Duracion:\n>   ");
        scanf("%d", &duracion);

        Tarea t = {id, pDesc, duracion};
        InsertarAlInicio(&pendientes, t);

        printf("\n\nAgregar mas tareas? (S/N)\n> ");
        getchar();
        scanf("%c", &opc);

        if (opc == 's' || opc == 'S' || opc == '1' || opc == 'y' || opc == 'Y')
        {
            id++;
            getchar();
            continue;
        }
        break;
    }

    printf("\n\n\n\n");

    while (1)
    {

        printf("\n========================================");
        printf("\n   1  -  Listar tareas");
        printf("\n   2  -  Transferir tarea a realizadas");
        printf("\n   3  -  Buscar tarea por ID");
        printf("\n   4  -  Buscar tarea por descripcion");
        printf("\n   5  -  Salir del programa");
        printf("\n========================================");
        printf("\n Ingresa una opcion:\n> ");
        getchar();
        scanf("%c", &opc);

        switch (opc)
        {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        default:
            break;
        }
        break;
    }

    printf("------ TAREAS PENDIENTES ------");
    Listar(pendientes);

    printf("------ TAREAS REALIZADAS ------");
    Listar(realizadas);

    DesalojarMemoria(&pendientes);
    DesalojarMemoria(&realizadas);
    /*
        1) Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes, en la cual se
        solicite descripción y duración de la misma (el id debe ser generado automáticamente por
        el sistema, de manera autoincremental comenzando desde el número 1000). Al cabo de
        cada tarea consulte al usuario si desea ingresar una nueva tarea o finalizar la carga.

        2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
        transferidas a la lista de tareas realizadas.

        3) Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.

        4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
        mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.
    */

    return 0;
}

void CrearLista(Lista *l)
{
    l = NULL;
}
void InsertarAlInicio(Lista *l, Tarea t)
{
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));

    n->Siguiente = *l;
    n->T = t;

    *l = n;
}
void InsertarAlFinal(Lista *l, Tarea t)
{
    // De momento es una operacion no soportada
}

void DesalojarMemoria(Lista *l)
{
    Nodo *aux = *l;
    while (aux != NULL)
    {
        free(aux->T.Descripcion);
        free(aux);
        aux = aux->Siguiente;
    }
    free(*l);
}

void Listar(Lista l)
{
    Nodo *aux = l;
    while (aux != NULL)
    {
        Tarea t = aux->T;
        printf("\n   N: %d\tDuracion: %d \t %s", t.TareaID, t.Duracion, t.Descripcion);
        aux = aux->Siguiente;
    }
}