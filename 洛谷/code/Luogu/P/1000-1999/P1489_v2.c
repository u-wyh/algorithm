#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

#define MAX_N 210
#define MAX_SUM 5000
#define MAX_K 110

int n;
int a[MAX_N];
int f[MAX_SUM + 1][MAX_K];

int main() {
    int i, j, k, sum = 0, ans = INT_MAX;

    scanf("%d", &n);
    memset(f, 0, sizeof(f)); // 初始化f数组为0
    f[0][0] = 1; // 初始条件

    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for (j = MAX_SUM; j >= a[i]; j--) {
            for (k = MAX_K - 1; k >= 1; k--) {
                f[j][k] = (f[j][k] > f[j - a[i]][k - 1]) ? f[j][k] : f[j - a[i]][k - 1];
            }
        }
        sum += a[i];
    }

    for (i = 0; i <= MAX_SUM; i++) {
        if (f[i][n / 2]) {
            if (ans > abs(i * 2 - sum)) {
                ans = abs(i * 2 - sum);
            }
        }
    }

    printf("%d %d\n", (sum - ans) / 2, (sum + ans) / 2);

    return 0;
}
