#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;
    int i;
    char *argv[3];
    argv[2] = NULL;
    pid = fork();
    if (pid == 0) {
        for (i=0; i<5; i++){
            pid = fork();
            if (pid == 0 && i==0){
                printf("Suma %d %d \n", getpid(), getppid());
                argv[0] = "./suma.out";
                argv[1] = "Ejecuntado desde el if suma";
                execv(argv[0], argv);
            } else if (pid == 0 && i==1) {
                printf("Resta %d %d \n", getpid(), getppid());
                exit(0);
            } else if (pid ==0 && i==2) {
                printf("Multiplicacion %d %d \n", getpid(), getppid());
                exit(0);
            } else if (pid == 0 && i == 3) {
                printf("Traspuesta %d %d \n", getpid(), getppid());
                exit(0);
            } else if (pid==0 && i==4) {
                printf("Inversa %d %d \n", getpid(), getppid());
                exit(0);
            } else{
                wait(0);
            }
        }
        printf("Imprimiendo el contenido de los archivos...\n");
        exit(0);
    } else {
        wait(0);
        exit(0);
    }
    return 0;
}
