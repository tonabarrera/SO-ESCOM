codigo=ejercicio1.c
extra=matrices.c
flags=-Wall
objeto=$(codigo:.c=.o)
obj_extra=$(extra:.c=.o)
exec=$(codigo:.c=.out)
exec_extra=$(extra:.c=.out)

run:$(exec)
	./$(exec)
$(exec):$(objeto) $(obj_extra)
	gcc $(objeto) $(obj_extra) -lpthread -o $@
$(exec_extra):$(obj_extra)
	gcc $(obj_extra) -o $@
$(objeto):$(codigo)
	gcc -c $(flags) $<
$(obj_extra):$(extra)
	gcc -c $(flags) $<
clear:
	rm *.out *.o *.txt
