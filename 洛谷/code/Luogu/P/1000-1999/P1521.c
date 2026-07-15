#include <stdio.h>

#define MAX_N 5000
#define MAX_K 5000
#define MOD 10000

int N, K;
int f[MAX_N + 1][MAX_K + 1];

int main() {
    scanf("%d %d", &N, &K);

    f[1][0] = 1;
    f[2][1] = 1;
    f[2][0] = 1;
    f[0][0] = 1;

    for (int i = 3; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            f[i][j] = 0;
            for (int k = 0; k <= i - 1 && k <= j; k++) {
                f[i][j] = (f[i][j] + f[i - 1][j - k]) % MOD;
            }
        }
    }

    // Êä³ö½á¹û
    printf("%d\n", f[N][K]);

    return 0;
}
