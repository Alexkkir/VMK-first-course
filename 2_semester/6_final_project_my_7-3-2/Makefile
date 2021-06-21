all: clean prog
prog: main.o functions.o
	gcc -m32 functions.o main.o -lm -o prog
main.o: main.c
	gcc -c -o main.o main.c -m32 -lm
functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm
clean:
	rm -rf *.o prog
