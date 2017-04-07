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

int invertir(int matriz[col][col], int inversa[col][col]) {
    double A[col][col];
    int x, y;
    for ( x = 0; x < col; x++) {
        for (y = 0; y < col; y++) {
            A[col][col] = matriz[col][col];
        }
    }
    int i;
    for (i = 0; i < COL; i++) {
        if (A[i][i] != 0) {
            int m, n;
            double divisor = A[i][i];
            for (m = 0; m < COL; m++) {
                A[i][m] = A[i][m]/divisor;
                inversa[i][m] = inversa[i][m]/divisor;
            }
            for(m=0; m<COL;m++){
                if(m!=i) {
                    double constante = A[m][i];
                    for (n = 0; n < COL; n++) {
                        printf("= %lf - (%lf * %lf)\n", inversa[m][n], inversa[i][n], constante);
                        A[m][n] = A[m][n]-(A[i][n]*constante);
                        inversa[m][n] = inversa[m][n] - (inversa[i][n]*constante);
                    }
                }
            }
        }
    }

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

