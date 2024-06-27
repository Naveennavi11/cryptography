#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BLOCK_SIZE 8
void xor_block(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}
void encrypt_ecb(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int length) {
    for (int i = 0; i < length / BLOCK_SIZE; i++) {
        xor_block(&plaintext[i * BLOCK_SIZE], key, &ciphertext[i * BLOCK_SIZE]);
    }
}
void decrypt_ecb(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext, int length) {
    for (int i = 0; i < length / BLOCK_SIZE; i++) {
        xor_block(&ciphertext[i * BLOCK_SIZE], key, &plaintext[i * BLOCK_SIZE]);
    }
}
void encrypt_cbc(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, int length) {
    uint8_t block[BLOCK_SIZE];
    memcpy(block, iv, BLOCK_SIZE);
    for (int i = 0; i < length / BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= plaintext[i * BLOCK_SIZE + j];
        }
        xor_block(block, key, &ciphertext[i * BLOCK_SIZE]);
        memcpy(block, &ciphertext[i * BLOCK_SIZE], BLOCK_SIZE);
    }
}
void decrypt_cbc(uint8_t *ciphertext, uint8_t *key, uint8_t *iv, uint8_t *plaintext, int length) {
    uint8_t block[BLOCK_SIZE];
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (int i = 0; i < length / BLOCK_SIZE; i++) {
        xor_block(&ciphertext[i * BLOCK_SIZE], key, block);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] = block[j] ^ prev_block[j];
        }
        memcpy(prev_block, &ciphertext[i * BLOCK_SIZE], BLOCK_SIZE);
    }
}
void print_hex(uint8_t *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
int main() {
    uint8_t plaintext[] = "This is a test message for ECB and CBC modes!";
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int length = (sizeof(plaintext) / BLOCK_SIZE + 1) * BLOCK_SIZE;
    uint8_t padded_plaintext[length];
    memset(padded_plaintext, 0, length);
    memcpy(padded_plaintext, plaintext, sizeof(plaintext));
    uint8_t ciphertext_ecb[length];
    uint8_t decrypted_ecb[length];
    uint8_t ciphertext_cbc[length];
    uint8_t decrypted_cbc[length];
    encrypt_ecb(padded_plaintext, key, ciphertext_ecb, length);
    decrypt_ecb(ciphertext_ecb, key, decrypted_ecb, length);
    encrypt_cbc(padded_plaintext, key, iv, ciphertext_cbc, length);
    decrypt_cbc(ciphertext_cbc, key, iv, decrypted_cbc, length);
    printf("Original plaintext: %s\n", plaintext);
    printf("ECB encrypted: ");
    print_hex(ciphertext_ecb, length);
    printf("ECB decrypted: %s\n", decrypted_ecb);
    printf("CBC encrypted: ");
    print_hex(ciphertext_cbc, length);
    printf("CBC decrypted: %s\n", decrypted_cbc);
    ciphertext_cbc[0] ^= 0xFF; 
    decrypt_cbc(ciphertext_cbc, key, iv, decrypted_cbc, length);
    printf("CBC decrypted with error in first ciphertext block: %s\n", decrypted_cbc);
    return 0;
}
