#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXM = 100007+5;
const int MAX4M = 400028+5;

int n, m, q;
int base0[MAXM], base1[MAXM];
int seg0[MAX4M], seg1[MAX4M];

void build(int node, int l, int r) {
    if (l == r) {
        seg0[node] = base0[l];
        seg1[node] = base1[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build((node << 1) | 1, mid + 1, r);
    seg0[node] = seg0[node << 1] | seg0[(node << 1) | 1];
    seg1[node] = seg1[node << 1] | seg1[(node << 1) | 1];
}

void update(int node, int l, int r, int pos, int n0, int n1) {
    if (l == r) {
        seg0[node] = n0;
        seg1[node] = n1;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(node << 1, l, mid, pos, n0, n1);
    else update((node << 1) | 1, mid + 1, r, pos, n0, n1);
    seg0[node] = seg0[node << 1] | seg0[(node << 1) | 1];
    seg1[node] = seg1[node << 1] | seg1[(node << 1) | 1];
}

void query(int node, int l, int r, int ql, int qr, int &res0, int &res1, bool &conflict) {
    if (conflict) return;
    if (ql <= l && r <= qr) {
        int new0 = res0 | seg0[node];
        int new1 = res1 | seg1[node];
        if (new0 & new1) conflict = true;
        res0 = new0;
        res1 = new1;
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        query(node << 1, l, mid, ql, qr, res0, res1, conflict);
        if (conflict) return;
    }
    if (qr > mid) {
        query((node << 1) | 1, mid + 1, r, ql, qr, res0, res1, conflict);
    }
}

signed main() {
    scanf("%lld %lld %lld", &n, &m, &q);
    char str[35];
    for (int i = 1; i <= m; i++) {
        scanf("%s", str);
        int m0 = 0, m1 = 0;
        for (int j = 0; j < n; j++) {
            if (str[j] == '0') m0 |= (1ll << j);
            else if (str[j] == '1') m1 |= (1ll << j);
        }
        base0[i] = m0;
        base1[i] = m1;
    }

    build(1, 1, m);

    int ans_total = 0;
    while (q--) {
        int opt;
        scanf("%lld", &opt);
        if (opt == 0) {
            int l, r;
            scanf("%lld %lld", &l, &r);
            int res0 = 0, res1 = 0;
            bool conflict = false;
            query(1, 1, m, l, r, res0, res1, conflict);
            if (conflict || (res0 & res1)) {
				continue;
            } else {
                int full_mask = (1ll << n) - 1;
                int free_mask = ~(res0 | res1) & full_mask;
                int cnt = __builtin_popcount(free_mask);
                int result = (1ll << cnt);
                ans_total ^= result;
            }
        } else {
            int pos;
            scanf("%lld %s", &pos, str);
            int m0 = 0, m1 = 0;
            for (int j = 0; j < n; j++) {
                if (str[j] == '0') m0 |= (1ll << j);
                else if (str[j] == '1') m1 |= (1ll << j);
            }
            update(1, 1, m, pos, m0, m1);
        }
    }

    printf("%lld\n", ans_total);
    return 0;
}