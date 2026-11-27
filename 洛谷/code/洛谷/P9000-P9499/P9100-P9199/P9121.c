// https://www.luogu.com.cn/problem/P9121
// 题意：前 T 天内，每天晚餐若有干草 Bessie 会吃掉 1 捆；
// 第 d_i 天早晨会送来 b_i 捆干草。
// 计算 Bessie 在前 T 天共吃掉的干草捆数。
// 数据范围：1 <= N <= 10^5，1 <= T <= 10^14，
// 1 <= d_1 < d_2 < ... < d_N <= T
// 1 <= b_i <= 10^9。
// 算法标签：模拟
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
