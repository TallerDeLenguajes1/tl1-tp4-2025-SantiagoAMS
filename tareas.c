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

int main()
{

    int id = 1000, duracion;
    char opc = ' ', buffer[128];
    char * pDesc;

    Lista pendientes, realizadas;
    CrearLista(&pendientes);
    CrearLista(&realizadas);

    while (1)
    {
        printf("\nIngresa la tarea:\n> ");
        gets(buffer);
        pDesc = malloc(sizeof(char) * strlen(buffer));
        strcpy(pDesc,buffer);

        printf("\nIngresa la duracion de la tarea:\n> ");
        scanf("%d", &duracion);

        Tarea t = {id, pDesc, duracion};
        InsertarAlInicio(&pendientes, t);

        printf("\nAgregar mas tareas? (S/N)\n> ");
        scanf("%c", &opc);
        getchar();

        if (opc == 's' || opc == 'S' || opc == '1' || opc == 'y' || opc == 'Y')
        {
            id++;
            continue;
        }
        break;
    }
    
    Nodo * aux = pendientes;
    while (aux !=NULL){
        free(aux->T.Descripcion);
        free(aux);
        aux = aux->Siguiente;
    }
    aux = realizadas;
    while (aux !=NULL){
        free(aux->T.Descripcion);
        free(aux);
        aux = aux->Siguiente;
    }

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