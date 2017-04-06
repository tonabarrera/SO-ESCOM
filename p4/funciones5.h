#ifndef __FUNCIONES_5_H__
#define __FUNCIONES_5_H__

#include <stdio.h>
#include <stdlib.h>
#define col 10

int sumar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]);
int restar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]);
int trasponer(int matriz[col][col], int traspuesta[col][col]);
int multiplicar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]);
int abrir(char *);
int escribir(int, int matriz[col][col]);
int imprimir(char *);

#endif
