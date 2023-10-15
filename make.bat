	nasm -f win64 fast.asm -o fast.o
	gcc -c aes.c -Ofast -nostdlib -w -static
	ld -relocatable fast.o aes.o -o AES_static.o
	@REM gcc -c main.c
	@REM gcc -o main.exe -w main.o aes.o fast.o -Ofast
	@REM del *.o
	del aes.o
	del fast.o
