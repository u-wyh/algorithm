// https://www.luogu.com.cn/problem/P8436
// 题意：给定 n 点 m 边的无向图（可能有重边和自环），
// 求所有边双连通分量的个数及每个分量包含的结点（分量及结点顺序任意）。
// 数据范围：100% 数据满足 1 <= n <= 5*10^5，
// 1 <= m <= 2*10^6。
// 难度评分：1600（洛谷分级换算）
// 算法标签：Tarjan、边双连通分量、深度优先搜索
#include <bits/stdc++.h>
using namespace std;
#define MAXN 500001

int n, m, u, v, cnt;
int dfn[MAXN], low[MAXN];
vector<pair<int, int>> e[MAXN];
vector<vector<int>> ans;
stack<int> st;

void tarjan(int x, int las){
	low[x] = dfn[x] = ++cnt;
	st.push(x);
	for (auto i: e[x]){
		if (i.second == (las ^ 1)) continue;
		if (!dfn[i.first]){
			tarjan(i.first, i.second);
			low[x] = min(low[x], low[i.first]);
		}else low[x] = min(low[x], dfn[i.first]);
	}
	if (dfn[x] == low[x]){
		vector<int> vec;
		vec.push_back(x);
		while (st.top() != x){
			vec.push_back(st.top());
			st.pop();
		}
		st.pop();
		ans.push_back(vec);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i(1); i<=m; ++i){
		cin >> u >> v;
		e[u].push_back(make_pair(v, i<<1));
		e[v].push_back(make_pair(u, i<<1|1));
	}
	for (int i(1); i<=n; ++i){
		if (!dfn[i]) tarjan(i, 0);
	}

	cout << ans.size() << '\n';
	for (auto i: ans){
		cout << i.size() << ' ';
		for (auto j: i) cout << j << ' ';
		cout << '\n';
	}

	return 0;
}
