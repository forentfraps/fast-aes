# fast-aes
Fast AES implementation in C and x86 windows, sadly wihtout SIMD, because my cpu does not support avx512 :-(.
Platform is windows and the code will not work on other architectures, due to the ABI calling conventions difference in windows and Linux.

To compile on windows you need nasm and gcc.

Inspired by Professor Paar Cryptography lectures, [check them out](https://www.youtube.com/@introductiontocryptography4223)
