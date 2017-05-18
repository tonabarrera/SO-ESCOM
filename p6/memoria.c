#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include "matrices.h"
int padre();
int hijo();
int nieto();

int main(void) {
    pid_t pid;
    if ((pid=fork())==0) {
        hijo();
        if ((pid=fork()==0)){
            nieto();
            exit(0);
        }
        wait(NULL);
        exit(0);
    } else {
        padre();
    }
    exit(0);
    return 0;
}

int padre() {
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
    };
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
    shm->estado = 0;
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++){
        for (j=0; j<COL; j++, pos++){
            (shm->matrizUno)[pos] = matrizA[i][j];
            (shm->matrizDos)[pos] = matrizB[i][j];

        }
    }
    printf("Estado en padre-hijo(1): %i\n", shm->estado);
    while (!shm->estado)
        sleep(1);

    printf("Estado en padre-hijo(2): %i\n", shm->estado);
    return 0;
}

int hijo(){
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
    }
    float **matrizA = matriz();
    float **matrizB = matriz();
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++){
        for (j=0; j<COL; j++, pos++){
            matrizA[i][j] = (shm->matrizUno)[pos];
            matrizB[i][j] = (shm->matrizDos)[pos];
        }
    }
    int matrizProducto[COL][COL];
    multiplicar(matrizA, matrizB, matrizProducto);
    shm->estado=1;
    mostrar_matriz(matrizProducto);
    
    /*Hijo-nieto*/
    int shmid2;
    struct Contenedor *shm2;
    key_t llave2 = 6678;
    if ((shmid2=shmget(llave2, TAM_MEM, 0666 | IPC_CREAT))<0) {
        perror("Error en hijo(2): shmget");
        exit(-1);
    }
    if ((shm2=shmat(shmid2, NULL, 0))==(void*)-1) {
        perror("Error en hijo(2):shmat");
        exit(-1);
    }
    shm2->estado = 0;
    if (shm2 != NULL){
        printf("Estado en hijo-nieto: %i\n", shm2->estado);
    }
    for (i = 0, pos=0; i<COL; i++){
        for (j=0; j<COL; j++, pos++){
            (shm2->matrizUno)[pos] = matrizA[i][j];
            (shm2->matrizDos)[pos] = matrizB[i][j];
        }
    }
    return 0;
}

int nieto() {
    printf("Nieto %i %i\n", getpid(), getppid());
    int shmid;
    struct Contenedor *shm;
    key_t llave = 6678;
    size_t TAM_MEM = sizeof(struct Contenedor);
    if ((shmid=shmget(llave, TAM_MEM, 0666))<0) {
        perror("Error en nieto(1): shmget");
        exit(-1);
    }
    if ((shm=shmat(shmid, NULL, 0))==(void*)-1) {
        perror("Error en nieto(1):shmat");
        exit(-1);
    }
    if (shm != NULL){
        printf("Estado en nieto: %i\n", shm->estado);
    }
    float **matrizA = matriz();
    float **matrizB = matriz();
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++){
        for (j=0; j<COL; j++, pos++){
            matrizA[i][j] = (shm->matrizUno)[pos];
            matrizB[i][j] = (shm->matrizDos)[pos];
        }
    }
    int matrizSuma[COL][COL];
    sumar(matrizA, matrizB, matrizSuma);
    mostrar_matriz(matrizSuma);
    return 0;
}