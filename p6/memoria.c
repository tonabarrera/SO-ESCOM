#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "matrices.h"

int main(void)
{
    pid_t pid;/*
    int matrizA[COL][COL] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 1},
        {1, 3, 5, 6, 7, -1, 7, 8, 9, 10},
        {-1, 2, 3, 4, 5, 0, 7, 8, 9, 1},
        {0, -2, -3, -9, 0, 2, -4, 1, 6, 3},
        {1, 4, 3, 0, 5, 6, 5, 5, 9, 10},
        {1, 0, 6, 4, -5, 4, 7, 8, 9, 1},
        {11, -2, 7, 4, 15, 6, 3, 3, 0, 1},
        {10, 2, 8, 4, 0, 1, -7, 8, 1, 10},
        {3, -2, -3, 4, 0, 6, 7, -8, 9, 10},
        {2, 2, 3, -4, 9, 6, 7, 8, 9, 10}
    };*/
    int matrizB[COL][COL] = {
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 0, 7, 0, 0, 8, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 5, 0, 0, 0},
        {0, 5, 0, 0, 2, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 5, 0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 4, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    };
    //float **pruebaA = matriz();
    float **pruebaB = matriz();
    copiar_matriz(pruebaB, matrizB);
    if ((pid=fork())==0) {
        char *argv[2];
        argv[0] = "./hijo.out";
        argv[1] = NULL;
        execv(argv[0], argv);
    } else {
        printf("Padre %i %i\n", getpid(), getppid());
        key_t llave = 5678;
        int shmid;
        struct Contenedor *shm;
        size_t TAM_MEM = sizeof(struct Contenedor);
        if ((shmid=shmget(llave, TAM_MEM, IPC_CREAT | 0666))<0) {
            perror("Error en padre: shmget");
            exit(-1);
        }
        if ((shm=shmat(shmid, NULL, 0)) == (void*)-1) {
            perror("Error en padre: shmat");
            exit(-1);
        }
        shm->estado = 90;
        float *prueba = shm->matrizUno;
        *prueba= 2;
        printf("Estado en padre: %i\n", shm->estado);
        printf("Valor del dato padre %f\n", *(shm->matrizUno));
        wait(NULL);
    }
    return 0;
}
