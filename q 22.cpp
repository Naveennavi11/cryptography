#include <stdio.h>
#include <stdint.h>
#include <string.h>


void initial_permutation(uint8_t *block) {
    uint8_t temp = *block;
    *block = ((temp & 0x80) >> 7) | ((temp & 0x40) >> 5) | ((temp & 0x20) >> 3) | ((temp & 0x10) >> 1) |
             ((temp & 0x08) << 1) | ((temp & 0x04) << 3) | ((temp & 0x02) << 5) | ((temp & 0x01) << 7);
}

void inverse_permutation(uint8_t *block) {
    uint8_t temp = *block;
    *block = ((temp & 0x80) >> 7) | ((temp & 0x40) >> 5) | ((temp & 0x20) >> 3) | ((temp & 0x10) >> 1) |
             ((temp & 0x08) << 1) | ((temp & 0x04) << 3) | ((temp & 0x02) << 5) | ((temp & 0x01) << 7);
}


uint8_t sdes(uint8_t input, uint8_t key, int mode) {
   
    initial_permutation(&input);

   
    uint8_t left = (input & 0xF0) >> 4;
    uint8_t right = input & 0x0F;

    
    uint8_t temp = right;
    if (mode == 0) {  
        right = left ^ (right ^ key);
    } else {  
        left = right ^ (left ^ key);
    }
    left = temp;

   
    input = (left << 4) | right;

   
    inverse_permutation(&input);

    return input;
}


void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, uint8_t iv, size_t length) {
    uint8_t block, prev_block = iv;

    for (size_t i = 0; i < length; i++) {
        block = plaintext[i] ^ prev_block;
        ciphertext[i] = sdes(block, key, 0);
        prev_block = ciphertext[i];
    }
}


void cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t key, uint8_t iv, size_t length) {
    uint8_t block, prev_block = iv;

    for (size_t i = 0; i < length; i++) {
        block = sdes(ciphertext[i], key, 1);
        plaintext[i] = block ^ prev_block;
        prev_block = ciphertext[i];
    }
}

int main() {
    uint8_t iv = 0xAA;  
    uint8_t key = 0xFD; 
    uint8_t plaintext[] = {0x01, 0x23}; 
    size_t length = sizeof(plaintext) / sizeof(plaintext[0]);

    uint8_t ciphertext[length];
    uint8_t decrypted[length];

   
    cbc_encrypt(plaintext, ciphertext, key, iv, length);

    
    cbc_decrypt(ciphertext, decrypted, key, iv, length);

    
    printf("Plaintext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    printf("Ciphertext: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    printf("Decrypted: ");
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", decrypted[i]);
    }
    printf("\n");

    return 0;
}
