#include <bits/stdc++.h>
using namespace std;

const int N = 150000 * 3 + 10;

int n, m;
struct Node {
    int mi, cnt;
    int ans, ad;
} t[4 * N];
int a[N], buc[N];
int st, lim;

void pushup(int x) {
    t[x].mi = min(t[x * 2].mi, t[x * 2 + 1].mi);
    t[x].cnt = (t[x * 2].mi == t[x].mi ? t[x * 2].cnt : 0) + 
               (t[x * 2 + 1].mi == t[x].mi ? t[x * 2 + 1].cnt : 0);
    t[x].ans = t[x * 2].ans + t[x * 2 + 1].ans;
}

void tag(int x, int c) {
    t[x].mi += c;
    t[x].ans = (t[x].mi == 0) ? t[x].cnt : 0;
    t[x].ad += c;
}

void pushdown(int x) {
    if (t[x].ad) {
        tag(x * 2, t[x].ad);
        tag(x * 2 + 1, t[x].ad);
        t[x].ad = 0;
    }
}

void build(int x, int l, int r) {
    if (l == r) {
        t[x].cnt = 1;
        t[x].ans = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void update(int x, int l, int r, int L, int R, int c) {
    if (L <= l && r <= R) {
        tag(x, c);
        return;
    }
    pushdown(x);
    int mid = (l + r) / 2;
    if (L <= mid) update(x * 2, l, mid, L, R, c);
    if (R > mid) update(x * 2 + 1, mid + 1, r, L, R, c);
    pushup(x);
}

int query(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[x].ans;
    pushdown(x);
    int mid = (l + r) / 2;
    if (R <= mid) return query(x * 2, l, mid, L, R);
    if (L > mid) return query(x * 2 + 1, mid + 1, r, L, R);
    return query(x * 2, l, mid, L, R) + query(x * 2 + 1, mid + 1, r, L, R);
}

void change(int x, int c) {
    int k = x - buc[x] + 1 - (c > 0);
    update(1, 1, lim, k, k, c);
    buc[x] += c;
}

int main() {
    cin >> n >> m;
    st = 150000 + 1;
    lim = 450000 + 5;
    build(1, 1, lim);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += st;
        change(a[i], 1);
    }
    int p, x;
    while (m--) {
        cin >> p >> x;
        if (p > 0) {
            if (a[p] <= st + n) {
                change(a[p], -1);
            } else {
                buc[a[p]]--;
            }
            a[p] = st + x;
            if (a[p] <= st + n) {
                change(a[p], 1);
            } else {
                buc[a[p]]++;
            }
        } else if (x > 0) {
            int pos = st + n;
            if (buc[pos]) update(1, 1, lim, pos - buc[pos] + 1, pos, -1);
            st--;
        } else {
            st++;
            int pos = st + n;
            if (buc[pos]) update(1, 1, lim, pos - buc[pos] + 1, pos, 1);
        }
        cout << query(1, 1, lim, st + 1, st + n) << endl;
    }
    return 0;
}