#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 2139063143
#define MAX_N 1002
#define MAX_M 1002

int D[MAX_N], C[MAX_M], f[MAX_N][MAX_M];

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d", &C[i]);
    }
    memset(f, 0x7f, sizeof(f));
    for (int i = 0; i <= M; i++) {
        f[0][i] = 0;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= M; j++) {
            f[i][j] = (f[i][j-1] < f[i-1][j-1] + D[i] * C[j]) ? f[i][j-1] : f[i-1][j-1] + D[i] * C[j];
        }
    }
    int ans = INF;
    for (int i = N; i <= M; i++) {
        ans = (ans < f[N][i]) ? ans : f[N][i];
    }
    printf("%d\n", ans);
    return 0;
}
