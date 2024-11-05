#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "distancia.h"
#include "colors.h"
#include "maxMonticulo.h"

typedef struct maximos{
	float maxEdad;
	float maxColesterol;
	float maxPresionSanguineaAlta;
	float maxPresionSanguineaBaja;
	float maxFrecuenciaCardiaca;
	float maxHorasEjercicio;
	float maxEstres;
	float maxSedentario;
	float maxIngreso;
	float maxImc;
	float maxTrigliceridos;
	float maxActividadFisica;
	float maxHorasDormir;
}maximo;

typedef struct minimos{
	float minEdad;
	float minColesterol;
	float minPresionSanguineaAlta;
	float minPresionSanguineaBaja;
	float minFrecuenciaCardiaca;
	float minHorasEjercicio;
	float minEstres;
	float minSedentario;
	float minIngreso;
	float minImc;
	float minTrigliceridos;
	float minActividadFisica;
	float minHorasDormir;
}minimo;


float minMaxNormalizacion(float valor, float min, float max);
void imprimeEjemplo(struct Linea k1);
void ajustarPrecision(struct Linea *imp);

int main(void)
{
	struct Linea ejemplo, k1, vecino;
	struct ListaLigada listaMedica = nuevaLL();
	struct ListaLigada listaWilson = nuevaLL();
	minimo minimos;
	maximo maximos;
	char *token;
	int contadorSi = 0, contadorNo = 0, mejorIndice = 10000, prediccion, k, opcion;
	float exitosTotales, porcentajeExito;

	FILE *Excel = fopen("heart_attack_prediction_dataset.csv", "r");
	FILE *Excel2 = fopen("heart_attack_prediction_dataset.csv", "r");

	char linea[1024];
	char linea2[1024];

	{
	maximos.maxEdad = 0;
	maximos.maxColesterol = 0;
	maximos.maxPresionSanguineaAlta = 0;
	maximos.maxPresionSanguineaBaja = 0;
	maximos.maxFrecuenciaCardiaca = 0;
	maximos.maxHorasEjercicio = 0;
	maximos.maxEstres = 0;
	maximos.maxSedentario = 0;
	maximos.maxIngreso = 0;
	maximos.maxImc = 0;
	maximos.maxTrigliceridos = 0;
	maximos.maxActividadFisica = 0;
	maximos.maxHorasDormir = 0;

	minimos.minEdad = 1000;
	minimos.minColesterol = 10000;
	minimos.minPresionSanguineaAlta = 10000;
	minimos.minPresionSanguineaBaja = 10000;
	minimos.minFrecuenciaCardiaca = 10000;
	minimos.minHorasEjercicio = 1000;
	minimos.minEstres = 10000;
	minimos.minSedentario = 10000;
	minimos.minIngreso = 100000;
	minimos.minImc = 1000;
	minimos.minTrigliceridos = 1000;
	minimos.minActividadFisica = 1000;
	minimos.minHorasDormir = 1000;
	}

	double mejorDistancia = 1000000000;

	//Bucle para sacar maximos y minimos de todo el dataset
	fgets(linea, sizeof(linea), Excel);
	for(int i = 1; i < 8764; i++){
		fgets(linea, sizeof(linea), Excel);
		token = strtok(linea, ",");
		if(token != NULL)
		{
			ejemplo.edad = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.sexo, token, sizeof(ejemplo.sexo));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.colesterol = atof(token);
			token = strtok(NULL, "/");
		}
		if(token != NULL)
		{
			ejemplo.presionSanguineaAlta = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.presionSanguineaBaja = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.frecuenciaCardiaca = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.diabetes = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.historialFamiliar = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.fuma = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.obesidad = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.alcohol = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.horasEjercicio = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.dieta, token, sizeof(ejemplo.dieta));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.problemasAnteriores = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.medicacion = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.estres = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.sedentario = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.ingreso = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.imc = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.trigliceridos = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.actividadFisica = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.horasDormir = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.pais, token, sizeof(ejemplo.pais));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.continente, token, sizeof(ejemplo.continente));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.hemisferio, token, sizeof(ejemplo.hemisferio));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.riesgoAtaque = atof(token);
			token = strtok(NULL, ",");
		}

		if(maximos.maxEdad < ejemplo.edad)
			maximos.maxEdad = ejemplo.edad;
		if(maximos.maxColesterol < ejemplo.colesterol)
			maximos.maxColesterol = ejemplo.colesterol;
		if(maximos.maxPresionSanguineaAlta < ejemplo.presionSanguineaAlta)
			maximos.maxPresionSanguineaAlta = ejemplo.presionSanguineaAlta;
		if(maximos.maxPresionSanguineaBaja < ejemplo.presionSanguineaBaja)
			maximos.maxPresionSanguineaBaja = ejemplo.presionSanguineaBaja;
		if(maximos.maxFrecuenciaCardiaca < ejemplo.frecuenciaCardiaca)
			maximos.maxFrecuenciaCardiaca = ejemplo.frecuenciaCardiaca;
		if(maximos.maxHorasEjercicio < ejemplo.horasEjercicio)
			maximos.maxHorasEjercicio = ejemplo.horasEjercicio;
		if(maximos.maxEstres < ejemplo.estres)
			maximos.maxEstres = ejemplo.estres;
		if(maximos.maxSedentario < ejemplo.sedentario)
			maximos.maxSedentario = ejemplo.sedentario;
		if(maximos.maxIngreso < ejemplo.ingreso)
			maximos.maxIngreso = ejemplo.ingreso;
		if(maximos.maxImc < ejemplo.imc)
			maximos.maxImc = ejemplo.imc;
		if(maximos.maxTrigliceridos < ejemplo.trigliceridos)
			maximos.maxTrigliceridos = ejemplo.trigliceridos;
		if(maximos.maxActividadFisica < ejemplo.actividadFisica)
			maximos.maxActividadFisica = ejemplo.actividadFisica;
		if(maximos.maxHorasDormir < ejemplo.horasDormir)
			maximos.maxHorasDormir = ejemplo.horasDormir;


		if(minimos.minEdad > ejemplo.edad)
			minimos.minEdad = ejemplo.edad;
		if(minimos.minColesterol > ejemplo.colesterol)
			minimos.minColesterol = ejemplo.colesterol;
		if(minimos.minPresionSanguineaAlta > ejemplo.presionSanguineaAlta)
			minimos.minPresionSanguineaAlta = ejemplo.presionSanguineaAlta;
		if(minimos.minPresionSanguineaBaja > ejemplo.presionSanguineaBaja)
			minimos.minPresionSanguineaBaja = ejemplo.presionSanguineaBaja;
		if(minimos.minFrecuenciaCardiaca > ejemplo.frecuenciaCardiaca)
			minimos.minFrecuenciaCardiaca = ejemplo.frecuenciaCardiaca;
		if(minimos.minHorasEjercicio > ejemplo.horasEjercicio)
			minimos.minHorasEjercicio = ejemplo.horasEjercicio;
		if(minimos.minEstres > ejemplo.estres)
			minimos.minEstres = ejemplo.estres;
		if(minimos.minSedentario > ejemplo.sedentario)
			minimos.minSedentario = ejemplo.sedentario;
		if(minimos.minIngreso > ejemplo.ingreso)
			minimos.minIngreso = ejemplo.ingreso;
		if(minimos.minImc > ejemplo.imc)
			minimos.minImc = ejemplo.imc;
		if(minimos.minTrigliceridos > ejemplo.trigliceridos)
			minimos.minTrigliceridos = ejemplo.trigliceridos;
		if(minimos.minActividadFisica > ejemplo.actividadFisica)
			minimos.minActividadFisica = ejemplo.actividadFisica;
		if(minimos.minHorasDormir > ejemplo.horasDormir)
			minimos.minHorasDormir = ejemplo.horasDormir;

	}


	//Bucle para normalizar cada dato del dataset
	fgets(linea2, sizeof(linea2), Excel2);
	for(int i = 1; i < 8764; i++){
		fgets(linea2, sizeof(linea2), Excel2);
		token = strtok(linea2, ",");
		if(token != NULL)
		{
			ejemplo.edad = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.sexo, token, sizeof(ejemplo.sexo));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.colesterol = atof(token);
			token = strtok(NULL, "/");
		}
		if(token != NULL)
		{
			ejemplo.presionSanguineaAlta = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.presionSanguineaBaja = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.frecuenciaCardiaca = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.diabetes = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.historialFamiliar = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.fuma = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.obesidad = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.alcohol = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.horasEjercicio = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.dieta, token, sizeof(ejemplo.dieta));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.problemasAnteriores = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.medicacion = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.estres = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.sedentario = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.ingreso = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.imc = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.trigliceridos = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.actividadFisica = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.horasDormir = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.pais, token, sizeof(ejemplo.pais));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.continente, token, sizeof(ejemplo.continente));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.hemisferio, token, sizeof(ejemplo.hemisferio));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.riesgoAtaque = atof(token);
			token = strtok(NULL, ",");
		}

		ejemplo.edad = minMaxNormalizacion(ejemplo.edad, minimos.minEdad, maximos.maxEdad);
		ejemplo.colesterol = minMaxNormalizacion(ejemplo.colesterol, minimos.minColesterol, maximos.maxColesterol);
		ejemplo.presionSanguineaAlta = minMaxNormalizacion(ejemplo.presionSanguineaAlta, minimos.minPresionSanguineaAlta, maximos.maxPresionSanguineaAlta);
		ejemplo.presionSanguineaBaja = minMaxNormalizacion(ejemplo.presionSanguineaBaja, minimos.minPresionSanguineaBaja, maximos.maxPresionSanguineaBaja);
		ejemplo.frecuenciaCardiaca = minMaxNormalizacion(ejemplo.frecuenciaCardiaca, minimos.minFrecuenciaCardiaca, maximos.maxFrecuenciaCardiaca);
		ejemplo.horasEjercicio = minMaxNormalizacion(ejemplo.horasEjercicio, minimos.minHorasEjercicio, maximos.maxHorasEjercicio);
		ejemplo.estres = minMaxNormalizacion(ejemplo.estres, minimos.minEstres, maximos.maxEstres);
		ejemplo.sedentario = minMaxNormalizacion(ejemplo.sedentario, minimos.minSedentario, maximos.maxSedentario);
		ejemplo.ingreso = minMaxNormalizacion(ejemplo.ingreso, minimos.minIngreso, maximos.maxIngreso);
		ejemplo.imc = minMaxNormalizacion(ejemplo.imc, minimos.minImc, maximos.maxImc);
		ejemplo.trigliceridos = minMaxNormalizacion(ejemplo.trigliceridos, minimos.minTrigliceridos, maximos.maxTrigliceridos);
		ejemplo.actividadFisica = minMaxNormalizacion(ejemplo.actividadFisica, minimos.minActividadFisica, maximos.maxActividadFisica);
		ejemplo.horasDormir = minMaxNormalizacion(ejemplo.horasDormir, minimos.minHorasDormir, maximos.maxHorasDormir);

		ajustarPrecision(&ejemplo);
		insertarEnLL(&listaMedica, i, ejemplo); // Normalizados

	}

	printf("Introduce el numero de k-vecinos: ");
	scanf("%d", &k);
	printf("\n\n");
	do
    {
		printf("--------MENU-------- \n");
		printf("1 - Cambiar numero de k-vecinos\n");
		printf("2 - Introducir un nuevo dato para clasificarlo con todo el dataset\n");
		printf("3 - Comparar todos con k1\n");
		printf("4 - Comparar todos los datos\n");
		printf("5 - Algoritmo de Wilson\n");
		printf("6 - Salir.\n");
		printf("Escoja una opcion: ");
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
			{
				printf("Introduce el numero de k-vecinos: ");
				scanf("%d",&k);
				printf("\n\n");
				break;
			}
			case 2:
			{
				tipoElementoMaxMonticulo masCercanok1;
				tipoMaxMonticulo kVecinosMasCercanosk1;
				nuevoMaxMonticulo(&kVecinosMasCercanosk1, k);
				porcentajeExito = 0;
				contadorSi = 0;
				contadorNo = 0;

				printf("Edad: ");
				scanf("%f", &k1.edad);

				printf("Sexo: ");
				scanf("%s", k1.sexo);

				printf("Colesterol: ");
				scanf("%f", &k1.colesterol);

				printf("Presion Sanguinea Alta: ");
				scanf("%f", &k1.presionSanguineaAlta);

				printf("Presion Sanguinea Baja: ");
				scanf("%f", &k1.presionSanguineaBaja);

				printf("Frecuencia Cardiaca: ");
				scanf("%f", &k1.frecuenciaCardiaca);

				printf("Diabetes: ");
				scanf("%f", &k1.diabetes);

				printf("Historial Familiar: ");
				scanf("%f", &k1.historialFamiliar);

				printf("Fuma: ");
				scanf("%f", &k1.fuma);

				printf("Obesidad: ");
				scanf("%f", &k1.obesidad);

				printf("Alcohol: ");
				scanf("%f", &k1.alcohol);

				printf("Horas de Ejercicio: ");
				scanf("%f", &k1.horasEjercicio);

				printf("Dieta: ");
				scanf("%s", k1.dieta);

				printf("Problemas Anteriores: ");
				scanf("%f", &k1.problemasAnteriores);

				printf("Medicacion: ");
				scanf("%f", &k1.medicacion);

				printf("Estres: ");
				scanf("%f", &k1.estres);

				printf("Sedentario: ");
				scanf("%f", &k1.sedentario);

				printf("Ingreso: ");
				scanf("%f", &k1.ingreso);

				printf("IMC: ");
				scanf("%f", &k1.imc);

				printf("Trigliceridos: ");
				scanf("%f", &k1.trigliceridos);

				printf("Actividad Fisica: ");
				scanf("%f", &k1.actividadFisica);

				printf("Horas Dormir: ");
				scanf("%f", &k1.horasDormir);

				printf("Pais: ");
				scanf("%s", k1.pais);

				printf("Continente: ");
				scanf(" %[^\n]", k1.continente);

				printf("Hemisferio: ");
				scanf(" %[^\n]", k1.hemisferio);

 				printf("Riesgo de Ataque: ");
 				scanf("%f", &k1.riesgoAtaque);

				k1.edad = minMaxNormalizacion(k1.edad, minimos.minEdad, maximos.maxEdad);
				k1.colesterol = minMaxNormalizacion(k1.colesterol, minimos.minColesterol, maximos.maxColesterol);
				k1.presionSanguineaAlta = minMaxNormalizacion(k1.presionSanguineaAlta, minimos.minPresionSanguineaAlta, maximos.maxPresionSanguineaAlta);
				k1.presionSanguineaBaja = minMaxNormalizacion(k1.presionSanguineaBaja, minimos.minPresionSanguineaBaja, maximos.maxPresionSanguineaBaja);
				k1.frecuenciaCardiaca = minMaxNormalizacion(k1.frecuenciaCardiaca, minimos.minFrecuenciaCardiaca, maximos.maxFrecuenciaCardiaca);
				k1.horasEjercicio = minMaxNormalizacion(k1.horasEjercicio, minimos.minHorasEjercicio, maximos.maxHorasEjercicio);
				k1.estres = minMaxNormalizacion(k1.estres, minimos.minEstres, maximos.maxEstres);
				k1.sedentario = minMaxNormalizacion(k1.sedentario, minimos.minSedentario, maximos.maxSedentario);
				k1.ingreso = minMaxNormalizacion(k1.ingreso, minimos.minIngreso, maximos.maxIngreso);
				k1.imc = minMaxNormalizacion(k1.imc, minimos.minImc, maximos.maxImc);
				k1.trigliceridos = minMaxNormalizacion(k1.trigliceridos, minimos.minTrigliceridos, maximos.maxTrigliceridos);
				k1.actividadFisica = minMaxNormalizacion(k1.actividadFisica, minimos.minActividadFisica, maximos.maxActividadFisica);
				k1.horasDormir = minMaxNormalizacion(k1.horasDormir, minimos.minHorasDormir, maximos.maxHorasDormir);

				ajustarPrecision(&k1);

				for (int i = 1; i < listaMedica.longitud; i++)
				{
					recuperarDeLL(&listaMedica, i, &ejemplo);
					float distancia = calcularDistancia(ejemplo, k1);
					if (distancia < mejorDistancia)
					{
						mejorDistancia = distancia;
						mejorIndice = i;
					}
				}

				if(mejorDistancia == 0){
					printf(LBLUE"El k1 es una linea del dataset por lo que la borro y volvemos a comparar\n"RESET);
					borrarNodoDeLL(&listaMedica, mejorIndice);
				}
				mejorDistancia = 10000;

				masCercanok1.distancia = 10000;
				masCercanok1.posicion = -1;
				masCercanok1.clase = -1;
				insertarMaxMonticulo(&kVecinosMasCercanosk1, masCercanok1);
				for (int i = 1; i < listaMedica.longitud; i++)
				{
					recuperarDeLL(&listaMedica, i, &ejemplo);

					float distancia = calcularDistancia(ejemplo, k1);
					masCercanok1.posicion = i;
					masCercanok1.distancia = distancia;
					masCercanok1.clase = ejemplo.riesgoAtaque;

					if(masCercanok1.distancia < (devolverRaiz(kVecinosMasCercanosk1)).distancia){
						if(estaLleno(kVecinosMasCercanosk1))
						{
							eliminarElemento(&kVecinosMasCercanosk1, devolverRaiz(kVecinosMasCercanosk1));
							insertarMaxMonticulo(&kVecinosMasCercanosk1, masCercanok1);
						}
						else
							insertarMaxMonticulo(&kVecinosMasCercanosk1, masCercanok1);
					}
				}
				printf(RED"Los %d vecinos más cercanos para la linea k1:\n", k);
				while (!esVacio(kVecinosMasCercanosk1)){
					tipoElementoMaxMonticulo masCercanosk1 = devolverRaiz(kVecinosMasCercanosk1);
					printf(GREEN"%f %d %d\n", masCercanosk1.distancia, masCercanosk1.posicion, masCercanosk1.clase);
					if(masCercanosk1.clase == 0)
						contadorNo += 1;
					else
						contadorSi += 1;
					masCercanok1 = devolverRaiz(kVecinosMasCercanosk1);
					eliminarElemento(&kVecinosMasCercanosk1, masCercanosk1);
				}
				if(contadorNo > contadorSi)
					prediccion = 0;
				else if(contadorNo < contadorSi)
					prediccion = 1;
				else
					prediccion = masCercanok1.clase;
				printf(YELLOW"La prediccion para la linea k1 es: %d\n"RESET, prediccion);
				if(prediccion == k1.riesgoAtaque)
					exitosTotales += 1;

				printf(BG_BLUE"Ejemplo mas cercano = %d\n",masCercanok1.posicion);
				printf("Distancia Minima = %f\n", masCercanok1.distancia);
				printf("Prediccion de clase = %d\n",prediccion);
				printf("\n\n");
				break;
			}
			case 3:
			{
				tipoElementoMaxMonticulo masCercano;
				tipoMaxMonticulo kVecinosMasCercanos;
				nuevoMaxMonticulo(&kVecinosMasCercanos, 1);
				porcentajeExito = 0;
				exitosTotales = 0;

				for (int i = 1; i <= listaMedica.longitud; i++) {
					masCercano.distancia = 10000;
					masCercano.posicion = -1;
					masCercano.clase = -1;
					insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
					recuperarDeLL(&listaMedica, i, &ejemplo);

					int contadorSi = 0;
					int contadorNo = 0;

					for (int j = 1; j <= listaMedica.longitud; j++) {
						if (i != j) {
							recuperarDeLL(&listaMedica, j, &vecino);
							float distancia = calcularDistancia(ejemplo, vecino);
							masCercano.posicion = j;
							masCercano.distancia = distancia;
							masCercano.clase = vecino.riesgoAtaque;

							if(masCercano.distancia < (devolverRaiz(kVecinosMasCercanos)).distancia){
								if(estaLleno(kVecinosMasCercanos))
								{
									eliminarElemento(&kVecinosMasCercanos, devolverRaiz(kVecinosMasCercanos));
									insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
								}
								else
									insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
							}
						}
					}

					printf(RED"Los %d vecinos más cercanos para la linea %d son:\n", 1, i);

					while (!esVacio(kVecinosMasCercanos)){
						tipoElementoMaxMonticulo masCercanos = devolverRaiz(kVecinosMasCercanos);
						printf(GREEN"%f %d %d\n", masCercanos.distancia, masCercanos.posicion, masCercanos.clase);
						if(masCercanos.clase == 0)
							contadorNo += 1;
						else
							contadorSi += 1;
						masCercano = devolverRaiz(kVecinosMasCercanos);
						eliminarElemento(&kVecinosMasCercanos, masCercanos);
					}

					if(contadorNo > contadorSi)
						prediccion = 0;
					else if(contadorNo < contadorSi)
						prediccion = 1;
					else
						prediccion = masCercano.clase;
					printf(YELLOW"La prediccion para la linea %d es: %d", i, prediccion);
					if(prediccion == ejemplo.riesgoAtaque)
						exitosTotales += 1;
					printf("\n\n");
				}

				porcentajeExito = (float) (exitosTotales / listaMedica.longitud) * 100;
				printf(WHITE BG_BLUE"Porcentaje de éxito para k1: %f%%\n" RESET, porcentajeExito);
				printf("\n\n");
				while(!esVacio(kVecinosMasCercanos)){
					printf("Error\n");
					eliminarElemento(&kVecinosMasCercanos, devolverRaiz(kVecinosMasCercanos));
				}
				break;
			}
			case 4:
			{
				tipoElementoMaxMonticulo masCercano;
				tipoMaxMonticulo kVecinosMasCercanos;
				nuevoMaxMonticulo(&kVecinosMasCercanos, k);
				float porcentajeExito = 0;
				exitosTotales = 0;


				for (int i = 1; i <= listaMedica.longitud; i++) {
					masCercano.distancia = 10000;
					masCercano.posicion = -1;
					masCercano.clase = -1;
					insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
					recuperarDeLL(&listaMedica, i, &ejemplo);

					int contadorSi = 0;
					int contadorNo = 0;

					for (int j = 1; j <= listaMedica.longitud; j++) {
						if (i != j) {
							recuperarDeLL(&listaMedica, j, &vecino);
							float distancia = calcularDistancia(ejemplo, vecino);
							masCercano.posicion = j;
							masCercano.distancia = distancia;
							masCercano.clase = vecino.riesgoAtaque;

							if(masCercano.distancia < (devolverRaiz(kVecinosMasCercanos)).distancia){
								if(estaLleno(kVecinosMasCercanos))
								{
									eliminarElemento(&kVecinosMasCercanos, devolverRaiz(kVecinosMasCercanos));
									insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
								}
								else
									insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
							}
						}
					}

					printf(RED"Los %d vecinos más cercanos para la linea %d son:\n", k, i);

					while (!esVacio(kVecinosMasCercanos)){
						tipoElementoMaxMonticulo masCercanos = devolverRaiz(kVecinosMasCercanos);
						printf(GREEN"%f %d %d\n", masCercanos.distancia, masCercanos.posicion, masCercanos.clase);
						if(masCercanos.clase == 0)
							contadorNo += 1;
						else
							contadorSi += 1;
						masCercano = devolverRaiz(kVecinosMasCercanos);
						eliminarElemento(&kVecinosMasCercanos, masCercanos);
					}

					if(contadorNo > contadorSi)
						prediccion = 0;
					else if(contadorNo < contadorSi)
						prediccion = 1;
					else
						prediccion = masCercano.clase;
					printf(YELLOW"La prediccion para la linea %d es: %d", i, prediccion);
					if(prediccion == ejemplo.riesgoAtaque)
						exitosTotales += 1;
					printf("\n\n");
				}

				porcentajeExito = (float) (exitosTotales / listaMedica.longitud) * 100;
				printf(WHITE BG_BLUE"Porcentaje de éxito para k%d: %f" RESET, k, porcentajeExito);
				printf("\n\n");
				while(!esVacio(kVecinosMasCercanos)){
					printf("Error\n");
					eliminarElemento(&kVecinosMasCercanos, devolverRaiz(kVecinosMasCercanos));
				}
				porcentajeExito = 0;
				break;
			}
			case 5:
			{
				tipoElementoMaxMonticulo masCercano;
				tipoMaxMonticulo kVecinosMasCercanos;
				nuevoMaxMonticulo(&kVecinosMasCercanos, k);
				int iWilson = 1;
				prediccion = -1;
				exitosTotales = 0;

				for (int i = 1; i <= listaMedica.longitud; i++) {
					masCercano.distancia = 10000;
					masCercano.posicion = -1;
					masCercano.clase = -1;
					insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
					recuperarDeLL(&listaMedica, i, &ejemplo);

					int contadorSi = 0;
					int contadorNo = 0;

					for (int j = 1; j <= listaMedica.longitud; j++) {
						if (i != j) {
							recuperarDeLL(&listaMedica, j, &vecino);
							float distancia = calcularDistancia(ejemplo, vecino);
							masCercano.posicion = j;
							masCercano.distancia = distancia;
							masCercano.clase = vecino.riesgoAtaque;

							if(masCercano.distancia < (devolverRaiz(kVecinosMasCercanos)).distancia){
								if(estaLleno(kVecinosMasCercanos))
								{
									eliminarElemento(&kVecinosMasCercanos, devolverRaiz(kVecinosMasCercanos));
									insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
								}
								else
									insertarMaxMonticulo(&kVecinosMasCercanos, masCercano);
							}
						}
					}

					printf(RED"Los %d vecinos más cercanos para la linea %d son:\n", k, i);

					while (!esVacio(kVecinosMasCercanos)){
						tipoElementoMaxMonticulo masCercanos = devolverRaiz(kVecinosMasCercanos);
						printf(GREEN"%f %d %d\n", masCercanos.distancia, masCercanos.posicion, masCercanos.clase);
						if(masCercanos.clase == 0)
							contadorNo += 1;
						else
							contadorSi += 1;
						masCercano = devolverRaiz(kVecinosMasCercanos);
						eliminarElemento(&kVecinosMasCercanos, masCercanos);
					}

					if(contadorNo > contadorSi)
						prediccion = 0;
					else if(contadorNo < contadorSi)
						prediccion = 1;
					else
						prediccion = masCercano.clase;
					printf(YELLOW"La prediccion para la linea %d es: %d\n", i, prediccion);
					if(prediccion == ejemplo.riesgoAtaque){
						exitosTotales += 1;
						printf("La prediccion es correcta, por lo que voy a insertarlo en la listaWilson\n");
						insertarEnLL(&listaWilson, iWilson, ejemplo);
						iWilson += 1;
					}
					printf("\n\n");
				}

				//WILSON
				prediccion = -1;
				exitosTotales = 0;
				tipoElementoMaxMonticulo masCercanoWilson;
				tipoMaxMonticulo kVecinosMasCercanosWilson;
				nuevoMaxMonticulo(&kVecinosMasCercanosWilson, k);
				for (int i = 1; i <= listaWilson.longitud; i++) {
					masCercanoWilson.distancia = 10000;
					masCercanoWilson.posicion = -1;
					masCercanoWilson.clase = -1;
					insertarMaxMonticulo(&kVecinosMasCercanosWilson, masCercanoWilson);
					recuperarDeLL(&listaWilson, i, &ejemplo);

					int contadorSiWilson = 0;
					int contadorNoWilson = 0;

					for (int j = 1; j <= listaWilson.longitud; j++) {
						if (i != j) {
							recuperarDeLL(&listaWilson, j, &vecino);
							float distanciaWilson = calcularDistancia(ejemplo, vecino);
							masCercanoWilson.posicion = j;
							masCercanoWilson.distancia = distanciaWilson;
							masCercanoWilson.clase = vecino.riesgoAtaque;

							if(masCercanoWilson.distancia < (devolverRaiz(kVecinosMasCercanosWilson)).distancia && (masCercanoWilson.distancia != 0)){
								if(estaLleno(kVecinosMasCercanosWilson))
								{
									eliminarElemento(&kVecinosMasCercanosWilson, devolverRaiz(kVecinosMasCercanosWilson));
									insertarMaxMonticulo(&kVecinosMasCercanosWilson, masCercanoWilson);
								}
								else
									insertarMaxMonticulo(&kVecinosMasCercanosWilson, masCercanoWilson);
							}
						}
					}

					printf(YELLOW"Los %d vecinos más cercanos para la linea %d son:\n", k, i);

					while (!esVacio(kVecinosMasCercanosWilson)){
						tipoElementoMaxMonticulo masCercanos = devolverRaiz(kVecinosMasCercanosWilson);
						printf(BLUE"%f %d %d\n", masCercanos.distancia, masCercanos.posicion, masCercanos.clase);
						if(masCercanos.clase == 0)
							contadorNoWilson += 1;
						else
							contadorSiWilson += 1;
						masCercanoWilson = devolverRaiz(kVecinosMasCercanosWilson);
						eliminarElemento(&kVecinosMasCercanosWilson, masCercanos);
					}

					if(contadorNoWilson > contadorSiWilson)
						prediccion = 0;
					else if(contadorNoWilson < contadorSiWilson)
						prediccion = 1;
					else
						prediccion = masCercanoWilson.clase;
					printf("La prediccion para la linea %d es: %d", i, prediccion);
					if(prediccion == ejemplo.riesgoAtaque)
						exitosTotales += 1;
					printf("\n\n");
				}

				float porcentajeExito = (float) (exitosTotales / listaWilson.longitud) * 100;
				printf(WHITE BG_BLUE"Porcentaje de éxito de wilson para k%d: %f%%" RESET, k, porcentajeExito);
				printf("\n\n");
				while(!esVacio(kVecinosMasCercanosWilson))
					eliminarElemento(&kVecinosMasCercanosWilson, devolverRaiz(kVecinosMasCercanosWilson));
				break;
			}
		}

	}while(opcion<6);
	return 0;
}

void imprimeEjemplo(struct Linea k1) {
		printf("%f\n", k1.edad);
		printf("%s\n", k1.sexo);
		printf("%f\n", k1.colesterol);
		printf("%f\n", k1.presionSanguineaAlta);
		printf("%f\n", k1.presionSanguineaBaja);
		printf("%f\n", k1.frecuenciaCardiaca);
		printf("%f\n", k1.diabetes);
		printf("%f\n", k1.historialFamiliar);
		printf("%f\n", k1.fuma);
		printf("%f\n", k1.obesidad);
		printf("%f\n", k1.alcohol);
		printf("%f\n", k1.horasEjercicio);
		printf("%s\n", k1.dieta);
		printf("%f\n", k1.problemasAnteriores);
		printf("%f\n", k1.medicacion);
		printf("%f\n", k1.estres);
		printf("%f\n", k1.sedentario);
		printf("%f\n", k1.ingreso);
		printf("%f\n", k1.imc);
		printf("%f\n", k1.trigliceridos);
		printf("%f\n", k1.actividadFisica);
		printf("%f\n", k1.horasDormir);
		printf("%s\n", k1.pais);
		printf("%s\n", k1.continente);
		printf("%s\n", k1.hemisferio);
		printf("%f\n", k1.riesgoAtaque);
}

float minMaxNormalizacion(float valor, float min, float max)
{
	return (valor - min) / (max - min);
}

void ajustarPrecision(struct Linea *imp) {
	float importanciaMax = 1;
	float importanciaAlta = 0.75;
	float importanciaMedia = 0.5;
	float importanciaBaja = 0.25;
	float importanciaMin = 0.1;

	if (imp->edad < 45 && imp->sexo == "Male"){
          imp->edad *= importanciaMedia;
	} else if (imp->edad < 55 && imp->sexo == "Female"){
			imp->edad *= importanciaMedia;
	} else {
         imp->edad *= importanciaAlta;
	}
	imp->colesterol *= importanciaMax;
	imp->presionSanguineaAlta *= importanciaMax;
	imp->presionSanguineaBaja *= importanciaBaja;
	imp->frecuenciaCardiaca *= importanciaMedia;
	imp->diabetes *= importanciaMax;
	imp->historialFamiliar *= importanciaMax;
	imp->fuma *= importanciaMax;
	imp->obesidad *= importanciaMax;
	imp->alcohol *= importanciaAlta;
	imp->horasEjercicio *= importanciaAlta;
	imp->problemasAnteriores *= importanciaBaja;
	imp->medicacion *= importanciaBaja;
	imp->estres *= importanciaAlta;
	imp->sedentario  *= importanciaAlta;
	imp->ingreso *= importanciaMin;
	imp->imc *= importanciaAlta;
	imp->trigliceridos *= importanciaMax;
	imp->actividadFisica *= importanciaAlta;
	imp->horasDormir *= importanciaBaja;
}
