#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int main(void)
{
    pid_t pid;
    if ((pid=fork())==0) {
        char *argv[2];
        argv[0] = "./hijo.out";
        argv[1] = NULL;
        execv(argv[0], argv);
    } else {
        wait(NULL);
        printf("Padre %i %i\n", getpid(), getppid());
        exit(0);
    }
    return 0;
}
