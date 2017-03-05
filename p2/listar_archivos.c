#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

char *ordenar(char *fecha);

int main(int argc, char *argv[]) {
	struct stat datos_archivo;
	DIR *direccion;
	struct dirent *archivo;
	char path_carpeta[250];
	printf("%s\n", "Listar archivos");
	printf("%s\n", "¿Qué directorio quieres? (teclea '.' para el actual):");
	fgets (path_carpeta, 250, stdin);
	size_t salto = strlen(path_carpeta)-1;
	if (path_carpeta[salto] == '\n')
    	path_carpeta[salto] = '\0';
	strcat(path_carpeta, "/");
	direccion = opendir(path_carpeta);
	printf("%s %s\n", "Mostrando archivos del directorio: ", path_carpeta);
	printf("Nombre\t\tTamaño (Bytes) \t\t Ultimo accesso \t \n");
	while((archivo=readdir(direccion)) != NULL){
		if (strcmp(archivo->d_name, ".") && strcmp(archivo->d_name, "..") ){
     		printf("%s\t", archivo->d_name);
     		stat(strcat(path_carpeta, archivo->d_name), &datos_archivo);
			printf("%ld\t\t\t", datos_archivo.st_size);
			printf("%s \n", ordenar(ctime(&datos_archivo.st_atim.tv_sec)));
		}
	}
	return 0;
}

char *ordenar(char *fecha){
	int i = 0;
	char *fecha2 = (char *) malloc(strlen(fecha));
	char *split;
	char hora[8];
	split = strtok(fecha, " \n");
	strcpy(fecha2, "");
	while (split != NULL) {
		if (i == 3){
			strcpy(hora, split);
		} else {
			strcat(fecha2, split);
			strcat(fecha2, " ");
		}
		split = strtok(NULL, " \n");
		i++;
	}
	strcat(fecha2, hora);
	return fecha2;
}