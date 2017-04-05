#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int i;
    int pid;
    printf("Raiz: %d\n", getpid());
    for (i = 0; i < 7; i++) {
        pid = fork();
        if (pid==0 && i != 4 && i!=5 && i !=6 && i!=3) {
            printf("Primero-%d %d\n", i, getpid());
            exit(0);
        }else {
            wait(NULL);
        }
        if (pid==0 && i==3) {
            printf("Primero-%d %d\n", i, getpid());
            pid = fork();
            if (pid==0) {
                printf("Segundo-%d %d\n", i, getpid());
                pid = fork();
                if (pid==0) {
                    printf("Tercero-%d %d\n", i, getpid());
                    int j;
                    for(j=0; j<2; j++){
                        pid = fork();
                        if(pid==0){
                            printf("Cuarto-%d-%d %d\n", i, j, getppid());
                            exit(0);
                        } else {
                            wait(NULL);
                        }
                    }
                    exit(0);
                } else {
                    wait(NULL);
                }
                exit(0);
            } else {
                wait(NULL);
            }
            exit(0);
        } else if (pid==0 && i==4) {
            printf("Primero-%d %d\n", i, getpid());
            pid = fork();
            if(pid==0) {
                printf("Segundo-%d %d\n", i, getpid());
                pid = fork();
                if (pid==0) {
                    printf("Tercero-%d %d\n", i, getppid());
                    exit(0);
                } else {
                    wait(NULL);
                }
                exit(0);
            }else {
                wait(NULL);
            }
            exit(0);
        } else if(pid==0 && i==5){
            printf("Primero-%d %d\n", i, getpid());
            pid = fork();
            if (pid==0) {
                printf("Segundo-%d %d\n", i, getpid());
                pid = fork();
                if (pid==0) {
                    printf("Tercero-%d %d\n", i, getppid());
                    exit(0);
                } else {
                    wait(NULL);
                }
                exit(0);
            } else {
                wait(NULL);
            }
            exit(0);
        } else if (pid==0 && i==6) {
            printf("Primero-%d %d\n", i, getpid());
            pid = fork();
            if (pid==0) {
                printf("Segundo-%d %d\n", i, getpid());
                pid = fork();
                if (pid==0) {
                    printf("Tercero-%d %d\n", i, getpid());
                    int j;
                    for(j=0; j<2; j++){
                        pid = fork();
                        if(pid==0){
                            printf("Cuarto-%d-%d %d\n", i, j, getppid());
                            exit(0);
                        } else {
                            wait(NULL);
                        }
                    }
                    exit(0);
                } else {
                    wait(NULL);
                }
                exit(0);
            } else {
                wait(NULL);
            }
            exit(0);
        } else
            wait(NULL);
    }
    return 0;
}
