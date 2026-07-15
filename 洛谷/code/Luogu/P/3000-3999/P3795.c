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
