#include "constants.c"

extern void _ShiftRows(unsigned char*[]);
extern void _invShiftRows(unsigned char*[]);
extern void _MixColumn(unsigned long* operand, void* table);
extern void _invMixColumn(unsigned long* operand, void* table);
extern void _Sbox(unsigned char* list, void* table);
extern void _KeyAdd(unsigned char* block, unsigned char* key);

union bl128{
    unsigned long ints[4];
    unsigned char bytes[16];
}typedef bl128;

union bl32{
    unsigned long i;
    unsigned char bytes[4];
} typedef bl32;

void Decrypt(bl128* restrict block, bl128* KeyList){
    unsigned char* ptr = &(block->bytes[0]);
    _KeyAdd(ptr, &((KeyList[10]).bytes[0]));
    _invShiftRows(ptr);
    _Sbox(ptr, rsbox);
    for (int i = 9; i > 0; --i){
        _KeyAdd(ptr, &(KeyList[i].bytes[0]));
        for (int j = 0; j < 4; ++j){
            _invMixColumn(&(block->ints[j]), MultiplicationTable);
        }
        _invShiftRows(ptr);
        _Sbox(ptr, rsbox);
    }
    _KeyAdd(ptr, &((*KeyList).bytes[0]));
}

void Encrypt(bl128* restrict block, bl128* KeyList){
    unsigned char* ptr = &(block->bytes[0]);
    _KeyAdd(ptr, &((*KeyList).bytes[0]));
    for (int i = 0; i < 9; ++i){
        // CipherRound(block, KeyList[i+1]);
        _Sbox(ptr, sbox);
        _ShiftRows(ptr);
        for (int j = 0; j < 4; ++j){
            _MixColumn(&(block->ints[j]), MultiplicationTable);
        }
        _KeyAdd(ptr, &(KeyList[i+1].bytes[0]));
    }
    _Sbox(ptr, sbox);
    _ShiftRows((unsigned char**)block->bytes);
    _KeyAdd(ptr, &((KeyList[10]).bytes[0]));
}

void CopyBlock(bl128 src, bl128* dest){
    for (int i = 0; i< 4; ++i){
        dest->ints[i]=src.ints[i];
    }
}

unsigned long G(unsigned long i32, int i){
    bl32 a;
    a.i = i32;
    unsigned char temp = a.bytes[0];
    a.bytes[0] = sbox[a.bytes[1]] ^ RC[i+1 % 10];
    a.bytes[1] = sbox[a.bytes[2]];
    a.bytes[2] = sbox[a.bytes[3]];
    a.bytes[3] = sbox[temp];
    return a.i;
}


void KeyScheduler(bl128 MasterKey, bl128* dest){
    bl128 tmp = MasterKey;
    bl128 scratch;
    CopyBlock(tmp, dest);
    for(int i = 0; i<10;++i){
        scratch.ints[0]  = G(tmp.ints[3], i) ^ tmp.ints[0];
        scratch.ints[1] = scratch.ints[0] ^ tmp.ints[1];
        scratch.ints[2] = scratch.ints[1] ^ tmp.ints[2];
        scratch.ints[3] = scratch.ints[2] ^ tmp.ints[3];
        CopyBlock(scratch, &(dest[i+1]));
        CopyBlock(scratch, &tmp);
    }
}

