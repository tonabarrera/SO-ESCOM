;nasm -f win32 G:\operativos\ensamblador\calculadora.asm
;ld calculadora.obj -m i386pe -e _main -L C:\MinGW\mingw32\bin -l kernel32 -o c.exe

global _main  ;este es el main del programa

extern _ExitProcess@4 ;windows api para llamar a exit del proceso
extern _GetStdHandle@4  ;windows api para el standard output handle
extern _WriteFile@20 ;api de windows para escribir
extern _ReadFile@20 ;api .. leer

section .data
  menu db 'Ingresa una opcion:', 0x0A, '1. Suma', 0x0A, '2. Resta', 0x0A, '3. Multiplicacion', 0x0A, '4. Division', 0x0A ; 67
  pedirNum1 db 'Ingresa el primer numero: ' ;26
  pedirNum2 db 'Ingresa el segundo numero: ' ;27
  prueba db 'si me meti',0x0A ;11

  manejador_lectura dd 0
  manejador_escritura dd 0
  bytesEscritos dd 0

  bytesLeidosOpcion dd 0
  bytesLeidosNum1 dd 0
  bytesLeidosNum2 dd 0

section .bss
  opcionLetra resb 10
  num1Letra resb 10
  num2Letra resb 10
  resultadoLetra resb 10
  opcion resd 1
  num1 resd 1
  num2 resd 1
  resultado resd 1
  lenResultadoLetra resd 1

section .code

  intToInt:
    xor ecx, ecx
    xor ebx, ebx
    mov ebx, 10
    .pilazo:
      xor edx, edx
      div ebx
      push dx
      inc cl
      test eax, eax
      jnz .pilazo

    mov ebx, ecx

    .despilazo:
      pop ax
      or al, 0x30
      mov byte [edi], al
      inc edi
      sub cl, 1
      jnz .despilazo

    mov byte[edi], 0
    mov eax, ebx
    ret


  strToInt:
    xor eax, eax
    xor edx, edx

    .ciclo:
      mov dl, byte [esi]

      cmp dl, 10
      je .terminar
      cmp dl, 13
      je .terminar
      cmp dl, 0
      je .terminar

      lea eax, [eax*5]
      add eax, eax
      add esi, 1
      and dl, 0x0F
      add eax, edx
      jmp .ciclo

    .terminar:
      ret

  _main:
    ;iniciamos el manejador de lectura
    push -10
    call _GetStdHandle@4
    mov [manejador_lectura], eax

    ;iniciamos el manejador de escritura
    push -11
    call _GetStdHandle@4
    mov [manejador_escritura], eax

    ;imprimimos el menu
    push 0
    push bytesEscritos
    push 67
    push menu
    push dword [manejador_escritura]
    call _WriteFile@20

    ;leemos la opcion elegida
    push 0
    push bytesLeidosOpcion
    push dword 10
    push dword opcionLetra
    push dword [manejador_lectura]
    call _ReadFile@20

    ;pedimos el primer numero y lo leemos
    push 0
    push bytesEscritos
    push 26
    push pedirNum1
    push dword [manejador_escritura]
    call _WriteFile@20

    push 0
    push bytesLeidosNum1
    push dword 10
    push dword num1Letra
    push dword [manejador_lectura]
    call _ReadFile@20

    ;pedimos el segundo numero y lo leemos
    push 0
    push bytesEscritos
    push 26
    push pedirNum2
    push dword [manejador_escritura]
    call _WriteFile@20

    push 0
    push bytesLeidosNum2
    push dword 10
    push dword num2Letra
    push dword [manejador_lectura]
    call _ReadFile@20

    ;convertimos nuestros datos
    mov esi, opcionLetra
    call strToInt
    mov [opcion], eax

    mov esi, num1Letra
    call strToInt
    mov [num1], eax

    mov esi, num2Letra
    call strToInt
    mov [num2], eax

    ;vemos cual fue la opcion que eligio el usuario
    mov eax, [opcion]
    cmp al, 1
    je sumar
    cmp al, 2
    je restar
    cmp al, 3
    je multiplicar
    cmp al, 4
    je dividir

    jmp fin

    sumar:
      xor eax, eax
      mov eax, [num1]
      add eax, [num2]
      mov [resultado], eax
      jmp imprimir

    restar:
      xor eax, eax
      mov eax, [num1]
      sub eax, [num2]
      mov [resultado], eax
      jmp imprimir

    multiplicar:
      xor eax, eax
      xor edx, edx
      mov eax, [num1]
      mul dword [num2]
      mov [resultado], eax
      jmp imprimir

    dividir:
      xor eax, eax
      xor edx, edx
      mov eax, [num1]
      div dword [num2]
      mov [resultado], eax
      jmp imprimir

    imprimir:
      ;convertimos el resultado a string
      mov eax, [resultado]
      mov edi, resultadoLetra
      call intToInt
      mov [lenResultadoLetra], eax

      ;ahora si imprimimos
      push 0
      push bytesEscritos
      push dword [lenResultadoLetra]
      push resultadoLetra
      push dword [manejador_escritura]
      call _WriteFile@20

    ;Nos salimos del programa
    fin:
      push 0
      call _ExitProcess@4
