#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones5.h"

int main(int argc, char const* argv[])
{
    char msj[100];
    int matrizA[COL][COL] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 1},
        {1, 3, 5, 6, 7, -1, 7, 8, 9, 10},
        {-1, 2, 3, 4, 5, 0, 7, 8, 9, 1},
        {0, -2, -3, -9, 0, 2, -4, 1, 6, 3},
        {1, 4, 3, 0, 5, 6, 5, 5, 9, 10},
        {1, 0, 6, 4, -5, 4, 7, 8, 9, 1},
        {11, -2, 7, 4, 15, 6, 3, 3, 0, 1},
        {10, 2, 8, 4, 0, 1, -7, 8, 1, 10},
        {3, -2, -3, 4, 0, 6, 7, -8, 9, 10},
        {2, 2, 3, -4, 9, 6, 7, 8, 9, 10}
    };
    int matrizB[COL][COL] = {
        {1, 2, 3, 4, 5, 0, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, -6, 7, 8, 9, 10},
        {1, -2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 0, 9, 10},
        {1, -2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 0, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, -3, 4, 5, 6, 7, 8, 9, 1}
    };
    float **inversaA;
    float **inversaB;
    strcpy(msj, "Realizando inversa - ");
    strcat(msj, argv[1]);
    printf("%s\n", msj);
    int ficheroInv = abrir("inversa.txt");
    int estado = 0;
    inversaA = matriz();
    inversaB = matriz();
    copiar_matriz(inversaA, matrizA);
    copiar_matriz(inversaB, matrizB);
    estado = gaussj(inversaA);
    if (estado != -1){
        escribir_texto(ficheroInv, "La inversa de la matriz A es:");
        escribir_float(ficheroInv, inversaA);
    } else
        escribir_texto(ficheroInv, "La matriz A es no invertible");
    estado = gaussj(inversaB);
    if (estado != -1){
        escribir_texto(ficheroInv, "La inversa de la matriz B es");
        escribir_float(ficheroInv, inversaB);
    } else
        escribir_texto(ficheroInv, "La matriz B es no invertible");
    close(ficheroInv);
    exit(0);
    return 0;
}
