#include <stdio.h>
#include <stdlib.h>

#define N 5010
#define MOD 1000000007

int n, a[N], dp[N], ans;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    dp[0] = 1;

    // 使用qsort对数组a进行排序
    qsort(a + 1, n, sizeof(int), compare);

    for (int i = 1; i <= n; i++) {
        for (int j = N - 10; j >= a[i] - 1; j--) {
            dp[min(j + a[i], N - 10)] = (dp[j] + dp[min(j + a[i], N - 10)]) % MOD;
        }
    }

    for (int i = 1; i <= N - 10; i++) {
        ans = (ans + dp[i]) % MOD;
    }

    printf("%d\n", ans);
    return 0;
}
