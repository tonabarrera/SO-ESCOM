#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones5.h"

int main(int argc, char const* argv[])
{
    char msj[100];
    int producto[COL][COL];
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
    strcpy(msj, "Realizando Multiplicacion - ");
    strcat(msj, argv[1]);
    printf("%s\n", msj);
    int ficheroMul = abrir("multiplicacion.txt");
    multiplicar(matrizA, matrizB, producto);
    escribir_matriz(ficheroMul, producto);
    close(ficheroMul);
    exit(0);
    return 0;
}
