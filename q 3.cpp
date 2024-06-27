#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int len = strlen(key);
    int used[26] = {0};  
    int row = 0, col = 0;

    for (int i = 0; i < len; i++) {
        if (key[i] == 'j') key[i] = 'i';
        if (!used[key[i] - 'a']) {
            keyMatrix[row][col++] = key[i];
            used[key[i] - 'a'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;
        if (!used[ch - 'a']) {
            keyMatrix[row][col++] = ch;
            used[ch - 'a'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

void preprocessText(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (text[i] == 'j') text[i] = 'i';
    }
}

void encryptPair(char keyMatrix[SIZE][SIZE], char *a, char *b) {
    int r1, c1, r2, c2;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == *a) {
                r1 = i;
                c1 = j;
            } else if (keyMatrix[i][j] == *b) {
                r2 = i;
                c2 = j;
            }
        }
    }

    if (r1 == r2) {  
        *a = keyMatrix[r1][(c1 + 1) % SIZE];
        *b = keyMatrix[r2][(c2 + 1) % SIZE];
    } else if (c1 == c2) {  
        *a = keyMatrix[(r1 + 1) % SIZE][c1];
        *b = keyMatrix[(r2 + 1) % SIZE][c2];
    } else { 
        *a = keyMatrix[r1][c2];
        *b = keyMatrix[r2][c1];
    }
}

void encryptText(char keyMatrix[SIZE][SIZE], char text[]) {
    preprocessText(text);
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        if (text[i] == text[i + 1]) {  
            for (int j = len; j > i + 1; j--) {
                text[j] = text[j - 1];
            }
            text[i + 1] = 'x';
            len++;
        }
        if (text[i + 1] == '\0') {
            text[i + 1] = 'x'; 
            text[i + 2] = '\0';
        }
        encryptPair(keyMatrix, &text[i], &text[i + 1]);
    }
}

int main() {
    char key[26];
    char text[100];
    char keyMatrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  
    for (int i = 0; key[i]; i++) key[i] = tolower(key[i]);

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    for (int i = 0; text[i]; i++) text[i] = tolower(text[i]);

    generateKeyMatrix(key, keyMatrix);

    encryptText(keyMatrix, text);

    printf("Encrypted text: %s\n", text);

    return 0;
}

