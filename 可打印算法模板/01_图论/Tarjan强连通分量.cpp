// 用途：求有向图的强连通分量，按最小点编号顺序输出。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 注意：n<=1e4，m<=1e5；递归 DFS。
// 例题：https://www.luogu.com.cn/problem/B3609
// 题意：把有向图划分成互相可达的极大点集。
// 思路：DFS 求 dfn/low，回溯到强连通分量根时弹出栈中节点。
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10001;
const int MAXM = 100001;
int n, m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg;

// dfn 是首次访问序，low 是能回到的最早祖先序。
int dfn[MAXN];
int low[MAXN];
int cntd;

int sta[MAXN];
int top;

int belong[MAXN];
int sccArr[MAXN];
int sccl[MAXN];
int sccr[MAXN];
int idx;
int sccCnt;

bool sccPrint[MAXN];

void addEdge(int u, int v) {
    nxt[++cntg] = head[u];
    to[cntg] = v;
    head[u] = cntg;
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
    // 当 low 等于 dfn 时，弹出一个完整强连通分量。
    if (dfn[u] == low[u]) {
        sccCnt++;
        sccl[sccCnt] = idx + 1;
        int pop;
        do {
            pop = sta[top--];
            belong[pop] = sccCnt;
            sccArr[++idx] = pop;
        } while (pop != u);
        sccr[sccCnt] = idx;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        addEdge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }
    cout << sccCnt << "\n";
    for (int i = 1; i <= sccCnt; i++) {
        sort(sccArr + sccl[i], sccArr + sccr[i] + 1);
    }
    for (int i = 1; i <= n; i++) {
        int scc = belong[i];
        if (!sccPrint[scc]) {
            sccPrint[scc] = true;
            for (int j = sccl[scc]; j <= sccr[scc]; j++) {
                cout << sccArr[j] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
