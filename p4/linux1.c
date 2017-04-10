#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("Soy el proceso hijo \n");
        exit(0);
    } else {
        printf("Soy el procesos padre\n");
        exit(0);
    }
    return 0;
}
