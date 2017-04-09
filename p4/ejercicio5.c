#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funciones5.h"

int main(int argc, char* argv[]) {
    int pid;
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

    pid = fork();
    if (pid == 0) {
        int i;
        for(i=0; i<5; i++){
            pid = fork();
            if(pid==0 && i==0){
                //printf("%s\n", "Suma");
                int ficheroSuma = abrir("suma.txt");
                sumar(matrizA, matrizB, matrizSuma);
                escribir(ficheroSuma, matrizSuma);
                close(ficheroSuma);
                exit(0);
            } else if (pid==0 && i==1){
                //printf("%s\n", "Resta");
                int ficheroResta = abrir("resta.txt");
                restar(matrizA, matrizB, matrizResta);
                escribir(ficheroResta, matrizResta);
                close(ficheroResta);
                exit(0);
            } else if (pid==0 && i==2){
                //printf("%s\n", "Multiplicacion");
                int ficheroMul = abrir("multiplicacion.txt");
                multiplicar(matrizA, matrizB, producto);
                escribir(ficheroMul, producto);
                close(ficheroMul);
                exit(0);
            } else if (pid==0 && i==3){
                //printf("%s\n", "Transpuesta");
                int ficheroTras = abrir("traspuesta.txt");
                trasponer(matrizA, traspuestaA);
                trasponer(matrizB, traspuestaB);
                escribir(ficheroTras, traspuestaA);
                escribir(ficheroTras, traspuestaB);
                close(ficheroTras);
                exit(0);
            } else if (pid==0 && i==4){
                //printf("%s\n", "Inversa");
                int ficheroInv = abrir("inversa.txt");
                inversaA = matriz();
                inversaB = matriz();
                copiar_matriz(inversaA, matrizA);
                copiar_matriz(inversaB, matrizB);
                gaussj(inversaA);
                escribirFloat(ficheroInv, inversaA);
                gaussj(inversaB);
                escribirFloat(ficheroInv, inversaA);
                escribirFloat(ficheroInv, inversaB);
                close(ficheroInv);
                exit(0);
            } else
                wait(NULL);
        }
        exit(0);
    } else {
        wait(NULL);
        printf("%s\n", "Salida");
        printf("%s\n", "Suma de matrices");
        imprimir("suma.txt");
        printf("%s\n", "Resta de matrices");
        imprimir("resta.txt");
        printf("%s\n", "Multiplicacion de matrices");
        imprimir("multiplicacion.txt");
        printf("%s\n", "Traspuesta de las dos matrices");
        imprimir("traspuesta.txt");
        printf("%s\n", "Iversa de matrices");
        imprimir("inversa.txt");
    }
    return 0;
}
