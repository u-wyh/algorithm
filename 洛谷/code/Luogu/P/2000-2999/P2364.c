#include <stdio.h>
#include <string.h>

char awa[105];
char waw[105];
char aaw[105];
int qwq[105][105][105];
char wqw[105][105][105][1000]; // 假设足够长的字符串以存储结果

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%s %s %s", awa, waw, aaw);
    int n, m, k;
    n = strlen(awa);
    m = strlen(waw);
    k = strlen(aaw);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int l = 1; l <= k; ++l) {
                if (awa[i - 1] == waw[j - 1] && awa[i - 1] == aaw[l - 1]) { // 转移方程
                    if (qwq[i][j][l] < qwq[i - 1][j - 1][l - 1] + 1) {
                        qwq[i][j][l] = qwq[i - 1][j - 1][l - 1] + 1;
                        snprintf(wqw[i][j][l], sizeof(wqw[i][j][l]), "%s%c", wqw[i - 1][j - 1][l - 1], awa[i - 1]); // 更新答案
                    }
                } else { // 考虑继承
                    if (qwq[i][j][l] < qwq[i - 1][j][l]) {
                        qwq[i][j][l] = qwq[i - 1][j][l];
                        strcpy(wqw[i][j][l], wqw[i - 1][j][l]); // 更新答案
                    }
                    if (qwq[i][j][l] < qwq[i][j - 1][l]) {
                        qwq[i][j][l] = qwq[i][j - 1][l];
                        strcpy(wqw[i][j][l], wqw[i][j - 1][l]);
                    }
                    if (qwq[i][j][l] < qwq[i][j][l - 1]) {
                        qwq[i][j][l] = qwq[i][j][l - 1];
                        strcpy(wqw[i][j][l], wqw[i][j][l - 1]);
                    }
                }
            }
        }
    }
    printf("%s\n", wqw[n][m][k]);
    return 0;
}
