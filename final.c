#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "distancia.h"
#include "colors.h"
#include "maxMonticulo.h"
#include "linea.h"

typedef struct maximos{
	float maxEdad;
	float maxHipertension;
	float maxEnfermedadCardiaca;
	float maxImc;
	float maxHemoglobina;
	float maxGlucosa;
}maximo;

typedef struct minimos{
	float minEdad;
	float minHipertension;
	float minEnfermedadCardiaca;
	float minImc;
	float minHemoglobina;
	float minGlucosa;
}minimo;


float minMaxNormalizacion(float valor, float min, float max);
void imprimeEjemplo(struct Linea k1);
//void ajustarPrecision(struct Linea *imp);

int main(void)
{
	struct Linea ejemplo, k1, vecino;
	struct ListaLigada listaMedica = nuevaLL();
	struct ListaLigada listaWilson = nuevaLL();
	minimo minimos;
	maximo maximos;
	char *token;
	int contadorSi = 0, contadorNo = 0, mejorIndice = 10000, prediccion, k, opcion, ndatos = 5000;
	float exitosTotales, porcentajeExito;

	FILE *Excel = fopen("diabetes_prediction_dataset.csv", "r");
	FILE *Excel2 = fopen("diabetes_prediction_dataset.csv", "r");

	char linea[1024];
	char linea2[1024];

	{
	maximos.maxEdad = 0;
	maximos.maxHipertension = 0;
	maximos.maxEnfermedadCardiaca = 0;
	maximos.maxImc = 0;
	maximos.maxHemoglobina = 0;
	maximos.maxGlucosa = 0;

	minimos.minEdad = 1000000;
	minimos.minHipertension = 100000;
	minimos.minEnfermedadCardiaca = 100000;
	minimos.minImc = 1000000;
	minimos.minHemoglobina = 100000;
	minimos.minGlucosa = 1000000;
	}

	double mejorDistancia = 1000000000;

	//Bucle para sacar maximos y minimos de todo el dataset
	fgets(linea, sizeof(linea), Excel);
	for(int i = 1; i < ndatos; i++){
		fgets(linea, sizeof(linea), Excel);
		token = strtok(linea, ",");
		if(token != NULL)
		{
			strncpy(ejemplo.sexo, token, sizeof(ejemplo.sexo));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.edad = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.hipertension = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.enfermedadCardiaca = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.fuma, token, sizeof(ejemplo.fuma));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.imc = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.hemoglobina = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.glucosa = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.diabetes = atof(token);
			token = strtok(NULL, ",");
		}

		if(maximos.maxEdad < ejemplo.edad)
			maximos.maxEdad = ejemplo.edad;
		if(maximos.maxHipertension < ejemplo.hipertension)
			maximos.maxHipertension = ejemplo.hipertension;
		if(maximos.maxEnfermedadCardiaca < ejemplo.enfermedadCardiaca)
			maximos.maxEnfermedadCardiaca = ejemplo.enfermedadCardiaca;
		if(maximos.maxImc < ejemplo.imc)
			maximos.maxImc = ejemplo.imc;
		if(maximos.maxHemoglobina < ejemplo.hemoglobina)
			maximos.maxHemoglobina = ejemplo.hemoglobina;
		if(maximos.maxGlucosa < ejemplo.glucosa)
			maximos.maxGlucosa = ejemplo.glucosa;


		if(minimos.minEdad > ejemplo.edad)
			minimos.minEdad = ejemplo.edad;
		if(minimos.minHipertension > ejemplo.hipertension)
			minimos.minHipertension = ejemplo.hipertension;
		if(minimos.minEnfermedadCardiaca > ejemplo.enfermedadCardiaca)
			minimos.minEnfermedadCardiaca = ejemplo.enfermedadCardiaca;
		if(minimos.minImc > ejemplo.imc)
			minimos.minImc = ejemplo.imc;
		if(minimos.minHemoglobina > ejemplo.hemoglobina)
			minimos.minHemoglobina = ejemplo.hemoglobina;
		if(minimos.minGlucosa > ejemplo.glucosa)
			minimos.minGlucosa = ejemplo.glucosa;

	}

	printf("Maximos:\n");
	printf("Edad: %f\n", maximos.maxEdad);
	printf("Hipertension: %f\n", maximos.maxHipertension);
	printf("Enfermedad Cardiaca: %f\n", maximos.maxEnfermedadCardiaca);
	printf("Imc: %f\n", maximos.maxImc);
	printf("Hemoglobina: %f\n", maximos.maxHemoglobina);
	printf("Glucosa: %f\n", maximos.maxGlucosa);

	printf("Minimos:\n");
	printf("Edad: %f\n", minimos.minEdad);
	printf("Hipertension: %f\n", minimos.minHipertension);
	printf("Enfermedad Cardiaca: %f\n", minimos.minEnfermedadCardiaca);
	printf("Imc: %f\n", minimos.minImc);
	printf("Hemoglobina: %f\n", minimos.minHemoglobina);
	printf("Glucosa: %f\n", minimos.minGlucosa);


	//Bucle para normalizar cada dato del dataset
	fgets(linea2, sizeof(linea2), Excel2);
	for(int i = 1; i < ndatos; i++){
		fgets(linea2, sizeof(linea2), Excel2);
		token = strtok(linea2, ",");
		if(token != NULL)
		{
			strncpy(ejemplo.sexo, token, sizeof(ejemplo.sexo));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.edad = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.hipertension = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.enfermedadCardiaca = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			strncpy(ejemplo.fuma, token, sizeof(ejemplo.fuma));
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.imc = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.hemoglobina = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.glucosa = atof(token);
			token = strtok(NULL, ",");
		}
		if(token != NULL)
		{
			ejemplo.diabetes = atof(token);
			token = strtok(NULL, ",");
		}

		ejemplo.edad = minMaxNormalizacion(ejemplo.edad, minimos.minEdad, maximos.maxEdad);
		ejemplo.hipertension = minMaxNormalizacion(ejemplo.hipertension, minimos.minHipertension, maximos.maxHipertension);
		ejemplo.enfermedadCardiaca = minMaxNormalizacion(ejemplo.enfermedadCardiaca, minimos.minEnfermedadCardiaca, maximos.maxEnfermedadCardiaca);
		ejemplo.imc = minMaxNormalizacion(ejemplo.imc, minimos.minImc, maximos.maxImc);
		ejemplo.hemoglobina = minMaxNormalizacion(ejemplo.hemoglobina, minimos.minHemoglobina, maximos.maxHemoglobina);
		ejemplo.glucosa = minMaxNormalizacion(ejemplo.glucosa, minimos.minGlucosa, maximos.maxGlucosa);
		//ajustarPrecision(&ejemplo);
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

				printf("Sexo: ");
				scanf("%s", k1.sexo);

				printf("Edad: ");
				scanf("%f", &k1.edad);

				printf("Hipertension: ");
				scanf("%f", &k1.hipertension);

				printf("Enfermedad Cardiaca: ");
				scanf("%f", &k1.enfermedadCardiaca);

				printf("Fuma: ");
				scanf("%s", k1.fuma);

				printf("Imc: ");
				scanf("%f", &k1.imc);

				printf("Hemoglobina: ");
				scanf("%f", &k1.hemoglobina);

				printf("Glucosa: ");
				scanf("%f", &k1.glucosa);

				printf("Diabetes: ");
				scanf("%f", &k1.diabetes);

				k1.edad = minMaxNormalizacion(k1.edad, minimos.minEdad, maximos.maxEdad);
				k1.hipertension = minMaxNormalizacion(k1.hipertension, minimos.minHipertension, maximos.maxHipertension);
				k1.enfermedadCardiaca = minMaxNormalizacion(k1.enfermedadCardiaca, minimos.minEnfermedadCardiaca, maximos.maxEnfermedadCardiaca);
				k1.imc = minMaxNormalizacion(k1.imc, minimos.minImc, maximos.maxImc);
				k1.hemoglobina = minMaxNormalizacion(k1.hemoglobina, minimos.minHemoglobina, maximos.maxHemoglobina);
				k1.glucosa = minMaxNormalizacion(k1.glucosa, minimos.minGlucosa, maximos.maxGlucosa);

				//ajustarPrecision(&k1);

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
				mejorDistancia = 1000000;

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
					masCercanok1.clase = ejemplo.diabetes;

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
				if(prediccion == k1.diabetes)
					exitosTotales += 1;

				printf(BG_BLUE"Ejemplo mas cercano = %d\n",masCercanok1.posicion);
				printf("Distancia Minima = %f\n", masCercanok1.distancia);
				printf("Prediccion de clase = %d\n"RESET,prediccion);
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
							masCercano.clase = vecino.diabetes;

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
					if(prediccion == ejemplo.diabetes)
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
							masCercano.clase = vecino.diabetes;

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
					if(prediccion == ejemplo.diabetes)
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
							masCercano.clase = vecino.diabetes;

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
					if(prediccion == ejemplo.diabetes){
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
							masCercanoWilson.clase = vecino.diabetes;

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
					if(prediccion == ejemplo.diabetes)
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
			case 6:
			{
				tipos = [1, 2, 3, 4, 5, 10, 20, 30, 40, 50];
				int casos = 0;
				for(int casos = 0; casos < 10; casos++){
					k = tipos[casos];
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
								masCercano.clase = vecino.diabetes;

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
						if(prediccion == ejemplo.diabetes)
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
				}
				break;
			}
		}
	}while(opcion<7);
	return 0;
}

void imprimeEjemplo(struct Linea k1) {
	printf("%s\n", k1.sexo);
	printf("%f\n", k1.edad);
	printf("%f\n", k1.hipertension);
	printf("%f\n", k1.enfermedadCardiaca);
	printf("%s\n", k1.fuma);
	printf("%f\n", k1.imc);
	printf("%f\n", k1.hemoglobina);
	printf("%f\n", k1.glucosa);
	printf("%f\n", k1.diabetes);
}

float minMaxNormalizacion(float valor, float min, float max)
{
	return (valor - min) / (max - min);
}

/*void ajustarPrecision(struct Linea *imp) {
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

	imp->hipertension *= importanciaMax;
	imp->enfermedadCardiaca *= importanciaMax;
	imp->imc *= importanciaBaja;
	imp->hemoglobina *= importanciaMedia;
	imp->glucosa *= importanciaMax;
	imp->diabetes *= importanciaMax;
}*/
