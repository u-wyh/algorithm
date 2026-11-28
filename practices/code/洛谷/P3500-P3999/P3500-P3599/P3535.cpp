// https://www.luogu.com.cn/problem/P3535
// 题意：输入点数 n、边数 m、限制阈值 k，
// 以及 m 条无向边 (u, v)（无重边）。
// 删除最少数量的边，使得编号在 1~k 内的所有点都不处于任何简单环上。
// 输出最少删边数 cnt，
// 以及接下来 cnt 行每行输出被删边的两个端点（小的在前，大的在后）。
// 数据范围：1 <= n <= 10^6，0 <= m <= 2*10^6，
// 1 <= k <= n，1 <= u < v <= n。
// 难度评分：1500（洛谷分级换算）
// 算法标签：并查集、贪心
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 5e6 + 10;

inline int read() {
    char c = getchar(); int x = 0, f = 1;
    for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
    for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

struct Edge {
    int u, v;
} h[maxn];

int n, m, k, ans;
int fa[maxn];

int find (int x) {
    return x == fa[x] ? x : fa[x] = find (fa[x]);
}

void djj () {
    n = read(), m = read(), k = read();
    for (register int i = 1; i <= n; i ++)
        fa[i] = i;
    for (register int i = 1; i <= m; i ++) {
        h[i].u = read(), h[i].v = read();
        if (h[i].u > k && h[i].v > k)
            fa[find (h[i].u)] = find (h[i].v);
    }
}

void lxy () {
    for (register int i = 1; i <= m; i ++)
        if (h[i].u <= k || h[i].v <= k) {
            if (find (h[i].u) == find (h[i].v))
                ans ++;
            else
                fa[find (h[i].u)] = find (h[i].v);
        }
    printf ("%d\n", ans);
    exit (0);
}

void djj_lxy () {
    djj (), lxy ();
}

int main () {
    djj_lxy ();
}
