#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include "matrices.h"

int padre();
int hijo();
int nieto();
int imprimir_matriz(float matriz[100]);

int main(void) {
    pid_t pid;
    srand(time(NULL));
    if ((pid=fork())==0) {
        hijo();
        if ((pid=fork()==0)){
            nieto();
            exit(0);
        }
        wait(NULL);
        exit(0);
    }
    padre();
    int shmid_nieto, shmid_hijo;
    key_t nieto_padre = 7678;
    key_t hijo_padre = 8678;
    int *shm_nieto, *shm_hijo;
    size_t TAM_MEM = 100*sizeof(int);
    if ((shmid_nieto=shmget(nieto_padre, TAM_MEM, 0666))<0) {
        perror("Error en inversa(1): shmget");
        exit(-1);
    }
    if ((shm_nieto=shmat(shmid_nieto, NULL, 0))==(void*)-1) {
        perror("Error en inversa(1):shmat");
        exit(-1);
    }
    if ((shmid_hijo=shmget(hijo_padre, TAM_MEM, 0666))<0) {
        perror("Error en inversa(2): shmget");
        exit(-1);
    }
    if ((shm_hijo=shmat(shmid_hijo, NULL, 0))==(void*)-1) {
        perror("Error en inversa(2):shmat");
        exit(-1);
    }
    float **inversa_suma = matriz();
    float **inversa_multiplicacion = matriz();
    int i, j, pos;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            inversa_suma[i][j] = (shm_nieto)[pos];
            inversa_multiplicacion[i][j] = (shm_hijo)[pos];
        }
    printf("Realizando inversas...\n");
    gaussj(inversa_suma);
    gaussj(inversa_multiplicacion);
    int ficheroInv = abrir("inversa_suma.txt");
    escribir_texto(ficheroInv, "La inversa de la matriz suma es:");
    escribir_float(ficheroInv, inversa_suma);
    close(ficheroInv);
    ficheroInv = abrir("inversa_multiplicacion.txt");
    escribir_texto(ficheroInv, "La inversa de la matriz multiplicacion es:");
    escribir_float(ficheroInv, inversa_multiplicacion);
    close(ficheroInv);
    exit(0);
    return 0;
}

int padre() {
    printf("Padre\n");
    key_t llave = 5678;
    int shmid_original;
    struct Contenedor *shm_cont;
    size_t TAM_MEM = sizeof(struct Contenedor);
    if ((shmid_original=shmget(llave, TAM_MEM, IPC_CREAT | 0666))<0) {
        perror("Error en padre: shmget");
        exit(-1);
    }
    if ((shm_cont=shmat(shmid_original, NULL, 0)) == (void*)-1) {
        perror("Error en padre: shmat");
        exit(-1);
    }
    shm_cont->estado = 0;
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            (shm_cont->matrizUno)[pos] = rand()%11;
            (shm_cont->matrizDos)[pos] = rand()%11;
        }
    printf("Matriz Uno para la multiplicacion:\n");
    imprimir_matriz(shm_cont->matrizUno);
    printf("Matriz Dos para la multiplicacion:\n");
    imprimir_matriz(shm_cont->matrizDos);
    while (!shm_cont->estado)
        sleep(1);
    return 0;
}

int hijo(){
    printf("Hijo\n");
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
    float **matrizA = matriz();
    float **matrizB = matriz();
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            matrizA[i][j] = (shm->matrizUno)[pos];
            matrizB[i][j] = (shm->matrizDos)[pos];
        }
    int matrizProducto[COL][COL];
    multiplicar(matrizA, matrizB, matrizProducto);
    printf("La matriz multiplicacion es:\n");
    mostrar_matriz(matrizProducto);

    /*Hijo-nieto*/
    int shmid2;
    struct Contenedor *shm2;
    key_t llave_nieto = 6678;
    if ((shmid2=shmget(llave_nieto, TAM_MEM, 0666 | IPC_CREAT))<0) {
        perror("Error en hijo(2): shmget");
        exit(-1);
    }
    if ((shm2=shmat(shmid2, NULL, 0))==(void*)-1) {
        perror("Error en hijo(2):shmat");
        exit(-1);
    }
    shm2->estado = 0;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            (shm2->matrizUno)[pos] = rand()%11;
            (shm2->matrizDos)[pos] = rand()%11;
        }
    printf("Matriz Uno para la suma:\n");
    imprimir_matriz(shm2->matrizUno);
    printf("Matriz Dos para la suma:\n");
    imprimir_matriz(shm2->matrizDos);
    /*Hijo-padre*/
    int shmid_padre;
    int *shm_padre;
    key_t hijo_padre = 8678;
    if ((shmid_padre=shmget(hijo_padre, 100*sizeof(int), 0666 | IPC_CREAT))<0) {
        perror("Error en hijo(3): shmget");
        exit(-1);
    }
    if ((shm_padre=shmat(shmid_padre, NULL, 0))==(void*)-1) {
        perror("Error en hijo(3):shmat");
        exit(-1);
    }
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++)
            shm_padre[pos] = matrizProducto[i][j];
    shm->estado = 1;
    return 0;
}

int nieto() {
    printf("Nieto\n");
    int shmid_ultimo;
    struct Contenedor *shm_ultimo;
    key_t llave = 6678;
    size_t TAM_MEM = sizeof(struct Contenedor);
    if ((shmid_ultimo=shmget(llave, TAM_MEM, 0666))<0) {
        perror("Error en nieto(1): shmget");
        exit(-1);
    }
    if ((shm_ultimo=shmat(shmid_ultimo, NULL, 0))==(void*)-1) {
        perror("Error en nieto(1):shmat");
        exit(-1);
    }
    float **matrizA = matriz();
    float **matrizB = matriz();
    int pos, i, j;
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++){
            matrizA[i][j] = (shm_ultimo->matrizUno)[pos];
            matrizB[i][j] = (shm_ultimo->matrizDos)[pos];
        }
    int matrizSuma[COL][COL];
    sumar(matrizA, matrizB, matrizSuma);
    printf("La matriz suma es:\n");
    mostrar_matriz(matrizSuma);

    /*nieto-padre*/
    int shmid_padre;
    int *shm_padre;
    key_t nieto_padre = 7678;
    if ((shmid_padre=shmget(nieto_padre, 100*sizeof(int), 0666 | IPC_CREAT))<0) {
        perror("Error en hijo(2): shmget");
        exit(-1);
    }
    if ((shm_padre=shmat(shmid_padre, NULL, 0))==(void*)-1) {
        perror("Error en hijo(2):shmat");
        exit(-1);
    }
    for (i = 0, pos=0; i<COL; i++)
        for (j=0; j<COL; j++, pos++)
            shm_padre[pos] = matrizSuma[i][j];
    return 0;
}

int imprimir_matriz(float matriz[100]) {
    int i;
    printf("[");
    for (i=0; i<100; i++){
        if (i%10 == 0)
            printf("\n");
        printf("%.0f ", matriz[i]);
    }
    printf("\n]\n");
    return 0;
}