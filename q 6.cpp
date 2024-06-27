#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}

void affineDecrypt(char* ciphertext, int a, int b, char* plaintext) {
    int i, a_inv = modInverse(a, 26);
    char ch;

    for (i = 0; ciphertext[i] != '\0'; ++i) {
        ch = ciphertext[i];

        if (isupper(ch)) {
            plaintext[i] = ((a_inv * ((ch - 'A' - b + 26) % 26)) % 26 + 'A');
        } else if (islower(ch)) {
            plaintext[i] = ((a_inv * ((ch - 'a' - b + 26) % 26)) % 26 + 'a');
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[i] = '\0'; 
}

int main() {
    char ciphertext[100];
    char plaintext[100];
    int a, b;
    int pos_E = 4;  
    int pos_T = 19; 
    int pos_B = 1;  
    int pos_U = 20; 
    int diff_pos = (pos_T - pos_E + 26) % 26;
    int diff_ciph = (pos_U - pos_B + 26) % 26;

    for (a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1 && (a * diff_pos) % 26 == diff_ciph) {
            break;
        }
    }

    b = (pos_B - a * pos_E + 26) % 26;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; 

    affineDecrypt(ciphertext, a, b, plaintext);
    printf("Decrypted string: %s\n", plaintext);

    return 0;
}
