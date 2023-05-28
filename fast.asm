    extern GaloisMul
    global _ShiftRows
    global _MixColumn
    global _Sbox
    section .text
;rcx -> address of block
;rax -> scratch
;rdx -> temp storage
    _ShiftRows:
        mov dl, [rcx + 1]
        mov al, [rcx + 5]
        mov [rcx + 1], al
        mov al, [rcx + 9]
        mov [rcx + 5], al
        mov al, [rcx + 13]
        mov [rcx + 9], al
        mov [rcx + 13], dl

        mov dl, [rcx + 2]
        mov al, [rcx + 10]
        mov [rcx + 2], al
        mov [rcx + 10], dl

        mov dl, [rcx + 6]
        mov al, [rcx + 14]
        mov [rcx + 6], al
        mov [rcx + 14], dl

        mov dl, [rcx + 3]
        mov al, [rcx + 15]
        mov [rcx + 3], al
        mov al, [rcx + 11]
        mov [rcx + 15], al
        mov al, [rcx + 7]
        mov [rcx + 11], al
        mov [rcx + 7], dl
        mov eax, 0
        ret

;rcx pointer to 4 bytes
;rdx unsigned char** table

    _MixColumn:
        push r12
        push rbx
        xor r12, r12
        xor r8, r8
        xor r9, r9
        xor r10, r10
        xor r11, r11
        mov r8b, [rcx]
        mov r9b, [rcx + 1]
        mov r10b, [rcx + 2]
        mov r11b, [rcx + 3]
        mov rbx, rcx
        lea rcx, [rdx + 2 * 256 + r8]
        xor r12b, [rcx]
        lea rcx, [rdx + 3 * 256 + r9]
        xor r12b, [rcx]
        xor r12b, r10b
        xor r12b, r11b
        mov [rbx], r12b
        ;;
        mov r12b, r8b
        lea rcx, [rdx + 2 * 256 + r9]
        xor r12b, [rcx]
        lea rcx, [rdx + 3 * 256 + r10]
        xor r12b, [rcx]
        xor r12b, r11b
        mov [rbx+1], r12b
        mov r12b, r8b
        xor r12b, r9b
        lea rcx, [rdx + 2 * 256 + r10]
        xor r12b, [rcx]
        lea rcx, [rdx + 3 * 256 + r11]
        xor r12b, [rcx]
        mov [rbx+2], r12b
        xor r12b, r12b
        ;;
        lea rcx, [rdx + 3 * 256 + r8]
        xor r12b, [rcx]
        xor r12b, r9b
        xor r12b, r10b
        lea rcx, [rdx + 2 * 256 + r11]
        xor r12b, [rcx]
        mov [rbx+3], r12b
        pop rbx
        pop r12
        mov eax, 0
        ret

;rcx = pointer to bytes to substitute
;rdx = table to substiture from
    _Sbox:
        mov rax, 15
        xor r10, r10

    _Sbox_back:
        cmp rax, 0
        jge _Sbox_Cycle
        ret
    _Sbox_Cycle:
        lea r9, [rcx + rax]
        mov r10b, [r9]
        lea r8, [rdx + r10]
        mov r8b, [r8]
        mov [r9], r8b
        dec rax
        jmp _Sbox_back
