#include <stdio.h>
#include <stdbool.h>

int n, m;
int a[15], b[15];
bool f[1005]; // 注意这里使用bool类型

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
    }

    // 初始化f数组，仅f[0]为true
    memset(f, 0, sizeof(f));
    f[0] = true;

    // 填充f数组
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 1000; j++) {
            // 注意这里使用逻辑或运算符的结果来设置f数组的值
            if (j >= a[i]) {
                f[j % 360] = f[j % 360] || f[(j - a[i]) % 360];
            }
            f[j % 360] = f[j % 360] || f[(j + a[i]) % 360];
        }
    }

    // 检查结果
    for (int i = 1; i <= m; i++) {
        if (f[b[i] % 360]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
