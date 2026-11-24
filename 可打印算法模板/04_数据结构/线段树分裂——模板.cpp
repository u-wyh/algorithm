// 用途：维护多个可合并、可按值域分裂的权值集合及区间和、第 k 小。
// 时间：单点加、区间和、第 k 小、分裂 O(log V)；合并 O(k)，k 为两树重叠节点数。
// 空间：O(n+m log V) 个节点，回收合并后的节点。
// 例题：https://www.luogu.com.cn/problem/P5494
// 题意：若干权值集合支持按值域分裂、合并、计数和第 k 小。
// 思路：动态开点权值线段树递归拆分或合并节点。
// 注意：n,m≤200000；合并 x、y 后 y 清空；x≠y，计数非负，第 k 小的 k 必须合法。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = MAXN * 25;

int n, m;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
long long sum[MAXT];
int version;

int pool[MAXT];
int top;

void prepare() {
	top = 0;
	for (int i = 1; i < MAXT; i++) {
		pool[++top] = i;
	}
}

int newNode() {
	// m 次分裂最多新增 O(m log n) 个节点；按题目上限调整 MAXT。
   	return pool[top--];
}

void del(int i) {
	pool[++top] = i;
	ls[i] = 0;
	rs[i] = 0;
	sum[i] = 0;
}

void up(int i) {
   	sum[i] = (sum[ls[i]] + sum[rs[i]]);
}

int add(int jobi, int jobv, int l, int r, int i) {
	int rt = i;
	if (rt == 0) {
		rt = newNode();
	}
	if (l == r) {
		sum[rt] += jobv;
	} else {
		int mid = (l + r) >> 1;
		if (jobi <= mid) {
			ls[rt] = add(jobi, jobv, l, mid, ls[rt]);
		} else {
			rs[rt] = add(jobi, jobv, mid + 1, r, rs[rt]);
		}
		up(rt);
	}
	return rt;
}

long long query(int jobl, int jobr, int l, int r, int i) {
	if (i == 0) {
		return 0;
	}
	if (jobl <= l && r <= jobr) {
		return sum[i];
	}
	int mid = (l + r) >> 1;
	long long ans = 0;
	if (jobl <= mid) {
		ans += query(jobl, jobr, l, mid, ls[i]);
	}
	if (jobr > mid) {
		ans += query(jobl, jobr, mid + 1, r, rs[i]);
	}
	return ans;
}

int kth(long long jobk, int l, int r, int i) {
	if (i == 0) {
		return -1;
	}
	if (l == r) {
		return l;
	}
	int mid = (l + r) >> 1;
	if (sum[ls[i]] >= jobk) {
		return kth(jobk, l, mid, ls[i]);
	} else {
		return kth(jobk - sum[ls[i]], mid + 1, r, rs[i]);
	}
}

int merge(int l, int r, int t1, int t2) {
	if (t1 == 0 || t2 == 0) {
		return t1 + t2;
	}
	if (l == r) {
		sum[t1] += sum[t2];
	} else {
		int mid = (l + r) >> 1;
		ls[t1] = merge(l, mid, ls[t1], ls[t2]);
		rs[t1] = merge(mid + 1, r, rs[t1], rs[t2]);
		up(t1);
	}
	// 这是和线段树合并唯一存在差别的地方，t2节点没用之后，放到回收池中
	del(t2);
	return t1;
}

// 表示分割的两个树的此时来到的头结点
int tree1, tree2;

void split(int jobl, int jobr, int l, int r, int t1) {
	if (t1 == 0) {
		// 当前来到了t1  此时t1也是0   说明本身就是什么都没有
		// 设置好tree1 tree2
		tree1 = t1;
		tree2 = 0;
		return;
	}
	if (jobl <= l && r <= jobr) {
		// 如果范围全包  那么直接将t1给tree2
		tree1 = 0;
		tree2 = t1;
		return;
	}
	int t2 = newNode();
	int mid = (l + r) >> 1;
	if (jobl <= mid) {
		split(jobl, jobr, l, mid, ls[t1]);
		// 划分开左子树节点
		ls[t1] = tree1;
		ls[t2] = tree2;
	}
	if (jobr > mid) {
		split(jobl, jobr, mid + 1, r, rs[t1]);
		// 划分开右子树节点
		rs[t1] = tree1;
		rs[t2] = tree2;
	}
	up(t1);
	up(t2);
	// 没有元素的一侧直接回收，避免多次空分裂耗尽节点池。
	if (sum[t1] == 0) {
		del(t1);
		t1 = 0;
	}
	if (sum[t2] == 0) {
		del(t2);
		t2 = 0;
	}
	// 注意更新tree1  tree2
	tree1 = t1;
	tree2 = t2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	prepare();
	cin >> n >> m;
	version = 1;
	for (int i = 1, x; i <= n; i++) {
		cin >> x;
		root[version] = add(i, x, 1, n, root[1]);
	}
	for (int i = 1, op, x, y, z; i <= m; i++) {
		cin >> op;
		if (op == 0) {
			cin >> x >> y >> z;
			split(y, z, 1, n, root[x]);
			root[x] = tree1;
			root[++version] = tree2;
		} else if (op == 1) {
			cin >> x >> y;
			root[x] = merge(1, n, root[x], root[y]);
			root[y] = 0;
		} else if (op == 2) {
			cin >> x >> y >> z;
			root[x] = add(z, y, 1, n, root[x]);
		} else if (op == 3) {
			cin >> x >> y >> z;
			cout << query(y, z, 1, n, root[x]) << '\n';
		} else {
			cin >> x >> y;
			cout << kth(y, 1, n, root[x]) << '\n';
		}
	}
	return 0;
}
