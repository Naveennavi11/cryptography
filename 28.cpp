#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

uint64_t mod_exp(uint64_t a, uint64_t b, uint64_t q) {
    uint64_t result = 1;
    a = a % q; 

    while (b > 0) {
        
        if (b & 1)
            result = (result * a) % q;
        
      
        b = b >> 1; 
        a = (a * a) % q; 
    }
    return result;
}

int main() {
    uint64_t q = 353; 
    uint64_t a = 3;  
    
    
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


    return 0;
}
