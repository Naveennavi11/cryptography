#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int e, int phi) {
    int t = 0, newT = 1;
    int r = phi, newR = e;
    while (newR != 0) {
        int quotient = r / newR;
        int tempT = newT;
        newT = t - quotient * newT;
        t = tempT;
        int tempR = newR;
        newR = r - quotient * newR;
        r = tempR;
    }
    if (t < 0) {
        t = t + phi;
    }
    return t;
}
int main() {
    int n = 3233; 
    int e = 17;    
    int M = 61;   
    int commonFactor = gcd(M, n);
    if (commonFactor == 1 || commonFactor == n) {
        printf("No common factor found with n.\n");
    } else {
        int p = commonFactor;
        int q = n / p;
        printf("Factors found: p = %d, q = %d\n", p, q);
        int phi = (p - 1) * (q - 1);
        printf("phi(n) = %d\n", phi);
        int d = modInverse(e, phi);
        printf("Private key d = %d\n", d);
    }
    return 0;
}

