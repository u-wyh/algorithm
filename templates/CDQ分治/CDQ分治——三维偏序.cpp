// 三维偏序，C++版
// 一共有n个对象，属性值范围[1, k]，每个对象有a属性、b属性、c属性
// f(i)表示，aj <= ai 且 bj <= bi 且 cj <= ci 且 j != i 的j的数量
// ans(d)表示，f(i) == d 的i的数量
// 打印所有的ans[d]，d的范围[0, n)
// 1 <= n <= 10^5
// 1 <= k <= 2 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3810
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//cdq分治其实和归并分治的过程大同小异
//对于三维排序问题  我们利用第一维进行一个排序分组  第二维进行组内排序
//第三维用于收集答案（借助于树状数组或者线段树）
//由于需要使用树状数组（或者线段树）的时间复杂度已经是n*logn了  那么排序用内置函数完成也无妨
//要注意一个小坑  就是三维都一样的需要提前补充一下答案
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXK = 200001;

int n, k;

struct Node {
   	int i, a, b, c;
};

//根据第一维进行排序分组  为了考虑三维值都一样的  需要bc比较
bool CmpAbc(Node x, Node y) {
	if (x.a != y.a) {
		return x.a < y.a;
	}
	if (x.b != y.b) {
		return x.b < y.b;
	}
	return x.c < y.c;
}

//第二维的排序
bool CmpB(Node x, Node y) {
   	return x.b < y.b;
}

Node arr[MAXN];

// 树状数组，根据属性c的值增加词频，查询 <= 某个数的词频累加和
int tree[MAXK];

// 每个对象的答案
int f[MAXN];

// 题目要求的ans[d]
int ans[MAXN];

int lowbit(int i) {
   	return i & -i;
}

void add(int i, int v) {
	while (i <= k) {
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

//合并左右两部分
void merge(int l, int m, int r) {
	// 利用左、右各自b属性有序
	// 不回退的找，当前右组对象包括了几个左组的对象
	int p1, p2;
	for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
		//p1的初始位置是在l-1 这里需要注意一下
		while (p1 + 1 <= m && arr[p1 + 1].b <= arr[p2].b) {
			p1++;
			add(arr[p1].c, 1);
		}
		f[arr[p2].i] += query(arr[p2].c);
	}
	// 清空树状数组   这里需要注意 用多少就清空多少 不要清多了
	for (int i = l; i <= p1; i++) {
		add(arr[i].c, -1);
	}
	// 直接根据b属性排序，无需写经典的归并过程，课上重点解释了原因
	sort(arr + l, arr + r + 1, CmpB);
}

// 大顺序已经按a属性排序，cdq分治里按b属性重新排序
void cdq(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) / 2;
	cdq(l, mid);
	cdq(mid + 1, r);
	merge(l, mid, r);
}

void prepare() {
	// 根据a排序，a一样根据b排序，b一样根据c排序
	// 排序后a、b、c一样的同组内，组前的下标得不到同组后面的统计量
	// 所以把这部分的贡献，提前补偿给组前的下标，然后再跑CDQ分治
	//其实一般来说 按照a排序即可  但是这里是为了解决那个小坑点  所以bc也要排序
	sort(arr + 1, arr + n + 1, CmpAbc);
	for (int l = 1, r = 1; l <= n; l = ++r) {
		while (r + 1 <= n && arr[l].a == arr[r + 1].a && arr[l].b == arr[r + 1].b && arr[l].c == arr[r + 1].c) {
			r++;
		}
		for (int i = l; i <= r; i++) {
			f[arr[i].i] = r - i;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		arr[i].i = i;
		cin >> arr[i].a >> arr[i].b >> arr[i].c;
	}
	prepare();
	cdq(1, n);
	for (int i = 1; i <= n; i++) {
		ans[f[i]]++;
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}