#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const* argv[])
{
    char msj[100];
    strcpy(msj, "Estoy en el programa inversa - ");
    strcat(msj, argv[1]);
    printf("%s\n", msj);
    exit(0);
    return 0;
}
