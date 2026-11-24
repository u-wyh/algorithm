// 用途：CDQ 优化最长不下降子序列 DP，要求任意一次指定修改后仍合法。
// 时间：O(n log² n)。
// 空间：O(n+V)，V=100000 为值域上限。
// 注意：原值和候选修改值都须在 1..100000，树状数组按值域开。
// 例题：https://www.luogu.com.cn/problem/P4093
// 题意：给出多种候选单点改值，可不改或任选一次；求任何选择下都保持不下降的最长下标子序列。
// 思路：每个位置取可能值的最小/最大；前点最大值不超过后点原值、前点原值不超过后点最小值时才能转移，CDQ 加树状数组求最大 DP。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXV = 100000;

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

// 树状数组下标是数值，不是位置；大小必须覆盖值域 V，而非数组长度 n。
int tree[MAXV + 1];
// dp[i]：以 i 结尾、对不修改或任意一个给定修改都合法的最长长度。
int dp[MAXN];

int lowbit(int i) {
    return i & -i;
}

void more(int i, int num) {
    while (i <= MAXV) {
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
    while (i <= MAXV) {
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
    // j<i 的转移条件是 v[j]<=lv[i] 且 rv[j]<=v[i]。
    int p1, p2;
    for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
        // 左侧对象.v <= 右侧对象.lv 窗口扩充
        while (p1 + 1 <= m && arr[p1 + 1].v <= arr[p2].lv) {
            p1++;
            // 树状数组中，下标是rv，加入的值是左侧对象的dp值
            more(arr[p1].rv, dp[arr[p1].i]);
        }
        // 树状数组只留 rv[j]<=v[i] 的前驱，取最大 dp[j]+1。
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
    // 按下标分治：左侧完成后更新右侧，再递归求右侧内部转移。
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
