// 德丽莎世界第一可爱，C++版
// 一共有n个怪兽，每个怪兽有a、b、c、d四个能力值，以及打败之后的收益v
// 可以选择任意顺序打怪兽，每次打的怪兽的四种能力值都不能小于上次打的怪兽
// 打印能获得的最大收益，可能所有怪兽收益都是负数，那也需要至少打一只怪兽
// 1 <= n <= 5 * 10^4
// -10^5 <= a、b、c、d <= +10^5
// -10^9 <= v <= +10^9
// 测试链接 : https://www.luogu.com.cn/problem/P5621
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//首先我们将abcd值相同的合并为一个  至少选择一个（题目要求）  得到最大收益
//我们设置dp[i]  表示将i作为最后一个打的怪兽可以获得的最大收益是多少
//那么有dp[i]=dp[j]+val[i]  (a[j]<=a[i]  b[j]<=b[i]  c[j]<=c[i]  d[j]<=d[i])
//我们大顺序上按照a来排序  这样的话先保证a是有序的  我们设置cdq1(l,r)函数  用于计算dp值
//首先计算出cdq1(l,mid)求出左半部分的  接下来计算左到右的值  
//我们按照b来排序  同时由于a的序已经定了  也就是即使按照b排完序后  在a中是左侧的部分 就算在b是右侧 也不能用在a中是右侧的值来更新
//所以我们将b中的值添加一个标签 判断是否是原来的左侧  进入cdq2函数
//在范围上按照c来排序   此时已经按照b分为了左右侧   a的大小关系可以通过是否是原来的左右侧来判断
//在树状数组中使用d来进行查询  得到更新
// 在 cdq1 和 cdq2的merge 中  都存在右侧不分还没有开始 所以要复制到数组中
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50001;
const long long INF = 1e18 + 1;

int n, s;

struct Node {
    int a, b, c, d;
    long long v;
    int i;
    bool left;// 是否是原左组的对象
};

Node arr[MAXN];
int sortd[MAXN];//将d数组进行离散化

// 根据b重排时，准备的辅助数组，不改变原始次序  即保持稳定性
Node tmp1[MAXN];

// 根据c重排时，准备的辅助数组，不改变原始次序  即保持稳定性
Node tmp2[MAXN];

// 树状数组，维护前缀最大值  按照d组织
long long tree[MAXN];

// dp[i]表示i号怪兽最后杀死的情况下，最大的收益
long long dp[MAXN];

bool Cmp1(Node x, Node y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    if (x.c != y.c) return x.c < y.c;
    if (x.d != y.d) return x.d < y.d;
    return x.v > y.v;
}

// 根据属性b进行排序，b一样的对象，保持原始次序
bool Cmp2(Node x, Node y) {
    if (x.b != y.b) return x.b < y.b;
    return x.i < y.i;
}

// 根据属性c进行排序，c一样的对象，保持原始次序
bool Cmp3(Node x, Node y) {
    if (x.c != y.c) return x.c < y.c;
    return x.i < y.i;
}

int lowbit(int i) {
    return i & -i;
}

void more(int i, long long num) {
    while (i <= s) {
        tree[i] = max(tree[i], num);
        i += lowbit(i);
    }
}

long long query(int i) {
    long long ret = -INF;
    while (i > 0) {
        ret = max(ret, tree[i]);
        i -= lowbit(i);
    }
    return ret;
}

void clear(int i) {
    while (i <= s) {
        tree[i] = -INF;
        i += lowbit(i);
    }
}

void merge(int l, int m, int r) {
    for (int i = l; i <= r; i++) {
        tmp2[i] = tmp1[i];
    }
    //按照c进行排序
    sort(tmp2 + l, tmp2 + m + 1, Cmp3);
    sort(tmp2 + m + 1, tmp2 + r + 1, Cmp3);
    int p1, p2;
    for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
        while (p1 + 1 <= m && tmp2[p1 + 1].c <= tmp2[p2].c) {
            p1++;
            if (tmp2[p1].left) {
                //在左侧 是左半部分才进入树状数组
                more(tmp2[p1].d, dp[tmp2[p1].i]);
            }
        }
        if (!tmp2[p2].left) {
            //在右侧  不是左半部分才查询
            dp[tmp2[p2].i] = max(dp[tmp2[p2].i], query(tmp2[p2].d) + tmp2[p2].v);
        }
    }
    //复原操作
    for (int i = l; i <= p1; i++) {
        if (tmp2[i].left) {
            clear(tmp2[i].d);
        }
    }
}

// tmp1[l..r]中所有对象根据b属性值稳定排序了
// 让每个原左组的对象影响到后面每个原右组对象(更新dp)
void cdq2(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq2(l, mid);
    merge(l, mid, r);
    cdq2(mid + 1, r);
}

void cdq1(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    //完成左半部分
    cdq1(l, mid);
    //数组进行拷贝  并添加是否是原来的左侧
    for (int i = l; i <= r; i++) {
        tmp1[i] = arr[i];
        tmp1[i].left = i <= mid;
    } 
    //按照b进行排序
    sort(tmp1 + l, tmp1 + r + 1, Cmp2);
    cdq2(l, r);
    //完成右侧
    cdq1(mid + 1, r);
}

int lower(long long num) {
    int l = 1, r = s, ans = 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (sortd[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

void prepare() {
    //离散化
    for (int i = 1; i <= n; i++) {
        sortd[i] = arr[i].d;
    }
    sort(sortd + 1, sortd + n + 1);
    s = 1;
    for (int i = 2; i <= n; i++) {
        if (sortd[s] != sortd[i]) {
            sortd[++s] = sortd[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i].d = lower(arr[i].d);
    }
    //进行合并操作
    sort(arr + 1, arr + n + 1, Cmp1);
    int m = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[m].a == arr[i].a && arr[m].b == arr[i].b &&
            arr[m].c == arr[i].c && arr[m].d == arr[i].d) {
            if (arr[i].v > 0) {
                arr[m].v += arr[i].v;
            }
        } else {
            arr[++m] = arr[i];//至少选择一个 即使是小于0的
        }
    }
    //初始化赋值
    n = m;
    for (int i = 1; i <= n; i++) {
        arr[i].i = i;
        dp[i] = arr[i].v;
    }
    for (int i = 1; i <= s; i++) {
        tree[i] = -INF;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].a >> arr[i].b >> arr[i].c >> arr[i].d >> arr[i].v;
    }
    prepare();
    cdq1(1, n);
    long long ans = -INF;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}