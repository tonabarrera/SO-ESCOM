codigo=ejemplo1.c
objeto=$(codigo:.c=.o)
ejecutable=$(codigo:.c=.out)

run:$(ejecutable)
	./$(ejecutable)
$(ejecutable):$(objeto)
	gcc $(objeto) -o $@
$(objeto):$(codigo)
	gcc -c -Wall $<
clear:
	rm $(ejecutable) $(objeto)
