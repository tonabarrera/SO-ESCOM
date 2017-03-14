segment .data
    handleConsola dd 1 ;Primer argumento para la llamada al sistema _WriteConsoleA()
    cadImprimir db 'Ensamblador en Windows',0xA ;Segundo argumento para la llamada al sistema _WriteConsoleA()
    longitudCadena dd 1 ;Tercer argumento para la llamada al sistema _WriteConsoleA()
    caractEscritos dd 1 ;Cuarto ya saben que
    ultimoArgumento dd 1 ;Ultimo
segment .text
global _main
extern _GetStdHandle@4 ;Acceso externo a la llamada al sistema _GetStdHandle()
extern _WriteConsoleA@20 ;Acceso externo a la llamada al sistema _WriteConsoleA()
extern _ExitProcess@4 ;Acceso externo a la llamada al sistema _ExitProcess()

_main: push dword -11 ;Argumento pasado por la pila y usado en _GetStdHandle para la salida estandar
    call _GetStdHandle@4 ;Invocacion _GetStdHandle()
    mov [handleConsola],eax ;Devolucion del manejador de consola para escritura en el registro eax

    xor eax,eax ;Limpieza del registro eax (eax=0)
    mov eax,23d ;eax=23 caracteres de longitud de la cadena a imprimir
    mov [longitudCadena],eax ;Se guarda la langitud en memoria
    xor eax,eax ;Limpieza del registro eax (eax=0)
    mov eax,0d ;eax=0 valor del ultimo argumento de _WriteConsoleA()
    mov [ultimoArgumento],eax ;Se guarda el valor del ultimo argumento en memoria

    push dword [ultimoArgumento] ;Quinto argumento
    push dword caractEscritos ;Cuarto argumento
    push dword [longitudCadena] ;Tercer argumento
    push dword cadImprimir ;Segundo argumento de _WriteConsoleA() pasado por la pila
    push dword [handleConsola] ;Primer argumento pasado por la pila
    call _WriteConsoleA@20 ;Invocacion de _WriteConsoleA()

    xor eax,eax ;Limpieza del registro eax (eax=0)
    mov eax,0d ;eax=0 valor del argumento _ExitProcess()
    mov [ultimoArgumento],eax ;Se guarda el valor del arguemento en memoria
    push dword [ultimoArgumento] ;Argumento de _ExitProcess() pasado por pila
    call _ExitProcess@4 ;Invocacion de _ExitProcess()
