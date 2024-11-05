
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "maxMonticulo.h"

//2i + 2 es el hijo derecho del MaxMonticulo
//2i + 1 es el hijo izquierdo del MaxMonticulo
//(i-1)/2 es el padre del MaxMonticulo


void nuevoMaxMonticulo(tipoMaxMonticulo* t, int nume)
{
    t->array = (tipoElementoMaxMonticulo*)malloc(sizeof(tipoElementoMaxMonticulo) * nume);

    if (t->array == NULL)
    {
        // Manejo de error si la asignación de memoria falla
        fprintf(stderr, "Error: Fallo en la asignación de memoria.\n");
        exit(EXIT_FAILURE); // O realiza cualquier acción de manejo de errores adecuada para tu aplicación.
    }

    t->pos = 0;
    t->numEl = nume;
}


void insertarMaxMonticulo(tipoMaxMonticulo *t, tipoElementoMaxMonticulo e)
{

    if (estaLleno(*t))
    {
        printf("\nERROR: El montículo está lleno\n");
    }
    else
    {
        int i;
        tipoElementoMaxMonticulo aux;
        t->array[t->pos] = e;
        t->pos++;
        i = t->pos - 1;
        while (i > 0 && e.distancia > t->array[(i - 1) / 2].distancia)
        {
            aux = t->array[i];
            t->array[i] = t->array[(i - 1) / 2];
            t->array[(i - 1) / 2] = aux;
            i = (i - 1) / 2;
        }
    }
}

void eliminarElemento(tipoMaxMonticulo *t, tipoElementoMaxMonticulo e)
{
    if (!esVacio(*t))
    {
        int i = 0;
        while (i < t->pos && t->array[i].distancia != e.distancia)
        {
            i++;
        }
        if (i == t->pos)
        {
            printf("\nERROR: No existe el elemento que quieres eliminar\n");
        }
        else
        {
            t->array[i] = t->array[t->pos - 1];
            t->pos = t->pos - 1;
            while ((2 * i + 1 < t->pos && t->array[i].distancia < t->array[2 * i + 1].distancia) || (2 * i + 2 < t->pos && t->array[i].distancia < t->array[2 * i + 2].distancia))
            {
                masCercanos aux;
                aux = t->array[i];
                if (2 * i + 2 < t->pos && t->array[2 * i + 1].distancia < t->array[2 * i + 2].distancia)
                {
                    t->array[i] = t->array[2 * i + 2];
                    t->array[2 * i + 2] = aux;
                    i = 2 * i + 2;
                }
                else
                {
                    t->array[i] = t->array[2 * i + 1];
                    t->array[2 * i + 1] = aux;
                    i = 2 * i + 1;
                }
            }
        }
    }
    else
    {
        printf("\nERROR: No se puede eliminar en monticulo vacio\n");

    }
}

tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo t)
{
    if (!esVacio(t))
    {
        return t.array[0];
    }
    else
    {
        printf("\nERROR: No hay raiz en monticulo vacio\n");
        exit(-1);
    }
}

void mostrarAnchura(tipoMaxMonticulo t)
{
    for(int i = 0; i < t.pos; i++)
    {
        printf("%f ", t.array[i].distancia);
    }
    printf("\n");
}

bool esVacio(tipoMaxMonticulo t)
{
    return t.pos == 0;
}

bool estaLleno(tipoMaxMonticulo t)
{
    return t.pos == t.numEl;
}
