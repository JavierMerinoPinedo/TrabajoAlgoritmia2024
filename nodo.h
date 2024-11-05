#ifndef NODO_H
#define NODO_H
#include "linea.h"

struct Nodo
{
    struct Linea linea;
    int indice;
    struct Nodo *sig;
};
struct Nodo crearNodo(struct Linea linea, int indice);           // (unsigned long) es un número sin signo de tipo long.
void borrarNodo(struct Nodo *nodo);

#endif
