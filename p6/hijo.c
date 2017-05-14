#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        key_t llave;
        float ***shm, **matrizA, **matrizB;
        llave = 5678;
        if ((shmid=shmget(llave, TAM_MEM, 0666))<0) {
            perror("Error al obtener memoria compartida: shmget");
            exit(-1);
        }
        if ((shm=shmat(shmid, NULL, 0))==(float***)-1) {
            perror("Error al enlazar la memoria compartida:shmat");
            exit(-1);
        }
        matrizA = *shm;
        matrizB = *(shm+1);
        float suma[10][10];
        sumar(matrizA, matrizB, suma);
        float **resultado = matriz();
        copiar_matriz(resultado, suma);
        wait(NULL);
        int shmid2;
        key_t llave2;
        float **shm2;
        llave2 = 5679;
        size_t TAM_MEM2 = sizeof(resultado);
        if ((shmid2=shmget(llave2, TAM_MEM2, IPC_CREAT | 0666))<0) {
            perror("Error al obtener memoria compartida: shmget");
            exit(-1);
        }
        if ((shm2=shmat(shmid2, NULL, 0))==(float**)-1) {
            perror("Error al enlazar la memoria compartida:shmat");
            exit(-1);
        }
        resultado = shm2;
        copiar_matriz(resultado, suma);
        exit(0);
    }
    return 0;
}
