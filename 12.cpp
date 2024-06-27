#include <stdio.h>
#include <string.h>

#define SIZE 2

void encrypt(char plaintext[], int key[SIZE][SIZE], char ciphertext[]) {
    for (int i = 0; i < strlen(plaintext); i += SIZE) {
        int p1 = plaintext[i] - 'a';
        int p2 = plaintext[i + 1] - 'a';

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        ciphertext[i] = c1 + 'a';
        ciphertext[i + 1] = c2 + 'a';
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(char ciphertext[], int key_inverse[SIZE][SIZE], char plaintext[]) {
    for (int i = 0; i < strlen(ciphertext); i += SIZE) {
        int c1 = ciphertext[i] - 'a';
        int c2 = ciphertext[i + 1] - 'a';

        int p1 = (key_inverse[0][0] * c1 + key_inverse[0][1] * c2) % 26;
        int p2 = (key_inverse[1][0] * c1 + key_inverse[1][1] * c2) % 26;

        plaintext[i] = p1 + 'a';
        plaintext[i + 1] = p2 + 'a';
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[] = "meetmeattheusualplaceattentratherthaneightoclock";
    int key[SIZE][SIZE] = {{9, 4}, {5, 7}};
    int key_inverse[SIZE][SIZE] = {{7, 22}, {5, 9}};
    char ciphertext[strlen(plaintext) + 1];
    char decrypted_text[strlen(plaintext) + 1];

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key_inverse, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}
