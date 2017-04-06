#include "funciones5.h"
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
int multiplicar(int matrizA[col][col], int matrizB[col][col], int resultado[col][col]) {
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

int abrir(char *archivo) {
    return open(archivo, O_WRONLY|O_CREAT, 0640);
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

int imprimir(char *archivo) {
    int fichero;
    char cadena[1];
    fichero = open(archivo, O_RDONLY);
    while (0 < read(fichero, cadena, 1)) {
        printf("%s", cadena);
    }
    close(fichero);
    return 0;
}
