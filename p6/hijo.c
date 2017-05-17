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
        struct Contenedor *shm
        llave = 5678;
        if ((shmid=shmget(llave, TAM_MEM, 0666))<0) {
            perror("Error al obtener memoria compartida: shmget");
            exit(-1);
        }
        if ((shm=shmat(shmid, NULL, 0))==(float***)-1) {
            perror("Error al enlazar la memoria compartida:shmat");
            exit(-1);
        }
        printf("Valor en hijo: %i\n", shm->estado);
        exit(0);
    }
    return 0;
}
