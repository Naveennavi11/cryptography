#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dict[26] = {0};
    int k = 0;

    
    for (int i = 0; key[i]; i++) {
        if (key[i] != 'J') {
            if (!dict[key[i] - 'A']) {
                keyTable[k / SIZE][k % SIZE] = key[i];
                k++;
            }
            dict[key[i] - 'A'] = 1;
        }
    }

   
    for (int i = 0; i < 26; i++) {
        if (!dict[i] && (i != ('J' - 'A'))) {
            keyTable[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void search(char keyTable[SIZE][SIZE], char a, char b, int *row1, int *col1, int *row2, int *col2) {
    if (a == 'J') a = 'I';
    if (b == 'J') b = 'I';

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                *row1 = i;
                *col1 = j;
            } else if (keyTable[i][j] == b) {
                *row2 = i;
                *col2 = j;
            }
        }
    }
}

void decrypt(char keyTable[SIZE][SIZE], char str[], char decoded[]) {
    int length = strlen(str);

    for (int i = 0; i < length; i += 2) {
        int row1, col1, row2, col2;
        search(keyTable, str[i], str[i + 1], &row1, &col1, &row2, &col2);

        if (row1 == row2) {
            decoded[i] = keyTable[row1][(col1 + SIZE - 1) % SIZE];
            decoded[i + 1] = keyTable[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            decoded[i] = keyTable[(row1 + SIZE - 1) % SIZE][col1];
            decoded[i + 1] = keyTable[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            decoded[i] = keyTable[row1][col2];
            decoded[i + 1] = keyTable[row2][col1];
        }
    }

    decoded[length] = '\0';
}

int main() {
    char key[] = "PLAYFAIRCIPHER";
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char keyTable[SIZE][SIZE];
    char decoded[sizeof(message)];

    generateKeyTable(key, keyTable);
    decrypt(keyTable, message, decoded);

    printf("Decrypted Message: %s\n", decoded);

    return 0;
}

