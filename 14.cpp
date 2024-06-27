#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void encrypt(char plaintext[], int key[], char ciphertext[]) {
    int keyLength = strlen(plaintext); 
    for (int i = 0; plaintext[i]; i++) {
        if (isalpha(plaintext[i])) {
            char ch = tolower(plaintext[i]);
            ch = 'a' + (ch - 'a' + key[i % keyLength]) % ALPHABET_SIZE;
            ciphertext[i] = isupper(plaintext[i]) ? toupper(ch) : ch;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[strlen(plaintext) + 1];
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

