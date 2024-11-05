#ifndef LISTALIGADA_H
#define LISTALIGADA_H
#include "nodo.h"

struct ListaLigada
{
    struct Nodo *cabeza;  //primer nodo de la lista
    int longitud;
};

struct ListaLigada nuevaLL();
bool esVaciaLL(struct ListaLigada listaLigada);
void borrarLL(struct ListaLigada *listaLigada);
void recuperarDeLL(struct ListaLigada *listaLigada, int indice, struct Linea *resultadoDevuelto);
void insertarEnLL(struct ListaLigada *listaLigada, int indice, struct Linea linea);
void borrarNodoDeLL(struct ListaLigada *listaLigada, int indice);
void liberarMemoriaNodoLL(struct Nodo *nodoBorrado); //solo libera la memoria de un nodo
struct Nodo * nuevoNodoLL(struct Linea linea, int indice);
struct Nodo * iterarHastaIndice(struct ListaLigada *listaLigada, int indice);

#endif
