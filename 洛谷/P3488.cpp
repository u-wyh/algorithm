#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 200005;

struct Node {
    ll sum, lmax, rmax, tmax;
} tree[4 * MAXN];

void pushup(int id) {
    int lc = id * 2, rc = id * 2 + 1;
    tree[id].sum = tree[lc].sum + tree[rc].sum;
    tree[id].lmax = max(tree[lc].lmax, tree[lc].sum + tree[rc].lmax);
    tree[id].rmax = max(tree[rc].rmax, tree[rc].sum + tree[lc].rmax);
    tree[id].tmax = max({tree[lc].tmax, tree[rc].tmax, tree[lc].rmax + tree[rc].lmax});
}

void build(int id, int l, int r, ll val) {
    if (l == r) {
        tree[id].sum = val;
        tree[id].lmax = val;
        tree[id].rmax = val;
        tree[id].tmax = val;
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid, val);
    build(id * 2 + 1, mid + 1, r, val);
    pushup(id);
}

void update(int id, int l, int r, int pos, ll x) {
    if (l == r) {
        tree[id].sum += x;
        tree[id].lmax += x;
        tree[id].rmax += x;
        tree[id].tmax += x;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(id * 2, l, mid, pos, x);
    else update(id * 2 + 1, mid + 1, r, pos, x);
    pushup(id);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    ll C = 1LL * k * d;
    build(1, 1, n, -k);
    while (m--) {
        int r, x;
        cin >> r >> x;
        update(1, 1, n, r, x);
        if (tree[1].tmax <= C) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }
    return 0;
}