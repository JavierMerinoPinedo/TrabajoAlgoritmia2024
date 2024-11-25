all: final

maxMonticulo.o: maxMonticulo.c
	gcc maxMonticulo.c -c

nodo.o: nodo.c
	gcc nodo.c -c

listaLigada.o: listaLigada.c
	gcc listaLigada.c -c

distancia.o: distancia.c
	gcc distancia.c -c


final: listaLigada.o nodo.o distancia.o maxMonticulo.o final.c
	gcc final.c nodo.o listaLigada.o distancia.o maxMonticulo.o -g -o final -lm

clean:
	rm -f final listaLigada.o nodo.o distancia.o maxMonticulo.o
