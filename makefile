all:prog

main.o:main.c
	gcc -o main.o -c main.c -m32
func.o:func.asm
	nasm -f elf32 -o func.o func.asm
prog: main.o func.o
	gcc -o prog main.o func.o -m32
clean:
	rm -f *.o prog
