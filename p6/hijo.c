#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"

void crear_memoria();
int imprimir_matriz(float matriz[100]);
void hijo_padre(int matrizProducto[COL][COL], struct Contenedor*);
void hijo_nieto();

int main(void) {
    srand(time(NULL));
    crear_memoria();
    exit(0);
    return 0;
}

void crear_memoria() {
    HANDLE hArchMapeo;
    char *idMemCompartida = "MemoriaPadre";
    size_t TAM_MEM = sizeof(struct Contenedor);
    struct Contenedor *apDatos;
    if ((hArchMapeo=OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, idMemCompartida))==NULL) {
        printf("No se abrio el archivo de mapeo de la memoria compartida(hijo): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(struct Contenedor*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se accedio a la memoria compartida(hijo): %i\n", GetLastError());
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
    int matrizProducto[COL][COL];
    printf("Matriz Uno para la multiplicacion:\n");
    imprimir_matriz(apDatos->matrizUno);
    printf("Matriz Dos para la multiplicacion:\n");
    imprimir_matriz(apDatos->matrizDos);
    multiplicar(matrizA, matrizB, matrizProducto);
    printf("La matriz multiplicacion es:\n");
    mostrar_matriz(matrizProducto);
    hijo_padre(matrizProducto, apDatos);
    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
    return;
}

void hijo_padre(int matrizProducto[COL][COL], struct Contenedor *anterior) {
    HANDLE hArchMapeo;
    char *idMemCompartida = "HijoPadre";
    size_t TAM_MEM = 100*sizeof(int);
    int *apDatos;
    if ((hArchMapeo=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, idMemCompartida))==NULL) {
        printf("No se mapeo la memoria compartida(hijo_padre): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(int*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se creo la memoria compartida(hijo_padre): %i\n", GetLastError());
        CloseHandle(hArchMapeo);
        exit(-1);
    }
    int i, j, pos;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++)
            apDatos[pos] = matrizProducto[i][j];
    hijo_nieto();
    anterior->estado = 1;
    while(*apDatos !=-90)
        sleep(1);
    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
    return;
}

void hijo_nieto(){
    /*Crear*/
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(NULL, "nieto.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess (%d)\n", (int)GetLastError());
        return -1;
    }
    /*Termina*/
    HANDLE hArchMapeo;
    char *idMemCompartida = "HijoNieto";
    size_t TAM_MEM = sizeof(struct Contenedor);
    struct Contenedor *apDatos;
    if ((hArchMapeo=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, idMemCompartida))==NULL) {
        printf("No se mapeo la memoria compartida(hijo_nieto): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(struct Contenedor*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se creo la memoria compartida(hijo_nieto): %i\n", GetLastError());
        CloseHandle(hArchMapeo);
        exit(-1);
    }
    apDatos->estado = 0;
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            (apDatos->matrizUno)[pos] = rand()%11;
            (apDatos->matrizDos)[pos] = rand()%11;
        }
    while(!apDatos->estado)
        sleep(1);

    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return;
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
