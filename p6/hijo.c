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
        wait(NULL);
        printf("Hijo %i %i\n", getpid(), getppid());
        exit(0);
    }
    return 0;
}
