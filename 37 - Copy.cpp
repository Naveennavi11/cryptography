#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
const float english_frequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, // A-G
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, // H-N
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, // O-U
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074                    // V-Z
};
typedef struct {
    char letter;
    int count;
    float frequency;
} LetterFrequency;
void count_letter_frequencies(const char *ciphertext, LetterFrequency frequencies[]) {
    int i, index;
    int total_letters = 0;
    int letter_counts[ALPHABET_SIZE] = {0};
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            index = tolower(ciphertext[i]) - 'a';
            letter_counts[index]++;
            total_letters++;
        }
    }
    for (i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i].letter = 'a' + i;
        frequencies[i].count = letter_counts[i];
        frequencies[i].frequency = (float)letter_counts[i] / total_letters;
    }
}
int compare_frequencies(const void *a, const void *b) {
    const LetterFrequency *freq1 = (const LetterFrequency *)a;
    const LetterFrequency *freq2 = (const LetterFrequency *)b;
    return (freq2->frequency > freq1->frequency) - (freq2->frequency < freq1->frequency);
}
void frequency_analysis(const char *ciphertext, int top_results) {
    LetterFrequency frequencies[ALPHABET_SIZE];
    count_letter_frequencies(ciphertext, frequencies);
    qsort(frequencies, ALPHABET_SIZE, sizeof(LetterFrequency), compare_frequencies);
    char decrypt_map[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        decrypt_map[frequencies[i].letter - 'a'] = 'A' + i; 
    }
    printf("Possible plaintexts in rough order of likelihood:\n");
    for (int i = 0; i < top_results; i++) {
        printf("%d. ", i + 1);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            if (isalpha(ciphertext[j])) {
                if (isupper(ciphertext[j])) {
                    printf("%c", decrypt_map[ciphertext[j] - 'A']);
                } else {
                    printf("%c", tolower(decrypt_map[tolower(ciphertext[j]) - 'a']));
                }
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }
}
int main() {
    char ciphertext[] = "Gwc uivioml bw nqvl bpm zqopb apqnb!";
    int top_results = 10;
    printf("Ciphertext: %s\n", ciphertext);
    frequency_analysis(ciphertext, top_results);
    return 0;
}