#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const* argv[])
{
    char mensaje[100];
    strcpy(mensaje, "Estoy en el programa suma ");
    strcat(mensaje, argv[1]);
    printf("%s\n", mensaje);
    exit(0);
    return 0;
}
