# fast-aes
Fast AES implementation in C and x86 windows, sadly wihtout SIMD, because my cpu does not support avx512 :-(.
Platform is windows and the code will not work on other architectures, due to the ABI calling conventions difference in windows and Linux.

To compile on windows you need nasm and gcc.

Fast is a massive overstatement, since I do not have access to SIMD instruction set, which would really help. 
Current speed is 1Gb per 34 seconds, so -> so about 32mb/s which is quite poor, in comparison with 24gbit in industrial implementations

Inspired by Professor Paar Cryptography lectures, [check them out](https://www.youtube.com/@introductiontocryptography4223)
