#include <stdio.h>
#include <stdint.h>

// Initial permutation table for 64-bit input
static const int initial_permutation[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Example 56-bit key (must be in parity-adjusted format)
static const uint64_t key = 0x133457799BBCDFF1;

// Perform initial permutation on 64-bit input
uint64_t initial_permute(uint64_t plaintext) {
    uint64_t permuted = 0;
    for (int i = 0; i < 64; ++i) {
        permuted |= ((plaintext >> (64 - initial_permutation[i])) & 1) << (63 - i);
    }
    return permuted;
}

// DES encryption function (simplified for demonstration)
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    // Perform initial permutation
    uint64_t permuted_plain = initial_permute(plaintext);

    // Apply the key (simplified, using example key)
    uint64_t encrypted = permuted_plain ^ key;

    return encrypted;
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF; // Example 64-bit plaintext
    uint64_t ciphertext;

    // Encrypt using DES
    ciphertext = des_encrypt(plaintext, key);

    // Output the ciphertext
    printf("Plaintext: 0x%016llX\n", plaintext);
    printf("Ciphertext: 0x%016llX\n", ciphertext);

    return 0;
}