#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_LEN 1000
void generate_random_key(int key[], int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}
void encrypt(char plaintext[], char ciphertext[], int key[], int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}
void decrypt(char ciphertext[], char decrypted[], int key[], int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decrypted[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decrypted[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[length] = '\0';
}
int main() {
    srand(time(0));
    char plaintext[MAX_LEN];
    char ciphertext[MAX_LEN];
    char decrypted[MAX_LEN];
    int key[MAX_LEN];
    printf("Enter the plaintext: ");
    fgets(plaintext, MAX_LEN, stdin);
    int length = strlen(plaintext) - 1;
    plaintext[length] = '\0';
    generate_random_key(key, length);
    encrypt(plaintext, ciphertext, key, length);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    decrypt(ciphertext, decrypted, key, length);
    printf("Decrypted text: %s\n", decrypted);
    return 0;
}