#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nrutil.h"
#define SWAP(a, b) {temp=(a);(a)=(b);(b)=temp;}

void gaussj(float **a, int n, int m) {
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
}

int main(int argc, char const *argv[]) {
    float **matriz = matrix(2, 2);
    int i, j;
    matriz[0][0] = 7;
    matriz[0][1] = 2;

    matriz[1][0] = 7;
    matriz[1][1] = 90;

    for (i=0; i<2; i++){
        for(j=0; j<2; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    gaussj(matriz, 2, 2);
    for (i=0; i<2; i++){
        for(j=0; j<2; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}
