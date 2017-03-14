segment .bss ;Segmento de datos
cadena resb 50 ;Espacio de memoria para la cadena almacenar
segment .text ;Segmento de codigo
global _start ;Punto de entrada al programa (usado en el enlazador ld)
_start: ;Inicio del programa
    mov edx,50d ;Longitud del buffer
    mov ecx,cadena ;Cadena a leer
    mov ebx,0 ;Entrada estandar
    mov eax,3 ;Numero de llamada al sistema sys_read
    int 0x80 ;Interrupcion de llamadas al sistema del kernel de Linux
    mov edx,50d ;Longitud de cadena
    mov ecx,cadena ;Cadena a escribir
    mov ebx,1 ;Salida estandar
    mov eax,4 ;Numero de llamadas al sistema sys_write
    int 0x80 ;Interrupcion de llamadas al sisema del kernel de Linux
    mov eax,1 ;Numero de llamadas al sistema sys_write
    int 0x80 ;Interrupcion de llamadas al sisema del kernel de Linux
