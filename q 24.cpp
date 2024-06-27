#include <stdio.h>


unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        exp = exp >> 1; 
        base = (base * base) % mod; 
    }
    return result;
}


unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


unsigned long long mod_inverse(unsigned long long e, unsigned long long phi_n) {
    long long d = 0;
    long long x1 = 0, x2 = 1, y1 = 1, temp_phi = phi_n;
    while (e > 0) {
        long long temp1 = temp_phi / e;
        long long temp2 = temp_phi - temp1 * e;
        temp_phi = e;
        e = temp2;
        long long x = x2 - temp1 * x1;
        long long y = d - temp1 * y1;
        x2 = x1;
        x1 = x;
        d = y1;
        y1 = y;
    }
    if (temp_phi == 1) {
        return (d + phi_n) % phi_n;
    }
}

int main() {
   
    unsigned long long e = 31;
    unsigned long long n = 3599;
    
    
    unsigned long long p, q;
    for (p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }
    

    unsigned long long phi_n = (p - 1) * (q - 1);
    
 
    unsigned long long d = mod_inverse(e, phi_n);
    
 
    printf("Private key (d): %llu\n", d);
    
    return 0;
}
