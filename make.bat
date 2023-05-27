	nasm -f win64 fast.asm -o fast.o
	gcc -c aes.c
	gcc -c main.c
	gcc -o main.exe -w main.o aes.o fast.o -O4
