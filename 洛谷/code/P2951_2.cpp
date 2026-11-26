// https://www.luogu.com.cn/problem/P2951
// 题意：输入谷仓数 N、无向边数 M，以及 M 条连接 A_i 与 B_i 的无向边（边权均为 1，起点为 1 号谷仓）。
// 计算所有谷仓到 1 号谷仓的最短路径长度，找出距离最大的谷仓。
// 若有多个谷仓并列最远，记录编号最小的谷仓编号、该最远距离、以及达到该最远距离的谷仓总数。
// 输出一行三个用空格隔开的整数：最远谷仓的最小编号、最远距离、满足该距离的谷仓数。
// 数据范围：对于 100% 的数据，2 <= n <= 50000，1 <= m <= 50000。
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

int n, m, a, b, h[100007], cnt, dis[100007], vis[100007];
struct edge {
	int v, to, nxt;
}e[100007];
priority_queue<pair<int, int> > q;
void a_e(int u, int v) {
	e[++cnt] = (edge){1, v, h[u]}; h[u] = cnt;
	e[++cnt] = (edge){1, u, h[v]}; h[v] = cnt;
}
void dj() {
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q.push(make_pair(0, 1));
	while(!q.empty()) {
		int x = q.top().second;
		q.pop();
		if(vis[x])	continue;
		vis[x] = 1;
		for(int i = h[x]; i; i = e[i].nxt) {
			int v = e[i].to, z = e[i].v;
			if(dis[v] > dis[x] + z) {
				dis[v] = dis[x] + z;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b);
		a_e(a, b);
	}
	dj();
	int maxi = 0, ans = 0;
	for(int i = 1; i <= n; ++i)
		maxi = max(maxi, dis[i]);
	for(int i = 1; i <= n; ++i)
		if(dis[i] == maxi) {
			printf("%d", i);
			break;
		}
	printf(" %d", maxi);
	for(int i = 1; i <= n; ++i)
		if(dis[i] == maxi)	ans++;
	printf(" %d", ans);
	return 0;
}
