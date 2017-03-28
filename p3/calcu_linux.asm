segment .data

msg db 10,13,"CALCULADORA ",10,13,"seleccione la operacion que desea realizar:",10,13,"1-Suma",10,13,"2-Resta:",10,13,"3-Multiplicacion",10,13,"4-Division",10,13,"5-Salir",10,13
lenmsg equ $ - msg
msg1 db 10,13,"Ingrese el primer numero: ",10,13
lenmsg1 equ $ - msg1
msg2 db 10,13,"Ingrese el segundo numero: ",10,13
lenmsg2 equ $ - msg2
msg3 db 10,13,"El resultado es: ",10,13
lenmsg3 equ $ - msg3
msg4 db 10,13," ",10,13
lenmsg4 equ $ - msg4
msgsum db 10,13,"",10,13,"El resultado de la suma es: "
lenmsgsum equ $ - msgsum
msgres db 10,13,"",10,13,"El resultado de la resta es: "
lenmsgres equ $ - msgres
msgmul db 10,13,"",10,13,"El resultado de la ultiplicacion es: "
lenmsgmul equ $ - msgmul
msgdiv db 10,13,"",10,13,"El resultado de la division es: "
lenmsgdiv equ $ - msgdiv
msgresi db 10,13,"El residuo de la division es: "
lenmsgresi equ $ - msgresi

segment .bss
  seleccionStr resb 20
  num1Str resb 20
  num2Str resb 20
  resultadoStr resb 20
  residuoStr resb 20
  lenResultadoStr resb 20
  lenresiduoStr resb 20
  seleccion resd 1 ; resd reserva palabras dobles
  num1 resd 1
  num2 resd 1
  resultado resd 1
  residuo resd 1


segment .text
  global _start

  dectoeax:
      mov eax,0                     ; Inicializamos eax y edx, la primera para que guarde el resultado y la segunda guardará el residuo al termino
      mov edx, 0

      .ciclo:
      mov dl, byte [esi]              ; lee el caracter, recordando que esi contiene a la cadena
      cmp dl, 10                      ; se valida si dl=10
      je .final                      ; de ser cierta la condicion de arriba, se saldrá del ciclo y
      lea eax, [eax*4+eax]            ; EAX = 5 * EAX ...
      add eax, eax                    ; al final de estas operaciones es como un EAX = 10*EAX, pero la operacion como tal no se puede realizar
      add esi, 1                      ; se da un incremento en esi
      and dl, 0x0F                    ; obtenemos el numero, despues de convertir el caracter
      add eax, edx                    ; sumamos el numero al que obtendremos al final de los ciclos
      jmp .ciclo                       ; se llama a si mismo y entra de nuevo al ciclo

      .final:
      ret                              ;convertimos el entero y termina la funcion

  eaxtodec:
      mov ebx, 10
      mov ecx, 0

      .ciclo1:
      mov edx, 0                    ; inicializamos a edx en 0
      div ebx                         ; DX:AX / BX = AX remainder: DX
      push dx                         ; Se mantiene el residuo en la pila
      inc ecx                          ; incrementamos a ecx
      test eax, eax                   ;  se realiza la pregunta AX = 0?
      jnz .ciclo1                 ; en el caso de resultar un no como respuesta, se repite el ciclo1

      mov ebx, ecx                    ; se guarda la longitud del string

      .ciclo2:
      pop ax                          ; se sacan los digitos almacenados en la pila
      or ax, 00110000b                ; Alo convertimos a caracter
      mov byte [edi], al              ; se guarda en la posicion del arreglo
      inc edi                         ; se incrementa edi y pasa a la siguiente posicion
      loop .ciclo2               ; lo hará hasta que no queden digitos

      mov byte [edi], 0               ; Ees necesario para marcar el final del string
      ret

_start:
  mov eax, 4
  mov ebx, 1
  mov ecx, msg
  mov edx, lenmsg
  int 80h

  mov eax, 3 ;lectura desde teclado
  mov ebx, 2
  mov ecx, seleccionStr
  mov edx, 80
  int 80h
  ;---------------------------------------------------------
   mov esi, seleccionStr
   call dectoeax
   mov [seleccion], eax ; los corchetes acceden al contenido de la direccion y sin corchetes modifica la direccion
 ;_---------------------------------------------------------

 ;**************************
  mov eax, [seleccion]
  cmp al, 5 ; necesitamos saber si el usuario pidió salir antes de pedir los numeros
  je salir
  ;*************************

  mov eax, 4
  mov ebx, 1
  mov ecx, msg1
  mov edx, lenmsg1
  int 80h

  mov eax, 3 ;lectura desde teclado del numero 1
  mov ebx, 2
  mov ecx, num1Str
  mov edx, 80
  int 80h
  ;---------------------------------------------------------
   mov esi, num1Str
   call dectoeax
   mov [num1], eax ; los corchetes acceden al contenido de la direccion y sin corchetes modifica la direccion
 ;_---------------------------------------------------------
  mov eax, 4
  mov ebx, 1
  mov ecx, msg2
  mov edx, lenmsg2
  int 80h

  mov eax, 3 ;lectura desde teclado del numero 2
  mov ebx, 2
  mov ecx,num2Str
  mov edx, 80
  int 80h
  ;---------------------------------------------------------
   mov esi, num2Str
   call dectoeax
   mov [num2], eax ; los corchetes acceden al contenido de la direccion y sin corchetes modifica la direccion
 ;_---------------------------------------------------------

 mov eax, [seleccion]
 cmp al, 1 ;cmp compara
 je suma ;da un salto o redirecciona si la ultima comparativa se da
 cmp al, 2
 je resta
 cmp al, 3
 je multiplicacion
 cmp al, 4
 je division
 jmp salir

suma:
  xor eax, eax ;aqui guardaremos el resultado
  mov eax, [num1]
  add eax, [num2] ; add hace la sumatoria de num1 y num2, es como tener eax=num1+num2
  mov [resultado], eax

  mov eax, [resultado]
  mov edi, resultadoStr
  call eaxtodec
  mov [lenResultadoStr], ebx

  mov eax, 4
  mov ebx, 1
  mov ecx, msgsum
  mov edx, lenmsgsum
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, resultadoStr
  mov edx, [lenResultadoStr] ;se necesita poner entre parentesis para acceder al contenido de la direccion, si no imprime cosas bien locas
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, msg4
  mov edx, lenmsg4
  int 80h

  jmp _start

resta:
  xor eax, eax
  mov eax, [num1]
  sub eax, [num2] ; add hace la resta de num1 y num2, es como tener eax=num1-num2
  mov [resultado], eax

  mov eax, [resultado]
  mov edi, resultadoStr
  call eaxtodec
  mov [lenResultadoStr], ebx

  mov eax, 4
  mov ebx, 1
  mov ecx, msgres
  mov edx, lenmsgres
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, resultadoStr
  mov edx, [lenResultadoStr]
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, msg4
  mov edx, lenmsg4
  int 80h

  jmp _start

multiplicacion:
  xor edx, 0 ;inicializacion de edx a cero
  mov eax, [num1]
  mul dword[num2]
  mov [resultado], eax

  mov eax, [resultado]
  mov edi, resultadoStr
  call eaxtodec ; convierte el resultado a cadena para poderlo imprimir
  mov [lenResultadoStr], ebx

  mov eax, 4
  mov ebx, 1
  mov ecx, msgmul
  mov edx, lenmsgmul
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, resultadoStr ; imrpime resultado
  mov edx, [lenResultadoStr]
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, msg4 ;imrpime salto de linea
  mov edx, lenmsg4
  int 80h

  jmp _start

division:
  mov eax, 0
  mov edx, 0
  mov eax, [num1]
  div dword [num2]
  mov [resultado], eax ;guardamos el coeficiente como resultado
  mov [residuo],edx

  mov eax, [resultado]
  mov edi, resultadoStr
  call eaxtodec ;imprime el resultado de la division a cadena para poderlo imprimir
  mov [lenResultadoStr], ebx

  mov eax, 4
  mov ebx, 1
  mov ecx, msgdiv ;imprime mensaje de resultado de la division
  mov edx, lenmsgdiv
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, resultadoStr
  mov edx, [lenResultadoStr] ;imprime resultado
  int 80h

  mov eax, [residuo]
  mov edi, residuoStr
  call eaxtodec  ;convierte el residuo en una cadena para poderlo imprimir
  mov [lenresiduoStr], ebx

  mov eax, 4
  mov ebx, 1
  mov ecx, msgresi ;imprime mensaje de residuo
  mov edx, lenmsgresi
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, residuoStr ;imprime el residuo
  mov edx, [lenresiduoStr]
  int 80h

  mov eax, 4
  mov ebx, 1
  mov ecx, msg4 ;imprime salto de linea
  mov edx, lenmsg4
  int 80h

  jmp _start

salir:
  mov eax, 1 ;salimos del programa
  xor ebx, ebx
  int 80h
