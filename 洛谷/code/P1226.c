#include <stdio.h>

long a, b, p,A,B;

long power() {
    long ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }
    return ans;
}

int main() {
    scanf("%ld %ld %ld", &a, &b, &p);
    A=a;
    B=b;
    printf("%ld^%ld mod %ld=%ld\n", A, B, p, power());
    return 0;
}
