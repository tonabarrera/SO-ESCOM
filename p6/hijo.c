#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "matrices.h"

int main(int argc, char *argv[]){
    pid_t pid;
    if ((pid=fork())==0) {
        char *argv[2];
        argv[0] = "./nieto.out";
        argv[1] = NULL;
        execv(argv[0], argv);
    } else {
        printf("Hijo %i %i\n", getpid(), getppid());
        int shmid;
        struct Contenedor *shm;
        key_t llave = 5678;
        size_t TAM_MEM = sizeof(struct Contenedor);
        if ((shmid=shmget(llave, TAM_MEM, 0666))<0) {
            perror("Error en hijo: shmget");
            exit(-1);
        }
        if ((shm=shmat(shmid, NULL, 0))==(void*)-1) {
            perror("Error en hijo:shmat");
            exit(-1);
        }
        if (shm != NULL){
            printf("Estado en hijo: %i\n", shm->estado);
            if (shm->matrizUno != NULL)
                printf("Valor chido %lf\n", *(shm->matrizUno));
        }
        exit(0);
    }
    return 0;
}
