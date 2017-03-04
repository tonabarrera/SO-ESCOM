#include <stdio.h>
#include <sys/stat.h> // mkdir
#include <unistd.h> // chdir, close, write
#include <fcntl.h> // open

int main(int argc, char *argv[]) {
	mkdir("prueba", 0777);
	chdir("prueba");
	int archivo = open("prueba.txt", O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0777); // Si no pones creat no hace nada
	if (archivo < 0) {
		printf("%s\n", "Mal =(");
		return 0;
	}
	int regreso = write(archivo, "Madre mia Willy sin usar fopen", 30); // Tiene que ser obligatoriamente el tamaño de la cadena o cosas raras pasan
	close(archivo);
	printf("Hola %d\n", regreso);
	return 0;
}