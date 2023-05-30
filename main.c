/* 64 bit windows */
#include "includes.h"
#include <time.h>




int main(void)
{
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
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
    clock_t s0 = clock();
    for (int i = 0; i <67108864; ++i){
        Encrypt(&plaintext,(bl128*) &KeyList);
    }
    clock_t s1 = clock();
    printf("TIME IS -> %lf\n", (double)(s1-s0)/CLOCKS_PER_SEC);
    printf("CIPHERTEXT\n");
    for (int i =0; i <16;++i){
        printf("%x ", plaintext.bytes[i]);
    }
    printf("\n");
    // free(KeyList);
    return 0;
}
