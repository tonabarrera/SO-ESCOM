#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#define COL 10 // Columnas y filas de la matriz
struct Contenedor {
	float *array;
	int estado;
};
int sumar(float **, float **, int resultado[COL][COL]);
int restar(float **, float **, int resultado[COL][COL]);
int trasponer(float **, int traspuesta[COL][COL]);
int multiplicar(float **, float **, int resultado[COL][COL]);
int abrir(char *);
int escribir_texto(int, char *);
int escribir_matriz(int, int matriz[COL][COL]);
int escribir_float(int, float **);
float **matriz(); // Crea la matriz
int imprimir(char *);
int gaussj(float **); // Realiza la inversa usando gauss jordan
int copiar_matriz(float **, int matriz[COL][COL]); // A nuestra matriz le pasamos valores de un arreglo
int fcopiar_matriz(float **, float**);
int mostrar_matriz(int matriz[COL][COL]);

#endif
