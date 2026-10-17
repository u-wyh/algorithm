// 用途：Tarjan 求无向图的边双连通分量。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 注意：原 P8436.cpp 递归版在 50 万点长链有爆栈风险，因此 DFS 用定长显式栈。
// 例题：https://www.luogu.com.cn/problem/P8436
// 原代码：P8436.cpp。
// 题意：划分无向图的边双连通分量。
// 思路：先找所有桥，再忽略桥遍历各连通块。
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500001;
const int MAXM = 2000001;
int n, m;

int head[MAXN];
int nxt[MAXM << 1];
int to[MAXM << 1];
int cntg;

int dfn[MAXN];
int low[MAXN];
int cntd;

int sta[MAXN];
int top;

int ebccSiz[MAXN];
int ebccArr[MAXN];
int ebccl[MAXN];
int ebccr[MAXN];
int idx;
int ebccCnt;
struct Frame { int u, edge, parentEdge; };
Frame callStack[MAXN];

void addEdge(int u, int v) {
   nxt[++cntg] = head[u];
   to[cntg] = v;
   head[u] = cntg;
}

void tarjan(int u, int preEdge) {
    // 模拟递归 DFS：edge 是当前点尚未扫描的下一条边。
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    int sp = 1;
    callStack[sp] = {u, head[u], preEdge};
    while (sp) {
        Frame &frame = callStack[sp];
        int x = frame.u;
        if (frame.edge) {
            int e = frame.edge;
            frame.edge = nxt[e];
            if ((e ^ 1) == frame.parentEdge) continue; // 只跳过反向树边，保留重边。
            int v = to[e];
            if (!dfn[v]) {
                dfn[v] = low[v] = ++cntd;
                sta[++top] = v;
                callStack[++sp] = {v, head[v], e};
            } else {
                low[x] = min(low[x], dfn[v]);
            }
        } else {
            // 子树已扫完：low 回传给父点；low[x]=dfn[x] 时弹出一个边双。
            if (dfn[x] == low[x]) {
                ++ebccCnt;
                ebccSiz[ebccCnt] = 0;
                ebccl[ebccCnt] = idx + 1;
                int pop;
                do {
                    pop = sta[top--];
                    ++ebccSiz[ebccCnt];
                    ebccArr[++idx] = pop;
                } while (pop != x);
                ebccr[ebccCnt] = idx;
            }
            int parentEdge = frame.parentEdge;
            --sp;
            if (parentEdge) {
                int parent = to[parentEdge ^ 1];
                low[parent] = min(low[parent], low[x]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cntg = 1;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(i, 0);
        }
    }
    cout << ebccCnt << "\n";
    for (int i = 1; i <= ebccCnt; i++) {
        cout << ebccSiz[i] << "\n";
        for (int j = ebccl[i]; j <= ebccr[i]; j++) {
            cout << ebccArr[j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
