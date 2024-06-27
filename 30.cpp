#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned int encrypt(unsigned int key, unsigned int block) {
    return block ^ key;
}
unsigned int cbc_mac_one_block(unsigned int key, unsigned int block) {
    return encrypt(key, block);
}
unsigned int cbc_mac_two_blocks(unsigned int key, unsigned int block1, unsigned int block2) {
    unsigned int intermediate = encrypt(key, block1);
    unsigned int combined = block2 ^ intermediate;
    return encrypt(key, combined);
}
int main() {
    unsigned int key = 0x5A;     
    unsigned int X = 0x12;      
    unsigned int T = cbc_mac_one_block(key, X);
    printf("MAC(K, X) = %02X\n", T);
    unsigned int X_xor_T = X ^ T;
    unsigned int T_prime = cbc_mac_two_blocks(key, X, X_xor_T);
    printf("MAC(K, X || (X ? T)) = %02X\n", T_prime);
    return 0;
}