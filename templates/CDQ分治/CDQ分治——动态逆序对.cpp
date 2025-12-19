// 动态逆序对，C++版
// 给定一个长度为n的排列，1~n所有数字都出现一次
// 如果，前面的数 > 后面的数，那么这两个数就组成一个逆序对
// 给定一个长度为m的数组，表示依次删除的数字
// 打印每次删除数字前，排列中一共有多少逆序对，一共m条打印
// 1 <= n <= 10^5
// 1 <= m <= 5 * 10^4
// 测试链接 : https://www.luogu.com.cn/problem/P3157
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题还是比较巧妙的
//我们将时间作为第一维   坐标作为第二维  效果作为第三维  统计答案作为第四维（附属）
//首先按照时间排序  那么可以有一点先确定 就是左边的组不能够统计右边的信息 
//即他们的地位是不平等的   时效性的设置
//右边的组需要统计左边组可以和自己构成逆序对的包括：前面大于自己的  后面小于自己的（这里的前面、后面指的是左组中位置在当前位置的前面后面）
//这里的将答案收集到右边组并不是说答案只是针对右边组  实际上左边和右边一同构成了右边查询的实际范围  只不过是将答案放在右边的查询中  和左边的查询并无区别
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXM = 50001;

int n, m;

// num : 原始序列依次的值
// pos : 每个值在什么位置
// del : 每一步删掉的值
int num[MAXN];
int pos[MAXN];
int del[MAXM];

// 数值v、位置i、效果d、问题编号q
struct Node {
   	int v, i, d, q;
};

// 这个相当于第二维的排序  按照修改位置排序
bool NodeCmp(Node x, Node y) {
   	return x.i < y.i;
}

Node arr[MAXN + MAXM];

int cnt = 0;

// 树状数组
int tree[MAXN];

// 每次逆序对的变化量
long long ans[MAXM];

int lowbit(int i) {
   	return i & -i;
}

void add(int i, int v) {
	while (i <= n) {
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

//这里需要注意一点：无论是从左到右 计算在当前位置之前大于自己的
//还是计算当前位置之后  小于自己的  答案都是统计到右边的答案数组中  这里指的是统计到右边组的查询中
//因为是按照时间来进行第一维的划分  右边的时间更靠后
//这样的话答案也不会统计出错
void merge(int l, int m, int r) {
	int p1, p2;
	// 要从左到右一遍  从右到左一遍  因为收集的答案是位于树状数组上的值
	// 从左到右统计左侧值大的数量
	for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
		while (p1 + 1 <= m && arr[p1 + 1].i < arr[p2].i) {
			p1++;
			add(arr[p1].v, arr[p1].d);
		}
		ans[arr[p2].q] += arr[p2].d * (query(n) - query(arr[p2].v));
	}
	// 清除树状数组
	for (int i = l; i <= p1; i++) {
		add(arr[i].v, -arr[i].d);
	}
	// 从右到左统计右侧值小的数量
	for (p1 = m + 1, p2 = r; p2 > m; p2--) {
		while (p1 - 1 >= l && arr[p1 - 1].i > arr[p2].i) {
			p1--;
			add(arr[p1].v, arr[p1].d);
		}
		ans[arr[p2].q] += arr[p2].d * query(arr[p2].v - 1);
	}
	// 清除树状数组
	for (int i = m; i >= p1; i--) {
		add(arr[i].v, -arr[i].d);
	}
	// 直接排序
	sort(arr + l, arr + r + 1, NodeCmp);
}

// 整体按时序组织，cdq分治里根据下标重新排序
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
	//前面的是最初的位置  问题编号是0
	//后面的是删除的位置  问题编号是删除时的操作
	//也就是说  只有问题0的答案是需要多次加工  其余的都是一次
	for (int i = 1; i <= n; i++) {
		arr[++cnt].v = num[i];
		arr[cnt].i = i;
		arr[cnt].d = 1;
		arr[cnt].q = 0;
	}
	for (int i = 1; i <= m; i++) {
		arr[++cnt].v = del[i];
		arr[cnt].i = pos[del[i]];
		arr[cnt].d = -1;
		arr[cnt].q = i;
	}
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> num[i];
		pos[num[i]] = i;//记录每个数字的位置
	}
	for (int i = 1; i <= m; i++) {
		cin >> del[i];
	}
	prepare();
	cdq(1, cnt);
	for (int i = 1; i < m; i++) {
		ans[i] += ans[i - 1];
	}
	for (int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
	return 0;
}