#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200000;
const int M = 64000000;

int n, m, ln;
int a[N + 5], lsh[N + 5];
int root[N + 5], lson[M], rson[M], sum[M], cnt;

inline int read() {
    int s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    return s * w;
}

void update_inner(int &rt, int l, int r, int pos, int val) {
    if (!rt) rt = ++cnt;
    sum[rt] += val;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update_inner(lson[rt], l, mid, pos, val);
    else
        update_inner(rson[rt], mid + 1, r, pos, val);
}

void update_outer(int pos, int val, int op) {
    for (int i = pos; i <= n; i += i & -i) {
        update_inner(root[i], 1, ln, val, op);
    }
}

int query_inner(int rt, int l, int r, int ql, int qr) {
    if (!rt) return 0;
    if (ql <= l && r <= qr) return sum[rt];
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid) res += query_inner(lson[rt], l, mid, ql, qr);
    if (qr > mid) res += query_inner(rson[rt], mid + 1, r, ql, qr);
    return res;
}

int query_range(int l, int r, int ql, int qr) {
    if (l > r || ql > qr) return 0;
    int res = 0;
    for (int i = r; i; i -= i & -i) {
        res += query_inner(root[i], 1, ln, ql, qr);
    }
    for (int i = l - 1; i; i -= i & -i) {
        res -= query_inner(root[i], 1, ln, ql, qr);
    }
    return res;
}

int query_greater(int l, int r, int v) {
    if (v + 1 > ln) return 0;
    return query_range(l, r, v + 1, ln);
}

int query_less(int l, int r, int v) {
    if (v - 1 < 1) return 0;
    return query_range(l, r, 1, v - 1);
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        lsh[i] = a[i];
    }
    sort(lsh + 1, lsh + n + 1);
    ln = unique(lsh + 1, lsh + n + 1) - lsh - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(lsh + 1, lsh + ln + 1, a[i]) - lsh;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += query_greater(1, i - 1, a[i]);
        update_outer(i, a[i], 1);
    }
    printf("%lld\n", ans);

    m = read();
    while (m--) {
        int x = read(), y = read();
        if (x == y) {
            printf("%lld\n", ans);
            continue;
        }
        if (x > y) swap(x, y);
        int vx = a[x], vy = a[y];
        ll A1 = query_greater(1, x - 1, vx) + query_less(x + 1, n, vx);
        ll A2 = query_greater(1, y - 1, vy) + query_less(y + 1, n, vy);
        ll add1 = A1 + A2;
        if (vx > vy) add1--;

        update_outer(x, vx, -1);
        update_outer(y, vy, -1);

        ll B1 = query_greater(1, x - 1, vy) + query_less(x + 1, n, vy);
        ll B2 = query_greater(1, y - 1, vx) + query_less(y + 1, n, vx);
        ll add2 = B1 + B2;
        if (vy > vx) add2++;

        update_outer(x, vy, 1);
        update_outer(y, vx, 1);
        swap(a[x], a[y]);

        ans += (add2 - add1);
        printf("%lld\n", ans);
    }
    return 0;
}
/*
3
130 150 140
2
2 3
1 3
*/