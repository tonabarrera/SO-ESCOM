#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"

int imprimir_matriz(float matriz[100]);
void nieto_padre(int matrizSuma[10][10], struct Contenedor *);

int main(void) {
    HANDLE hArchMapeo;
    char *idMemCompartida = "HijoNieto";
    size_t TAM_MEM = sizeof(struct Contenedor);
    struct Contenedor *apDatos;
    if ((hArchMapeo=OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, idMemCompartida))==NULL) {
        printf("No se abrio el archivo de mapeo de la memoria compartida(nieto): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(struct Contenedor*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se accedio a la memoria compartida(nieto): %i\n", GetLastError());
        CloseHandle(hArchMapeo);
        exit(-1);
    }
    float **matrizA = matriz();
    float **matrizB = matriz();
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            matrizA[i][j] = (apDatos->matrizUno)[pos];
            matrizB[i][j] = (apDatos->matrizDos)[pos];
        }
    int matrizSuma[COL][COL];
    printf("Matriz Uno para la suma:\n");
    imprimir_matriz(apDatos->matrizUno);
    printf("Matriz Dos para la suma:\n");
    imprimir_matriz(apDatos->matrizDos);
    sumar(matrizA, matrizB, matrizSuma);
    printf("La matriz suma es:\n");
    mostrar_matriz(matrizSuma);
    nieto_padre(matrizSuma, apDatos);
    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
    exit(0);
    return 0;
}

void nieto_padre(int matrizSuma[10][10], struct Contenedor *anterior) {
    HANDLE hArchMapeo;
    char *idMemCompartida = "NietoPadre";
    size_t TAM_MEM = 100*sizeof(int);
    int *apDatos;
    if ((hArchMapeo=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, idMemCompartida))==NULL) {
        printf("No se mapeo la memoria compartida(nieto_padre): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(int*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se creo la memoria compartida(nieto_padre): %i\n", GetLastError());
        CloseHandle(hArchMapeo);
        exit(-1);
    }
    anterior->estado = 1;
    int i, j, pos;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++)
            apDatos[pos] = matrizSuma[i][j];
    while(*apDatos !=-90)
        sleep(1);

    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
}

int imprimir_matriz(float matriz[100]) {
    int i;
    printf("[");
    for (i=0; i<100; i++){
        if (i%10 == 0)
            printf("\n");
        printf("%.0f ", matriz[i]);
    }
    printf("\n]\n");
    return 0;
}
