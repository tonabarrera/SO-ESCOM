segment .data
    handleConsola dd 1
    cadenaImprimir db '0',10  ;El 10=0xA es para que haga un salto de linea
    longitudCadena dd 2 ;Es de tamaño dos ya que cuenta el salto de linea
    caractEscritos dd 1
    ultimoArgumento dd 1
    contador dd 0

segment .text
    global _main
    extern _GetStdHandle@4
    extern _WriteConsoleA@20
    extern _ExitProcess@4

_main: push dword -11
    call _GetStdHandle@4
    mov [handleConsola],eax ; Guardamos el manegador que retorna _GetStdHandle
    ;Tal vez el siguiente bloque debe de ir dentro del do-while
    xor eax,eax
    mov eax,2d
    mov [longitudCadena],eax
    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    ;Un poderoso do while
    ciclo:
        push dword [ultimoArgumento]
        push dword caractEscritos
        push dword [longitudCadena]
        push dword cadenaImprimir
        push dword [handleConsola]
        call _WriteConsoleA@20

        inc byte [cadenaImprimir] ;Agrega 1 byte al primer byte de nuestro numero
        inc dword [contador] ;Agrega 1 a la direccion de memoria
        mov eax, [contador] ;Lo cargamos
        cmp eax,10 ;if eax<10 entonces jb regresa al inicio de ciclo
        jb ciclo

    xor eax,eax
    mov eax,0d
    mov [ultimoArgumento],eax
    push dword [ultimoArgumento]
    call _ExitProcess@4
