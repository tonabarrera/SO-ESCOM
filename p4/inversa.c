#include <stdio.h>
#define COL 4
int main(int argc, char const* argv[])
{
    double A[COL][COL] = {
        {1, 2, 3, 4},
        {3, 4, 6, 7},
        {1, -1, 0, 1},
        {2, 3, 2, 5},
    };
    double inversa[COL][COL] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
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

    int x, y;
    for (x = 0; x < COL; x++) {
        for ( y = 0; y < COL; y++) {
            printf("%.2lf ", inversa[x][y]);
        }
        printf("\n");
    }
    return 0;
}
