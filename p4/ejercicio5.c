#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funciones5.h"

int main(int argc, char* argv[]){
    int pid;
    int matrizSuma[COL][COL];
    int matrizResta[COL][COL];
    int producto[COL][COL];
    int traspuestaA[COL][COL];
    int traspuestaB[COL][COL];
    //int matrizInversa[COL][COL];
    int matrizA[COL][COL] = {
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
    int matrizB[COL][COL] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 100}
    };
    pid = fork();
    if (pid == 0) {
        int i;
        for(i=0; i<4; i++){
            pid = fork();
            if(pid==0 && i==0){
                printf("%s\n", "Suma");
                sumar(matrizA, matrizB, matrizSuma);
                int ficheroSuma = abrir("suma.txt");
                escribir(ficheroSuma, matrizSuma);
                close(ficheroSuma);
                exit(0);
            } else if (pid==0 && i==1){
                printf("%s\n", "Resta");
                restar(matrizA, matrizB, matrizResta);
                int ficheroResta = abrir("resta.txt");
                escribir(ficheroResta, matrizResta);
                close(ficheroResta);
                exit(0);
            } else if (pid==0 && i==2){
                printf("%s\n", "Multiplicacion");
                multiplicar(matrizA, matrizB, producto);
                int ficheroMul = abrir("multiplicacion.txt");
                escribir(ficheroMul, producto);
                close(ficheroMul);
                exit(0);
            } else if (pid==0 && i==3){
                printf("%s\n", "Transpuesta");
                trasponer(matrizA, traspuestaA);
                trasponer(matrizB, traspuestaB);
                int ficheroTras = abrir("traspuesta.txt");
                escribir(ficheroTras, traspuestaA);
                escribir(ficheroTras, traspuestaB);
                close(ficheroTras);
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
    }
    return 0;
}
