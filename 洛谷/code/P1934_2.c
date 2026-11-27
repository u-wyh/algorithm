// https://www.luogu.com.cn/problem/P1934
// 题意：给定 n 层封印的坚固值 a_i。
// 单破第 i 层耗费 a_i×n²。
// 若连续一段 [i,j] 的两端坚固值之和不超过 t，可以整段打破，耗费为两端坚固值之和乘以整段坚固值之和。
// 求全部打破的最小耗费。
// 数据范围：1 ≤ n ≤ 1000，1 ≤ a_i,t ≤ 20000。
// 算法标签：动态规划、前缀和

#include <stdio.h>
#include <stdlib.h>

int n, t;
long long f[1003], s[1003], a[1003];

int main() {
    scanf("%d %d", &n, &t);
    int m = n * n;

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++) {
        long long ans = (long long)m * a[i];
        if (i > 1) {
            ans += f[i - 1];
        }

        for (int j = 1; j < i; j++) {
            if (a[i] + a[j] > t) continue;
            ans = (ans < ((a[i] + a[j]) * (s[i] - s[j - 1]) + f[j - 1])) ? ans : ((a[i] + a[j]) * (s[i] - s[j - 1]) + f[j - 1]);
        }

        f[i] = ans;
    }

    printf("%lld\n", f[n]);
    return 0;
}
