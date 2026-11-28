// https://www.luogu.com.cn/problem/P10194
// 题意：N 头奶牛围成一圈，第 i 头的桶容量为 a[i]，起初装满。
// 每分钟每头把全部牛奶倒给下一头，所有传递同时发生，超出容量的部分倒掉。
// 依次输出每分钟结束后剩余的总量，共 N 行。
// 数据范围：1 ≤ N ≤ 5 × 10^5，1 ≤ a[i] ≤ 10^9。
// 难度评分：1600（洛谷分级换算）
// 算法标签：单调栈思想、差分、前缀和

#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
int l[1000005], r[1000005];
int ans[1000005];

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
	}
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
		cout << sum - ans[i] <<endl;
}