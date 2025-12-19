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