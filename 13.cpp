#include <stdio.h>
#include <string.h>

#define SIZE 3 

void encrypt(char plaintext[], int key[SIZE][SIZE], char ciphertext[]) {
    for (int i = 0; i < strlen(plaintext); i += SIZE) {
        int plaintext_matrix[SIZE][1];
        int ciphertext_matrix[SIZE][1];

        for (int j = 0; j < SIZE; j++) {
            plaintext_matrix[j][0] = plaintext[i + j] - 'a';
        }

        int temp[SIZE][1];
        for (int j = 0; j < SIZE; j++) {
            temp[j][0] = 0;
            for (int k = 0; k < SIZE; k++) {
                temp[j][0] += key[j][k] * plaintext_matrix[k][0];
            }
            temp[j][0] %= 26;
        }

        for (int j = 0; j < SIZE; j++) {
            ciphertext_matrix[j][0] = temp[j][0];
            ciphertext[i + j] = ciphertext_matrix[j][0] + 'a';
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char plaintext[] = "hello";
    int key[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};
    char ciphertext[strlen(plaintext) + 1];

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
