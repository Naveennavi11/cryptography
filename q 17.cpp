#include <stdio.h>
#include <stdint.h>

static const int IP[64] = { };
static const int FP[64] = { };
static const int E[48] = { };
static const int S[8][64] = { };
static const int P[32] = { };
static const int PC1[56] = { };
static const int PC2[48] = { };
static const int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void permute(const int *table, uint8_t *block, int n) {
    uint8_t temp[8] = {0};
    for (int i = 0; i < n; i++)
        temp[i / 8] |= ((block[table[i] - 1] >> (7 - (table[i] - 1) % 8)) & 0x01) << (7 - i % 8);
    for (int i = 0; i < 8; i++) block[i] = temp[i];
}

void generateSubkeys(uint64_t key, uint64_t subkeys[16]) {
    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; i++) permutedKey |= ((key >> (64 - PC1[i])) & 0x01) << (55 - i);
    uint32_t C = (permutedKey >> 28) & 0x0FFFFFFF, D = permutedKey & 0x0FFFFFFF;

    for (int i = 0; i < 16; i++) {
        C = ((C << shifts[i]) | (C >> (28 - shifts[i]))) & 0x0FFFFFFF;
        D = ((D << shifts[i]) | (D >> (28 - shifts[i]))) & 0x0FFFFFFF;
        uint64_t combinedKey = ((uint64_t)C << 28) | D;
        subkeys[i] = 0;
        for (int j = 0; j < 48; j++) subkeys[i] |= ((combinedKey >> (56 - PC2[j])) & 0x01) << (47 - j);
    }
}

uint32_t f(uint32_t R, uint64_t K) {
    uint64_t expandedR = 0;
    for (int i = 0; i < 48; i++) expandedR |= ((R >> (32 - E[i])) & 0x01) << (47 - i);
    expandedR ^= K;

    uint32_t output = 0;
    for (int i = 0; i < 8; i++) {
        uint8_t chunk = (expandedR >> (42 - 6 * i)) & 0x3F;
        uint8_t row = ((chunk & 0x20) >> 4) | (chunk & 0x01);
        uint8_t col = (chunk >> 1) & 0x0F;
        output = (output << 4) | S[i][row * 16 + col];
    }

    uint32_t permutedOutput = 0;
    for (int i = 0; i < 32; i++) permutedOutput |= ((output >> (32 - P[i])) & 0x01) << (31 - i);

    return permutedOutput;
}

void DES_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint64_t key) {
    uint64_t subkeys[16];
    generateSubkeys(key, subkeys);

    permute(IP, ciphertext, 64);
    uint32_t L = (ciphertext[0] << 24) | (ciphertext[1] << 16) | (ciphertext[2] << 8) | ciphertext[3];
    uint32_t R = (ciphertext[4] << 24) | (ciphertext[5] << 16) | (ciphertext[6] << 8) | ciphertext[7];

    for (int i = 15; i >= 0; i--) {
        uint32_t temp = R;
        R = L ^ f(R, subkeys[i]);
        L = temp;
    }

    uint64_t combined = ((uint64_t)R << 32) | L;
    for (int i = 0; i < 8; i++) ciphertext[i] = (combined >> (56 - 8 * i)) & 0xFF;

    permute(FP, ciphertext, 64);
    for (int i = 0; i < 8; i++) plaintext[i] = ciphertext[i];
}

int main() {
    uint8_t ciphertext[8] = {  };
    uint8_t plaintext[8];
    uint64_t key = 0x133457799BBCDFF1; 
    DES_decrypt(ciphertext, plaintext, key);

    printf("Decrypted text: ");
    for (int i = 0; i < 8; i++) printf("%02x ", plaintext[i]);
    printf("\n");

    return 0;
}

