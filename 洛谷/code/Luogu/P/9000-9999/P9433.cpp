#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

struct Edge {
	int to, w;
};

int n, q, k, root, deep[N], dp[N][30], sz[N], dis[N], sum;

bool isK[N];

vector<Edge> nbr[N];

int dfs(int cur, int fa) {
	deep[cur] = deep[fa] + 1;
	dp[cur][0] = fa;
	if (isK[cur])
		sz[cur] = 1;
	for (int j = 1; (1 << j) <= deep[cur]; j++)
		dp[cur][j] = dp[dp[cur][j - 1]][j - 1];
	for (auto nxt : nbr[cur])
		if (nxt.to != fa)
			dis[nxt.to] = dis[cur] + nxt.w, sz[cur] += dfs(nxt.to, cur);
	return sz[cur];
}

void get_sum(int cur, int fa) {
	if (!sz[cur])
		return ;
	isK[cur] = 1;
	for (auto nxt : nbr[cur])
		if (nxt.to != fa)
			get_sum(nxt.to, cur), sum += isK[nxt.to] * nxt.w;
}

int nbrK(int cur) {
	if (isK[cur])
		return cur;
	for (int j = 20; j >= 0; j--)
		if (dp[cur][j] && !isK[dp[cur][j]])
			cur = dp[cur][j];
	return dp[cur][0];
}

int lca(int x, int y) {
	if (deep[x] > deep[y])
		swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (deep[dp[y][i]] >= deep[x])
			y = dp[y][i];
	if (x == y)
		return x;
	for (int i = 20; i >= 0; i--)
		if (dp[x][i] != dp[y][i])
			x = dp[x][i], y = dp[y][i];
	return dp[x][0];
}

int dist(int u, int v) {
	return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> q >> k;
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		nbr[u].emplace_back((Edge){v, w});
		nbr[v].emplace_back((Edge){u, w});
	}
	for (int i = 1, u; i <= k; i++) {
		cin >> u;
		isK[u] = 1;
		root = u;
	}
	dfs(root, 0);
	get_sum(root, 0);
	while (q --) {
		int s, t, u, v;
        cin >> s >> t;
		u = nbrK(s), v = nbrK(t);
		cout << sum * 2 - dist(u, v) + dist(s, u) + dist(v, t) << "\n";
	}
	return 0;
}
