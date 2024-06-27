#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 1000
#define ALPHABET_SIZE 26
const float english_freq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
void calculate_frequency(const char text[], float freq[]) {
    int count[ALPHABET_SIZE] = {0};
    int length = strlen(text);
    int total = 0;
    
    for (int i = 0; i < length; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            count[text[i] - 'A']++;
            total++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
            total++;
        }
    } 
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (float)count[i] / total * 100;
    }
}
float calculate_score(const float text_freq[]) {
    float score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (text_freq[i] - english_freq[i]) * (text_freq[i] - english_freq[i]);
    }
    return score;
}
void decrypt_with_key(const char ciphertext[], char plaintext[], int key) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}
typedef struct {
    int key;
    float score;
    char plaintext[MAX_LEN];
} DecryptionResult;
int compare_scores(const void *a, const void *b) {
    float scoreA = ((DecryptionResult *)a)->score;
    float scoreB = ((DecryptionResult *)b)->score;
    return (scoreA > scoreB) - (scoreA < scoreB);
}
int main() {
    char ciphertext[MAX_LEN];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_LEN, stdin);
    int length = strlen(ciphertext) - 1;
    ciphertext[length] = '\0';
    int num_results;
    printf("Enter the number of top results to display: ");
    scanf("%d", &num_results);
    DecryptionResult results[ALPHABET_SIZE]; 
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt_with_key(ciphertext, results[key].plaintext, key);
        float freq[ALPHABET_SIZE];
        calculate_frequency(results[key].plaintext, freq);
        results[key].score = calculate_score(freq);
        results[key].key = key;
    }
    qsort(results, ALPHABET_SIZE, sizeof(DecryptionResult), compare_scores);
    printf("\nTop %d possible plaintexts:\n", num_results);
    for (int i = 0; i < num_results; i++) {
        printf("Key %2d: %s\n", results[i].key, results[i].plaintext);
    }
    return 0;
}