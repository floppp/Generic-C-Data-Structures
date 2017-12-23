/**
	@file libaleatorios.c
	@brief funciones sacadas de los ejercicios y listados

	Modulo con funciones necesarias para calculo de numeros aleatorios del
	trabajo sobre Metodo de Monte-Carlo de asignatura Fisica
	Computacional I

	@author Fernando Lopez Laso
	@date 05/12/14
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/libaleatorios.h"

/* El entero mas largo que se pueda: 64 bits en sistemas de 32 */
static long long semilla_normal = SEMILLA;
static long long semilla_uniforme = SEMILLA;

/**
	@brief Calculo de numeros aleatorios con distribicion uniforme

	Cálculo de números pseudoaleatorios mediante el método de la congruencia
	lineal.

	@returns - Pasamos punteros, luego no devolvemos nada
*/
double uniforme()
{
	semilla_uniforme = (LINEAL_A*semilla_uniforme + LINEAL_B) % CONGRUENCIA;

	return (double) semilla_uniforme / CONGRUENCIA;
}

/**
	@brief Calculo de aleatorios con distribucion normal

	Funcion que devuelve numeros pseudo-aleatorios con distribucion
	normal alrededor del 0 a partir de una seride de valores con
	distribucion normal, con media en 0 y varianza 1.

	@return valor pseudo-aleatorio con probabilidad de distribucion
			normal
*/
double normal()
{
	double f, s;

	s = 0.0;
	for (int n = 0; n < N_UNIFORMES; n++) {
		semilla_normal = (LINEAL_A*semilla_normal + LINEAL_B) % CONGRUENCIA;
		f = (double) semilla_normal / CONGRUENCIA;
		s += f;
	}

	return (s - 0.5*N_UNIFORMES) / sqrt((1.0/1.2) * N_UNIFORMES);
}

/**
	@brief Calculamos frecuencia de cada rango

	Procedimiento que calcula la frecuencia con que aparecen los
	valores de cada rango

	@param n_pts  numero de puntos totales
	@param *x     vector con valores de los numeros aleatorios
	@param n_hist numero total de rangos en que dividimos el histograma
	@param histo  vector en el que almacenamos las frecuencias
	@param x_min  valor minimo del que queremos calcular la frecuencia
	@param x_max  valor maximo del que queremos calcular la frecuencia

*/
void histograma(int n_pts, double* x, int n_hist, int* histo, double x_min, double x_max)
{
	int i;
	for (i = 0; i < n_hist; i++)
		histo[i] = 0;

	for (int n = 0; n < n_pts; n++)	{
		/* Calculamos en que rango esta cada valor */
		i = (int) floor((n_hist * (x[n] - x_min)) / (x_max - x_min));
		if (0 <= i && i < N_HISTOGRAMA)
			histo[i]++;
	}

	return ;
}

/**
	@brief Funcion para generar numeros

	Funcion que genera un numero de puntos (dato fijo del programa
	en el que usemos la funcion) a partir de una funcion dada

	@param arch puntero a archivo en el que grabar
	@param f    funcion a partir de la que generar los puntos
*/
void generarNumeros(char* arch, double (*f)(), int n_pts_max)
{
	int i, n_pts;
	FILE *fout;

	fout = fopen(arch, "w");
	n_pts = 0;
	for (i = 0; i < n_pts_max; i++)
		fprintf(fout, "%f\n", f());

	fclose(fout);

	return ;
}

/**
	@brief Lectura de numeros desde archivos

	Funcion que lee numeros desde archivo (un numero en cada fila)
	y devuelve el numero de puntos leidos

	@param arch puntero a archivo que queremos leer
	@param x    vector (puntero) donde almacenar puntos leidos
*/
int leeNumeros(char* arch, double* x, int n_pts_max)
{
	int n, n_pts;
	double xa;

	FILE *fin;

	fin = fopen(arch, "r");

	n_pts = 0;
	do {
		n = fscanf(fin, "%lf", &xa);
		if (n == 1 && n_pts_max)
			x[n_pts] = xa;
		n_pts++;
	} while (n == 1 && n_pts <= n_pts_max);

	fclose(fin);

	/* error */
	if (n_pts == n_pts_max + 1 && n == 1)
		n_pts = -1;

	return n_pts;
}
