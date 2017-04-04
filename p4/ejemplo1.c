#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int id_proc;
    id_proc = fork();
    if (id_proc == 0) {
        printf("Soy el proceso hijo \n");
        exit(0);
    } else {
        printf("Soy el procesos padre\n");
        exit(0);
    }
    return 0;
}
