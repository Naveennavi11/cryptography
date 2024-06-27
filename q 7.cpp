#include <stdio.h>
#include <string.h>
#include <ctype.h>
void countFrequency(const char *ciphertext, int freq[]) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isprint(ciphertext[i])) {
            freq[ciphertext[i]]++;
        }
    }
}

void printFrequency(const int freq[]) {
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("Character %c: %d times\n", i, freq[i]);
        }
    }
}

int main() {
    const char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡8†83(88)5†;46(;88*96*?;8)‡(;485);5†2:‡(;4956*2(5—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    int freq[256] = {0};

    countFrequency(ciphertext, freq);

    printf("Character frequencies in the ciphertext:\n");
    printFrequency(freq);

    return 0;
}
