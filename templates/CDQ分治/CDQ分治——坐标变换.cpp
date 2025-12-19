// 天使玩偶，C++版
// 规定(x1, y1)和(x2, y2)之间的距离 = | x1 - x2 | + | y1 - y2 |
// 一开始先给定n个点的位置，接下来有m条操作，每种操作是如下两种类型中的一种
// 操作 1 x y : 在(x, y)位置添加一个点
// 操作 2 x y : 打印已经添加的所有点中，到(x, y)位置最短距离的点是多远
// 1 <= n、m <= 3 * 10^5
// 0 <= x、y <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P4169
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题难度很大 进行了坐标系变换 其实就是想到坐标变换有点难 但实际上还是很简单的
//将第一象限的全部对应到第二象限、第三象限、第四象限
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300001;
const int MAXV = 1000002;
const int INF = 1000000001;

int n, m, v;

// op == 1代表添加事件，x、y、空缺
// op == 2代表查询事件，x、y、查询编号q
// tim永远保持原始时序，每次变换象限都拷贝给arr，然后执行cdq分治
struct Node {
   	int op, x, y, q;
};

bool NodeCmp(Node a, Node b) {
   	return a.x < b.x;
}

Node tim[MAXN << 1];
Node arr[MAXN << 1];
int cnte = 0;
int cntq = 0;

// 树状数组，下标是y的值，维护前缀范围上的最大值
int tree[MAXV];

int ans[MAXN];

int lowbit(int i) {
   	return i & -i;
}

// 树状数组，如果i位置之前的值更大，忽略，num更大才更新
void more(int i, int num) {
	while (i <= v) {
		tree[i] = max(tree[i], num);
		i += lowbit(i);
	}
}

// 树状数组，查询1~i范围上的最大值
int query(int i) {
	int ret = -INF;
	while (i > 0) {
		ret = max(ret, tree[i]);
		i -= lowbit(i);
	}
	return ret;
}

// 因为本题的特殊性，树状数组一定全部清空
// 所以当初更新时，i位置碰过哪些位置，一律设置无效值即可
void clear(int i) {
	while (i <= v) {
		tree[i] = -INF;
		i += lowbit(i);
	}
}

void merge(int l, int m, int r) {
	int p1, p2;
	for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
		while (p1 + 1 <= m && arr[p1 + 1].x <= arr[p2].x) {
			p1++;
			if (arr[p1].op == 1) {
				more(arr[p1].y, arr[p1].x + arr[p1].y);
			}
		}
		if (arr[p2].op == 2) {
			ans[arr[p2].q] = min(ans[arr[p2].q], arr[p2].x + arr[p2].y - query(arr[p2].y));
		}
	}
	for (int i = l; i <= p1; i++) {
		if (arr[i].op == 1) {
			clear(arr[i].y);
		}
	}
	sort(arr + l, arr + r + 1, NodeCmp);
}

void cdq(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	merge(l, mid, r);
}

// 点变换到第一象限进行cdq分治
void to1() {
	for (int i = 1; i <= cnte; i++) {
		arr[i] = tim[i];
	}
	cdq(1, cnte);
}

// 点变换到第二象限进行cdq分治
void to2() {
	for (int i = 1; i <= cnte; i++) {
		arr[i] = tim[i];
		arr[i].x = v - arr[i].x;
	}
	cdq(1, cnte);
}

// 点变换到第三象限进行cdq分治
void to3() {
	for (int i = 1; i <= cnte; i++) {
		arr[i] = tim[i];
		arr[i].x = v - arr[i].x;
		arr[i].y = v - arr[i].y;
	}
	cdq(1, cnte);
}

// 点变换到第四象限进行cdq分治
void to4() {
	for (int i = 1; i <= cnte; i++) {
		arr[i] = tim[i];
		arr[i].y = v - arr[i].y;
	}
	cdq(1, cnte);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
		tim[++cnte].op = 1;
		tim[cnte].x = ++x;
		tim[cnte].y = ++y;
		v = max(v, max(x, y));
	}
	for (int i = 1, op, x, y; i <= m; i++) {
		cin >> op >> x >> y;
		tim[++cnte].op = op;
		tim[cnte].x = ++x;
		tim[cnte].y = ++y;
		if (op == 2) {
			tim[cnte].q = ++cntq;
		}
		v = max(v, max(x, y));
	}
	v++;
	for (int i = 1; i <= v; i++) {
		tree[i] = -INF;
	}
	for (int i = 1; i <= cntq; i++) {
		ans[i] = INF;
	}
	to1();
	to2();
	to3();
	to4();
	for (int i = 1; i <= cntq; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}