	nasm -f win64 fast.asm -o fast.o
	gcc -c aes.c -Ofast -nostdlib -w -static
	@REM gcc -c main.c
	@REM gcc -o main.exe -w main.o aes.o fast.o -Ofast
	@REM del *.o
	ld -relocatable fast.o aes.o -o AES_static.o
	strip AES_static.o
	del aes.o
	del fast.o
