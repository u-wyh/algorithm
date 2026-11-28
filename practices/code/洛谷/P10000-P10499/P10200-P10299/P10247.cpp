// https://www.luogu.com.cn/problem/P10247
// 题意：给 m 个不同的数对。
// 对第 i 对，找出另一对 j，使这两对里的四个数字互不相同。
// 输出任意一个符合要求的下标 j，找不到就输出 0。
// 数据范围：1 ≤ u[i] < v[i] ≤ n ≤ 3 × 10^5，
// 1 ≤ m ≤ 3 × 10^5。
// 难度评分：1300（洛谷分级换算）
// 算法标签：枚举、查询分组

#include <bits/stdc++.h>

inline bool ok(int a, int b, int c, int d) {
	if (a == c || a == d || b == c || b == d)
        return false;
	return true;
}

#define MAXN 300001
int x[MAXN], y[MAXN], res[MAXN];
void solve(std::vector<std::pair<int, int>> &m, int n, int tar) {
	std::vector<int> pos;
	for (int i = 1; i <= n; ++i)
        if (x[i] != tar && y[i] != tar) pos.push_back(i);
	// for each m, try to find match tar.
	if (pos.empty())
        return;
	int P = x[pos[0]], Q = y[pos[0]];
	for (auto [i, key] : m)
        if (key != P && key != Q) res[i] = pos[0];
	else /* O(1) * O(n) */
		for (int u : pos) if (x[u] != key && y[u] != key) res[i] = u;
}

int main() {
	int m, n;
	std::cin >> m >> n;
	std::vector<std::pair<int, int>> vX, vY;
	for (int i = 1; i <= n; ++i)
        std::cin >> x[i] >> y[i];
	for (int i = 2; i <= n; ++i)
        if (ok(x[1], y[1], x[i], y[i]))
            res[i] = 1, res[1] = i;
        else if (x[i] == x[1] || y[i] == x[1])
            vX.push_back({i, x[i] ^ y[i] ^ x[1]});
        else
            vY.push_back({i, x[i] ^ y[i] ^ y[1]});
	solve(vX, n, x[1]), solve(vY, n, y[1]);
	for (int i = 1; i <= n; ++i)
        std::cout << res[i] << " \n"[i == n];
	return 0;
}
