#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherSequence(const char *keyword, char *cipher) {
    int seen[26] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        if (isalpha(keyword[i])) {
            char ch = toupper(keyword[i]);
            if (!seen[ch - 'A']) {
                cipher[index++] = ch;
                seen[ch - 'A'] = 1;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!seen[i]) {
            cipher[index++] = 'A' + i;
        }
    }

    cipher[index] = '\0';
}

void encryptMessage(const char *plain, const char *cipher, char *encrypted) {
    for (int i = 0; plain[i] != '\0'; i++) {
        if (isalpha(plain[i])) {
            if (isupper(plain[i])) {
                encrypted[i] = cipher[plain[i] - 'A'];
            } else {
                encrypted[i] = tolower(cipher[plain[i] - 'a']);
            }
        } else {
            encrypted[i] = plain[i];
        }
    }
    encrypted[strlen(plain)] = '\0';
}

void decryptMessage(const char *encrypted, const char *cipher, char *plain) {
    char reverseCipher[26];
    for (int i = 0; i < 26; i++) {
        reverseCipher[cipher[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; encrypted[i] != '\0'; i++) {
        if (isalpha(encrypted[i])) {
            if (isupper(encrypted[i])) {
                plain[i] = reverseCipher[encrypted[i] - 'A'];
            } else {
                plain[i] = tolower(reverseCipher[encrypted[i] - 'a']);
            }
        } else {
            plain[i] = encrypted[i];
        }
    }
    plain[strlen(encrypted)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipher[27];
    char plaintext[100];
    char encrypted[100];
    char decrypted[100];

    generateCipherSequence(keyword, cipher);

    printf("Cipher sequence: %s\n", cipher);

    printf("Enter a message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 

    encryptMessage(plaintext, cipher, encrypted);
    printf("Encrypted message: %s\n", encrypted);

    decryptMessage(encrypted, cipher, decrypted);
    printf("Decrypted message: %s\n", decrypted);

    return 0;
}
