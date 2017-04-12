#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funciones5.h"

int main(int argc, char* argv[]) {
    pid_t pid;
    int i, I;
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
    float **inversaA;
    float **inversaB;
    printf("--La matriz A es:\n");
    mostrar_matriz(matrizA);
    printf("\n");
    printf("--La matriz B es:\n");
    mostrar_matriz(matrizB);
    printf("\n");
    pid = fork();
    if (pid == 0) {
        for(i=0; i<5; i++){
            pid = fork();
            if(pid==0 && i==0){
                printf("%s\n", "Realizando Suma...");
                int ficheroSuma = abrir("suma.txt");
                sumar(matrizA, matrizB, matrizSuma);
                escribir_matriz(ficheroSuma, matrizSuma);
                close(ficheroSuma);
                exit(0);
            } else if (pid==0 && i==1){
                printf("%s\n", "Realizando Resta...");
                int ficheroResta = abrir("resta.txt");
                restar(matrizA, matrizB, matrizResta);
                escribir_matriz(ficheroResta, matrizResta);
                close(ficheroResta);
                exit(0);
            } else if (pid==0 && i==2){
                printf("%s\n", "Realizando Multiplicacion...");
                int ficheroMul = abrir("multiplicacion.txt");
                multiplicar(matrizA, matrizB, producto);
                escribir_matriz(ficheroMul, producto);
                close(ficheroMul);
                exit(0);
            } else if (pid==0 && i==3){
                printf("%s\n", "Realizando Transpuesta...");
                int ficheroTras = abrir("traspuesta.txt");
                trasponer(matrizA, traspuestaA);
                trasponer(matrizB, traspuestaB);
                escribir_texto(ficheroTras, "La matriz traspuesta de A es:");
                escribir_matriz(ficheroTras, traspuestaA);
                escribir_texto(ficheroTras, "La matriz traspuesta de B es:");
                escribir_matriz(ficheroTras, traspuestaB);
                close(ficheroTras);
                exit(0);
            } else if (pid==0 && i==4){
                printf("%s\n", "Realizando Inversa...");
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
            }
        }
        for (I = 0; I < 5; I++)
            wait(NULL);
        exit(0);
    } else {
        wait(NULL);
        printf("\n%s\n", "Leyendo los archivos...");
        printf("\n%s\n", "--Suma de las dos matrices");
        imprimir("suma.txt");
        printf("\n%s\n", "--Resta de las dosmatrices");
        imprimir("resta.txt");
        printf("\n%s\n", "--Multiplicacion de las dosmatrices");
        imprimir("multiplicacion.txt");
        printf("\n%s\n", "--Traspuesta de las dos matrices");
        imprimir("traspuesta.txt");
        printf("\n%s\n", "--Iversa de las dos matrices");
        imprimir("inversa.txt");
    }
    return 0;
}
