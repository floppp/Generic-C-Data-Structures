#ifndef _LIBALEATORIOS_H_
#define _LIBALEATORIOS_H_

/* Defino aqui los valores de las constantes para no dejar al usuario
   de la libreria esa responsabilidad */

/* POSIBLE BUENAS DEFINICIONES DE GENERADORES DE NÚMEROS PSEUDOALEATORIOS
   POR CONGRUENCIAS LINEALES (está en el los apuntes)

período 509-------------            período 32749-------------
#define SEMILLA     123L            #define SEMILLA     12345L
#define LINEAL_A    65L             #define LINEAL_A    1944L
#define LINEAL_B    0L              #define LINEAL_B    0L
#define CONGRUENCIA 509L            #define CONGRUENCIA 32749L

período 2174483647------            período 4294967296-------------
#define SEMILLA       12345678L     #define SEMILLA    1234567891LL
#define LINEAL_A         16807L     #define LINEAL_A      1664525LL
#define LINEAL_B             0L     #define LINEAL_B   1013904223LL
#define CONGRUENCIA 2147482647L     #define CONGRUENCIA 424927296LL
*/

/* LA DEFINICION DE LOS PARAMETROS TAMBIEN COMPENSA REALIZARLA AQUI
   EN VEZ DE PASARLA A LA FUNCION DESDE DONDE LA LLAMAMOS */
/* Usamos período 4294967296 */
#define SEMILLA    1234567891LL
#define LINEAL_A      1664525LL
#define LINEAL_B   1013904223LL
#define CONGRUENCIA 424927296LL

/* Definimos el numero de variables U(0, 1)
   para construir la variable gaussiana */
#define N_UNIFORMES 100
#define N_HISTOGRAMA 1000
// #define N_MAX_PTS 1000000
// Si uso constantes en vez de #define me da error el compilador
// por multiples definiciones
// const int N_MAX_PTS = 100000;

double uniforme();
double normal();
void histograma(int, double*, int, int*, double, double);
void generarNumeros(char* arch, double (*f)(), int);
int leeNumeros(char* arch, double* x, int);

#endif
