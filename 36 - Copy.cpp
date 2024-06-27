#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find the modular multiplicative inverse of a under modulo m using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclidean algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as Euclid's algorithm
        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to encrypt plaintext using the affine Caesar cipher
void encrypt(char *plaintext, char *ciphertext, int a, int b) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((a * (plaintext[i] - 'A') + b) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((a * (plaintext[i] - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters remain the same
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt ciphertext using the affine Caesar cipher
void decrypt(char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = modInverse(a, 26); // Find modular multiplicative inverse of a
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'A' - b + 26) % 26)) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'a' - b + 26) % 26)) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabet characters remain the same
        }
    }
    plaintext[i] = '\0'; // Null-terminate the plaintext
}

// Function to check if a and 26 are coprime (GCD should be 1)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove newline character

    // Get valid values for a and b
    do {
        printf("Enter value of a (must be coprime with 26): ");
        scanf("%d", &a);
        if (gcd(a, 26) != 1) {
            printf("Invalid value for a. Please enter a value that is coprime with 26.\n");
        }
    } while (gcd(a, 26) != 1);

    printf("Enter value of b: ");
    scanf("%d", &b);

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, a, b);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedtext, a, b);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}