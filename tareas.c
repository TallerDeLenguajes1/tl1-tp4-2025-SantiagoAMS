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
    Nodo *Siguiente;
} Nodo;

typedef Nodo *Lista;

int main()
{

    int id = 1000;
    char opc = ' ';
    char buffer[128];

    while (1)
    {
        printf("Ingresa la tarea: ");
        gets(buffer);

        printf("\n¿Agregar mas tareas?");
        scanf("%c", &opc);
        getchar();
        if (opc == 's' || opc == 'S' || opc == '1'){
            id++;
            continue;
        }
        break;
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