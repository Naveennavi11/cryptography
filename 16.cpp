#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26


const float english_frequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

void frequencyAnalysis(char text[], float freq[]) {
    int totalLetters = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char ch = tolower(text[i]);
            freq[ch - 'a']++;
            totalLetters++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (freq[i] / totalLetters) * 100.0;
    }
}


float calculateScore(float freq[]) {
    float score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += freq[i] * english_frequencies[i];
    }
    return score;
}

int main() {
    char ciphertext[] = "GWCUG EQORNG KPMU VQ XOOG QPAQEWPKVG.";
    float freq[ALPHABET_SIZE] = {0};

    frequencyAnalysis(ciphertext, freq);
    float score = calculateScore(freq);

    printf("Score: %.2f\n", score);

    return 0;
}
