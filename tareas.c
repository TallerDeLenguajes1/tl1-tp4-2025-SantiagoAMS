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
void DesalojarMemoria(Lista *l);
void Listar(Lista l);
Nodo *BuscarPorId(Lista l, int id);
Nodo *BuscarPorDescripcion(Lista l, char *descripcion);
Nodo *MoverTarea(Lista *lOrigen, Lista *lDestino, Nodo *n);
void ListarTarea(Tarea t);
int EsConfirmacion(char opc);

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

        if (EsConfirmacion(opc))
        {
            id++;
            getchar();
            continue;
        }
        break;
    }

    printf("\n\n\n\n");

    short int continuar = 1, estaEnRealizadas = 0, estaEnPendientes = 0;
    Nodo *aux;
    while (continuar)
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

        system("clear");
        switch (opc)
        {
        case '1': /////////////////////////////////////////////////////////////////////////7///////////////////////////////////////
            printf("------ TAREAS PENDIENTES ------");
            Listar(pendientes);

            printf("------ TAREAS REALIZADAS ------");
            Listar(realizadas);
            break;
        case '2': /////////////////////////////////////////////////////////////////////////7///////////////////////////////////////

            printf("------ TAREAS PENDIENTES ------");
            Listar(pendientes);
            printf("\n-------------------------------");
            printf("Ingresa el ID de la tarea a transferir:\n>  ");
            scanf("%d", &id);
            aux = BuscarPorId(pendientes, id);
            if (aux == NULL)
            {
                printf("\nHas ingresado una ID incorrecta...");
            }
            else
            {
                printf("\nTransferir a la lista de realizadas?");
                scanf("%c", opc);
                if (EsConfirmacion(opc))
                {
                    // MOVER
                }
            }

            break;
        case '3': /////////////////////////////////////////////////////////////////////////7///////////////////////////////////////
            estaEnPendientes = 1;
            estaEnRealizadas = 1;

            printf("Ingresa el ID de la tarea:\n>  ");
            scanf("%d", &id);
            aux = BuscarPorId(pendientes, id);
            if (aux == NULL)
            {
                estaEnPendientes = 0;
                aux = BuscarPorId(realizadas, id);

                if (aux == NULL)
                {
                    estaEnRealizadas = 0;
                }
            }
            if (estaEnPendientes)
            {
                printf("\nEncontrada en la lista de tareas pendientes");
                ListarTarea(aux->T);
            }
            else if (estaEnRealizadas)
            {
                printf("\nEncontrada en la lista de tareas realizadas");
                ListarTarea(aux->T);
            }
            else
            {
                printf("\nTarea no encontrada...");
            }

            break;
        case '4': /////////////////////////////////////////////////////////////////////////7///////////////////////////////////////
            estaEnPendientes = 1;
            estaEnRealizadas = 1;

            printf("Ingresa la descripcion de la tarea:\n>  ");
            gets(buffer);
            aux = BuscarPorDescripcion(pendientes, buffer);

            if (aux == NULL)
            {
                estaEnPendientes = 0;
                aux = BuscarPorDescripcion(realizadas, buffer);

                if (aux == NULL)
                {
                    estaEnRealizadas = 0;
                }
            }
            if (estaEnPendientes)
            {
                printf("\nEncontrada en la lista de tareas pendientes");
                ListarTarea(aux->T);
            }
            else if (estaEnRealizadas)
            {
                printf("\nEncontrada en la lista de tareas realizadas");
                ListarTarea(aux->T);
            }
            else
            {
                printf("\nTarea no encontrada...");
            }
            break;
        case '5':
            continuar = 0;
            break;
        default:
            printf("Has ingresado una opcion inesperada...");
            break;
        }

        if (!continuar)
        {
            system("pause");
            system("clear");
        }
    }

    printf("\n<<<<< Nos vemos >>>>>");
    DesalojarMemoria(&pendientes);
    DesalojarMemoria(&realizadas);
    /*
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
        ListarTarea(aux->T);
        aux = aux->Siguiente;
    }
}

void ListarTarea(Tarea t)
{
    printf("\n   ID: %d\tDuracion: %d \t %s", t.TareaID, t.Duracion, t.Descripcion);
}

Nodo *BuscarPorId(Lista l, int id)
{
    Nodo *aux = l;

    while (aux != NULL)
    {
        if (aux->T.TareaID == id)
        {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return NULL;
}

Nodo *MoverTarea(Lista *lOrigen, Lista *lDestino, Nodo *n)
{

    Nodo *aux = *lOrigen;
    Nodo *prev = NULL;

    while (aux != NULL)
    {

        if (aux == n)
        {
            break;
        }

        aux = aux->Siguiente;
        prev = aux;
    }
    if (aux == NULL){
        return; //Porque no se encontro lo que hay que mover
    }

    if (prev != NULL) // Si hay alguien detras del auxiliar
    {
        prev->Siguiente = aux->Siguiente;
    }
    else // O sea si la cabeza apunta al auxiliar
    {
        lOrigen = aux->Siguiente;
    }
    n->Siguiente = lDestino;
    lDestino = n;
}

Nodo *BuscarPorDescripcion(Lista l, char *descripcion)
{
    Nodo *aux = l;

    while (aux != NULL)
    {
        if (strstr(descripcion, aux->T.Descripcion) != NULL)
        {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return NULL;
}

int EsConfirmacion(char opc)
{
    return (opc == 's' || opc == 'S' || opc == '1' || opc == 'y' || opc == 'Y');
}