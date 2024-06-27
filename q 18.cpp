#include <stdio.h>
#include <stdint.h>
#include <string.h>

int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

int PC2[48] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void permute(uint8_t *in, uint8_t *out, int *perm, int n) {
    memset(out, 0, (n + 7) / 8);
    for (int i = 0; i < n; i++) {
        int bit = (in[(perm[i] - 1) / 8] >> (7 - ((perm[i] - 1) % 8))) & 1;
        out[i / 8] |= bit << (7 - (i % 8));
    }
}


void rotate_left(uint8_t *key, int n, int bits) {
    uint32_t k = 0;
    for (int i = 0; i < 4; i++) {
        k = (k << 8) | key[i];
    }
    k = ((k << bits) | (k >> (28 - bits))) & 0x0FFFFFFF;
    for (int i = 3; i >= 0; i--) {
        key[i] = k & 0xFF;
        k >>= 8;
    }
}

void generate_subkeys(uint8_t *key, uint8_t subkeys[16][6]) {
    uint8_t pc1_out[7];
    permute(key, pc1_out, PC1, 56);

    uint8_t C[4], D[4];
    memcpy(C, pc1_out, 4);
    memcpy(D, pc1_out + 3, 4);
    D[0] &= 0x0F;

    for (int i = 0; i < 16; i++) {
        rotate_left(C, 28, shifts[i]);
        rotate_left(D, 28, shifts[i]);

        uint8_t CD[7];
        memcpy(CD, C, 3);
        CD[3] = (C[3] & 0xF0) | (D[0] >> 4);
        memcpy(CD + 4, D + 1, 3);

        permute(CD, subkeys[i], PC2, 48);
    }
}

int main() {
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t subkeys[16][6];

    generate_subkeys(key, subkeys);

    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("K%d: ", i + 1);
        for (int j = 0; j < 6; j++) {
            printf("%02X ", subkeys[i][j]);
        }
        printf("\n");
    }

    return 0;
}

