// https://www.luogu.com.cn/problem/P3795
// 题意：输入一个正整数 k（输入格式中记为 x）。
// 设集合 N = M = {1, 2, ..., k}，
// 求满足 f(f(x)) = x 的 N 到 M 的不同映射 f 的个数。
// 输出答案对 14233333 取余的结果。
// 数据范围：1 <= k <= 10^7；注意本题内存限制为 20MB。
// 算法标签：递推、组合数学
#include <stdio.h>

typedef long long ll;
const int mod = 14233333;

int main() {
    ll a = 2, b = 1, now, n;
    scanf("%lld", &n); // 使用 %lld 匹配 long long 类型的输入

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    if (n == 2) {
        printf("2\n");
        return 0;
    }

    for (ll i = 3; i <= n; ++i) {
        now = b * (i - 1) + a;
        now %= mod;
        b = a;
        a = now;
    }

    printf("%lld\n", a); // 输出结果并换行
    return 0;
}
