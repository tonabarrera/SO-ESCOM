#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void prueba(int i, int pid){
    printf("Primero-%d %d\n", i, getpid());
    pid = fork();
    if (pid == 0) {
        printf("Segundo-%d %d\n", i, getpid());
        pid = fork();
        if (pid == 0) {
            printf("Tercero-%d %d padre: %d\n\n", i, getpid(), getppid());
            exit(0);
        } else
            wait(NULL);
        exit(0);
    } else
        wait(NULL);
    exit(0);
}

void prueba2(int i, int pid) {
    printf("Primero-%d %d\n", i, getpid());
    pid = fork();
    if (pid == 0) {
    printf("Segundo-%d %d\n", i, getpid());
    pid = fork();
    if (pid == 0) {
        printf("Tercero-%d %d\n", i, getpid());
        int j;
        for(j=0; j<2; j++){
            pid = fork();
            if(pid == 0){
                printf("Cuarto-%d-%d %d padre: %d\n", i, j,getpid(), getppid());
                exit(0);
            } else
                wait(NULL);
        }
        printf("\n");
        exit(0);
    } else
        wait(NULL);
    exit(0);
    } else
        wait(NULL);
    exit(0);
}

void prueba3(int i, int pid){
    printf("Primero-%d %d\n", i, getpid());
    pid = fork();
    if (pid == 0) {
        printf("Segundo-%d %d\n", i, getpid());
        pid = fork();
        if (pid == 0) {
            printf("Tercero-%d %d\n", i, getpid());
            pid = fork();
            if (pid == 0) {
                printf("Cuarto-%d %d\n", i, getpid());
                 int j;
                for(j=0; j<3; j++){
                    pid = fork();
                    if(pid == 0){
                        printf("Quinto-%d-%d %d padre: %d\n", i, j, getpid(), getppid());
                        exit(0);
                    } else
                        wait(NULL);
                }
                printf("\n");
                exit(0);
            } else
                wait(NULL);
            exit(0);
        } else
            wait(NULL);
        exit(0);
    } else
        wait(NULL);
    exit(0);
}

void prueba4(int i, int pid){
    printf("Primero-%d %d\n", i, getpid());
    pid = fork();
    if (pid == 0) {
        printf("Segundo-%d %d\n", i, getpid());
        pid = fork();
        if (pid == 0) {
            printf("Tercero-%d %d\n", i, getpid());
            pid = fork();
            if (pid == 0) {
                printf("Cuarto-%d %d\n", i, getpid());
                pid = fork();
                if (pid == 0){
                    printf("Quinto-%d %d\n", i, getpid());
                    int j;
                    for(j=0; j<4; j++){
                        pid = fork();
                        if(pid == 0){
                            printf("Sexto-%d-%d %d padre: %d\n", i, j, getpid(), getppid());
                            exit(0);
                        } else
                            wait(NULL);
                    }
                    printf("\n");
                    exit(0);
                } else
                    wait(NULL);
                exit(0);
            } else
                wait(NULL);
            exit(0);
        } else
            wait(NULL);
        exit(0);
    } else
        wait(NULL);
    exit(0);
}

void prueba5(int i, int pid){
    printf("Primero-%d %d\n", i, getpid());
    pid = fork();
    if (pid == 0) {
        printf("Segundo-%d %d\n", i, getpid());
        pid = fork();
        if (pid == 0) {
            printf("Tercero-%d %d\n", i, getpid());
            pid = fork();
            if (pid == 0) {
                printf("Cuarto-%d %d\n", i, getpid());
                pid = fork();
                if (pid == 0){
                    printf("Quinto-%d %d\n", i, getpid());
                    pid = fork();
                    if (pid == 0){
                        printf("Sexto-%d %d\n", i, getpid());
                        int j;
                        for(j=0; j<5; j++){
                            pid = fork();
                            if(pid == 0){
                                printf("Septimo-%d-%d %d\n", i, j, getppid());
                                exit(0);
                            } else
                                wait(NULL);
                        }
                        printf("\n");
                        exit(0);
                    } else
                        wait(NULL);
                    exit(0);
                } else
                    wait(NULL);
                exit(0);
            } else
                wait(NULL);
            exit(0);
        } else
            wait(NULL);
        exit(0);
    } else
        wait(NULL);
    exit(0);
}

int main(int argc, char* argv[]) {
    int i;
    int I;
    int pid;
    printf("Raiz: %d\n\n", getpid());
    for (i = 0; i < 10; i++) {
        pid = fork();
        if (pid==0 && i==0)
            prueba5(i, pid);
        else if (pid==0 && i==1)
            prueba4(i, pid);
        else if (pid==0 && i==2)
            prueba3(i, pid);
        else if (pid==0 && i==3)
            prueba2(i, pid);
        else if (pid==0 && i==4)
            prueba(i, pid);
        else if(pid==0 && i==5)
            prueba(i, pid);
        else if (pid==0 && i==6)
            prueba2(i, pid);
        else if (pid==0 && i==7)
            prueba3(i, pid);
        else if (pid==0 && i==8)
            prueba4(i, pid);
        else if (pid==0 && i==9)
            prueba5(i, pid);
    }
    for (I = 0; I < 10; I++)
        wait(NULL);
    return 0;
}
