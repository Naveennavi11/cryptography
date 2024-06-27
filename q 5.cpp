#include <stdio.h>

char encrypt(char p, int a, int b) {
    return (a * (p - 'a') + b) % 26 + 'a';
}

char decrypt(char c, int a, int b) {
    int inv_a = 0;
    while ((inv_a * a) % 26 != 1) {
        inv_a++;
    }
    return (inv_a * (c - 'a' - b)) % 26 + 'a';
}

int main() {
    int a, b;
    char p, c;

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Enter a plaintext letter: ");
    scanf(" %c", &p);

    c = encrypt(p, a, b);
    printf("Ciphertext letter: %c\n", c);

    p = decrypt(c, a, b);
    printf("Decrypted plaintext letter: %c\n", p);

    return 0;
}
