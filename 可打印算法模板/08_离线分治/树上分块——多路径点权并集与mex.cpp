// 用途：树链剖分和序列分块的位图合并，求多路径点权并集及 mex。
// 时间：单次 O(k log n·(B+nV/(64B))+V)，B 为块长，V=30001。
// 空间：O(n+nV/(8B))，B 为块长，V=30001。
// 注意：点权在 0..30000；f=1 时端点用上次“不同数个数+mex”异或解码。
// 例题：https://www.luogu.com.cn/problem/P3603
// 题意：每次给多条树上路径，求路径并集的不同点权个数和最小缺失非负点权。
// 思路：重链剖分把路径拆成 DFS 序区间，边角逐点、整块按预处理位图做或运算。
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 401;
const int MAXV = 30001;

int n, m, f, k;
int arr[MAXN];

int head[MAXN];
int nxt[MAXN << 1];
int to[MAXN << 1];
int cntg;

int fa[MAXN];
int dep[MAXN];
int siz[MAXN];
int son[MAXN];
int top[MAXN];
int dfn[MAXN];
int val[MAXN];
int cntd;
int dfsStack[MAXN], dfsOrder[MAXN], chainTop[MAXN];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
bitset<MAXV> bitSet[MAXB];

bitset<MAXV> ans;

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void dfs1(int u, int f) {
    // 深链可达 10 万层；用定长数组栈收集前序，再倒序求子树大小。
    fa[u] = f;
    dep[u] = dep[f] + 1;
    int sp = 0, count = 0;
    dfsStack[++sp] = u;
    while (sp) {
        int x = dfsStack[sp--];
        dfsOrder[++count] = x;
        for (int e = head[x]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa[x]) {
                fa[v] = x;
                dep[v] = dep[x] + 1;
                dfsStack[++sp] = v;
            }
        }
    }
    for (int i = count; i >= 1; i--) {
        int x = dfsOrder[i];
        siz[x] = 1;
        for (int e = head[x]; e; e = nxt[e]) {
            int v = to[e];
            if (v != fa[x]) {
                siz[x] += siz[v];
                if (!son[x] || siz[son[x]] < siz[v]) {
                    son[x] = v;
                }
            }
        }
    }
}

void dfs2(int u, int t) {
    // 重儿子沿当前链直接走；轻儿子留在栈里稍后展开。
    int sp = 0;
    dfsStack[++sp] = u;
    chainTop[sp] = t;
    while (sp) {
        int x = dfsStack[sp], headOfChain = chainTop[sp--];
        while (x) {
            top[x] = headOfChain;
            dfn[x] = ++cntd;
            val[cntd] = arr[x];
            for (int e = head[x]; e; e = nxt[e]) {
                int v = to[e];
                if (v != fa[x] && v != son[x]) {
                    dfsStack[++sp] = v;
                    chainTop[sp] = v;
                }
            }
            x = son[x];
        }
    }
}

void query(int l, int r) {
    // 同一条重链映射成连续 DFS 序；边角逐点、完整块按位或。
    if (bi[l] == bi[r]) {
        for (int i = l; i <= r; i++) {
            ans[val[i]] = 1;
        }
    } else {
        for (int i = l; i <= br[bi[l]]; i++) {
            ans[val[i]] = 1;
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            ans[val[i]] = 1;
        }
        //块间操作
        for (int i = bi[l] + 1; i <= bi[r] - 1; i++) {
            ans |= bitSet[i];
        }
    }
}

// 这个其实就是树链剖分中的路径信息查询
void updateAns(int x, int y) {
    // 重链剖分跳链，把一条树上路径拆为若干 DFS 序区间。
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            swap(x, y);
        }
        query(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    query(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]));
}

void prepare() {
    dfs1(1, 0);
    dfs2(1, 1);
    blen = (int)sqrt(n * 20);//这道题的块间操作是位图的或   代价比较大
    bnum = (n + blen - 1) / blen;
    //这个是按照dfn序组织的
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, n);
        for (int j = bl[i]; j <= br[i]; j++) {
            bitSet[i][val[j]] = 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> f;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    prepare();
    for (int i = 1, lastAns = 0; i <= m; i++) {
        ans.reset(); // 本次多条路径求并集，先清空上次的位图。
        cin >> k;
        for (int j = 1, x, y; j <= k; j++) {
            cin >> x >> y;
            if (f) {
                // 在线输入用上次两个答案的和异或解码端点。
                x ^= lastAns;
                y ^= lastAns;
            }
            updateAns(x, y);
        }
        int ans1 = ans.count();
        int ans2 = MAXV;
        for (int i = 0; i < MAXV; i++) {
            if (ans[i] == 0) {
                ans2 = i;
                break;
            }
        }
        cout << ans1 << ' ' << ans2 << '\n';
        lastAns = ans1 + ans2;
    }
    return 0;
}
