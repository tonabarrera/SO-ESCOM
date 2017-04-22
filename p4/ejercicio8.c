#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "funciones5.h"
#include <time.h>
#include <sys/time.h>

double timeval_diff(struct timeval *a, struct timeval *b)
{
  return (double)(a->tv_sec + (double)a->tv_usec/1000000) - (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int main(void) {
    struct timeval t_ini, t_fin;
    double secs;
    gettimeofday(&t_ini, NULL);
    pid_t pid;
    int i, I;
    char *argv[3];
    argv[2] = NULL;
    printf("---Procesos por sustitucion de codigo---\n");
    pid = fork();
    if (pid == 0) {
        for (i=0; i<5; i++){
            pid = fork();
            if (pid == 0 && i==0){
                argv[0] = "./suma.out";
                argv[1] = "Ejecuntado desde el if suma...";
                execv(argv[0], argv);
            } else if (pid == 0 && i==1) {
                argv[0] = "./resta.out";
                argv[1] = "Ejecutando desde el if resta...";
                execv(argv[0], argv);
            } else if (pid ==0 && i==2) {
                argv[0] = "./multiplicacion.out";
                argv[1] = "Ejecutando desde el if multiplicacion...";
                execv(argv[0], argv);
            } else if (pid == 0 && i == 3) {
                argv[0] = "./traspuesta.out";
                argv[1] = "Ejecutando desde el if traspuesta...";
                execv(argv[0], argv);
            } else if (pid==0 && i==4) {
                argv[0] = "./inversa.out";
                argv[1] = "Ejecuntando desde el if inversa...";
                execv(argv[0], argv);
            }
        }
        for (I=0; I<5; I++)
            wait(NULL);
        exit(0);
    } else {
        wait(0);
        printf("\n%s\n", "Leyendo los archivos...");
        printf("\n%s\n", "--Suma de las dos matrices");
        imprimir("suma.txt");
        printf("\n%s\n", "--Resta de las dosmatrices");
        imprimir("resta.txt");
        printf("\n%s\n", "--Multiplicacion de las dos matrices");
        imprimir("multiplicacion.txt");
        printf("\n%s\n", "--Traspuesta de las dos matrices");
        imprimir("traspuesta.txt");
        printf("\n%s\n", "--Inversa de las dos matrices");
        imprimir("inversa.txt");

        gettimeofday(&t_fin, NULL);
        secs = timeval_diff(&t_fin, &t_ini);
        printf("%.16g milliseconds\n", secs * 1000.0);
    }
    return 0;
}
