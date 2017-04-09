#include "funciones5.h"
#define SWAP(a, b) {temp=(a);(a)=(b);(b)=temp;}
int sumar(int matrizA[COL][COL], int matrizB[COL][COL], int resultado[COL][COL]) {
    int i, j;
    for (i = 0; i < COL; i++) {
        for (j = 0; j < COL; j++)
            resultado[i][j] = matrizA[i][j] + matrizB[i][j];
    }
    return 0;
}

int restar(int matrizA[COL][COL], int matrizB[COL][COL], int resultado[COL][COL]) {
    int i, j;
    for (i = 0; i < COL; i++)
        for (j = 0; j < COL; j++){
            resultado[i][j] = matrizA[i][j] - matrizB[i][j];
    }
    return 0;
}

int trasponer(int matriz[COL][COL], int traspuesta[COL][COL]) {
    int i, j;
    for(i=0;i<COL; i++){
        for(j=0; j<COL; j++)
            traspuesta[j][i] = matriz[i][j];
    }
    return 0;
}
//Tal vez sea mejor si uso recursion
int multiplicar(int matrizA[COL][COL], int matrizB[COL][COL], int resultado[COL][COL]) {
    int i, j, k;
    int valor = 0;
    for(i=0; i<COL; i++){
        for(j=0; j<COL; j++){
            valor = 0;
            for(k=0; k<COL; k++){
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

/*la forma no pro
int invertir(double aux[COL][COL], double inversa[COL][COL]) {
    int x, y;
    printf("Hak\n");
    for (x=0; x<COL; x++){
        for (y=0; y<COL; y++){
           printf("%.2lf ", aux[x][y]);
        }
        printf("\n");
    }
    int i;
    printf("Algo\n");
    for (i = 0; i < COL; i++) {
        if (aux[i][i] != 0) {
            int m, n;
            double divisor = aux[i][i];
            for (m = 0; m < COL; m++) {
                aux[i][m] = aux[i][m]/divisor;
                inversa[i][m] = inversa[i][m]/divisor;
            }
            for(m=0; m<COL;m++){
                if(m!=i) {
                    double constante = aux[m][i];
                    for (n = 0; n < COL; n++) {
                        //printf("= %lf - (%lf * %lf)\n", inversa[m][n], inversa[i][n], constante);
                        aux[m][n] = aux[m][n]-(aux[i][n]*constante);
                        inversa[m][n] = inversa[m][n] - (inversa[i][n]*constante);
                    }
                }
            }
        }else {
            printf("ERROR %lf %d %d ", aux[i][i], i, i);
        }
    }
    return 0;
}*/

int gaussj(float **a, int n, int m) {
    int *indxc, *indxr, *ipiv;
    int i, icol, irow, j, k, l, ll;
    float big, dum, pivinv, temp;

    indxc = (int *) malloc((size_t)((n)*sizeof(int)));;
    indxr = (int *) malloc((size_t)((n)*sizeof(int)));
    ipiv = (int *) malloc((size_t)((n)*sizeof(int)));

    for (j=0; j<n; j++) ipiv[j]=0;
    for (i=0; i<n; i++){
        big = 0.0;
        for (j=0; j<n; j++){
            if(ipiv[j] !=1){
                for (k=0; k<n; k++){
                    if(ipiv[k] == 0){
                        if(fabs(a[j][k]) >= big){
                            big = fabs(a[j][k]);
                            irow = j;//2 2
                            icol = k;//1 2
                        }
                    } else if(ipiv[k]>1) {
                        printf("Error");
                        exit(1);
                    }
                }
            }
        }
        ++(ipiv[icol]);//ipiv[1]=1 ipiv[2]=2
        if (irow != icol) {
            for (l=0; l<n; l++) SWAP(a[irow][l], a[icol][l]);
        }
        indxr[i] = irow;//2 2
        indxc[i] = icol;//1 2
        if (a[icol][icol]==0.0) {
            printf("Error\n");
            exit(1);
        }
        pivinv = 1.0/a[icol][icol]; //dividir fila del pivote
        a[icol][icol] = 1.0;

        //Continnuar la division de columnas de la fila en la que nos encontramos
        for (l=0; l<n; l++) a[icol][l] *= pivinv;
        //resta menos en la fila del pivote icol
        for (ll=0; ll<n; ll++){
            if(ll != icol) {
                dum = a[ll][icol];
                a[ll][icol]=0.0;
                for (l=0; l<n; l++) a[ll][l] -= a[icol][l]*dum;
            }
        }
    }

    for (l=n-1; l>=0; l--){
        if(indxr[l] != indxc[l]){
            for(k=0; k<n; k++)
                SWAP(a[k][indxr[l]], a[k][indxc[l]]);
        }
    }/*
    free_ivector(ipiv, 1, n);
    free_ivector(indxr, 1, n);
    free_ivector(indxc, 1, n);*/
    return 0;
}

int escribir(int fichero, int matriz[COL][COL]) {
    int m, n;
    char caracter[5];
    write(fichero, "[\n", 2);
    for (m=0; m<COL; m++){
        for(n=0; n<COL; n++){
            sprintf(caracter, "%d", matriz[m][n]);
            write(fichero, caracter, strlen(caracter));
            write(fichero, " ", 1);
        }
        write(fichero, "\n", 1);
    }
    write(fichero, "]\n", 2);
    return 0;
}

/*
int escribirDouble(int fichero, double matriz[COL][COL]) {
    int m, n;
    char caracter[5];
    write(fichero, "[\n", 2);
    for (m=0; m<COL; m++){
        for(n=0; n<COL; n++){
            sprintf(caracter, "%lf", matriz[m][n]);
            write(fichero, caracter, strlen(caracter));
            write(fichero, " ", 1);
        }
        write(fichero, "\n", 1);
    }
    write(fichero, "]\n", 2);
    return 0;
}*/

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
