run:contador_linux
	./contador_linux
contador_linux:contador_linux.o
	ld -m  elf_i386 contador_linux.o -o contador_linux
contador_linux.o:contador_linux.asm
	nasm -f elf contador_linux.asm -o contador_linux.o
clear:
	rm contador_linux.o contador_linux
