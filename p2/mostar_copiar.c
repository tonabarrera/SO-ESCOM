#include <stdio.h>
#include <fcntl.h> // open
#include <unistd.h> // read
#include <sys/stat.h> // stat
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

ssize_t obtener_size(char *archivo, int *archivo_abierto){
	*archivo_abierto = open(archivo, O_RDONLY);
	struct stat datos_archivo;
	stat(archivo, &datos_archivo);
	return datos_archivo.st_size;
}

int mostar_contenido(char *archivo){
	int archivo_abierto = 0;
	strtok(archivo, "\n");
	ssize_t size = obtener_size(archivo, &archivo_abierto);
	printf("Mostar: --%s-- size %d\n", archivo, size);
	char buffer[size];
	int i = 0;
	strcpy(buffer, "");
	read(archivo_abierto, buffer, size);
	while ((*(buffer +i) != '\0') && i+1 <=size) {
		if(*(buffer +i) > 0)
			printf("%c", *(buffer +i));
		i++;
	}
	close(archivo_abierto);
	return 0;
}

int copiar_archivo(char *archivo, char *nuevo_direcctorio){
	int archivo_abierto = 0;
	strtok(archivo, "\n");
	strtok(nuevo_direcctorio, "\n");
	
	ssize_t size = obtener_size(archivo, &archivo_abierto);
	printf("Copiar: --%s-- size %d\n", archivo, size);

	char buffer[size];
	strcpy(buffer, "");
	read(archivo_abierto, buffer, size);

	close(archivo_abierto);
	chdir(nuevo_direcctorio);
	int archivo_nuevo = open(archivo, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, 0777);
	write(archivo_nuevo, buffer, size);
	close(archivo_nuevo);
	chdir("..");
	return 0;
}

int main(int argc, char *argv[]) {
	char archivo[100];
	int eleccion = 0;
	char continuar = 's';
	char directorio[100];
	int c;
	printf("Mostar contenido de un archivo o copiar archivos\n");
	while(continuar == 's'){
		strcpy(archivo, "");
		strcpy(directorio, "");
		printf("%s\n", "Qué quieres hacer?");
		printf("%s\n", "Mostar contenido de un archivo........(1)");
		printf("%s\n", "Copiar archivos.......................(2)");
		scanf("%d", &eleccion);
		do{
    		c = getchar();
		}while(c != EOF && c != '\n');
		if (eleccion == 1) {
			printf("Escribe el nombre del archivo a mostar:\n");
			fflush(stdin);
			fgets(archivo, 100, stdin);
			printf("Mostrando contenido del archivo %s\n", archivo);
			mostar_contenido(archivo);
		} else if (eleccion == 2) {
			printf("Escribe el nombre del archivo a copiar: ");
			fgets(archivo, 100, stdin);
			printf("Escribe ruta del directorio destino: ");
			fgets(directorio, 100, stdin);
			copiar_archivo(archivo, directorio);
		} else {
			printf("%s\n", "Accion no valida");
		}
		printf("\n");
		printf("%s\n", "Volver a realizar alguna accion? [s/n]");
		scanf(" %c", &continuar);
	}
	printf("\n");
	return 0;
}