#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e4+5;
int n, tot, a[N<<2];
ll ans;//十年oi一场空，不开long long见祖宗
struct edge {
	int y, x1, x2, k;
} e[N<<1];
struct SegmentTree {
	int l, r;
	ll len, cnt;
} t[N<<3];
void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) return;
	int mid = (l+r)>>1;
	build(p<<1, l, mid);
	build(p<<1|1, mid+1, r);
}
void update(int p) {//向上传递
	if (t[p].cnt) t[p].len = a[t[p].r+1]-a[t[p].l];
	else t[p].len = t[p<<1].len+t[p<<1|1].len;
}
void change(int p, int l, int r, int x) {
	if (l <= t[p].l && t[p].r <= r) {
		t[p].cnt += x;
		update(p);
		return;
	}
	int mid = (t[p].l+t[p].r)>>1;
	if (l <= mid) change(p<<1, l, r, x);
	if (mid < r) change(p<<1|1, l, r, x);
	update(p);
}
bool cmp(edge x, edge y) {return x.y < y.y;}
int query(int x) {return lower_bound(a+1, a+tot+1, x)-a;}//查询
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		e[(i<<1)-1] = (edge){y1, x1, x2, 1};
		e[i<<1] = (edge){y2, x1, x2, -1};
		a[(i<<1)-1] = x1, a[i<<1] = x2;
	}
	n <<= 1;
	sort(e+1, e+n+1, cmp);
	sort(a+1, a+n+1);
	tot = unique(a+1, a+n+1)-a-1;//离散化
	build(1, 1, tot);
	for (int i = 1; i <= n; ++i) {
		change(1, query(e[i].x1), query(e[i].x2)-1, e[i].k);
		ans += t[1].len*(e[i+1].y-e[i].y);
	}
	cout << ans;
	return 0;
}
