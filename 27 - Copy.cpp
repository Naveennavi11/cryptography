#include <stdio.h>
#include <math.h>

// Function to perform modular exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Public key components
    unsigned long long e = 65537;  // example large e
    unsigned long long n = 999630013489;  // example large n
    
    // Array to store ciphertexts for plaintext values 0 to 25
    unsigned long long ciphertexts[26];
    
    // Encrypt each plaintext value and store the result
    for (int m = 0; m < 26; m++) {
        ciphertexts[m] = mod_exp(m, e, n);
    }
    
    // Print the ciphertexts and their corresponding plaintext values
    printf("Plaintext to Ciphertext mapping:\n");
    for (int m = 0; m < 26; m++) {
        printf("Plaintext: %d, Ciphertext: %llu\n", m, ciphertexts[m]);
    }
    
    // Example intercepted ciphertext
    unsigned long long intercepted_ciphertext = 123456789012;  // replace with actual intercepted ciphertext
    
    // Decrypt the intercepted ciphertext
    for (int m = 0; m < 26; m++) {
        if (ciphertexts[m] == intercepted_ciphertext) {
            printf("Intercepted ciphertext %llu corresponds to plaintext %d\n", intercepted_ciphertext, m);
            break;
        }
    }
    
    return 0;
}
