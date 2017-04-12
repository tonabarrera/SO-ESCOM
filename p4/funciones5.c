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
/*Con esto creamos nuestra matriz con apuntadores ya que usar un simple array a la antigua es mas dificil*/
float **matriz() {
    int i;
    float **m;
    m = (float**) malloc((size_t)((COL)*sizeof(float*)));

    if (!m) {
        printf("error en matriz()");
        exit(1);
    }

    for(i=0; i<COL; i++)
        m[i] = (float *) malloc((size_t)((COL)*sizeof(float)));

    if(!m[COL-1]){
         printf("error en matriz()");
         exit(1);
    }
    return m;
}
int copiar_matriz(float **destino, int origen[COL][COL]){
    int i, j;
    for (i = 0; i < COL; i++) {
       for (j = 0; j < COL; j++){
           destino[i][j] = origen[i][j];
       }
    }
    return 0;
}

int gaussj(float **inversa) {
    int *indxc, *indxr, *ipiv;
    int i, icol, irow, j, k, l, ll;
    float big, dum, pivinv, temp;

    indxc = (int *) malloc((size_t)((COL)*sizeof(int)));;
    indxr = (int *) malloc((size_t)((COL)*sizeof(int)));
    ipiv = (int *) malloc((size_t)((COL)*sizeof(int)));

    for (j=0; j < COL; j++)
        ipiv[j]=0;

    for (i=0; i < COL; i++){
        big = 0.0;
        for (j=0; j < COL; j++){
            if(ipiv[j] !=1){
                for (k=0; k<COL; k++){
                    if(ipiv[k] == 0){
                        if(fabs(inversa[j][k]) >= big){
                            big = fabs(inversa[j][k]);
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
            for (l=0; l<COL; l++) SWAP(inversa[irow][l], inversa[icol][l]);
        }
        indxr[i] = irow;//2 2
        indxc[i] = icol;//1 2
        if (inversa[icol][icol]==0.0) {
            printf("Error\n");
            exit(1);
        }
        pivinv = 1.0/inversa[icol][icol]; //dividir fila del pivote
        inversa[icol][icol] = 1.0;

        //Continnuar la division de columnas de la fila en la que nos encontramos
        for (l=0; l < COL; l++)
            inversa[icol][l] *= pivinv;
        //resta menos en la fila del pivote icol
        for (ll=0; ll < COL; ll++){
            if(ll != icol) {
                dum = inversa[ll][icol];
                inversa[ll][icol]=0.0;
                for (l=0; l < COL; l++)
                    inversa[ll][l] -= inversa[icol][l]*dum;
            }
        }
    }

    for (l=COL-1; l >= 0; l--){
        if(indxr[l] != indxc[l]){
            for(k=0; k<COL; k++)
                SWAP(inversa[k][indxr[l]], inversa[k][indxc[l]]);
        }
    }
    free(indxr);
    free(indxc);
    free(ipiv);
    return 0;
}

int abrir(char *archivo) {
    return open(archivo, O_WRONLY|O_CREAT, 0640);
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


int escribirFloat(int fichero, float **matriz) {
    int m, n;
    char caracter[5];
    write(fichero, "[\n", 2);
    for (m=0; m<COL; m++){
        for(n=0; n<COL; n++){
            sprintf(caracter, "%.2f", matriz[m][n]);
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
