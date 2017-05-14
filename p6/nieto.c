#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {
    printf("Nieto %i %i\n", getpid(), getppid());
    exit(0);
    return 0;
}
