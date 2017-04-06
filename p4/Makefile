codigo=ejercicio5.c
libreria=funciones5.c
objeto=$(codigo:.c=.o)
lib=$(libreria:.c=.o)
ejecutable=$(codigo:.c=.out)

run:$(ejecutable)
	./$(ejecutable)
$(ejecutable):$(objeto) $(lib)
	gcc $(objeto) $(lib) -o $@
$(objeto):$(codigo)
	gcc -c -Wall $<
$(lib):$(libreria)
	gcc -c -Wall $<
clear:
	rm $(ejecutable) $(objeto) $(lib)
