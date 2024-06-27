#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

// Function to perform modular exponentiation a^b mod q
uint64_t mod_exp(uint64_t a, uint64_t b, uint64_t q) {
    uint64_t result = 1;
    a = a % q; // Ensure base is modulo q

    while (b > 0) {
        // If b is odd, multiply a with result
        if (b & 1)
            result = (result * a) % q;
        
        // b must be even now
        b = b >> 1; // b = b / 2
        a = (a * a) % q; // Change a to a^2
    }
    return result;
}

int main() {
    uint64_t q = 353; // Prime modulus
    uint64_t a = 3;   // Primitive root
    
    // Alice's private key
    uint64_t x = 97;  // Private key (should be kept secret)

    // Bob's private key
    uint64_t y = 233; // Private key (should be kept secret)

    // Alice computes public value A = a^x mod q
    uint64_t A = mod_exp(a, x, q);

    // Bob computes public value B = a^y mod q
    uint64_t B = mod_exp(a, y, q);

    // Both Alice and Bob compute the shared secret key
    uint64_t secret_Alice = mod_exp(B, x, q); // Alice computes B^x mod q
    uint64_t secret_Bob = mod_exp(A, y, q);   // Bob computes A^y mod q

    // Printing the shared secret keys computed by Alice and Bob
    printf("Shared secret computed by Alice: %" PRIu64 "\n", secret_Alice);
    printf("Shared secret computed by Bob: %" PRIu64 "\n", secret_Bob);

    return 0;
}