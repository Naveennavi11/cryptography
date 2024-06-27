#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 


void des_encrypt(uint8_t *block, const uint8_t *key) {

}

void des_decrypt(uint8_t *block, const uint8_t *key) {
   
}


void pad_block(uint8_t *block, size_t data_len) {
    size_t pad_len = BLOCK_SIZE - data_len;
    block[data_len] = 0x80;
    for (size_t i = data_len + 1; i < BLOCK_SIZE; i++) {
        block[i] = 0x00;
    }
}


void ecb_mode(uint8_t *plaintext, size_t length, const uint8_t *key, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    size_t num_blocks = length / BLOCK_SIZE + 1;

    for (size_t i = 0; i < num_blocks; i++) {
        memcpy(block, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);
        if (i == num_blocks - 1) {
            pad_block(block, length % BLOCK_SIZE);
        }
        des_encrypt(block, key);
        memcpy(ciphertext + i * BLOCK_SIZE, block, BLOCK_SIZE);
    }
}


void cbc_mode(uint8_t *plaintext, size_t length, const uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    size_t num_blocks = length / BLOCK_SIZE + 1;

    for (size_t i = 0; i < num_blocks; i++) {
        memcpy(block, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);
        if (i == num_blocks - 1) {
            pad_block(block, length % BLOCK_SIZE);
        }
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= prev_block[j];
        }
        des_encrypt(block, key);
        memcpy(prev_block, block, BLOCK_SIZE);
        memcpy(ciphertext + i * BLOCK_SIZE, block, BLOCK_SIZE);
    }
}

// CFB mode
void cfb_mode(uint8_t *plaintext, size_t length, const uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t block[BLOCK_SIZE];
    uint8_t feedback[BLOCK_SIZE];
    memcpy(feedback, iv, BLOCK_SIZE);

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        des_encrypt(feedback, key);
        for (size_t j = 0; j < BLOCK_SIZE && i + j < length; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ feedback[j];
            feedback[j] = ciphertext[i + j]; 
        }
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x00}; 
    uint8_t iv[BLOCK_SIZE] = {0x00}; 
    uint8_t plaintext[] = "This is a test message for encryption modes!"; 
    size_t length = strlen((char *)plaintext);

    uint8_t ecb_ciphertext[sizeof(plaintext) + BLOCK_SIZE];
    uint8_t cbc_ciphertext[sizeof(plaintext) + BLOCK_SIZE];
    uint8_t cfb_ciphertext[sizeof(plaintext) + BLOCK_SIZE];

    ecb_mode(plaintext, length, key, ecb_ciphertext);
    cbc_mode(plaintext, length, key, iv, cbc_ciphertext);
    cfb_mode(plaintext, length, key, iv, cfb_ciphertext);

    printf("ECB ciphertext: ");
    for (size_t i = 0; i < sizeof(ecb_ciphertext); i++) {
        printf("%02x", ecb_ciphertext[i]);
    }
    printf("\n");

    printf("CBC ciphertext: ");
    for (size_t i = 0; i < sizeof(cbc_ciphertext); i++) {
        printf("%02x", cbc_ciphertext[i]);
    }
    printf("\n");

    printf("CFB ciphertext: ");
    for (size_t i = 0; i < sizeof(cfb_ciphertext); i++) {
        printf("%02x", cfb_ciphertext[i]);
    }
    printf("\n");

    return 0;
}
