#include <stdlib.h>
#include <stdio.h>
#include "listaLigada.h"

bool esVaciaLL(struct ListaLigada listaLigada)
{
    return (listaLigada.cabeza == NULL);
}

struct ListaLigada nuevaLL()
{
    struct ListaLigada nuevaLista;
    nuevaLista.cabeza = NULL;
    nuevaLista.longitud = 0;

    return nuevaLista;
}

void borrarLL(struct ListaLigada *listaLigada)
{
    for (int i = 0; i <= listaLigada->longitud; i++)
    {
        borrarNodoDeLL(listaLigada, 1);
    }
}

struct Nodo * nuevoNodoLL(struct Linea linea, int indice)
{
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL)
    {
        printf("Error al asignar memoria para el nuevo nodo...\n");
        exit(1);
    }
    *nuevoNodo = crearNodo(linea, indice);
    return nuevoNodo; //Si en lugar de return nuevoNodo; se usara return *nuevoNodo;, estarias intentando devolver el valor al que apunta el puntero nuevoNodo
}

void liberarMemoriaNodoLL(struct Nodo *nodoBorrado)
{
    borrarNodo(nodoBorrado);
}

struct Nodo * iterarHastaIndice(struct ListaLigada *listaLigada, int indice)
{
    if (indice < 0 || indice > listaLigada->longitud)
    {
        printf("Error: Indice fuera de rango %d/%d.\n", indice, listaLigada->longitud);
        exit(-1);
        return NULL;
    }

    struct Nodo *nodoBuscarIndice = listaLigada->cabeza;

    for(int i = 1; i < indice; i++)
    {
        if (nodoBuscarIndice == NULL)
        {
            printf("Error: Nodo nulo encontrado al buscar el indice %d.\n", i);
            exit(-1);
            return NULL;
        }
        nodoBuscarIndice = nodoBuscarIndice->sig;
    }
    return nodoBuscarIndice;
}

void insertarEnLL(struct ListaLigada *listaLigada, int indice, struct Linea linea)
{
    struct Nodo *nuevoNodoInsertar = nuevoNodoLL(linea,indice);

    if (nuevoNodoInsertar == NULL)
    {
        printf("Error: Fallo al ubicar memoria.\n");
        exit(-1);
        return;
    }

    if (indice == 1)
    {
        nuevoNodoInsertar->sig = listaLigada->cabeza;
        listaLigada->cabeza = nuevoNodoInsertar;
    }
    else if (indice == 2){
        nuevoNodoInsertar->sig = listaLigada->cabeza->sig;
        listaLigada->cabeza->sig = nuevoNodoInsertar;
    }
    else
    {
        struct Nodo *nodoAnteriorIndice = iterarHastaIndice(listaLigada, indice-1); //Buscar el nodo anterior al del indice
        if (nodoAnteriorIndice == NULL)
        {
            printf("Error: No se pudo encontrar nodo con ese indice.\n");
            free(nuevoNodoInsertar);
            return;
        }
        nuevoNodoInsertar->sig = nodoAnteriorIndice->sig;
        nodoAnteriorIndice->sig = nuevoNodoInsertar;
    }
    listaLigada->longitud = listaLigada->longitud + 1;
    //printf("Nodo insertado en la lista en la posicion %d.\n", indice);
}

void borrarNodoDeLL(struct ListaLigada *listaLigada, int indice)
{
    if (indice == 1)
    {
        struct Nodo *nuevoNodoBorrar = listaLigada->cabeza;
        if (nuevoNodoBorrar)
        {
            listaLigada->cabeza = nuevoNodoBorrar->sig;
            liberarMemoriaNodoLL(nuevoNodoBorrar);
        }
        if(listaLigada->cabeza->sig == NULL){

        }
    }
    else
    {
        struct Nodo *nodoBuscarIndice = iterarHastaIndice(listaLigada, indice-1); //apuntar el nodo anterior al indice
        struct Nodo *nuevoNodoBorrar = nodoBuscarIndice->sig;
        nodoBuscarIndice->sig = nuevoNodoBorrar->sig;
        liberarMemoriaNodoLL(nuevoNodoBorrar);
    }
    listaLigada->longitud = listaLigada->longitud-1;
}

void recuperarDeLL(struct ListaLigada *listaLigada, int indice, struct Linea *resultadoDevuelto)
{
    struct Nodo *nodoDevuelto = iterarHastaIndice(listaLigada, indice);
    if (nodoDevuelto)
    {
        *resultadoDevuelto = nodoDevuelto->linea;
    }
    else
    {
        printf("Error: No existe nodo con ese indice\n");
        exit(-1);
    }
}
