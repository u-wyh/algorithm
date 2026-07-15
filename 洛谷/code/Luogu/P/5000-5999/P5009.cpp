#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 200000 + 5;
const ll MOD = 100000007LL;

int n, m;

ll sumC[MAXN << 2];
ll sumA[MAXN << 2];
ll sumB[MAXN << 2];
ll sumAB[MAXN << 2];

// 懒标记
ll lazyA[MAXN << 2];
ll lazyB[MAXN << 2];
ll lazyPC[MAXN << 2];
ll lazyCA[MAXN << 2];
ll lazyCB[MAXN << 2];

ll v[MAXN], a[MAXN], b[MAXN];

ll mod(ll x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

void push_up(int p) {
    sumC[p] = mod(sumC[p << 1] + sumC[p << 1 | 1]);
    sumA[p] = mod(sumA[p << 1] + sumA[p << 1 | 1]);
    sumB[p] = mod(sumB[p << 1] + sumB[p << 1 | 1]);
    sumAB[p] = mod(sumAB[p << 1] + sumAB[p << 1 | 1]);
}

void add_tag(int p, int l, int r, ll da, ll db, ll pc, ll ca, ll cb) {
    int len = r - l + 1;

    ll oldA = sumA[p];
    ll oldB = sumB[p];
    ll oldAB = sumAB[p];

    // 更新 sumC
    sumC[p] = mod(
        sumC[p]
        + pc * len % MOD
        + ca * oldA % MOD
        + cb * oldB % MOD
    );

    // 更新 sumAB
    sumAB[p] = mod(
        oldAB
        + da * oldB % MOD
        + db * oldA % MOD
        + da * db % MOD * len % MOD
    );

    // 更新 sumA、sumB
    sumA[p] = mod(oldA + da * len % MOD);
    sumB[p] = mod(oldB + db * len % MOD);

    // 合并懒标记
    lazyPC[p] = mod(
        lazyPC[p]
        + pc
        + ca * lazyA[p] % MOD
        + cb * lazyB[p] % MOD
    );

    lazyCA[p] = mod(lazyCA[p] + ca);
    lazyCB[p] = mod(lazyCB[p] + cb);
    lazyA[p] = mod(lazyA[p] + da);
    lazyB[p] = mod(lazyB[p] + db);
}

void push_down(int p, int l, int r) {
    if (
        lazyA[p] == 0 &&
        lazyB[p] == 0 &&
        lazyPC[p] == 0 &&
        lazyCA[p] == 0 &&
        lazyCB[p] == 0
    ) {
        return;
    }

    int mid = (l + r) >> 1;

    add_tag(p << 1, l, mid,
            lazyA[p], lazyB[p], lazyPC[p], lazyCA[p], lazyCB[p]);

    add_tag(p << 1 | 1, mid + 1, r,
            lazyA[p], lazyB[p], lazyPC[p], lazyCA[p], lazyCB[p]);

    lazyA[p] = lazyB[p] = lazyPC[p] = lazyCA[p] = lazyCB[p] = 0;
}

void build(int p, int l, int r) {
    if (l == r) {
        sumC[p] = mod(v[l]);
        sumA[p] = mod(a[l]);
        sumB[p] = mod(b[l]);
        sumAB[p] = mod(a[l] * b[l]);
        return;
    }

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

void update(int p, int l, int r, int ql, int qr,
            ll da, ll db, ll pc, ll ca, ll cb) {
    if (ql <= l && r <= qr) {
        add_tag(p, l, r, da, db, pc, ca, cb);
        return;
    }

    push_down(p, l, r);

    int mid = (l + r) >> 1;

    if (ql <= mid) {
        update(p << 1, l, mid, ql, qr, da, db, pc, ca, cb);
    }

    if (qr > mid) {
        update(p << 1 | 1, mid + 1, r, ql, qr, da, db, pc, ca, cb);
    }

    push_up(p);
}

ll queryC(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sumC[p];
    }

    push_down(p, l, r);

    int mid = (l + r) >> 1;
    ll ans = 0;

    if (ql <= mid) {
        ans = mod(ans + queryC(p << 1, l, mid, ql, qr));
    }

    if (qr > mid) {
        ans = mod(ans + queryC(p << 1 | 1, mid + 1, r, ql, qr));
    }

    return ans;
}

ll queryAB(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sumAB[p];
    }

    push_down(p, l, r);

    int mid = (l + r) >> 1;
    ll ans = 0;

    if (ql <= mid) {
        ans = mod(ans + queryAB(p << 1, l, mid, ql, qr));
    }

    if (qr > mid) {
        ans = mod(ans + queryAB(p << 1 | 1, mid + 1, r, ql, qr));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> a[i] >> b[i];

        v[i] = mod(v[i]);
        a[i] = mod(a[i]);
        b[i] = mod(b[i]);
    }

    build(1, 1, n);

    while (m--) {
        int opt;
        ll t, z;
        int x, y;

        cin >> opt;

        if (opt == 1) {
            cin >> t >> x >> y;

            t = mod(t);

            ll c = queryC(1, 1, n, x, y);
            ll ab = queryAB(1, 1, n, x, y);

            ll ans = mod(c + t * ab % MOD);
            cout << ans << '\n';
        } else {
            cin >> t >> x >> y >> z;

            t = mod(t);
            z = mod(z);

            if (opt == 2) {
                /*
                    a += z

                    c -= t * z * b
                    ab += z * b
                */
                ll da = z;
                ll db = 0;
                ll pc = 0;
                ll ca = 0;
                ll cb = mod(-t * z % MOD);

                update(1, 1, n, x, y, da, db, pc, ca, cb);
            } else if (opt == 3) {
                /*
                    b += z

                    c -= t * z * a
                    ab += z * a
                */
                ll da = 0;
                ll db = z;
                ll pc = 0;
                ll ca = mod(-t * z % MOD);
                ll cb = 0;

                update(1, 1, n, x, y, da, db, pc, ca, cb);
            } else if (opt == 4) {
                /*
                    v += z

                    因为 v = c + t * ab
                    所以 c += z
                */
                ll da = 0;
                ll db = 0;
                ll pc = z;
                ll ca = 0;
                ll cb = 0;

                update(1, 1, n, x, y, da, db, pc, ca, cb);
            }
        }
    }

    return 0;
}