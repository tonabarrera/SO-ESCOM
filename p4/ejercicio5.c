#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#define col 10

int sumar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]) {
    int i, j;
    for (i = 0; i < col; i++) {
        for (j = 0; j < col; j++)
            resultado[i][j] = matrizA[i][j] + matrizB[i][j];
    }
    return 0;
}

int restar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]) {
    int i, j;
    for (i = 0; i < col; i++)
        for (j = 0; j < col; j++){
            resultado[i][j] = matrizA[i][j] - matrizB[i][j];
    }
    return 0;
}

int trasponer(int matriz[col][col], int traspuesta[col][col]) {
    int i, j;
    for(i=0;i<col; i++){
        for(j=0; j<col; j++)
            traspuesta[j][i] = matriz[i][j];
    }
    return 0;
}
//Tal vez sea mejor si uso recursion
int multiplicar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]){
    int i, j, k;
    int valor = 0;
    for(i=0; i<col; i++){
        for(j=0; j<col; j++){
            valor = 0;
            for(k=0; k<col; k++){
                valor+= matrizA[i][k]*matrizB[k][j];
            }
            resultado[i][j] = valor;
        }
    }
    return 0;
}

int escribir(int fichero, int matriz[col][col]) {
    int m, n;
    char caracter[5];
    write(fichero, "[\n", 2);
    for (m=0; m<col; m++){
        for(n=0; n<col; n++){
            sprintf(caracter, "%d", matriz[m][n]);
            write(fichero, caracter, strlen(caracter));
            write(fichero, " ", 1);
        }
        write(fichero, "\n", 1);
    }
    write(fichero, "]\n", 2);
    return 0;
}

int imprimir(char *archivo){
    int fichero = 0;
    char cadena[2000];
    fichero = open(archivo, O_RDONLY);
    read(fichero, cadena, 2000);
    printf("%s", cadena);
    close(fichero);
    return 0;
}

int main(int argc, char* argv[]){
    int pid;
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
    pid = fork();
    if (pid == 0) {
        int i;
        for(i=0; i<4; i++){
            pid = fork();
            if(pid==0 && i==0){
                printf("%s\n", "Suma");
                sumar(matrizA, matrizB, matrizSuma);
                int ficheroSuma = open("suma.txt", O_WRONLY|O_CREAT, 0640);
                escribir(ficheroSuma, matrizSuma);
                close(ficheroSuma);
                exit(0);
            } else if (pid==0 && i==1){
                printf("%s\n", "Resta");
                restar(matrizA, matrizB, matrizResta);
                int ficheroResta = open("resta.txt", O_WRONLY|O_CREAT, 0640);
                escribir(ficheroResta, matrizResta);
                close(ficheroResta);
                exit(0);
            } else if (pid==0 && i==2){
                printf("%s\n", "Multiplicacion");
                multiplicar(matrizA, matrizB, producto);
                int ficheroMul = open("multiplicacion.txt", O_WRONLY|O_CREAT, 0640);
                escribir(ficheroMul, producto);
                close(ficheroMul);
                exit(0);
            } else if (pid==0 && i==3){
                printf("%s\n", "Transpuesta");
                trasponer(matrizA, traspuestaA);
                trasponer(matrizB, traspuestaB);
                int ficheroTras = open("traspuesta.txt", O_WRONLY|O_CREAT, 0640);
                escribir(ficheroTras, traspuestaA);
                escribir(ficheroTras, traspuestaB);
                exit(0);
            } else
                wait(0);
        }
        exit(0);
    } else {
        wait(NULL);
        int fichero = 0;
        char cadenas[2000];
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
