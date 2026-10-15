// 用途：Tarjan 求无向图的点双连通分量。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 例题：https://www.luogu.com.cn/problem/P8435
// 题意：划分无向图的点双连通分量。
// 思路：DFS 求 dfn/low，遇到 low[子] ≥ dfn[父] 时弹出边栈构成分量。
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

int vbccSiz[MAXN];
int vbccArr[MAXN << 1];
int vbccl[MAXN];
int vbccr[MAXN];
int idx;
int vbccCnt;
struct Frame { int u, edge, parent; };
Frame callStack[MAXN];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
}

void tarjan(int u) {
    // 定长调用栈保留递归版的边扫描顺序，避免 50 万点链爆栈。
    dfn[u] = low[u] = ++cntd;
    sta[++top] = u;
    int sp = 1;
    callStack[sp] = {u, head[u], 0};
    while (sp) {
        Frame &frame = callStack[sp];
        int x = frame.u;
        if (frame.edge) {
            int e = frame.edge;
            frame.edge = nxt[e];
            int v = to[e];
            if (!dfn[v]) {
                dfn[v] = low[v] = ++cntd;
                sta[++top] = v;
                callStack[++sp] = {v, head[v], x};
            } else {
                low[x] = min(low[x], dfn[v]);
            }
        } else {
            int parent = frame.parent;
            --sp;
            if (parent) {
                low[parent] = min(low[parent], low[x]);
                if (low[x] >= dfn[parent]) {
                    // x 子树无法绕回 parent 祖先，弹到 x 构成一个点双。
                    ++vbccCnt;
                    vbccSiz[vbccCnt] = 1;
                    vbccArr[++idx] = parent;
                    vbccl[vbccCnt] = idx;
                    int pop;
                    do {
                        pop = sta[top--];
                        ++vbccSiz[vbccCnt];
                        vbccArr[++idx] = pop;
                    } while (pop != x);
                    vbccr[vbccCnt] = idx;
                }
            } else {
                --top; // 根点本身已在各个子点双中记录，不留给下一连通块。
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (u != v) {
            addEdge(u, v);
            addEdge(v, u);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            if (head[i] == 0) {
                vbccCnt++;
                vbccSiz[vbccCnt] = 1;
                vbccArr[++idx] = i;
                vbccl[vbccCnt] = vbccr[vbccCnt] = idx;
            } else {
                tarjan(i);
            }
        }
    }
    cout << vbccCnt << "\n";
    for (int i = 1; i <= vbccCnt; i++) {
        cout << vbccSiz[i] << "\n";
        for (int j = vbccl[i]; j <= vbccr[i]; j++) {
            cout << vbccArr[j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
