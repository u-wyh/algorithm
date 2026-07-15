#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int LIMIT = 19;

int n,m,power,root;
int sz[MAXN],son[MAXN];
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    son[u]=son[f]+sz[u];
    for (int p = 1; p <= power; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    //完成u的deep  stjump
    for (int e = head[u]; e != 0; e = Next[e]) {
        if (to[e] != f) {
            dfs(to[e], u);
        }
        //向下递归
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系
    for (int p = power; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return a;
    }
    //如果相同说明就是祖先关系
    for (int p = power; p >= 0; p--) {
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
        //判断跳完后是否符合规则
    }
    return stjump[a][0]==0?root:stjump[a][0];
    //我们将头结点的祖先设置为0  实际上没有0
}
signed main()
{
    cin>>n>>m;
    power=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
        sz[u]++,sz[v]++;
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v;
        w=lca(u,v);
        int ans=son[u]+son[v]-2*son[w]+sz[w];
        cout<<ans<<endl;
    }
    return 0;
}
