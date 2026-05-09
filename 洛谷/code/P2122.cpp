#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 100000 + 5;

int n, m;
ll sumv[MAXN << 2];
ll sqv[MAXN << 2];
ll lazy[MAXN << 2];

ll gcdll(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void printFrac(ll up, ll down) {
    if (up == 0) {
        cout << "0/1\n";
        return;
    }
    ll g = gcdll(up, down);
    up /= g;
    down /= g;
    cout << up << '/' << down << '\n';
}

void apply(int i, int l, int r, ll d) {
    ll len = r - l + 1;
    sqv[i] += 2 * d * sumv[i] + len * d * d;
    sumv[i] += len * d;
    lazy[i] += d;
}

void pushDown(int i, int l, int r) {
    if (lazy[i] == 0) return;

    int mid = (l + r) >> 1;
    apply(i << 1, l, mid, lazy[i]);
    apply(i << 1 | 1, mid + 1, r, lazy[i]);

    lazy[i] = 0;
}

void pushUp(int i) {
    sumv[i] = sumv[i << 1] + sumv[i << 1 | 1];
    sqv[i] = sqv[i << 1] + sqv[i << 1 | 1];
}

void build(int i, int l, int r) {
    if (l == r) {
        ll x;
        cin >> x;
        sumv[i] = x;
        sqv[i] = x * x;
        return;
    }

    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    pushUp(i);
}

void add(int jobl, int jobr, ll d, int i, int l, int r) {
    if (jobl <= l && r <= jobr) {
        apply(i, l, r, d);
        return;
    }

    pushDown(i, l, r);

    int mid = (l + r) >> 1;
    if (jobl <= mid) {
        add(jobl, jobr, d, i << 1, l, mid);
    }
    if (jobr > mid) {
        add(jobl, jobr, d, i << 1 | 1, mid + 1, r);
    }

    pushUp(i);
}

ll querySum(int jobl, int jobr, int i, int l, int r) {
    if (jobl <= l && r <= jobr) {
        return sumv[i];
    }

    pushDown(i, l, r);

    int mid = (l + r) >> 1;
    ll ans = 0;

    if (jobl <= mid) {
        ans += querySum(jobl, jobr, i << 1, l, mid);
    }
    if (jobr > mid) {
        ans += querySum(jobl, jobr, i << 1 | 1, mid + 1, r);
    }

    return ans;
}

ll querySq(int jobl, int jobr, int i, int l, int r) {
    if (jobl <= l && r <= jobr) {
        return sqv[i];
    }

    pushDown(i, l, r);

    int mid = (l + r) >> 1;
    ll ans = 0;

    if (jobl <= mid) {
        ans += querySq(jobl, jobr, i << 1, l, mid);
    }
    if (jobr > mid) {
        ans += querySq(jobl, jobr, i << 1 | 1, mid + 1, r);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    build(1, 1, n);

    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 1) {
            ll d;
            cin >> d;
            add(l, r, d, 1, 1, n);
        } else if (op == 2) {
            ll s = querySum(l, r, 1, 1, n);
            ll len = r - l + 1;
            printFrac(s, len);
        } else {
            ll s = querySum(l, r, 1, 1, n);
            ll sq = querySq(l, r, 1, 1, n);
            ll len = r - l + 1;

            ll up = len * sq - s * s;
            ll down = len * len;

            printFrac(up, down);
        }
    }

    return 0;
}
