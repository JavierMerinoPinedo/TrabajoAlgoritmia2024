#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nodo.h"

struct Nodo crearNodo(struct Linea linea, int indice)
{
    struct Nodo nodo;
    nodo.linea = linea;
    nodo.indice = indice;
    nodo.sig = NULL;
    return nodo;
}

void borrarNodo(struct Nodo *nodo)
{
    free(nodo);
}
