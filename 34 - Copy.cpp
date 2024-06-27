#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

typedef unsigned char BYTE;
typedef BYTE DES_key[8];

void pad_block(BYTE *block, size_t block_size);
void print_hex(const char *label, const BYTE *data, size_t len);

void DES_encrypt_block(BYTE *block, DES_key key);
void DES_decrypt_block(BYTE *block, DES_key key);
void ECB_encrypt(BYTE *plaintext, BYTE *ciphertext, size_t length, DES_key key);
void ECB_decrypt(BYTE *ciphertext, BYTE *plaintext, size_t length, DES_key key);
void CBC_encrypt(BYTE *plaintext, BYTE *ciphertext, size_t length, DES_key key, BYTE *iv);
void CBC_decrypt(BYTE *ciphertext, BYTE *plaintext, size_t length, DES_key key, BYTE *iv);
void CFB_encrypt(BYTE *plaintext, BYTE *ciphertext, size_t length, DES_key key, BYTE *iv);
void CFB_decrypt(BYTE *ciphertext, BYTE *plaintext, size_t length, DES_key key, BYTE *iv);

int main() {
    DES_key key = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    BYTE iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    BYTE plaintext[BLOCK_SIZE] = "OpenAI!";
    BYTE padded_plaintext[BLOCK_SIZE];
    memcpy(padded_plaintext, plaintext, BLOCK_SIZE);
    pad_block(padded_plaintext, BLOCK_SIZE);
    BYTE ciphertext[BLOCK_SIZE];
    BYTE decryptedtext[BLOCK_SIZE];

    printf("ECB Mode:\n");
    ECB_encrypt(padded_plaintext, ciphertext, BLOCK_SIZE, key);
    print_hex("Ciphertext", ciphertext, BLOCK_SIZE);
    ECB_decrypt(ciphertext, decryptedtext, BLOCK_SIZE, key);
    print_hex("Decrypted text", decryptedtext, BLOCK_SIZE);
    printf("Decrypted text: %s\n\n", decryptedtext);

    printf("CBC Mode:\n");
    CBC_encrypt(padded_plaintext, ciphertext, BLOCK_SIZE, key, iv);
    print_hex("Ciphertext", ciphertext, BLOCK_SIZE);
    CBC_decrypt(ciphertext, decryptedtext, BLOCK_SIZE, key, iv);
    print_hex("Decrypted text", decryptedtext, BLOCK_SIZE);
    printf("Decrypted text: %s\n\n", decryptedtext);

    printf("CFB Mode:\n");
    CFB_encrypt(padded_plaintext, ciphertext, BLOCK_SIZE, key, iv);
    print_hex("Ciphertext", ciphertext, BLOCK_SIZE);
    CFB_decrypt(ciphertext, decryptedtext, BLOCK_SIZE, key, iv);
    print_hex("Decrypted text", decryptedtext, BLOCK_SIZE);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

void pad_block(BYTE *block, size_t block_size) {
    block[block_size - 1] = 0x80;  
}
void print_hex(const char *label, const BYTE *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}
void DES_encrypt_block(BYTE *block, DES_key key) {
}

void DES_decrypt_block(BYTE *block, DES_key key) {

}

void ECB_encrypt(BYTE *plaintext, BYTE *ciphertext, size_t length, DES_key key) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        DES_encrypt_block(plaintext + i, key);
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
    }
}

void ECB_decrypt(BYTE *ciphertext, BYTE *plaintext, size_t length, DES_key key) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        DES_decrypt_block(ciphertext + i, key);
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE);
    }
}

void CBC_encrypt(BYTE *plaintext, BYTE *ciphertext, size_t length, DES_key key, BYTE *iv) {
    BYTE buffer[BLOCK_SIZE];
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            buffer[j] = plaintext[i + j] ^ iv[j];
        }
        DES_encrypt_block(buffer, key);
        memcpy(ciphertext + i, buffer, BLOCK_SIZE);
        memcpy(iv, buffer, BLOCK_SIZE);
    }
}

void CBC_decrypt(BYTE *ciphertext, BYTE *plaintext, size_t length, DES_key key, BYTE *iv) {
    BYTE buffer[BLOCK_SIZE];
    BYTE prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(buffer, ciphertext + i, BLOCK_SIZE);
        DES_decrypt_block(buffer, key);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = buffer[j] ^ prev_block[j];
        }
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void CFB_encrypt(BYTE *plaintext, BYTE *ciphertext, size_t length, DES_key key, BYTE *iv) {
    BYTE buffer[BLOCK_SIZE];
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(buffer, iv, BLOCK_SIZE);
        DES_encrypt_block(buffer, key);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ buffer[j];
            iv[j] = ciphertext[i + j];
        }
    }
}

void CFB_decrypt(BYTE *ciphertext, BYTE *plaintext, size_t length, DES_key key, BYTE *iv) {
    BYTE buffer[BLOCK_SIZE];
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(buffer, iv, BLOCK_SIZE);
        DES_encrypt_block(buffer, key);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] = ciphertext[i + j] ^ buffer[j];
            iv[j] = ciphertext[i + j];
        }
    }
}