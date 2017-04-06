#include <stdio.h>
#include <stdlib.h>
#include "funciones5.h"

int main(int argc, char const* argv[]){
    int matrizSuma[col][col];
    int matrizResta[col][col];
    int producto[col][col];
    int traspuestaA[col][col];
    int traspuestaB[col][col];
    //int matrizInversa[col][col];
    int matrizA[col][col] = {
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
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 100}
    };
    int fichero;
    printf("Secuencial\n");

    sumar(matrizA, matrizB, matrizSuma);
    fichero = abrir("suma2.txt");
    escribir(fichero, matrizSuma);
    close(fichero);

    restar(matrizA, matrizB, matrizResta);
    fichero = abrir("resta2.txt");
    escribir(fichero, matrizResta);
    close(fichero);

    multiplicar(matrizA, matrizB, producto);
    fichero = abrir("multiplicacion2.txt");
    escribir(fichero, producto);
    close(fichero);

    trasponer(matrizA, traspuestaA);
    fichero = abrir("traspuesta2.txt");
    escribir(fichero, traspuestaA);
    trasponer(matrizB, traspuestaB);
    escribir(fichero, traspuestaB);
    close(fichero);
    // Lectura
    printf("%s\n", "Suma");
    imprimir("suma2.txt");
    printf("%s\n", "Resta");
    imprimir("resta2.txt");
    printf("%s\n", "Multiplicacion");
    imprimir("multiplicacion2.txt");
    printf("%s\n", "Traspuestas");
    imprimir("traspuesta2.txt");
    printf("%s\n", "Inversa");
    return 0;
}
