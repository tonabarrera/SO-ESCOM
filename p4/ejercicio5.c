#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define col 10

int suma(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]) {
    int i, j;
    for (i = 0; i < col; i++) {
        for (j = 0; j < col; j++)
            resultado[i][j] = matrizA[i][j] + matrizB[i][j];
    }
    return 0;
}

int resta(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]) {
    int i, j;
    for (i = 0; i < col; i++) {
        for (j = 0; j < col; j++)
            resultado[i][j] = matrizA[i][j] - matrizB[i][j];
    }
    return 0;
}

int trasponer(int matriz[col][col], int traspuesta[col][col]) {
    int i, j;
    for(i=0;i<col; i++){
        for(j=0; j<col; j++)
            traspuesta[j][i] = matriz[i][j];
    }
    return 0;
}
//Tal vez sea mejor si uso recursion
int multiplicar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]){
    int i, j, k;
    int valor = 0;
    for(i=0; i<col; i++){
        for(j=0; j<col; j++){
            valor = 0;
            for(k=0; k<col; k++){
                valor+= matrizA[i][k]*matrizB[k][j];
            }
            resultado[i][j] = valor;
        }
    }
    return 0;
}

int main(int argc, char* argv[]){
    int matrizSuma[col][col];
    int matrizResta[col][col];
    int producto[col][col];
    int traspuesta[col][col];/*
    int matrizInversa[col][col];*/
    int matrizA[col][col] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 75, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    int matrizB[col][col] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    };
    suma(matrizA, matrizB, matrizSuma);
    resta(matrizA, matrizB, matrizResta);
    trasponer(matrizA, traspuesta);
    multiplicar(matrizA, matrizB, producto);
    printf("Valor %d\n", matrizSuma[9][9]);
    printf("Valor %d\n", matrizResta[3][5]);
    printf("Valor %d\n", traspuesta[4][2]);
    printf("Producto %d\n", producto[0][0]);
    return 0;
}

