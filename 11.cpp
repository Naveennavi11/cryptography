#include <stdio.h>
#include <math.h>

#define FACTORIAL 25


unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    
    unsigned long long totalPermutations = factorial(FACTORIAL);

   
    unsigned long long uniqueKeys = totalPermutations / 8;

 
    double log2Total = log2((double)totalPermutations);
    double log2Unique = log2((double)uniqueKeys);

    printf("Total number of possible keys (ignoring identical results): %.2e (approx 2^%.2f)\n", 
            (double)totalPermutations, log2Total);
    printf("Number of effectively unique keys: %.2e (approx 2^%.2f)\n", 
            (double)uniqueKeys, log2Unique);

    return 0;
}

