// 领导集团问题，C++版
// 一共有n个节点，给定每个点的点权，所有节点组成一棵树
// 已知1号节点是整棵树的头，其他节点的父亲节点都会给出
// 如果你在树上选择了u、v两个节点，并且u是v的祖先节点的话
// 那么需要保证 u的点权 <= v的点权，除此之外就没有别的限制了
// 打印你最多能在树上选择几个点
// 1 <= n <= 2 * 10^5
// 1 <= 点权 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P4577
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// dp[u][i]的含义是在以u为头的子树中  选择出的权值最小为i  最多可以选几个
// 转移方程是：(v是u的子节点)
// 选u的情况  dp[u][arr[u]]=1+max(dp[v][arr[u]~n])  因为如果选择了u  那么u的权值一定是子树上选择的最小的
// 不选u的情况  dp[u][i]=dp[u][i]+max(dp[v][i~n])
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200001;
const int MAXT = MAXN * 20;

int n;
int arr[MAXN];
int sorted[MAXN];
int cntv;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int maxv[MAXT];
int addLazy[MAXT];
int cntt;

int kth(int num) {
	int left = 1, right = cntv, ret = 0;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (sorted[mid] <= num) {
			ret = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return ret;
}

void addEdge(int u, int v) {
	nxt[++cntg] = head[u];
	to[cntg] = v;
	head[u] = cntg;
}

void up(int i) {
   	maxv[i] = max(maxv[ls[i]], maxv[rs[i]]);
}

void lazy(int i, int v) {
	if (i != 0) {
		maxv[i] += v;
		addLazy[i] += v;
	}
}

void down(int i) {
	if (addLazy[i] > 0) {
		lazy(ls[i], addLazy[i]);
		lazy(rs[i], addLazy[i]);
		addLazy[i] = 0;
	}
}

// jobi来了个新值jobv，如果比之前获得的值更大就更新，否则不更新
int update(int jobi, int jobv, int l, int r, int i) {
	int rt = i;
	if (rt == 0) {
		rt = ++cntt;
	}
	if (l == r) {
		maxv[rt] = max(maxv[rt], jobv);
	} else {
		down(rt);
		int mid = (l + r) >> 1;
		if (jobi <= mid) {
			ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
		} else {
			rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
		}
		up(rt);
	}
	return rt;
}

// 查询[jobl..jobr]范围上的最大值
int query(int jobl, int jobr, int l, int r, int i) {
	if (i == 0) {
		return 0;
	}
	if (jobl <= l && r <= jobr) {
		return maxv[i];
	}
	down(i);
	int mid = (l + r) >> 1;
	int ans = 0;
	if (jobl <= mid) {
		ans = max(ans, query(jobl, jobr, l, mid, ls[i]));
	}
	if (jobr > mid) {
		ans = max(ans, query(jobl, jobr, mid + 1, r, rs[i]));
	}
	return ans;
}

// 线段树合并
// max1代表dp[u][r+1...]的最大值，max2代表dp[v][r+1...]的最大值
int merge(int l, int r, int t1, int t2, int max1, int max2) {
	if (t1 == 0 || t2 == 0) {
		// 如果有一个节点为0  那么说明完全可以用另外一个代替  并用自己的来更新（前提是另外一个得存在）
		if (t1 != 0) {
			lazy(t1, max2);
		}
		if (t2 != 0) {
			lazy(t2, max1);
		}
		return t1 + t2;
	}
	if (l == r) {
		maxv[t1] += max(maxv[t2], max2);
	} else {
		down(t1);
		down(t2);
		int mid = (l + r) >> 1;
		ls[t1] = merge(l, mid, ls[t1], ls[t2], max(max1, maxv[rs[t1]]), max(max2, maxv[rs[t2]]));
		rs[t1] = merge(mid + 1, r, rs[t1], rs[t2], max1, max2);
		up(t1);
	}
	return t1;
}

void dp(int u) {
	// sum的作用就是用于辅助计算选择u的情况
	int sum = 0;
	for (int e = head[u]; e; e = nxt[e]) {
		int v = to[e];
		dp(v);
		sum += query(arr[u], cntv, 1, cntv, root[v]);
		// 不选u的情况，每棵子树合并一遍
		root[u] = merge(1, cntv, root[u], root[v], 0, 0);
	}
	// 选u的情况，最后sum需要加1
	root[u] = update(arr[u], sum + 1, 1, cntv, root[u]);
}

void prepare() {
	for (int i = 1; i <= n; i++) {
		sorted[++cntv] = arr[i];
	}
	sort(sorted + 1, sorted + cntv + 1);
	int len = 1;
	for (int i = 2; i <= cntv; i++) {
		if (sorted[len] != sorted[i]) {
			sorted[++len] = sorted[i];
		}
	}
	cntv = len;
	for (int i = 1; i <= n; i++) {
		arr[i] = kth(arr[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	for (int i = 2, fa; i <= n; i++) {
		cin >> fa;
		addEdge(fa, i);
	}
	prepare();
	dp(1);
	cout << query(1, cntv, 1, cntv, root[1]) << '\n';
	return 0;
}