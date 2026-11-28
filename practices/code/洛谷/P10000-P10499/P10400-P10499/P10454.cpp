// https://www.luogu.com.cn/problem/P10454
// 题意：每组给两个 n×n 的滑块局面，0 是空格。
// 每次可把空格和上下左右相邻的数字交换。
// 判断两个局面能否互相到达，可以就输出 TAK，否则输出 NIE。
// 数据范围：1 ≤ n < 500，n 为奇数，
// 每个局面恰好包含 0 到 n²-1 各一次。
// 难度评分：1600（洛谷分级换算）
// 算法标签：归并排序、逆序对

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 500*500+100;

int temp[N];

ll msort(int l, int r, int *a) {
	if (l>=r) return 0;
	int mid = l+r>>1, k=0;
	ll res = msort(l, mid, a)+msort(mid+1, r, a);
	int i = l, j = mid+1;
	while (i<=mid && j<=r)
		if (a[i]<=a[j]) temp[k++] = a[i++];
		else temp[k++] = a[j++], res += (mid-i+1);
	while (i<=mid) temp[k++] = a[i++];
	while (j<=r) temp[k++] = a[j++];
	for (i=l, j=0; i<=r; i++, j++) a[i] = temp[j];
	return res;
}

int st[N], en[N];

int main()
{
	for (int n; cin >> n;) {
		n*=n;
		for(int i=1, x, f=0; i<=n&&cin>>x; i++, f|=(!x)) st[i-f] = x;
		for(int i=1, x, f=0; i<=n&&cin>>x; i++, f|=(!x)) en[i-f] = x;
		ll u = msort(1, n - 1, st);
		ll v = msort(1, n - 1, en);
		if((u&1)==(v&1)) cout << "TAK\n";
		else cout << "NIE\n";
	}
	return 0;
}
