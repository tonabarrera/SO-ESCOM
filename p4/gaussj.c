#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "nrutil.h"
#define SWAP(a, b) {temp=(a);(a)=(b);(b)=temp;}

void gaussj(float **a, int n, int m) {
    int *indxc, *indxr, *ipiv;
    int i, icol, irow, j, k, l, ll;
    int a1, a2;
    float big, dum, pivinv, temp;

    indxc = ivector(1, n);
    indxr = ivector(1, n);
    ipiv = ivector(1, n);

    for (j=1; j<=n; j++) ipiv[j]=0;
    for (i=1; i<=n; i++){
        big = 0.0;
        for (j=1; j<=n; j++){
            if(ipiv[j] !=1){
                for (k=1; k<=n; k++){
                    if(ipiv[k] == 0){
                        if(fabs(a[j][k]) >= big){
                            big = fabs(a[j][k]);
                            irow = j;//2 2
                            icol = k;//1 2
                        }
                    } else if(ipiv[k]>1) {
                        nrerror("gaussj:Singular matriz-1");
                    }
                }
            }
        }
        ++(ipiv[icol]);//ipiv[1]=1 ipiv[2]=2
        if (irow != icol) {
            for (l=1; l<=n; l++) SWAP(a[irow][l], a[icol][l]);
        }
        printf("Despues Intercambio\n");
        for (a1=1; a1<=2; a1++){
            for(a2=1; a2<=2; a2++){
                printf("%f ", a[a1][a2]);
            }
            printf("\n");
        }
        printf("\n");
        indxr[i] = irow;//2 2
        indxc[i] = icol;//1 2
        if (a[icol][icol]==0.0) nrerror("gaussj:singular matriz-2");
        pivinv = 1.0/a[icol][icol]; //dividir fila del pivote
        a[icol][icol] = 1.0;

        printf("Chido\n");
        for (a1=1; a1<=2; a1++){
            for(a2=1; a2<=2; a2++){
                printf("%f ", a[a1][a2]);
            }
            printf("\n");
        }
        printf("\n");
        //Continnuar la division de columnas de la fila en la que nos encontramos
        for (l=1; l<=n; l++) a[icol][l] *= pivinv;
        printf("Despues de multiplicar\n");
        for (a1=1; a1<=2; a1++){
            for(a2=1; a2<=2; a2++){
                printf("%f ", a[a1][a2]);
            }
            printf("\n");
        }
        printf("\n");
        //resta menos en la fila del pivote icol
        for (ll=1; ll<=n; ll++){
            if(ll != icol) {
                dum = a[ll][icol];
                a[ll][icol]=0.0;
                for (l=1; l<=n; l++) a[ll][l] -= a[icol][l]*dum;
            }
        }
        printf("Despues de restar\n");
        for (a1=1; a1<=2; a1++){
            for(a2=1; a2<=2; a2++){
                printf("%f ", a[a1][a2]);
            }
            printf("\n");
        }
        printf("\n");
    }
    //Acomodar columnas el for despues de este
    printf("pre Acomoda\n");
    for (a1=1; a1<=2; a1++){
        for(a2=1; a2<=2; a2++){
            printf("%f ", a[a1][a2]);
        }
        printf("\n");
    }
    printf("\n");

    for (l=n; l>=1; l--){
        if(indxr[l] != indxc[l]){
            for(k=1; k<=n; k++)
                SWAP(a[k][indxr[l]], a[k][indxc[l]]);
        }
    }
    free_ivector(ipiv, 1, n);
    free_ivector(indxr, 1, n);
    free_ivector(indxc, 1, n);
}

int main(int argc, char const *argv[]) {
    float **matriz = matrix(1, 2, 1, 2);
    int i, j;
    matriz[1][1] = 0;
    matriz[1][2] = 2;

    matriz[2][1] = 7;
    matriz[2][2] = 4;


    for (i=1; i<=2; i++){
        for(j=1; j<=2; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    gaussj(matriz, 2, 2);
    for (i=1; i<=2; i++){
        for(j=1; j<=2; j++){
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}
