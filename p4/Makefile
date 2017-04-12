codigo=ejercicio5.c
libreria=funciones5.c
flags=-fno-stack-protector
objeto=$(codigo:.c=.o)
lib=$(libreria:.c=.o)
ejecutable=$(codigo:.c=.out)
ejecutable2=$(libreria:.c=.out)

run:$(ejecutable)
	./$(ejecutable)
$(ejecutable):$(objeto) $(lib)
	gcc $(objeto) $(lib) -o $@
$(ejecutable2):$(lib)
	gcc $(lib) -o $@
$(objeto):$(codigo)
	gcc -c -Wall $<
$(lib):$(libreria)
	gcc -c -Wall $<
clear:
	rm *.out *.o  *.txt
