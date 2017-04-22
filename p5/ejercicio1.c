#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funciones.h"

void *suma(void *arg);
void *resta(void *arg);
void *multiplicacion(void *arg);
void *transpuesta(void *arg);
void *inversa(void *argv);

int main(int argc, char const* argv[]) {
    int numero_hilos = 5;
    int prueba[2] = {90, 777};
    pthread_t *hilos = malloc(numero_hilos * sizeof(pthread_t));
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
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 7, 0, 0, 8, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 5, 0, 0, 0},
        {0, 5, 0, 0, 2, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 5, 0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 4, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    };
    printf("--La matriz A es:\n");
    mostrar_matriz(matrizA);
    printf("\n");
    printf("--La matriz B es:\n");
    mostrar_matriz(matrizB);
    printf("\n");
    printf("Ejecutando los hilos...\n");
    pthread_create(&hilos[0], NULL, suma, prueba);
    pthread_create(&hilos[1], NULL, resta, prueba);
    pthread_create(&hilos[2], NULL, multiplicacion, prueba);
    pthread_create(&hilos[3], NULL, transpuesta, prueba);
    pthread_create(&hilos[4], NULL, inversa, prueba);
    int i;
    for (i=0; i<numero_hilos; i++)
        pthread_join(hilos[i], NULL);

    printf("\n%s\n", "Leyendo los archivos...");
    printf("\n%s\n", "--Suma de las dos matrices");
    imprimir("suma.txt");
    printf("\n%s\n", "--Resta de las dosmatrices");
    imprimir("resta.txt");
    printf("\n%s\n", "--Multiplicacion de las dos matrices");
    imprimir("multiplicacion.txt");
    printf("\n%s\n", "--Traspuesta de las dos matrices");
    imprimir("traspuesta.txt");
    printf("\n%s\n", "--Inversa de las dos matrices");
    imprimir("inversa.txt");
    free(hilos);
    return 0;
}

void *suma(void *arg) {
    int matrizSuma[COL][COL];
    printf("Realizando suma de matrices...\n");
    int ficheroSuma = abrir("suma.txt");
    sumar(matrizA, matrizB, matrizSuma);
    escribir_matriz(ficheroSuma, matrizSuma);
    close(ficheroSuma);
    return NULL;
}
void *resta(void *arg) {
    int matrizResta[COL][COL];
    printf("Realizando resta de matrices...\n");
    int ficheroResta = abrir("resta.txt");
    restar(matrizA, matrizB, matrizResta);
    escribir_matriz(ficheroResta, matrizResta);
    close(ficheroResta);
    return NULL;
}
void *multiplicacion(void *arg) {
    int producto[COL][COL];
    printf("Realizando multiplicacion de matrices...\n");
    int ficheroMul = abrir("multiplicacion.txt");
    multiplicar(matrizA, matrizB, producto);
    escribir_matriz(ficheroMul, producto);
    close(ficheroMul);
    return NULL;
}
void *transpuesta(void *arg) {
    int traspuestaA[COL][COL];
    int traspuestaB[COL][COL];printf("Realizando transpuesta de matrices...\n");
    int ficheroTras = abrir("traspuesta.txt");
    trasponer(matrizA, traspuestaA);
    trasponer(matrizB, traspuestaB);
    escribir_texto(ficheroTras, "La matriz traspuesta de A es:");
    escribir_matriz(ficheroTras, traspuestaA);
    escribir_texto(ficheroTras, "La matriz traspuesta de B es:");
    escribir_matriz(ficheroTras, traspuestaB);
    close(ficheroTras);
    return NULL;
}
void *inversa(void *arg) {
    float **inversaA;
    float **inversaB;
    printf("Realizando inversa de matrices...\n");
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
    return NULL;
}
