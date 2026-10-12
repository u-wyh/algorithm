// 用途：求无向图全部割点；输入 n m 和 m 条边。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 注意：支持非连通图与重边；显式栈避免长链爆栈。
// 例题：https://www.luogu.com.cn/problem/P3388
// 题意：找出删除后会使无向图连通块增加的点。
// 思路：DFS 求 dfn/low；分别处理根节点和非根节点的割点条件。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;
const int MAXE = 2e5+5;

int head[MAXN], to[MAXE], nxt[MAXE], edgeCnt;
// low 记录子树通过返祖边能到达的最早序号。
int dfn[MAXN],low[MAXN];
int Time;
bool cut[MAXN];
int parentNode[MAXN], nextEdge[MAXN], childCount[MAXN];
int st[MAXN], top;
int n,m;

void addEdge(int u, int v) {
    to[++edgeCnt] = v;
    nxt[edgeCnt] = head[u];
    head[u] = edgeCnt;
}

void tarjan(int root) {
    st[top++] = root;
    nextEdge[root] = head[root];
    dfn[root] = low[root] = ++Time;
    while (top) {
        int u = st[top - 1];
        if (nextEdge[u]) {
            int e = nextEdge[u];
            nextEdge[u] = nxt[e];
            int v = to[e];
            if (!dfn[v]) {
                parentNode[v] = u;
                childCount[u]++;
                dfn[v] = low[v] = ++Time;
                nextEdge[v] = head[v];
                st[top++] = v;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        } else {
            --top;
            int p = parentNode[u];
            if (p) {
                low[p] = min(low[p], low[u]);
                // 非根点 p 的子树无法绕过 p 时，p 是割点。
                if (parentNode[p] && low[u] >= dfn[p]) cut[p] = true;
            } else if (childCount[u] >= 2) {
                cut[u] = true;
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            ans++;
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(cut[i]){
            cout<<i<<' ';
        }
    }
    return 0;
}
