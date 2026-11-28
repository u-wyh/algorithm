// https://www.luogu.com.cn/problem/P7774
// 题意：给定 N 个初始角 a_i，
// 回答 M 个目标角 b_i 能否通过若干个 a_i（可重复或不用）做加减运算在模
// 360 度意义下得到
// 输出 YES/NO。
// 数据范围：1 <= N, M <= 10，0 < a_i, b_i < 360。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划、完全背包
#include <stdio.h>
#include <string.h>
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
