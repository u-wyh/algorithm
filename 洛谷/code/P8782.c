// https://www.luogu.com.cn/problem/P8782
// 题意：输入进制上限指示 N（每位可用进制为 2 到 N+1）、位数 Ma 及 A 的各位十进制值、位数 Mb 及 B 的各位十进制值（从高位到低位
// A 与 B 共用同一组各数位进制且每位数字须小于该位进制，保证 A >= B）；
// 输出合法进制选择下 A - B 的最小可能十进制值对 10^9+7 取模的结果。
// 数据范围：2 <= N <= 1000，1 <= Ma, Mb <= 10^5。
// 算法标签：贪心、进制转换
#include <stdio.h>
#include <stdlib.h>

#define int long long
#define MAX_SIZE 100010

int a[MAX_SIZE];
int b[MAX_SIZE];
int c[MAX_SIZE];
int d[MAX_SIZE];
const int mod = 1e9 + 7;

int main() {
    int n; // 实际上n在后续代码中未使用，可能是题目描述中的一部分
    scanf("%lld", &n);
    int ma;
    scanf("%lld", &ma);
    for (int i = ma; i > 0; i--) {
        scanf("%lld", &a[i]);
    }
    int mb;
    scanf("%lld", &mb);
    for (int i = mb; i > 0; i--) {
        scanf("%lld", &b[i]);
    }

    for (int i = (ma > mb ? ma : mb); i > 0; i--) {
        c[i] = (a[i] > b[i] ? a[i] : b[i]) + 1;
    }
    for (int i = (ma > mb ? ma : mb); i > 0; i--) {
        c[i] = (c[i] > 2 ? c[i] : 2);
    }

    d[1] = 1;
    for (int i = 2; i <= (ma > mb ? ma : mb); i++) {
        d[i] = (d[i - 1] * c[i - 1]) % mod;
    }

    long long ka = 0, kb = 0;
    for (int i = ma; i > 0; i--) {
        ka = (ka + a[i] * d[i]) % mod;
    }
    for (int i = mb; i > 0; i--) {
        kb = (kb + b[i] * d[i]) % mod;
    }

    printf("%lld\n", (ka - kb + mod) % mod); // 特别注意：模意义下的减法
    return 0;
}
