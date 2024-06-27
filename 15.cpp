#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void decrypt(char ciphertext[], int key, char decryptedText[]) {
    int len = strlen(ciphertext);
    
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = tolower(ciphertext[i]);
            char decryptedChar = 'a' + (ch - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE;
            decryptedText[i] = isupper(ciphertext[i])? toupper(decryptedChar) : decryptedChar;
        } else {
            decryptedText[i] = ciphertext[i];
        }
    }
    decryptedText[len] = '\0';
}

int main() {
    char ciphertext[] = "GWCUG EQORNG KPMU VQ XOOG QPAQEWPKVG.";
    char decryptedText[strlen(ciphertext) + 1];
    
    decrypt(ciphertext, 3, decryptedText);
    
    printf("Plaintext: %s\n", decryptedText);
    
    return 0;
}
