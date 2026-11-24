// 用途：四维非下降宝藏链的最大收益与最优方案数。
// 时间：O(n log³ n)。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P4849
// 题意：四个属性都不下降地取宝藏，求最大收益及最优取法数；同坐标宝藏合为一个选择。
// 思路：同坐标先合并；两层 CDQ 依次处理第一、二维，按第三维扫描，树状数组维护第四维的最大收益与方案数。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 80001;
const long long INF = 1e18 + 1;
const int MOD = 998244353;
int n, s;

struct Node {
    int a, b, c, d;
    long long v;
    int i;
    bool left;
};

Node arr[MAXN];
Node tmp1[MAXN];
Node tmp2[MAXN];
int sortd[MAXN];

long long treeVal[MAXN];
int treeCnt[MAXN];

long long dp[MAXN];
int cnt[MAXN];
// dp[i]：以第 i 个合并后的坐标结尾的最大收益；cnt[i]：对应方案数。

int lowbit(int i) {
   return i & -i;
}

bool Cmp1(Node x, Node y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    if (x.c != y.c) return x.c < y.c;
    return x.d < y.d;
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

void more(int i, long long v, int c) {
    // 第四维的树状数组：前缀最大收益，平局时累加方案数。
    while (i <= s) {
        if (v > treeVal[i]) {
            treeVal[i] = v;
            treeCnt[i] = c % MOD;
        } else if (v == treeVal[i]) {
            treeCnt[i] = (treeCnt[i] + c) % MOD;
        }
        i += lowbit(i);
    }
}

long long queryVal;
int queryCnt;

void query(int i) {
    queryVal = -INF;
    queryCnt = 0;
    while (i > 0) {
        if (treeVal[i] > queryVal) {
            queryVal = treeVal[i];
            queryCnt = treeCnt[i];
        } else if (treeVal[i] == queryVal) {
            queryCnt = (queryCnt + treeCnt[i]) % MOD;
        }
        i -= lowbit(i);
    }
}

void clear(int i) {
    // 每次内层 CDQ 合并结束后撤销本层插入，避免串到别的区间。
    while (i <= s) {
        treeVal[i] = -INF;
        treeCnt[i] = 0;
        i += lowbit(i);
    }
}

void merge(int l, int m, int r) {
    // 两侧按第三维排序；只让外层 CDQ 原左半的点更新原右半。
    for (int i = l; i <= r; i++) {
        tmp2[i] = tmp1[i];
    }
    sort(tmp2 + l, tmp2 + m + 1, Cmp3);
    sort(tmp2 + m + 1, tmp2 + r + 1, Cmp3);
    int p1, p2, id;
    for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
        while (p1 + 1 <= m && tmp2[p1 + 1].c <= tmp2[p2].c) {
            p1++;
            if (tmp2[p1].left) {
                more(tmp2[p1].d, dp[tmp2[p1].i], cnt[tmp2[p1].i]);
            }
        }
        if (!tmp2[p2].left) {
            query(tmp2[p2].d);
            id = tmp2[p2].i;
            if (queryVal + tmp2[p2].v > dp[id]) {
                dp[id] = queryVal + tmp2[p2].v;
                cnt[id] = queryCnt;
            } else if (queryVal + tmp2[p2].v == dp[id]) {
                cnt[id] = (cnt[id] + queryCnt) % MOD;
            }
        }
    }
    for (int i = l; i <= p1; i++) {
        if (tmp2[i].left) {
            clear(tmp2[i].d);
        }
    }
}

void cdq2(int l, int r) {
    // 第二维已排序，再分治；合并时按第三维扫描、第四维查询。
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq2(l, mid);
    merge(l, mid, r);
    cdq2(mid + 1, r);
}

void cdq1(int l, int r) {
    // 首维按字典序固定；先算左侧 DP，再用左侧更新右侧。
    if (l == r) return;
    int mid = (l + r) / 2;
    cdq1(l, mid);
    for (int i = l; i <= r; i++) {
        tmp1[i] = arr[i];
        tmp1[i].left = i <= mid;
    }
    sort(tmp1 + l, tmp1 + r + 1, Cmp2);
    cdq2(l, r);
    cdq1(mid + 1, r);
}

int lower(int num) {
    int l = 1, r = s, ans = 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (sortd[mid] >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void prepare() {
    //按照d进行排序
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
    sort(arr + 1, arr + n + 1, Cmp1);
    int m = 1;
    // 同坐标宝藏算同一个选择；收益全为正，因此选中就全部拿取。
    for (int i = 2; i <= n; i++) {
        if (arr[m].a == arr[i].a && arr[m].b == arr[i].b &&
            arr[m].c == arr[i].c && arr[m].d == arr[i].d) {
            arr[m].v += arr[i].v;
        } else {
            arr[++m] = arr[i];
        }
    }
    //初始化赋值
    n = m;
    for (int i = 1; i <= n; i++) {
        arr[i].i = i;
        dp[i] = arr[i].v;
        cnt[i] = 1;
    }
    for (int i = 1; i <= s; i++) {
        treeVal[i] = -INF;
        treeCnt[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    cin >> n >> m; // m 是网格最大坐标；合法偏序链均可从起点到终点经过。
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].a >> arr[i].b >> arr[i].c >> arr[i].d >> arr[i].v;
    }
    prepare();
    cdq1(1, n);
    long long best = 0;
    int ways = 0;
    for (int i = 1; i <= n; i++) {
        best = max(best, dp[i]);//求出最大值
    }
    for (int i = 1; i <= n; i++) {
        if (dp[i] == best) {
            ways = (ways + cnt[i]) % MOD;//查询方法数
        }
    }
    cout << best << '\n';
    cout << ways << '\n';
    return 0;
}
