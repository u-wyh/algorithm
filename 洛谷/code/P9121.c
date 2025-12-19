#include <stdio.h>
#include <stdlib.h>

// 定义 long long 类型，如果编译器不支持则可能需要调整
typedef long long ll;

// 添加 min 函数的定义，因为 C 标准库中没有直接提供
ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    ll n, t, sum = 0, ans = 0, pos, d[100010], b[100010];
    scanf("%lld%lld", &n, &t);

    // 注意：d[0] 未被初始化，但在这里 d[i-1] 在 i=1 时是未定义的，需要特别处理
    // 假设 d[0] = 0，或者添加对 i=1 的特殊处理
    d[0] = 0; // 假设起始位置为0

    for (ll i = 1; i <= n; i++) {
        scanf("%lld%lld", &d[i], &b[i]);

        // 注意：当 i=1 时，d[i-1] 是 d[0]，这里已经假设为0
        pos = min(sum, d[i] - d[i - 1]); // 当 i=1 时，不移动
        sum -= pos;
        ans += pos;
        sum += b[i];
    }

    // 注意：t-d[n]+1 可能超出 ll 范围，但这里假设不会
    printf("%lld\n", ans + min(sum, t - d[n] + 1));

    return 0;
}
