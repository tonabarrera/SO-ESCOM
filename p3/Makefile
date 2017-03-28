run:calcu
	./calcu
calcu:calcu.o
	ld -m  elf_i386 calcu.o -o calcu
calcu.o:calcu.asm
	nasm -f elf calcu.asm -o calcu.o
clear:
	rm calcu.o calcu
