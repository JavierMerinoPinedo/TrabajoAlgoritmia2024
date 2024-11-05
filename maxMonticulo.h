#include <stdbool.h>

typedef struct masCercanos{ //definir tipo
    int posicion;
    float distancia;
	int clase;
}masCercanos;

typedef masCercanos tipoElementoMaxMonticulo;

typedef struct tMM{
	tipoElementoMaxMonticulo* array;
	int pos; //El numero de elementos que hay en la tabla
	int numEl;
}tipoMaxMonticulo;

void nuevoMaxMonticulo(tipoMaxMonticulo*, int);

void insertarMaxMonticulo(tipoMaxMonticulo *, tipoElementoMaxMonticulo);

void eliminarElemento(tipoMaxMonticulo *, tipoElementoMaxMonticulo);

tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo);

void mostrarAnchura(tipoMaxMonticulo);

bool esVacio(tipoMaxMonticulo);

bool estaLleno(tipoMaxMonticulo);
