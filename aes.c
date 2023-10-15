#include "constants.c"
// #include "includes.h"


extern void _ShiftRows(unsigned char*[]);
extern void _invShiftRows(unsigned char*[]);
extern void _MixColumn(unsigned long* operand, void* table);
extern void _invMixColumn(unsigned long* operand, void* table);
extern void _Sbox(unsigned char* list, void* table);
extern void _KeyAdd(unsigned char* block, unsigned char* key);

// void PrintBlock(unsigned char* block){
//     for (int i =0; i <16;++i){
//         printf("%x ", block[i]);
//     }
// }

void Decrypt(unsigned char* block, unsigned char** KeyList){
    _KeyAdd(block, &KeyList[10]);
    _invShiftRows(block);
    _Sbox(block, rsbox);
    for (int i = 9; i > 0; --i){
        _KeyAdd(block, &KeyList[i]);
        for (int j = 0; j < 4; ++j){
            _invMixColumn(block + j * sizeof(unsigned long), MultiplicationTable);
        }
        _invShiftRows(block);
        _Sbox(block, rsbox);
    }
    _KeyAdd(block, &KeyList[0]);
}

void Encrypt(unsigned char* block, unsigned char** KeyList){
    _KeyAdd(block,&KeyList[0]);
    for (int i = 0; i < 9; ++i){
        _Sbox(block, sbox);
        _ShiftRows(block);
        for (int j = 0; j < 4; ++j){
            _MixColumn(block + j * sizeof(int), MultiplicationTable);
        }
        _KeyAdd(block, &(KeyList[i+1]));
    }
    _Sbox(block, sbox);
    _ShiftRows(block);
    _KeyAdd(block, &KeyList[10]);
}

void CopyBlock(unsigned char* src, unsigned char* dest){
    for (int i = 0; i< 16; ++i){
        dest[i]=src[i];
    }
}

void G(unsigned char* i32, int i, unsigned char* dest){
    unsigned char temp = i32[0];
    i32[0] = sbox[i32[1]] ^ RC[i+1 % 10];
    i32[1] = sbox[i32[2]];
    i32[2] = sbox[i32[3]];
    i32[3] = sbox[temp];
}

void XorI32(unsigned char* op1, unsigned char* op2, unsigned char* dest){
    *((unsigned long*)dest) =  *((unsigned long*)op1) ^ *((unsigned long*)op2);
}

void KeyScheduler(unsigned char* MasterKey, unsigned char** dest){
    unsigned char tmp[16];
    unsigned char scratch[16];
    unsigned char G_storage[4] = {0,0,0,0};
    CopyBlock(MasterKey, &tmp);
    CopyBlock(tmp, &(dest[0]));
    for(int i = 0; i<10;++i){
        G(&(tmp[3 * sizeof(unsigned long)]), i, G_storage);
        XorI32(G_storage, &(tmp[0 * sizeof(unsigned long)]), &(scratch[0 * sizeof(unsigned long)]));
        XorI32(&(scratch[0 * sizeof(unsigned long)]), &(tmp[1 * sizeof(unsigned long)]), &(scratch[1 * sizeof(unsigned long)]));
        XorI32(&(scratch[1 * sizeof(unsigned long)]), &(tmp[2 * sizeof(unsigned long)]), &(scratch[2 * sizeof(unsigned long)]));
        XorI32(&(scratch[2 * sizeof(unsigned long)]), &(tmp[3 * sizeof(unsigned long)]), &(scratch[3 * sizeof(unsigned long)]));
        CopyBlock(scratch, &(dest[i+1]));
        CopyBlock(scratch, tmp);
    }
}

