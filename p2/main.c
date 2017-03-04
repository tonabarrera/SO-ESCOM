#include <string.h>     /* Función strlen() */
#include <fcntl.h>      /* Modos de apertura y función open()*/
#include <stdlib.h>     /* Funciones write() y close() */

int main ( int argc, char* argv[] )
{
   /* Cadena que se va a escribir */
   const char* cadena = "Hola, mundo";

   /* Creación y apertura del fichero */
   int fichero = open ("mi_fichero", O_CREAT|O_WRONLY,0644);

   /* Comprobación de errores */
   if (fichero==-1)
   {
        perror("Error al abrir fichero:");
        exit(1);
   }

   /* Escritura de la cadena */
   write(fichero, cadena, strlen(cadena));
   close(fichero);
   return 0;

}


