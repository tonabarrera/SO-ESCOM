#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int i;
    int pid;
    for (i = 0; i < 7; i++) {
        pid = fork();
        if (pid==0 && i != 4 && i!=5 && i !=6) {
            printf("Primero %d\n", getpid());
            exit(0);
        }else {
            wait(NULL);
        }
        if (pid==0 && i==4) {
            printf("Primero-4 %d\n", getpid());
            pid = fork();
            if(pid==0) {
                printf("Segundo-4 %d\n", getpid());
                pid = fork();
                if (pid==0) {
                    printf("Tercero-4 %d\n", getpid());
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
            printf("Primero-5 %d\n", getpid());
            pid = fork();
            if (pid==0) {
                printf("Segundo-5 %d\n", getpid());
                pid = fork();
                if (pid==0) {
                    printf("Tercero-5 %d\n", getpid());
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
            exit(0);
        } else
            wait(NULL);
    }
    return 0;
}
