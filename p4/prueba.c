#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char const* argv[])
{
    int pid;
    pid = fork();
    if(pid==0){
        int i;
        for (i=0; i<5000; i++){
            printf("hijo %d %d \n", getpid(), getppid());
        }
        exit(0);
    } else {
        int j;
        for (j=0; j<5000; j++)
            printf("padre %d ", getpid());
        wait(NULL);
    }

    return 0;
}
