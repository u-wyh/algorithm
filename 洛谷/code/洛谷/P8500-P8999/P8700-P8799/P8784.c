// https://www.luogu.com.cn/problem/P8784
// 题意：输入整数 N，
// 用大小 2 的 I 型（1*2）和大小 3 的 L
// 型（3 格拐角）积木（可任意旋转）无缝铺满方向固定的 2*N 矩形画布
// 输出铺法总数对 10^9+7 取模的结果。
// 数据范围：1 <= N <= 10^7。
// 算法标签：动态规划、递推
#include <stdio.h>
#define N  10000005
const int MOD = 1000000007;

int n, f[N];

int main() {
    scanf("%d", &n);
    f[0] = 1;
    f[1] = 1;
    f[2] = 2;
    f[3] = 5;

    for (int i = 4; i <= n; i++) {
        f[i] = (((f[i-1] + (f[i-2] * 2) % MOD) % MOD + f[i-3]) % MOD + f[i-4]) % MOD;
    }

    printf("%d\n", f[n] % MOD);

    return 0;
}
