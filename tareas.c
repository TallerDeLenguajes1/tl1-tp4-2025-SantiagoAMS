#include <stdio.h>
#include <stdlib.h>

typedef struct Tarea{
    int TareaID; //[1000, ... )
    char *Descripcion;
    int Duracion; // [10, 100]
} Tarea;

typedef struct Nodo{
    Tarea T;
    Nodo * Siguiente;
} Nodo;

typedef Nodo * Lista;

int main(){

    
    return 0;
}