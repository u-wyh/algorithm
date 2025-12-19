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
