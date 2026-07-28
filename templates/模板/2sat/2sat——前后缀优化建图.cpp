// 互质，C++版
// 一共n张卡片，每张卡片给定两个待选数字，选择其中一个数字作为卡片的值
// 确定每张卡片的值之后，如果任意两张卡片的值都是互质的，那么算作成功
// 存在成功的选值方案打印"Yes"，不存在打印"No"
// 1 <= n <= 3 * 10^4
// 1 <= 待选数字 <= 2 * 10^6
// 测试链接 : https://www.luogu.com.cn/problem/AT_abc210_f
// 测试链接 : https://atcoder.jp/contests/abc210/tasks/abc210_f
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题也是非常好的一道题  尤其是数学部分非常巧妙
// 两个数字必须要互质,那么也就是说他们不能有相同的质因子
// 将所有的数字分配到他们所在的质因子的集合中,然后建图连边

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000001;
const int MAXV = 2000001;
const int MAXM = 3000001;

struct Node {
    int p, i;
};

bool NodeCmp(Node a, Node b) {
    if (a.p != b.p) {
        return a.p < b.p;
    }
    return a.i < b.i;
}

int n, cntt, maxv;
int ab[MAXN];

// 利用欧拉筛生成最小质因子表
bool vis[MAXV];
int prime[MAXV];
int minp[MAXV];
int cntp;

// 质因子、拥有这个质因子的数字编号
// 排序后得到每个质因子的数字编号列表
Node arr[MAXN];
int cnta;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg;

int dfn[MAXN];
int low[MAXN];
int cntd;

int sta[MAXN];
int top;

int belong[MAXN];
int sccCnt;

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

int other(int x) {
    return x <= n ? (x + n) : (x - n);
}

void euler() {
    for (int i = 2; i <= maxv; i++) {
        if (!vis[i]) {
            prime[++cntp] = i;
            minp[i] = i;
        }
        for (int j = 1, p, v; j <= cntp; j++) {
            p = prime[j];
            v = i * p;
            if (v > maxv) {
                break;
            }
            vis[v] = true;
            minp[v] = p;
            if (i % p == 0) {
                break;
            }
        }
    }
}

void decompose() {
    for (int i = 1; i <= n << 1; i++) {
        for (int v = ab[i], p = minp[v]; v > 1; p = minp[v]) {
            arr[++cnta].p = p;
            arr[cnta].i = i;
            while (v % p == 0) {
                v /= p;
            }
        }
    }
}

// 前后缀优化建图
void link() {
    sort(arr + 1, arr + cnta + 1, NodeCmp);
    for (int l = 1, r = 1; l <= cnta; l = ++r) {
        while (r + 1 <= cnta && arr[l].p == arr[r + 1].p) {
            r++;
        }
        cntt++;
        addEdge(cntt, other(arr[l].i));
        for (int i = l + 1; i <= r; i++) {
            cntt++;
            addEdge(cntt, other(arr[i].i));
            addEdge(arr[i].i, cntt - 1);
            addEdge(cntt, cntt - 1);
        }
        cntt++;
        addEdge(cntt, other(arr[r].i));
        for (int i = r - 1; i >= l; i--) {
            cntt++;
            addEdge(cntt, other(arr[i].i));
            addEdge(arr[i].i, cntt - 1);
            addEdge(cntt, cntt - 1);
        }
    }
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    for (int e = head[u]; e > 0; e = nxt[e]) {
        int v = to[e];
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else {
            if (belong[v] == 0) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    if (dfn[u] == low[u]) {
        sccCnt++;
        int pop;
        do {
            pop = sta[top--];
            belong[pop] = sccCnt;
        } while (pop != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    cntt = n << 1;
    for (int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        ab[i] = a;
        ab[i + n] = b;
        maxv = max(maxv, max(a, b));
    }
    euler();
    decompose();
    link();
    for (int i = 1; i <= cntt; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }
    bool check = true;
    for (int i = 1; i <= n; i++) {
        if (belong[i] == belong[i + n]) {
            check = false;
            break;
        }
    }
    cout << (check ? "Yes" : "No") << "\n";
    return 0;
}