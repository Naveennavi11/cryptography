#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Function to compute gcd using Euclidean algorithm
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to find the modular inverse using the extended Euclidean algorithm
uint64_t mod_inverse(uint64_t a, uint64_t m) {
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;

    if (m == 1) {
        return 0;
    }

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
    if (x1 < 0) {
        x1 += m0;
    }

    return x1;
}

// Function to factorize n into p and q
void factorize(uint64_t n, uint64_t *p, uint64_t *q) {
    for (uint64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
}

// Function to decrypt ciphertext using private key
uint64_t rsa_decrypt(uint64_t C, uint64_t d, uint64_t n) {
    uint64_t result = 1;
    C = C % n;
    while (d > 0) {
        if (d % 2 == 1) {
            result = (result * C) % n;
        }
        d = d >> 1;
        C = (C * C) % n;
    }
    return result;
}

// Function to encrypt plaintext using public key
uint64_t rsa_encrypt(uint64_t M, uint64_t e, uint64_t n) {
    uint64_t result = 1;
    M = M % n;
    while (e > 0) {
        if (e % 2 == 1) {
            result = (result * M) % n;
        }
        e = e >> 1;
        M = (M * M) % n;
    }
    return result;
}

int main() {
    uint64_t n = 3599; // n = p * q
    uint64_t e_old = 31;   // Old public key exponent
    uint64_t d_old = 1703; // Old private key exponent (leaked)
    uint64_t p, q;

    // Factorize n into p and q using the leaked private key
    factorize(n, &p, &q);
    printf("Factors of %lu are p = %lu and q = %lu\n", n, p, q);

    // Compute f(n)
    uint64_t phi_n = (p - 1) * (q - 1);
    printf("f(n) = %lu\n", phi_n);

    // Generate a new public key exponent e_new
    uint64_t e_new = 37; // e_new must be coprime with f(n)
    while (gcd(e_new, phi_n) != 1) {
        e_new++;
    }

    // Compute the new private key d_new
    uint64_t d_new = mod_inverse(e_new, phi_n);
    printf("New public key (e_new, n): (%lu, %lu)\n", e_new, n);
    printf("New private key d_new is %lu\n", d_new);

    // Encrypt and decrypt a message
    uint64_t message = 1234; // Example plaintext
    uint64_t encrypted = rsa_encrypt(message, e_new, n);
    uint64_t decrypted = rsa_decrypt(encrypted, d_new, n);
    printf("Original message: %lu\n", message);
    printf("Encrypted message: %lu\n", encrypted);
    printf("Decrypted message: %lu\n", decrypted);

    // Demonstrate insecurity by decrypting with the old private key
    uint64_t decrypted_with_old = rsa_decrypt(encrypted, d_old, n);
    printf("Decrypted message with old private key: %lu\n", decrypted_with_old);

    return 0;
}