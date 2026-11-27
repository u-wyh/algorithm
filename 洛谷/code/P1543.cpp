// https://www.luogu.com.cn/problem/P1543
// 题意：每个同学 i 监视另一名同学 a[i]。选一些人去搬东西，要求每个被选者至少有一名监视自己的人没有被选。无人监视的同学不能选，输出最多能选几人。
// 数据范围：1 ≤ n ≤ 10^6，1 ≤ a[i] ≤ n，a[i] ≠ i。
// 算法标签：基环树、拓扑排序、贪心

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
queue <int> q;
int to[MAXN], n, ans, in[MAXN];
bool choose[MAXN], vis[MAXN]; // choose是看是否派去，vis是看在不在环中

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> to[i];
		in[to[i]] ++;
	}
	for (int i = 1; i <= n; i++)
		if (!in[i]) 
			q.push(i); // 无人监管，防止为所欲为，不能派去
	while (q.size()) {
		int u = q.front();
		vis[u] = 1;
		if (choose[u]) {
			in[to[u]] --; // 他去执行任务，他监视的人脱离了他的监管
			if (in[to[u]] == 0) 
				q.push(to[u]);
		} else { // 如果他不能去执行任务，他监视的人就要去执行任务
			if (!choose[to[u]]) { // 防止重新入队和额外统计答案
				ans++;
				q.push(to[u]);
			}
			choose[to[u]] = 1;
		}
		q.pop();
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i] && in[i]) { // 在环中，肯定选一半的人派去执行任务。
			int cnt = 0;
			for (int j = i; !vis[j]; j = to[j]) {
				cnt++;
				vis[j] = 1;
			}
			ans += cnt / 2; // 向下取整
		}
	}
	cout << ans;
}
