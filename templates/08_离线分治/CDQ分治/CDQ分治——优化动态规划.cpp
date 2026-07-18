// 序列，C++版
// 给定一个长度为n的数组arr，一共有m条操作，格式为 x v 表示x位置的数变成v
// 你可以选择不执行任何操作，或者只选择一个操作来执行，然后arr不再变动
// 请在arr中选出一组下标序列，不管你做出什么选择，下标序列所代表的数字都是不下降的
// 打印序列能达到的最大长度
// 1 <= 所有数字 <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4093
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题是CDQ分治优化动态数组
//我们首先记录一下每个位置上的数字变化后最大是多少  最小是多少
//dp的含义是 以i为结尾的、最多有一次修改操作后可以保证的最长递增序列长度
//那么dp[i]=dp[j]+1  如果满足  j<i  rv[j]<v[i]  v[j]<lv[i]
//也就是说i位置的dp值需要前面的dp值辅助完成
//既然如此 加入来到了1~8范围上  分为左右两部分 
//在1~4已经完成好了的前提下  我们将目前的范围上的数值拷贝下来
//那么5依赖的是1~4  6依赖的1~5=1~4+5~5  7依赖的是1~6=1~4+5~6 等等
//那么也就是说  我们可以分批次完成  比如先将7的1~4完成 然后如果5~6完成后  在继续更新
//也就说顺序是先左  其次合并（得到部分的答案）  最后右部分
// cdq分治优化动态规划的时候  在merge过程中都需要拷贝到另外一个数组中  因为右侧部分还没有开始cdq
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;
int v[MAXN];
int lv[MAXN];//这个位置上的最小值
int rv[MAXN];//这个位置上的最大值

// 位置i、数值v、最小值lv、最大值rv
struct Node {
    int i, v, lv, rv;
};

bool CmpV(Node a, Node b) {
    return a.v < b.v;
}

bool CmpLv(Node a, Node b) {
    return a.lv < b.lv;
}

Node arr[MAXN];

// 树状数组维护前缀最大值  可以添加、查询 不允许修改、删除
int tree[MAXN];
// 以i结尾的  最多选择一个操作的最长不下降子序列长度
int dp[MAXN];

int lowbit(int i) {
    return i & -i;
}

void more(int i, int num) {
    while (i <= n) {
        tree[i] = max(tree[i], num);
        i += lowbit(i);
    }
}

int query(int i) {
    int ret = 0;
    while (i > 0) {
        ret = max(ret, tree[i]);
        i -= lowbit(i);
    }
    return ret;
}

void clear(int i) {
    while (i <= n) {
        tree[i] = 0;
        i += lowbit(i);
    }
}

void merge(int l, int m, int r) {
    // 辅助数组arr拷贝l..r所有的对象
	// 接下来的排序都发生在arr中，不影响原始的次序
    for (int i = l; i <= r; i++) {
        arr[i].i = i;
        arr[i].v = v[i];
        arr[i].lv = lv[i];
        arr[i].rv = rv[i];
    }
    // 左侧根据v排序
    sort(arr + l, arr + m + 1, CmpV);
    // 右侧根据lv排序
    sort(arr + m + 1, arr + r + 1, CmpLv);
    //这样排序的原因是我们比较的是 lv[i]>v[j]
    int p1, p2;
    for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
        // 左侧对象.v <= 右侧对象.lv 窗口扩充
        while (p1 + 1 <= m && arr[p1 + 1].v <= arr[p2].lv) {
            p1++;
            // 树状数组中，下标是rv，加入的值是左侧对象的dp值
            more(arr[p1].rv, dp[arr[p1].i]);
        }
        // 右侧对象更新dp值，查出1..v范围上最大的dp值 + 1
        dp[arr[p2].i] = max(dp[arr[p2].i], query(arr[p2].v) + 1);
    }
    // 清空树状数组
    for (int i = l; i <= p1; i++) {
        clear(arr[i].rv);
    }
    // 合并结束的时候  并不需要进行统一排序 因为可能根据左右侧不同  排序也是不同的 
    // 更主要的原因还是  此时右侧部分还没有结束   右侧部分中的左侧和右侧要区别对待
}

void cdq(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    cdq(l, mid);
    merge(l, mid, r);
    cdq(mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        lv[i] = v[i];
        rv[i] = v[i];
    }
    for (int i = 1, idx, val; i <= m; i++) {
        cin >> idx >> val;
        lv[idx] = min(lv[idx], val);
        rv[idx] = max(rv[idx], val);
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
    }
    cdq(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}