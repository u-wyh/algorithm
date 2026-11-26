// https://www.luogu.com.cn/problem/P10318
// 题意：n 个水槽围成一圈，容量为 a[i]，开始都装满。每秒同时把每个水槽的水全倒到下一个水槽，装不下的部分溢出。输出从第 1 秒到第 n 秒，每秒结束后的总水量。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ a[i] ≤ 10^9。

#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
int l[200005], r[200005];
int ans[200005];

signed main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = n + 1; i <= n + n; i++)
		a[i] = a[i - n];
	l[1] = 0;
	for (int i = 2; i <= n + n; i++) {
		int x = i - 1;
		while (a[x] >= a[i] && x != 0)
			x = l[x];
		l[i] = x;
	}
	r[n + n] = n + n + 1;
	for (int i = n + n - 1; i >= 1; i--) {
		int x = i + 1;
		while (a[x] > a[i] && x != 0 && x != n + n + 1)
			x = r[x];
		r[i] = x;
	}
	int tmp = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] < a[tmp] || tmp == 0)
			tmp = i;
		sum += a[i];
	}\
	for (int i = tmp + 1; i <= tmp + n; i++) {
		if (a[i] == a[tmp])
			continue;
		int chang = r[i] - l[i] - 1, kuan = a[i] - max(a[l[i]] + 1, a[r[i]] + 1) + 1;
		ans[1] += kuan;
		ans[chang + 1] -= kuan;
	}
	for (int i = 1; i <= n; i++)
		ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i++)
		ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i++)
		cout << sum - ans[i] <<' ';
}