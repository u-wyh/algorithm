#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define maxn 60

int a[maxn][maxn];
int F[2 * maxn][maxn][maxn];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 初始化F数组为-1
    memset(F, -1, sizeof(F));
    // 初始化左上角点
    F[2][1][1] = 0;

    // 动态规划填充F数组
    for (int k = 3; k < m + n; k++) {
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int s = F[k][i][j];
                if (F[k - 1][i][j] > s) s = F[k - 1][i][j];
                if (F[k - 1][i - 1][j] > s) s = F[k - 1][i - 1][j];
                if (F[k - 1][i][j - 1] > s) s = F[k - 1][i][j - 1];
                if (F[k - 1][i - 1][j - 1] > s) s = F[k - 1][i - 1][j - 1];
                if (s == -1) continue; // 如果s仍然是-1，说明不能到达该点
                F[k][i][j] = s + a[k - i][i] + a[k - j][j];
            }
        }
    }

    // 输出右下角的结果（假设总是可达的，实际可能需要检查）
    printf("%d\n", F[m + n - 1][n - 1][n]);

    return 0;
}
