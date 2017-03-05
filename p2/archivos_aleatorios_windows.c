#include <stdio.h>
#include <direct.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>     /* Función strlen() */
#include <fcntl.h>      /* Modos de apertura y función open()*/
#include <stdlib.h>     /* Funciones write() y close() */

int main ( int argc, char* argv[] ){
   /* Cadena que se va a escribir */
   char* cadena[15];
   cadena[0]="perro   ";
   cadena[1]="gato    ";
   cadena[2]="liebre  ";
   cadena[3]="leon    ";
   cadena[4]="jirafa  ";
   cadena[5]="elefante";
   cadena[6]="cebra   ";
   cadena[7]="gallina ";
   cadena[8]="conejo  ";
   cadena[9]="delfin  ";
   cadena[10]="koala  ";
   cadena[11]="oso    ";
   cadena[12]="pez    ";
   cadena[13]="loro   ";
   cadena[14]="tigre  ";

   char* nombre[15];
   nombre[0]="archivo1";
   nombre[1]="archivo2";
   nombre[2]="archivo3";
   nombre[3]="archivo4";
   nombre[4]="archivo5";
   nombre[5]="archivo6";
   nombre[6]="archivo7";
   nombre[7]="archivo8";
   nombre[8]="archivo9";
   nombre[9]="archivo10";
   nombre[10]="archivo11";
   nombre[11]="archivo12";
   nombre[12]="archivo13";
   nombre[13]="archivo14";
   nombre[14]="archivo15";

   int i=0;
   srand(time(NULL));
   int numero_arch = rand()%15;
   char nombre_dir[30];

   printf("Se crearan %d archivos, ingresa el nombre que pondras a tu directorio:\n", numero_arch);
   scanf("%s",nombre_dir);
   mkdir(nombre_dir);
   chdir(nombre_dir);
   //int dir = mkdir(nombre_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   //int algo = chdir(nombre_dir);

for ( i = 0; i < numero_arch; i++) {
  int contenido = rand()%15;

   int fichero = open (nombre[i], O_CREAT|O_WRONLY,0644); /* Creación y apertura del fichero */


   if (fichero==-1){/* Comprobación de errores */

        printf("Error al abrir fichero:");
        exit(1);
   }
   write(fichero, cadena[contenido], strlen(cadena[contenido]));/* Escritura de la cadena */
   close(fichero);

   }
   return 0;

}

