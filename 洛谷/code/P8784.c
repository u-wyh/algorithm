#include <stdio.h>
#define N  10000005
const int MOD = 1000000007;

int n, f[N];

int main() {
    scanf("%d", &n);
    f[0] = 1;
    f[1] = 1;
    f[2] = 2;
    f[3] = 5;

    for (int i = 4; i <= n; i++) {
        f[i] = (((f[i-1] + (f[i-2] * 2) % MOD) % MOD + f[i-3]) % MOD + f[i-4]) % MOD;
    }

    printf("%d\n", f[n] % MOD);

    return 0;
}
