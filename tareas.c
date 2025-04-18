#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID; //[1000, ... )
    char *Descripcion;
    int Duracion; // [10, 100]
} Tarea;

#define DURACION_MIN 10
#define DURACION_MAX 100

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

typedef Nodo *Lista;

Nodo *GenerarNodo(Tarea t);
void CrearLista(Lista *l);
void InsertarAlInicio(Lista *l, Nodo *n);
void InsertarAlFinal(Lista *l, Nodo *n);
void DesalojarMemoria(Lista *l);
int MoverTarea(Lista *lOrigen, Lista *lDestino, Nodo *n);
void Listar(Lista l);
void ListarTarea(Tarea t);
int EsConfirmacion(char opc);
int TomarDuracion();
Nodo *BuscarPorId(Lista l, int id);
Nodo *BuscarPorDescripcion(Lista l, char *descripcion);

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

        duracion = TomarDuracion();

        Tarea t = {id, pDesc, duracion};
        InsertarAlFinal(&pendientes, GenerarNodo(t));

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

    short estaEnRealizadas = 0, estaEnPendientes = 0;
    Nodo *aux;
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
        scanf(" %c", &opc);

        system("cls");

        if (opc == '1')
        {
            printf("------ TAREAS PENDIENTES ------");
            Listar(pendientes);

            printf("------ TAREAS REALIZADAS ------");
            Listar(realizadas);
        }
        else if (opc == '2')
        {
            printf("------ TAREAS PENDIENTES ------");
            Listar(pendientes);
            printf("\n-------------------------------");
            printf("\nIngresa el ID de la tarea a transferir:\n>  ");
            scanf("%d", &id);
            aux = BuscarPorId(pendientes, id);
            if (aux == NULL)
            {
                printf("\nHas ingresado una ID incorrecta...\n");
            }
            else
            {
                getchar();
                printf("\nTransferir a la lista de realizadas?\n>  ");
                scanf("%c", &opc);
                if (EsConfirmacion(opc))
                {
                    if (MoverTarea(&pendientes, &realizadas, aux))
                    {
                        printf("\nTarea transladada exitosamente.\n");
                    }
                    else
                    {
                        printf("\nNo se pudo mover la tarea...\n");
                    }
                }
            }
        }
        else if (opc == '3')
        {
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
                printf("\nEncontrada en la lista de tareas pendientes\n");
                ListarTarea(aux->T);
            }
            else if (estaEnRealizadas)
            {
                printf("\nEncontrada en la lista de tareas realizadas\n");
                ListarTarea(aux->T);
            }
            else
            {
                printf("\nTarea no encontrada...\n");
            }
        }
        else if (opc == '4')
        {
            estaEnPendientes = 1;
            estaEnRealizadas = 1;
            getchar();
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
                printf("\nEncontrada en la lista de tareas pendientes\n");
                ListarTarea(aux->T);
            }
            else if (estaEnRealizadas)
            {
                printf("\nEncontrada en la lista de tareas realizadas\n");
                ListarTarea(aux->T);
            }
            else
            {
                printf("\nTarea no encontrada...\n");
            }
        }
        else if (opc == '5')
        {
            break;
        }
        else
        {
            printf("Has ingresado una opcion inesperada...\n");
            opc = ' ';
            getchar();
        }
        printf("\n");
        system("pause");
        system("cls");
    }

    printf("\n<<<<< Nos vemos >>>>>");
    DesalojarMemoria(&pendientes);
    DesalojarMemoria(&realizadas);

    return 0;
}

void CrearLista(Lista *l)
{
    *l = NULL;
}

Nodo *GenerarNodo(Tarea t)
{
    Nodo *n = (Nodo *)malloc(sizeof(Nodo));
    n->T = t;
    n->Siguiente = NULL;
    return n;
}

void InsertarAlInicio(Lista *l, Nodo *n)
{
    n->Siguiente = *l;
    *l = n;
}

void InsertarAlFinal(Lista *l, Nodo *n)
{
    if (*l == NULL)
    {
        *l = n;
    }
    else
    {
        Nodo *aux = *l;
        while (aux->Siguiente != NULL)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = n;
    }
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
    if (l == NULL)
    {
        printf("\n\tLista vacia...");
    }
    Nodo *aux = l;
    while (aux != NULL)
    {

        ListarTarea(aux->T);
        aux = aux->Siguiente;
    }
    printf("\n");
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

int MoverTarea(Lista *lOrigen, Lista *lDestino, Nodo *n)
{

    Nodo *aux = *lOrigen;
    Nodo *prev = NULL;

    while (aux != NULL)
    {

        if (aux == n)
        {
            break;
        }

        prev = aux;
        aux = aux->Siguiente;
    }
    if (aux == NULL)
    {
        return 0; // Porque no se encontro lo que hay que mover
    }

    if (prev != NULL) // Si hay alguien detras del auxiliar
    {
        prev->Siguiente = aux->Siguiente;
    }
    else // O sea si la cabeza apunta al auxiliar
    {
        *lOrigen = aux->Siguiente;
    }
    n->Siguiente = NULL;
    InsertarAlFinal(lDestino, n);
    // n->Siguiente = *lDestino;
    //*lDestino = n;
    return 1;
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

int TomarDuracion()
{
    int ret = DURACION_MIN - 1;

    do
    {
        printf("\n  Duracion:\n>  ");
        scanf("%d", &ret);
        if (ret > DURACION_MAX || ret < DURACION_MIN)
        {
            printf("\nERROR, LA DURACION DEBE ESTAR ENTRE %d Y %d", DURACION_MIN, DURACION_MAX);
        }
        else
        {
            break;
        }
    } while (1);
    return ret;
}