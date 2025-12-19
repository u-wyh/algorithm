#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

struct node {
	int l, r; ll v, add;
} t[MAXN << 2];

inline
void upd(int p, ll v) {
	t[p].add += v, t[p].v += v;
}

inline
void pushup(int p) {
	t[p].v = max(t[p << 1].v, t[p << 1 | 1].v);
}

inline
void pushdown(int p) {
	if (!t[p].add) return ;
	upd(p << 1, t[p].add), upd(p << 1 | 1, t[p].add), t[p].add = 0;
}

void build(int l, int r, int p) {
	if (l > r) return ;
	t[p].l = l, t[p].r = r, t[p].v = t[p].add = 0;
	if (l == r) return ; int mid = l + r >> 1;
	build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
}

void modify(int l, int r, ll v, int p) {
	if (l > r) return ;
	if (l <= t[p].l && t[p].r <= r) return upd(p, v);
	pushdown(p); int mid = t[p].l + t[p].r >> 1;
	if (l <= mid) modify(l, r, v, p << 1);
	if (r > mid) modify(l, r, v, p << 1 | 1); pushup(p);
}

ll query(int l, int r, int p) {
	if (l > r) return 0;
	if (l <= t[p].l && t[p].r <= r) return t[p].v;
	pushdown(p); int mid = t[p].l + t[p].r >> 1; ll res = 0;
	if (l <= mid) res = max(res, query(l, r, p << 1));
	if (r > mid) res = max(res, query(l, r, p << 1 | 1)); return res;
}

int T, n; ll a[MAXN], dp[MAXN];

int main() {
    for (scanf("%d", &T); T--;) {
	    scanf("%d", &n), build(1, n, 1);
	    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	    for (int i = n, l, r; i; i--) {
	    	dp[i] = a[i], l = i + 1, r = min<ll>(i + a[i], n);
	    	dp[i] = max(dp[i], query(l, r, 1));
	    	modify(l, n, a[i], 1), modify(i, i, dp[i], 1);
		}
		printf("%lld\n", dp[1]);
	}
}
