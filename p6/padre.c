#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrices.h"

int imprimir_matriz(float matriz[100]);
void crear_memoria();
void recibir_inversas();

int main(void) {
    srand(time(NULL));
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(NULL, "hijo.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Fallo al invocar CreateProcess (%d)\n", (int)GetLastError());
        return -1;
    }
    crear_memoria();
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

void crear_memoria() {
    HANDLE hArchMapeo;
    char *idMemCompartida = "MemoriaPadre";
    size_t TAM_MEM = sizeof(struct Contenedor);
    struct Contenedor *apDatos;
    if ((hArchMapeo=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, TAM_MEM, idMemCompartida))==NULL) {
        printf("No se mapeo la memoria compartida(padre): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(struct Contenedor*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se creo la memoria compartida(padre): %i\n", GetLastError());
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
    recibir_inversas();
    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
}

void recibir_inversas() {
    HANDLE hArchMapeo, hArchMapeo2;
    char *idMemCompartida = "HijoPadre";
    char *idMemCompartida2 = "NietoPadre";

    size_t TAM_MEM = 100*sizeof(int);
    int *apDatos, *apDatos2;
    /*Para la multiplicacion*/
    if ((hArchMapeo=OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, idMemCompartida))==NULL) {
        printf("No se abrio el archivo de mapeo de la memoria compartida(hijo_padre): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos=(int*)MapViewOfFile(hArchMapeo, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se accedio a la memoria compartida(hijo_padre): %i\n", GetLastError());
        CloseHandle(hArchMapeo);
        exit(-1);
    }
    /*Otro*/
    if ((hArchMapeo2=OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, idMemCompartida2))==NULL) {
        printf("No se abrio el archivo de mapeo de la memoria compartida(nieto_padre): %i\n", GetLastError());
        exit(-1);
    }

    if ((apDatos2=(int*)MapViewOfFile(hArchMapeo2, FILE_MAP_ALL_ACCESS, 0, 0, TAM_MEM))==NULL) {
        printf("No se accedio a la memoria compartida(nieto_padre): %i\n", GetLastError());
        CloseHandle(hArchMapeo);
        exit(-1);
    }

    float **inversa_suma = matriz();
    float **inversa_multiplicacion = matriz();
    int i, j, pos;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            inversa_suma[i][j] = (apDatos2)[pos];
            inversa_multiplicacion[i][j] = (apDatos)[pos];
        }
    printf("Realizando inversas...\n");
    gaussj(inversa_suma);
    gaussj(inversa_multiplicacion);
    int ficheroInv = abrir("inversa_suma.txt");
    escribir_texto(ficheroInv, "La inversa de la matriz suma es:");
    escribir_float(ficheroInv, inversa_suma);
    close(ficheroInv);
    ficheroInv = abrir("inversa_multiplicacion.txt");
    escribir_texto(ficheroInv, "La inversa de la matriz multiplicacion es:");
    escribir_float(ficheroInv, inversa_multiplicacion);
    close(ficheroInv);
    *apDatos =-90;
    *apDatos2 =-90;
    UnmapViewOfFile(apDatos);
    CloseHandle(hArchMapeo);
    UnmapViewOfFile(apDatos2);
    CloseHandle(hArchMapeo2);
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
