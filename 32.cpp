#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t initial_permutation(uint8_t input) {
    uint8_t output = 0;
    output |= (input & 0x80) >> 1;  // bit 8 -> bit 7
    output |= (input & 0x40) >> 3;  // bit 6 -> bit 5
    output |= (input & 0x20) << 1;  // bit 5 -> bit 6
    output |= (input & 0x10) << 3;  // bit 4 -> bit 8
    output |= (input & 0x08) >> 1;  // bit 3 -> bit 2
    output |= (input & 0x04) >> 3;  // bit 2 -> bit 4
    output |= (input & 0x02) << 1;  // bit 1 -> bit 3
    output |= (input & 0x01) << 3;  // bit 0 -> bit 1
    return output;
}
uint8_t inverse_permutation(uint8_t input) {
    uint8_t output = 0;
    output |= (input & 0x80) << 1;  // bit 7 -> bit 8
    output |= (input & 0x40) << 3;  // bit 6 -> bit 5
    output |= (input & 0x20) >> 1;  // bit 5 -> bit 6
    output |= (input & 0x10) >> 3;  // bit 4 -> bit 8
    output |= (input & 0x08) << 1;  // bit 3 -> bit 2
    output |= (input & 0x04) << 3;  // bit 2 -> bit 4
    output |= (input & 0x02) >> 1;  // bit 1 -> bit 3
    output |= (input & 0x01) >> 3;  // bit 0 -> bit 1
    return output;
}

uint8_t sdes_encrypt(uint8_t input, uint8_t key) {
    
    input = initial_permutation(input);

    uint8_t left = (input & 0xF0) >> 4;
    uint8_t right = input & 0x0F;
    uint8_t temp = right;
    right = left ^ (right ^ key);
    left = temp;

    input = (left << 4) | right;

    input = inverse_permutation(input);

    return input;
}
void ctr_encrypt_decrypt(uint8_t *input, uint8_t *output, uint8_t key, uint8_t counter, size_t length) {
    for (size_t i = 0; i < length; i++) {
        uint8_t encrypted_counter = sdes_encrypt(counter, key);
        output[i] = input[i] ^ encrypted_counter;
        counter++;
    }
}

int main() {
    uint8_t key = 0xFD;       // Binary: 01111 11101
    uint8_t counter = 0x00;   // Counter starting at 0000 0000
    uint8_t plaintext[] = {0x01, 0x02, 0x04};  // Binary: 0000 0001 0000 0010 0000 0100
    size_t length = sizeof(plaintext) / sizeof(plaintext[0]);

    uint8_t ciphertext[length];
    uint8_t decrypted[length];

    // Encrypt the plaintext
    ctr_encrypt_decrypt(plaintext, ciphertext, key, counter, length);

    // Decrypt the ciphertext
    ctr_encrypt_decrypt(ciphertext, decrypted, key, counter, length);

    // Print the results
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
