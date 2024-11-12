#include <stdio.h>
#include "distancia.h"
#include <math.h>
#include <string.h>
//prueba

float calcularDistanciaString(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0) {
        return 0;
    } else {
        return 1;
    }
}
float calcularDistancia(struct Linea a, struct Linea b){
	float suma = (calcularDistanciaString(a.sexo, b.sexo) + 
				pow(a.edad - b.edad,2) +
				pow(a.hipertension - b.hipertension,2) +
				pow(a.enfermedadCardiaca - b.enfermedadCardiaca,2) +
				calcularDistanciaString(a.fuma, b.fuma) +
				pow(a.imc - b.imc,2) +
				pow(a.hemoglobina - b.hemoglobina,2) +
				pow(a.glucosa - b.glucosa,2));
    return sqrt(suma);
}
