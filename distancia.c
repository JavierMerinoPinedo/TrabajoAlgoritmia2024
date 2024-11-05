#include <stdio.h>
#include "distancia.h"
#include <math.h>
#include <string.h>


float calcularDistanciaString(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0) {
        return 0;
    } else {
        return 1;
    }
}
float calcularDistancia(struct Linea a, struct Linea b){
	float suma = (pow(a.edad - b.edad,2) +
				calcularDistanciaString(a.sexo, b.sexo) +
				pow(a.colesterol - b.colesterol,2) +
				pow(a.presionSanguineaAlta - b.presionSanguineaAlta,2) +
				pow(a.presionSanguineaBaja - b.presionSanguineaBaja,2) +
				pow(a.frecuenciaCardiaca - b.frecuenciaCardiaca,2) +
				pow(a.diabetes - b.diabetes,2) +
				pow(a.historialFamiliar - b.historialFamiliar,2) +
				pow(a.fuma - b.fuma,2) +
				pow(a.obesidad - b.obesidad,2) +
				pow(a.alcohol - b.alcohol,2) +
				pow(a.horasEjercicio - b.horasEjercicio,2) +
				calcularDistanciaString(a.dieta, b.dieta) +
				pow(a.problemasAnteriores - b.problemasAnteriores,2) +
				pow(a.medicacion - b.medicacion,2) +
				pow(a.estres - b.estres,2) +
				pow(a.sedentario - b.sedentario,2) +
				pow(a.ingreso - b.ingreso,2) +
				pow(a.imc - b.imc,2) +
				pow(a.trigliceridos - b.trigliceridos,2) +
				pow(a.actividadFisica - b.actividadFisica,2) +
				pow(a.horasDormir - b.horasDormir,2) +
				calcularDistanciaString(a.pais, b.pais) +
				calcularDistanciaString(a.continente, b.continente) +
				calcularDistanciaString(a.hemisferio, b.hemisferio));
    return sqrt(suma);
}
