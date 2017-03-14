segment data ;Segmento de datos
cadena db 'Programando en ensamblador para Linux',0xA ;Cadena a imprimir
segment .text ;Segmento de codigo
global _start ;Punto de entrada al programa (usado en el enlazador ld)
_start: ;Inicio del programa
    mov edx,38d ;Longitud de Cadena
    mov ecx,cadena ;Cadena a escribir
    mov ebx,1 ;Salida estandar
    mov eax,4 ;Numero de llamada al sistema sys_write
    int 0x80 ;Interrupcion de llamadas al sistema del kernel de Linux
    mov eax,1 ;Numero de llamadas al sistema sys_exit
    int 0x80 ;Interrupcion de llamadas al sisema del kernel de Linux
