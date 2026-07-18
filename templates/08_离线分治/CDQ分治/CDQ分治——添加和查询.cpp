// 摩基亚，C++版
// 给定数字w，表示一个w * w的正方形区域，所有位置都在其中
// 接下来有m条操作，每种操作是如下两种类型中的一种
// 操作 1 x y v   : 坐标(x, y)位置增加了v个人
// 操作 2 a b c d : 打印左上角(a, b)、右下角(c, d)区域里的人数
// 1 <= w <= 2 * 10^6
// 1 <= m <= 2 * 10^5
// 0 <= v <= 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P4390
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题将三维偏序和空间计数结合
//既有动态的添加数据  也有二维查询
//我们要把坐标全部加一  因为查询操作我们变成了四个  其中会有减去1
//但是树状数组里面不要出现0  所以我们全部加一
//时间作为第一维  x坐标第二维 在y上建立树状数组添加信息 相当于在二维偏序上加一个时间维度
#include <bits/stdc++.h>
using namespace std;
const int MAXM = 200001;
const int MAXV = 2000002;
const int INF = 1000000001;

int w;

// op == 1表示增加事件，x、y、人数v
// op == 2表示查询事件，x、y、效果v、查询编号q
struct Node {
   	int op, x, y, v, q;
};

bool NodeCmp(Node a, Node b) {
   	return a.x < b.x;
}

Node arr[MAXM];
int cnte = 0;
int cntq = 0;

// 树状数组
int tree[MAXV];

int ans[MAXM];

int lowbit(int i) {
   	return i & -i;
}

void add(int i, int v) {
	while (i <= w) {
		tree[i] += v;
		i += lowbit(i);
	}
}

int query(int i) {
	int ret = 0;
	while (i > 0) {
		ret += tree[i];
		i -= lowbit(i);
	}
	return ret;
}

void addPeople(int x, int y, int v) {
    arr[++cnte].op = 1;
    arr[cnte].x = x;
    arr[cnte].y = y;
    arr[cnte].v = v;
}

void addQuery(int x, int y, int v, int q) {
    arr[++cnte].op = 2;
    arr[cnte].x = x;
    arr[cnte].y = y;
    arr[cnte].v = v;
    arr[cnte].q = q;
}

void merge(int l, int m, int r) {
	int p1, p2;
	for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
		// 这里不能像二维计数那样统计答案  因为这里的第二维是x坐标  第三维才是y坐标
		while (p1 + 1 <= m && arr[p1 + 1].x <= arr[p2].x) {
			p1++;
			if (arr[p1].op == 1) {
				add(arr[p1].y, arr[p1].v);
			}
		}
		if (arr[p2].op == 2) {
			ans[arr[p2].q] += arr[p2].v * query(arr[p2].y);
		}
	}
	for (int i = l; i <= p1; i++) {
		if (arr[i].op == 1) {
			add(arr[i].y, -arr[i].v);
		}
	}
	sort(arr + l, arr + r + 1, NodeCmp);
}

void cdq(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	cdq(l, mid);
	cdq(mid + 1, r);
	merge(l, mid, r);
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int tmp;
	cin >> tmp >> w;
	w++;
	int op, x, y, v, a, b, c, d;
	cin >> op;
	while (op != 3) {
		if (op == 1) {
			cin >> x >> y >> v;
			x++; y++;
			addPeople(x, y, v);
		} else {
			cin >> a >> b >> c >> d;
			a++; b++; c++; d++;
			addQuery(c, d, 1, ++cntq);
			addQuery(a - 1, b - 1, 1, cntq);
			addQuery(a - 1, d, -1, cntq);
			addQuery(c, b - 1, -1, cntq);
		}
		cin >> op;
	}
	cdq(1, cnte);
	for (int i = 1; i <= cntq; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}