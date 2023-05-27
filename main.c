/* 64 bit linux. */
#include "includes.h"
#include <time.h>




int main(void)
{
    const char hwText[] = "Hello world! \n";
    bl128 plaintext;
    bl128 KeyList[11];
    for(int i = 0; i < 16; ++i){
        plaintext.bytes[i] = i;
    }
    bl128 MasterKey;
    for (int i = 0; i< 16; ++i){
        MasterKey.bytes[i] = i*16 + i;
    }
    for (int i =0; i <16;++i){
        printf("%x ", plaintext.bytes[i]);
    }
    printf("\n");
    KeyScheduler(MasterKey, KeyList);
    printf("KEYS DONE\n");
    Encrypt(&plaintext,(bl128*) &KeyList);
    printf("CIPHERTEXT\n");
    for (int i =0; i <16;++i){
        printf("%x ", plaintext.bytes[i]);
    }
    printf("\n");
    // free(KeyList);
    return 0;
}