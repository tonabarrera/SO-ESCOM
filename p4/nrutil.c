#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

float **matrix(long row, long col) {
    long i;
    float **m;
    m = (float**) malloc((size_t)((row)*sizeof(float*)));
    if (!m) {
        printf("matriz()");
        exit(1);
    }

    for(i=0; i<col; i++){
        m[i] = (float *) malloc((size_t)((col)*sizeof(float)));
    }
    if(!m[col-1]){
         printf("matriz()");
         exit(1);
    }

    return m;
}
