#ifndef __FUNCIONES_5_H__
#define __FUNCIONES_5_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define COL 10

int sumar(int matrizA[COL][COL], int matrizB[COL][COL], int resultado[COL][COL]);
int restar(int matrizA[COL][COL], int matrizB[COL][COL], int resultado[COL][COL]);
int trasponer(int matriz[COL][COL], int traspuesta[COL][COL]);
int multiplicar(int matrizA[COL][COL], int matrizB[COL][COL], int resultado[COL][COL]);
int abrir(char *);
int escribir(int, int matriz[COL][COL]);
int imprimir(char *);
int invertir(int matriz[COL][COL], double inversa[COL][COL]);

#endif
