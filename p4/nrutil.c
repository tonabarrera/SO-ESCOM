#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char *

void nrerror(char error_text[]) {
    fprintf(stderr, "Numerical algo\n");
    fprintf(stderr, "%s\n", error_text);
    fprintf(stderr, "... now exiting to system\n");
    exit(1);
}

int *ivector(long nl, long nh) {
    int *v;
    v=(int *) malloc((size_t)((nh-nl+1+NR_END)*sizeof(int)));
    if (!v) nrerror("Allocation failure in vector()");
    return v-nl+NR_END;
}

void free_ivector(int *v, long nl, long nh) {
    free((FREE_ARG)(v+nl-NR_END));
}

float **matrix(long nrl, long nrh, long ncl, long nch) {
    long i, nrow = nrh-nrl+1, ncol=nch-ncl+1;
    float **m;
    m= (float**) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
    if (!m) nrerror("matriz()");
    m +=NR_END;
    m-=nrl;
    m[nrl] = (float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
    if(!m[nrl]) nrerror("matriz()");
    m[nrl] += NR_END;
    m[nrl] -= ncl;
    for(i=nrl+1;i<=nrh;i++) m[i] = m[i-1] + ncol;
    return m;
}
