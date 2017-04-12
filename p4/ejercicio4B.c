#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int prueba(int i, int pid){
    printf("---Primero-%d %d\n", i, getpid());
    int r, R;
    int actual, padre;
    for(r=0; r<2; r++){
        pid = fork();
        if(pid == 0) {
            actual = getpid();
            padre = getppid();
            if(r==1){
                printf("--Ultimo %d %d\n", actual, padre);
                exit(0);
            } else
                printf("--Proceso %d %d\n", actual, padre);
        } else
            break;
    }
    for (R=0; R<2; R++)
        wait(NULL);
    exit(0);
    return 0;
}

int otro(int i, int pid, int numero){
    int r, R, q, Q;
    printf("Primero-%d %d\n", i, getpid());
    for (r=0; r<numero; r++){
        pid = fork();
        if (pid == 0) {
            printf("Proceso-%d %d %d\n", i, getpid(), getppid());
            if (r==(numero-1)){
                for (q=0; q<numero; q++){
                    pid = fork();
                    if (pid==0){
                        printf("Ultimo-%d %d %d\n", i, getpid(), getppid());
                        exit(0);
                    }
                }
                for (Q=0; Q<numero; Q++)
                    wait(NULL);
            }
        } else
            break;
    }
    for (R=0; R<numero; R++)
        wait(NULL);
    exit(0);
    return 0;
}

int main(int argc, char* argv[]) {
    int i;
    int I;
    int pid;
    printf("Raiz: %d\n\n", getpid());
    for (i = 0; i < 10; i++) {
        pid = fork();
        if (pid==0 && i==0)
            otro(i, pid, 5);
        else if (pid==0 && i==1)
            otro(i, pid, 4);
        else if (pid==0 && i==2)
            otro(i, pid, 3);
        else if (pid==0 && i==3)
            otro(i, pid, 2);
        else if (pid==0 && i==4)
            prueba(i, pid);
        else if(pid==0 && i==5)
            prueba(i, pid);
        else if (pid==0 && i==6)
            otro(i, pid, 2);
        else if (pid==0 && i==7)
            otro(i, pid, 3);
        else if (pid==0 && i==8)
            otro(i, pid, 4);
        else if (pid==0 && i==9)
            otro(i, pid, 5);
    }
    for (I = 0; I < 10; I++)
        wait(NULL);
    return 0;
}
