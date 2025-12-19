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
