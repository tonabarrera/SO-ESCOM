#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char const* argv[])
{
    int archivo = open("suma.txt", O_RDONLY);
    char buffer[1];
    while (0 < read(archivo, buffer, 1)) {
        printf("%s", buffer);
    }
    close(archivo);
    return 0;
}
