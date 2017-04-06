codigo=ejemplo6.c
libreria=hola.c
objeto=$(codigo:.c=.o)
lib=$(libreria:.c=.o)
ejecutable=$(codigo:.c=.out)

run:$(ejecutable)
	./$(ejecutable)
$(ejecutable):$(objeto) 
	gcc $(objeto) -o $@
$(objeto):$(codigo)
	gcc -c -Wall $<
$(lib):$(libreria)
	gcc -c -Wall $<
clear:
	rm $(ejecutable) $(objeto) $(lib)
