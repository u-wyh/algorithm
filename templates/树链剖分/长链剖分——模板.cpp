// 树上k级祖先，C++版
// 一共有n个节点，编号1~n，给定一个长度为n的数组arr，表示依赖关系
// 如果arr[i] = j，表示i号节点的父节点是j，如果arr[i] == 0，表示i号节点是树头
// 一共有m条查询，每条查询 x k : 打印x往上走k步的祖先节点编号
// 题目要求预处理的时间复杂度O(n * log n)，处理每条查询的时间复杂度O(1)
// 题目要求强制在线，必须按顺序处理每条查询，如何得到每条查询的入参，请打开测试链接查看
// 1 <= n <= 5 * 10^5
// 1 <= m <= 5 * 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P5903
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
#define ui unsigned int
using namespace std;
const int MAXN = 500001;
const int MAXH = 20;

int n, m;
ui s;//题目要求的随机数种子
int root;

// 链式前向星，注意是有向图，所以边的数量不需要增倍
int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg = 0;

// 倍增表 + 长链剖分
int stjump[MAXN][MAXH];//倍增表
int dep[MAXN];//深度表
int len[MAXN];//长度表
int son[MAXN];//长儿子
int top[MAXN];
int dfn[MAXN];
int cntd = 0;

// 查询答案需要
int high[MAXN];//high[i]记录的是i的二进制最高位对应的数字是多少  意思是i>=2^high[i]&&i<2^(high[i]+1)
int up[MAXN];//记录节点i向上走1 2 3 到达那个节点  只有长链的头结点才可以有
//并且只会填长儿子大小的个数   即使向上走还存在更远的  也不填了
int down[MAXN];//这个和上面一样  记录的是向下走几步  每个节点只填自己长儿子大小个数的位置

// 题目规定如何得到输入数据的函数  强制在线要求
ui get(ui x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    s = x;
    return x;
}

//设置u这个节点向上走i步 达到v节点  u一定是某条长链的头结点
void setUp(int u, int i, int v) {
    up[dfn[u] + i] = v;
}

//查询u节点向上走i步到达那个节点  u一定是某条长链的头结点
int getUp(int u, int i) {
    return up[dfn[u] + i];
}

//设置u这个节点向下走i步 达到v节点  u一定是某条长链的头结点
void setDown(int u, int i, int v) {
    down[dfn[u] + i] = v;
}

//查询u节点向下走i步到达那个节点  u一定是某条长链的头结点
int getDown(int u, int i) {
    return down[dfn[u] + i];
}

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int f) {
    stjump[u][0] = f;//没有fa数组 因为倍增表可以直接查询
    for (int p = 1; p < MAXH; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    dep[u] = dep[f] + 1;
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            dfs1(v, u);
        }
    }
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != f) {
            if (son[u] == 0 || len[son[u]] < len[v]) {
                son[u] = v;
            }
        }
    }
    len[u] = len[son[u]] + 1;//每个节点的大小是自己长儿子加一
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cntd;
    if (son[u] == 0) return;
    dfs2(son[u], t);
    for (int e = head[u], v; e > 0; e = nxt[e]) {
        v = to[e];
        if (v != stjump[u][0] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

void prepare() {
    dfs1(root, 0);
    dfs2(root, root);
    high[0] = -1;
    for (int i = 1; i <= n; i++) {
        high[i] = high[i / 2] + 1;
    }
    for (int u = 1; u <= n; u++) {
        if (top[u] == u) {
            //如果这个节点是长链的头结点 那么设置up和down数组
            for (int i = 0, a = u, b = u; i < len[u]; i++, a = stjump[a][0], b = son[b]) {
                //只能设置len个位置
                setUp(u, i, a);
                setDown(u, i, b);
            }
        }
    }
}

//查询x节点向上走k步能到哪里
int query(int x, int k) {
    if (k == 0) {
        //如果是0步  那么直接就是这个节点
        return x;
    }
    if (k == (1 << high[k])) {
        //如果这个k正好是2的某次方  那么直接st表查询即可
        return stjump[x][high[k]];
    }
    //否则  我们先将其最高位的1用st表查询  找到一个中间节点
    x = stjump[x][high[k]];
    //然后k减去它的最高位
    k -= (1 << high[k]);
    //k剩下的这部分就通过来到的中间节点和他的头结点查询
    k -= dep[x] - dep[top[x]];
    x = top[x];
    return (k >= 0) ? getUp(x, k) : getDown(x, -k);
    //如果k小于0  那么说明根本到不了top[x]  那么向下走一点就好
    //如果k大于0  那么说明top[x]也不够 那么向上走一点就好
    //而且可以肯定的是  top[x]一定可以解决
    //因为既然初始节点走了k的最高位的距离来到了中间节点   至少走了k/2
    //那么说明这个中间节点的头结点的长儿子长度至少要大于k/2
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, father; i <= n; i++) {
        cin >> father;
        if (father == 0) {
            root = i;
        } else {
            addEdge(father, i);
        }
    }
    prepare();
    long long ans = 0;
    for (int i = 1, x, k, lastAns = 0; i <= m; i++) {
        x = (get(s) ^ lastAns) % n + 1;
        k = (get(s) ^ lastAns) % dep[x];
        lastAns = query(x, k);
        ans ^= (long long) i * lastAns;
    }
    cout << ans << '\n';
    return 0;
}