#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones5.h"

int main(int argc, char const* argv[]){
    clock_t t_ini, t_fin;
    double secs;
    t_ini = clock();
    int estado = 0;
    int matrizSuma[COL][COL];
    int matrizResta[COL][COL];
    int producto[COL][COL];
    int traspuestaA[COL][COL];
    int traspuestaB[COL][COL];
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
    int fichero;
    printf("Secuencial\n");
    float **inversaA;
    float **inversaB;
    printf("--La matriz A es:\n");
    mostrar_matriz(matrizA);
    printf("\n");
    printf("--La matriz B es:\n");
    mostrar_matriz(matrizB);
    printf("\n");

    printf("%s\n", "Realizando Suma...");
    fichero = abrir("suma2.txt");
    sumar(matrizA, matrizB, matrizSuma);
    escribir_matriz(ficheroSuma, matrizSuma);
    close(fichero);

    printf("%s\n", "Realizando Resta...");
    fichero = abrir("resta2.txt");
    restar(matrizA, matrizB, matrizResta);
    escribir_matriz(fichero, matrizResta);
    close(fichero);

    printf("%s\n", "Realizando Multiplicacion...");
    fichero = abrir("multiplicacion.txt");
    multiplicar(matrizA, matrizB, producto);
    escribir_matriz(fichero, producto);
    close(fichero);

    printf("%s\n", "Realizando Transpuesta...");
    fichero = abrir("traspuesta2.txt");
    trasponer(matrizA, traspuestaA);
    trasponer(matrizB, traspuestaB);
    escribir_texto(fichero, "La matriz traspuesta de A es:");
    escribir_matriz(fichero, traspuestaA);
    escribir_texto(fichero, "La matriz traspuesta de B es:");
    escribir_matriz(fichero, traspuestaB);
    close(fichero);

    printf("%s\n", "Realizando Inversa...");
    int fichero = abrir("inversa2.txt");
    inversaA = matriz();
    inversaB = matriz();
    copiar_matriz(inversaA, matrizA);
    copiar_matriz(inversaB, matrizB);
    estado = gaussj(inversaA);
    if (estado != -1){
        escribir_texto(fichero, "La inversa de la matriz A es:");
        escribir_float(fichero, inversaA);
    } else
        escribir_texto(fichero, "La matriz A es no invertible");
    estado = gaussj(inversaB);
    if (estado != -1){
        escribir_texto(fichero, "La inversa de la matriz B es");
        escribir_float(fichero, inversaB);
    } else
        escribir_texto(fichero, "La matriz B es no invertible");
    close(fichero);
    // Lectura
    printf("\n%s\n", "Leyendo los archivos...");
    printf("\n%s\n", "--Suma de las dos matrices");
    imprimir("suma2.txt");
    printf("\n%s\n", "--Resta de las dos matrices");
    imprimir("resta2.txt");
    printf("\n%s\n", "--Multiplicacion de las dosmatrices");
    imprimir("multiplicacion2.txt");
    printf("\n%s\n", "--Traspuesta de las dos matrices");
    imprimir("traspuesta2.txt");
    printf("\n%s\n", "--Iversa de las dos matrices");
    imprimir("inversa2.txt");
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    printf("%.16g milisegundos\n", secs * 1000.0);
    return 0;
}
