#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 100010, INF = 1e9;

struct edge {
	int to, cost;
};
std::vector<edge> G[MAXN], G1[MAXN], G2[MAXN];

int n, m, d1[MAXN], d2[MAXN], d[MAXN];
bool exist[MAXN];
queue<int> q;

void spfa1(int s) { //第一个GPS系统
	fill(d1+1, d1+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d1[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G1[v].size(); i++) {
			edge e = G1[v][i];
			if (d1[v] + e.cost < d1[e.to]) {
				d1[e.to] = d1[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

void spfa2(int s) { //第二个GPS系统
	fill(d2+1, d2+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d2[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G2[v].size(); i++) {
			edge e = G2[v][i];
			if (d2[v] + e.cost < d2[e.to]) {
				d2[e.to] = d2[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

void spfa(int s) { //计算抱怨值
	fill(d+1, d+1+n, INF);
	memset(exist, false, sizeof(exist));//初始化莫忘掉！
	d[s] = 0;
	q.push(s);
	exist[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		exist[v] = false;
		for (int i=0; i<G[v].size(); i++) {
			edge e = G[v][i];
			if (d[v] + e.cost < d[e.to]) {
				d[e.to] = d[v] + e.cost;
				if (!exist[e.to]) {
					q.push(e.to);
					exist[e.to] = true;
				}
			} 
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i=1; i<=m; i++) {
		int u, v, c1, c2;
		cin >> u >> v >> c1 >> c2;
		G1[v].push_back((edge){u, c1});
		G2[v].push_back((edge){u, c2});//注意！因为是有向图，所以在建反向图时，要注意方向。
	}//建反向图
	spfa1(n);
	spfa2(n);
	for (int i=1; i<=n; i++)
		for (int j=0; j<G1[i].size(); j++) {
			edge e1 = G1[i][j], e2 = G2[i][j];
			int cnt = 0;
			if (d1[e1.to] - d1[i] != e1.cost) cnt++;
			if (d2[e2.to] - d2[i] != e2.cost) cnt++; //注意！这里不能写成d2[i] - d2[e.to]，因为你之前建的是反向图，所以应该是e2.to的权值大。上一行同理。
			G[e1.to].push_back((edge){i, cnt}); //注意！因为最后一次跑SPFA时，是从1号节点出发的，所以建图时要是正向图。
		}
	spfa(1);
	cout << d[n]  << endl;
	return 0;//完结撒花！
}