#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

const int N = 100005;

int n, m, w[N];

struct Seg {
    int L0, R0;
    int L1, R1;
    int C0, C1;
    int L[2][2];
    int R[2][2];
    LL res;
} v[N << 2];

void seg_init(Seg &s) {
    s.L0 = s.R0 = s.L1 = s.R1 = s.C0 = s.C1 = s.res = 0;
    memset(s.L, 0, sizeof(s.L));
    memset(s.R, 0, sizeof(s.R));
}

void seg_init_single(Seg &s, int x) {
    seg_init(s);
    if (x) {
        s.L1 = s.R1 = s.C1 = 1;
        s.L[0][1] = s.R[0][1] = 1;
        s.res = 1;
    } else {
        s.L0 = s.R0 = s.C0 = 1;
        s.L[1][0] = s.R[1][0] = 1;
        s.res = 0;
    }
}

void seg_merge(Seg &c, const Seg &a, const Seg &b, int mid) {
    seg_init(c);
    
    c.C0 = a.C0 + b.C0;
    c.C1 = a.C1 + b.C1;
    
    c.L0 = a.L0;
    if (a.C1 == 0) c.L0 += b.L0;
    
    c.R0 = b.R0;
    if (b.C1 == 0) c.R0 += a.R0;
    
    c.L1 = a.L1;
    if (a.C1 == 0) c.L1 += b.L1;
    if (a.C1 == 1) c.L1 += b.L0;
    
    c.R1 = b.R1;
    if (b.C1 == 0) c.R1 += a.R1;
    if (b.C1 == 1) c.R1 += a.R0;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c.L[i][j] = a.L[i][j];
            if (i >= a.C0) {
                int ni = i - a.C0;
                int nj = j ^ (a.C1 & 1);
                if (ni < 2) c.L[i][j] += b.L[ni][nj];
            }
            c.R[i][j] = b.R[i][j];
            if (i >= b.C0) {
                int ni = i - b.C0;
                int nj = j ^ (b.C1 & 1);
                if (ni < 2) c.R[i][j] += a.R[ni][nj];
            }
        }
    }
    
    c.res = a.res + b.res;
    c.res += (LL)a.R0 * b.L1 + (LL)a.R1 * b.L0;
    c.res += (LL)a.R[0][0] * (b.L[0][1] + b.L[1][1]) + (LL)a.R[0][1] * (b.L[0][0] + b.L[1][0]);
    c.res += (LL)a.R[1][0] * b.L[0][1] + (LL)a.R[1][1] * b.L[0][0];
    
    if (w[mid] + w[mid + 1] == 1) c.res--;
}

void build(int p, int l, int r) {
    if (l == r) {
        seg_init_single(v[p], w[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    seg_merge(v[p], v[p << 1], v[p << 1 | 1], mid);
}

void change(int p, int l, int r, int x) {
    if (l == r) {
        seg_init_single(v[p], w[l]);
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) change(p << 1, l, mid, x);
    else change(p << 1 | 1, mid + 1, r, x);
    seg_merge(v[p], v[p << 1], v[p << 1 | 1], mid);
}

Seg query(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return v[p];
    int mid = (l + r) >> 1;
    if (y <= mid) return query(p << 1, l, mid, x, y);
    if (x > mid) return query(p << 1 | 1, mid + 1, r, x, y);
    
    Seg left_seg = query(p << 1, l, mid, x, y);
    Seg right_seg = query(p << 1 | 1, mid + 1, r, x, y);
    Seg result;
    seg_merge(result, left_seg, right_seg, mid);
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", w + i);
    build(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        int opt;
        scanf("%d", &opt);
        if (opt == 1) {
            int x;
            scanf("%d", &x);
            w[x] ^= 1;
            change(1, 1, n, x);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);
            LL total = (LL)(r - l + 1) * (r - l + 2) / 2;
            Seg ans = query(1, 1, n, l, r);
            printf("%lld\n", total - ans.res);
        }
    }
    return 0;
}