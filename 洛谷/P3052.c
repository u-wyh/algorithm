#include<stdio.h>
#include<string.h>
#include<stdlib.h> // 引入stdlib.h以使用memset

int n, w;
int a[20];
int f[1 << 18]; // f[i]表示状态i的最小次数
int g[1 << 18]; // g[i]表示状态i时，最后一个电梯的剩余体积

int main() {
    scanf("%d%d", &n, &w);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(f, 0x3f, sizeof(f)); // 初始化f数组为一个大数
    f[0] = 1;
    g[0] = w;

    // 枚举状态
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 1; j <= n; j++) {
            // 枚举每一头奶牛
            if (i & (1 << (j - 1))) continue; // 如果这头奶牛已经在电梯里了
            if (g[i] >= a[j] && f[i | (1 << (j - 1))] >= f[i]) {
                // 如果这个电梯坐得下
                f[i | (1 << (j - 1))] = f[i];
                // 更新剩余体积
                g[i | (1 << (j - 1))] = (g[i] >= a[j]) ? g[i] - a[j] : 0;
            } else if (g[i] < a[j] && f[i | (1 << (j - 1))] >= f[i] + 1) {
                // 如果这个电梯坐不下
                f[i | (1 << (j - 1))] = f[i] + 1; // 电梯次数+1
                g[i | (1 << (j - 1))] = w - a[j]; // 重新开始一个电梯
            }
        }
    }

    printf("%d\n", f[(1 << n) - 1]);

    return 0;
}
