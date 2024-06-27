#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2

void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int pt[MATRIX_SIZE];
    int ct[MATRIX_SIZE];
    int len = strlen(plaintext);

    for (int i = 0; i < len; i += MATRIX_SIZE) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pt[j] = plaintext[i + j] - 'A';
        }

        for (int j = 0; j < MATRIX_SIZE; j++) {
            ct[j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                ct[j] += key[j][k] * pt[k];
            }
            ct[j] %= 26;
            ciphertext[i + j] = ct[j] + 'A';
        }
    }
    ciphertext[len] = '\0';
}

void known_plaintext_attack(int pt[MATRIX_SIZE][MATRIX_SIZE], int ct[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    // Solve the system of equations to find the key matrix
    // This example uses a simple method suitable for 2x2 matrices
    int determinant = (pt[0][0] * pt[1][1] - pt[0][1] * pt[1][0]) % 26;
    int determinant_inv = 0;
    for (int i = 0; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            determinant_inv = i;
            break;
        }
    }

    int adj[MATRIX_SIZE][MATRIX_SIZE] = {
        { pt[1][1], -pt[0][1] },
        { -pt[1][0], pt[0][0] }
    };

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            adj[i][j] = (adj[i][j] * determinant_inv) % 26;
            if (adj[i][j] < 0) {
                adj[i][j] += 26;
            }
        }
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            key[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                key[i][j] += ct[i][k] * adj[k][j];
            }
            key[i][j] %= 26;
        }
    }
}

int main() {
    char plaintext[] = "HELLO";
    char ciphertext[6];
    int key[MATRIX_SIZE][MATRIX_SIZE] = { { 6, 24 }, { 1, 13 } };

    printf("Original Key Matrix:\n");
    print_matrix(key);

    encrypt(key, plaintext, ciphertext);
    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    // Known plaintext-ciphertext pairs
    int pt_pairs[MATRIX_SIZE][MATRIX_SIZE] = { { 7, 4 }, { 11, 11 } }; // HE and LL
    int ct_pairs[MATRIX_SIZE][MATRIX_SIZE] = { { 8, 12 }, { 2, 3 } };  // IM and CD

    int recovered_key[MATRIX_SIZE][MATRIX_SIZE];
    known_plaintext_attack(pt_pairs, ct_pairs, recovered_key);

    printf("Recovered Key Matrix:\n");
    print_matrix(recovered_key);

    return 0;
}
