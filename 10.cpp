#include <stdio.h>
#include <string.h>

#define SIZE 5

// Define the Playfair key matrix
char keyTable[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void search(char keyTable[SIZE][SIZE], char a, char b, int *row1, int *col1, int *row2, int *col2) {
    if (a == 'J') a = 'I';
    if (b == 'J') b = 'I';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                *row1 = i;
                *col1 = j;
            }
            if (keyTable[i][j] == b) {
                *row2 = i;
                *col2 = j;
            }
        }
    }
}

void encrypt(char keyTable[SIZE][SIZE], char str[], char encrypted[]) {
    int length = strlen(str);
    for (int i = 0; i < length; i += 2) {
        int row1, col1, row2, col2;
        search(keyTable, str[i], str[i + 1], &row1, &col1, &row2, &col2);
        if (row1 == row2) {
            encrypted[i] = keyTable[row1][(col1 + 1) % SIZE];
            encrypted[i + 1] = keyTable[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encrypted[i] = keyTable[(row1 + 1) % SIZE][col1];
            encrypted[i + 1] = keyTable[(row2 + 1) % SIZE][col2];
        } else {
            encrypted[i] = keyTable[row1][col2];
            encrypted[i + 1] = keyTable[row2][col1];
        }
    }
    encrypted[length] = '\0';
}

void prepareMessage(char message[], char prepared[]) {
    int length = strlen(message);
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            prepared[j++] = message[i] - 'a' + 'A';
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            prepared[j++] = message[i];
        }
    }
    prepared[j] = '\0';
    for (int i = 0; i < j; i += 2) {
        if (prepared[i] == prepared[i + 1]) {
            for (int k = j; k > i + 1; k--) {
                prepared[k] = prepared[k - 1];
            }
            prepared[i + 1] = 'X';
            j++;
        }
    }
    if (j % 2 != 0) {
        prepared[j++] = 'X';
    }
    prepared[j] = '\0';
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char prepared[strlen(message) * 2];
    char encrypted[strlen(prepared) + 1];
    prepareMessage(message, prepared);
    encrypt(keyTable, prepared, encrypted);
    printf("Prepared Message: %s\n", prepared);
    printf("Encrypted Message: %s\n", encrypted);
    return 0;
}

