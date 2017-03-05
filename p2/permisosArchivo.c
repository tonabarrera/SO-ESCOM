//Programa para cambiar los permisos de un archivo seleccionado por el usuario
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>     /* Funcion strlen() */
#include <fcntl.h>      /* Modos de apertura y funcion open()*/
#include <stdlib.h>     /* Funciones write() y close() */
#include <sys/types.h>
#include <ctype.h>

void cambiarPermisos(char *path);
int menuPermisos(void);
int iscad_num(char *string);

void cambiarPermisos(char *path){
    strtok(path, "\n");
    int fd = chdir(path);//cambiar de directorio
    int mod, fm;
    char fichero[25];//nombre del archivo 
    char path2[255];
    if(fd < 0){  printf("Error el directorio no existe\n");}
    else{
        printf("\nEscriba el nombre del archivo al que quiere cambiar los permisos:\n");
        fflush(stdin);
        strcpy(path2, "");
        strcpy(fichero, "");
        fgets(fichero, 25, stdin);
        strtok(fichero, "\n");
        fflush(stdin);
        strcat(path2, fichero);//A la ruta resultante le concatena el archivo
        mod = menuPermisos();//mod= bits del modo elegido
        fm = chmod(path2, mod);
        if(fm < 0)//Devuelve -1
            printf("\nError.No existe el fichero en el directorio\n");
        else
            printf("\nSe han cambiado los permisos del fichero con exito\n");   		 
    }
    fflush(stdin);
}

int menuPermisos(void){
    char usuario,grupo,otros;
    char cad[5];
    int c;
    system("clear");
    printf("\t\tPermisos\n");
    printf("\nCombinacion\tvalor\tDescripcion\n");
    printf("1. ---  \t  0 \tNo se tiene ningun permiso\n");
    printf("2. --x  \t  1 \tsolo permiso de ejecución\n");
    printf("3. -w-  \t  2 \tsolo permiso de escritura\n");
    printf("4. -wx  \t  3 \tperimiso de escritura y ejecucion\n");
    printf("5. r--  \t  4 \tsolo permiso de lectura\n");
    printf("6. r-x  \t  5 \tpermiso de lectura y ejecucion\n");
    printf("7. rw-  \t  6 \tpermiso de lectura y escritura\n");
    printf("8. rwx  \t  7 \ttodos los permisos\n");
    fflush(stdin);
    printf("\nIngrese el valor del permiso para usuario: ");
    scanf(" %c",&usuario);
    printf("Ingrese el valor del permiso para grupos: ");
    fflush(stdin);
    scanf(" %c",&grupo);
    printf("Ingrese el valor del permiso para otros: ");
    fflush(stdin);
    scanf(" %c",&otros);

    do{
        c = getchar();
    }while(c != EOF && c != '\n');

    cad[0]='0';
    cad[1]=usuario;
    cad[2]=grupo;
    cad[3]=otros;
    cad[4]='\0';

    if(iscad_num(cad)){//Si la cadena es numero (devuelve 1)
        if(atoi(cad)>777 || atoi(cad)<0){//valor fuera de rango, atoi(convierte la cadena de digitos a su numero correspondiente)
            printf("\nIngreso permisos no validos, porfavor vuelva a intentarlo\n");
            fflush(stdin);
            menuPermisos();
        }
    } else{
        printf("\nIngreso un caracter en vez de un numero, porfavor vuelva a intentarlo\n");
        fflush(stdin);
        menuPermisos();    
    }
    fflush(stdin);
    return strtol(cad,0,8);    
}

//Verifica si la cadena está compuesta por numeros
int iscad_num(char *string){
    int i;
    int valor=1;

    for(i=0;i<strlen(string);i++){
        if(!isdigit(string[i])){//Si no es digito, cadena no valida
            valor = 0;
            break;
        }
    }
    return valor;
}

int main(int argc, char *argv[]) {
    char rutaArchivo [250];
    printf("Ingrese la ruta donde se encuentra el archivo al que desea modificar los permisos:\n");
    fflush(stdin);
    fgets(rutaArchivo, 25, stdin);
    cambiarPermisos(rutaArchivo);
    return 0;
}

