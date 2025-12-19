#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LL unsigned long long

int n, i, j;
int a[101]; // 存数
int f[101][101]; // f[i][j]表示取i~j这个区间段player1最高得分
int s[101]; // s[i]表示a[1]~a[i]的和

int max(int x, int y) {
    return x > y ? x : y;
}

int main() {
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]); // 读入
        s[i] = s[i - 1] + a[i]; // 求和
        f[i][i] = a[i]; // 初始化
    }

    // 表示a[i]~a[j]的和的方法：s[j]-s[i-1]
    for (i = n - 1; i >= 1; i--) {
        for (j = i + 1; j <= n; j++) {
            f[i][j] = max((s[j] - s[i - 1]) - f[i + 1][j],
                          (s[j] - s[i - 1]) - f[i][j - 1]);
        }
    }
    printf("%d %d\n", f[1][n], s[n] - f[1][n]);
    return 0;
}
