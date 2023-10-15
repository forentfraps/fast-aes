# fast-aes
Fast AES implementation in C and x86 windows, sadly wihtout SIMD, because my cpu does not support avx512 :-(
Platform is windows and the code will not work on other architectures, due to the ABI calling conventions difference in windows and Linux.

To compile on windows you need nasm and gcc.
Resulting object file is statically linked.

Fast is a massive overstatement, since I do not have access to SIMD instruction set, which would really help. 
Current speed is 1Gb per 15.9 seconds, so -> so about 64.4 mb/s which is quite poor, in comparison with 24gbit in industrial implementations
Decryption would be a bit slower due to unfortunate coeffitients in inverse mix column matrix

Inspired by Professor Paar Cryptography lectures, [check them out](https://www.youtube.com/@introductiontocryptography4223)
