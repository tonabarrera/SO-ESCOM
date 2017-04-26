#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrices.h"

void *suma(void *arg);
void *resta(void *arg);
void *multiplicacion(void *arg);
void *transpuesta(void *arg);
void *inversa(void *argv);

int main(int argc, char const* argv[]) {
    int numero_hilos = 5;
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
    float ***contenedor = malloc(2*sizeof(float***));
    float **pruebaA = matriz();
    float **pruebaB = matriz();
    copiar_matriz(pruebaA, matrizA);
    copiar_matriz(pruebaB, matrizB);
    *contenedor = pruebaA;
    *(contenedor+1)= pruebaB;
    printf("--La matriz A es:\n");
    mostrar_matriz(matrizA);
    printf("\n");
    printf("--La matriz B es:\n");
    mostrar_matriz(matrizB);
    printf("\n");
    printf("Ejecutando los hilos...\n");
    pthread_create(&hilos[0], NULL, suma, (void*)contenedor);
    pthread_create(&hilos[1], NULL, resta, (void*)contenedor);
    pthread_create(&hilos[2], NULL, multiplicacion, (void*)contenedor);
    pthread_create(&hilos[3], NULL, transpuesta, (void*)contenedor);
    pthread_create(&hilos[4], NULL, inversa, (void*)contenedor);
    int i;
    for (i=0; i < numero_hilos; i++)
        pthread_join(hilos[i], NULL);

    printf("\n%s\n", "Leyendo los archivos...");
    printf("\n%s\n", "--Suma de las dos matrices");
    imprimir("suma.txt");
    printf("\n%s\n", "--Resta de las dos matrices");
    imprimir("resta.txt");
    printf("\n%s\n", "--Multiplicacion de las dos matrices");
    imprimir("multiplicacion.txt");
    printf("\n%s\n", "--Traspuesta de las dos matrices");
    imprimir("traspuesta.txt");
    printf("\n%s\n", "--Inversa de las dos matrices");
    imprimir("inversa.txt");
    free(hilos);
    free(pruebaB);
    free(pruebaA);
    free(contenedor);
    return 0;
}

void *suma(void *arg) {
    float ***contenedor = (float***) arg;
    int matrizSuma[COL][COL];
    printf("Realizando suma de matrices...\n");
    int ficheroSuma = abrir("suma.txt");
    sumar(contenedor[0], contenedor[1], matrizSuma);
    escribir_matriz(ficheroSuma, matrizSuma);
    close(ficheroSuma);
    free(contenedor);
    return NULL;
}

void *resta(void *arg) {
    int matrizResta[COL][COL];
    float ***contenedor = (float***)arg;
    printf("Realizando resta de matrices...\n");
    int ficheroResta = abrir("resta.txt");
    restar(contenedor[0], contenedor[1], matrizResta);
    escribir_matriz(ficheroResta, matrizResta);
    close(ficheroResta);
    free(contenedor);
    return NULL;
}
void *multiplicacion(void *arg) {
    int producto[COL][COL];
    float ***contenedor = (float***)arg;
    printf("Realizando multiplicacion de matrices...\n");
    int ficheroMul = abrir("multiplicacion.txt");
    multiplicar(contenedor[0], contenedor[1], producto);
    escribir_matriz(ficheroMul, producto);
    close(ficheroMul);
    free(contenedor);
    return NULL;
}
void *transpuesta(void *arg) {
    int traspuestaA[COL][COL];
    int traspuestaB[COL][COL];
    float ***contenedor = (float***)arg;
    printf("Realizando transpuesta de matrices...\n");
    int ficheroTras = abrir("traspuesta.txt");
    trasponer(contenedor[0], traspuestaA);
    trasponer(contenedor[1], traspuestaB);
    escribir_texto(ficheroTras, "La matriz traspuesta de A es:");
    escribir_matriz(ficheroTras, traspuestaA);
    escribir_texto(ficheroTras, "La matriz traspuesta de B es:");
    escribir_matriz(ficheroTras, traspuestaB);
    close(ficheroTras);
    free(contenedor);
    return NULL;
}
void *inversa(void *arg) {
    float ***contenedor = (float ***)arg;
    float **inversaA = matriz();
    float **inversaB = matriz();
    fcopiar_matriz(inversaA, contenedor[0]);
    fcopiar_matriz(inversaB, contenedor[1]);

    printf("Realizando inversa de matrices...\n");
    int ficheroInv = abrir("inversa.txt");
    int estado = 0;
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
    free(contenedor);
    free(inversaA);
    free(inversaB);
    return NULL;
}
