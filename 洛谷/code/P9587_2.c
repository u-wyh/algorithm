// https://www.luogu.com.cn/problem/P9587
// 题意：给定长度 n 的数组 a 和整数 k。
// 定义 f(i) = (a 中严格大于 a_i 的元素个数) + 1，g(i) = (a 中大于等于 a_i 的元素个数)。
// 每次操作可选任意 t ∈ [1, n] 使 a_t 加 1。
// 对每个 i ∈ [1, n] 分别独立求使得 f(i) <= k <= g(i) 成立的最少操作次数。
// 题意：第一行输入测试点编号 c 及 n, k，第二行输入 a_1..a_n；输出 n 行，第 i 行为第 i 个位置的答案。
// 数据范围：1 <= k <= n <= 5 * 10^5，1 <= a_i <= 10^9。
// 算法标签：排序、前缀和
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch - '0'); ch = getchar(); }
    return x * f;
}

int _, n, k, maxx = 0;

typedef struct {
    int x, num;
} node;

node a[500007];
ll sum[500007], ans[500007];

int cmp(const void *i, const void *j) {
    node *ni = (node *)i;
    node *nj = (node *)j;
    return nj->x - ni->x; // 注意这里为了逆序，用了ni->x - nj->x的相反数
}

int main() {
    _ = read(), n = read(), k = read();
    for(int i = 1; i <= n; i++) {
        a[i].x = read();
        a[i].num = i;
    }
    qsort(a + 1, n, sizeof(node), cmp);
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i].x;
    }
    for(int i = 1; i <= n; i++) {
        if(a[i].x == a[k].x) continue;
        if(a[i].x < a[k].x) {
            ans[a[i].num] = a[k].x - a[i].x;
        } else {
            ans[a[i].num] = (ll)(k - i) * a[i].x - (sum[k] - sum[i]);
        }
    }
    for(int i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
