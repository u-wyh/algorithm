#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 998244353;
const int N = 100005;

LL pow_mod(LL x, LL n) {
    LL res = 1;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
struct Node {
    int ls, rs, val;
} tr[N * 20];
int root[N], ck;
void update(int &u, int o, int l, int r, int x, int v) {
    u = ++ck;
    tr[u] = tr[o];
    tr[u].val = (tr[u].val + v) % mod;
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid)
        update(tr[u].ls, tr[o].ls, l, mid, x, v);
    else
        update(tr[u].rs, tr[o].rs, mid + 1, r, x, v);
}
LL query(int u, int o, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return tr[u].val - tr[o].val;
    }
    int mid = l + r >> 1;
    LL res = 0;
    if (x <= mid) res += query(tr[u].ls, tr[o].ls, l, mid, x, y);
    if (y > mid) res += query(tr[u].rs, tr[o].rs, mid + 1, r, x, y);
    return res;
}
int a[N], b[N], l[N], r[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    LL sb = 1;
    for (int i = 2; i <= n; i++) {
        scanf("%d%d", &l[i], &r[i]);
        sb = sb * (r[i] - l[i] + 1) % mod;
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
        LL now = i == 1 ? 1 : (query(root[r[i]], root[l[i] - 1], 1, n, 1, a[i]) % mod + mod) % mod * pow_mod(r[i] - l[i] + 1, mod - 2) % mod;
        update(root[i], root[i - 1], 1, n, a[i], now);
        ans += now * sb % mod;
    }
    ans %= mod;
    printf("%lld\n", ans);
    return 0;
}
