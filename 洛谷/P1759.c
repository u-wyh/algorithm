#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101
#define MAXM 201

int a[MAXN], b[MAXN], c[MAXN];
int dp[MAXM][MAXM];
char path[MAXM][MAXM][MAXN * 2];  // 假设路径长度不会超过MAXN * 2个字符
int m, v, n;

void build() {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= v; j++) {
            dp[i][j] = 0;
            path[i][j][0] = '\0';  // 初始化字符串为空
        }
    }
}

void compute() {
    char p2[MAXN * 2];
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= a[i]; j--) {
            for (int k = v; k >= b[i]; k--) {
                if (path[j - a[i]][k - b[i]][0] == '\0') {
                    snprintf(p2, sizeof(p2), "%d", i);
                } else {
                    snprintf(p2, sizeof(p2), "%s %d", path[j - a[i]][k - b[i]], i);
                }
                if (dp[j][k] < dp[j - a[i]][k - b[i]] + c[i]) {
                    dp[j][k] = dp[j - a[i]][k - b[i]] + c[i];
                    strcpy(path[j][k], p2);
                } else if (dp[j][k] == dp[j - a[i]][k - b[i]] + c[i]) {
                    // 如果两个路径值相同，选择字典序较小的
                    if (strcmp(p2, path[j][k]) < 0) {
                        strcpy(path[j][k], p2);
                    }
                }
            }
        }
    }
}

int main() {
    int temp;
    while (scanf("%d %d %d", &m, &v, &n) != EOF) {
        build();
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &a[i], &b[i], &c[i]);
        }
        compute();
        printf("%d\n", dp[m][v]);
        printf("%s\n", path[m][v]);
    }
    return 0;
}
