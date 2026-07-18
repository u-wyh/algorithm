#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int LIMIT = 20;

int n,m,root;
int log_2[MAXN];
int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int deep[MAXN],stjump[MAXN][LIMIT];

void build(){
    log_2[0]=-1;
    for(int i=1;i<=n;i++){
        log_2[i]=log_2[i>>1]+1;
    }
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    //完成u的deep  stjump
    for (int p = 1; p <= log_2[n]; p++) {
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    }
    for (int e = head[u]; e != 0; e = Next[e]) {
        //向下递归
        if (to[e] != f) {
            dfs(to[e], u);
        }
    }
}

int lca(int a, int b) {
    //确定大小关系
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //首先将两者变为同一高度
    for (int p = log_2[n]; p >= 0; p--) {
        if (deep[stjump[a][p]] >= deep[b]) {
            a = stjump[a][p];
        }
    }
    //如果相同说明就是祖先关系
    if (a == b) {
        return a;
    }
    for (int p = log_2[n]; p >= 0; p--) {
        //判断跳完后是否符合规则
        if (stjump[a][p] != stjump[b][p]) {
            a = stjump[a][p];
            b = stjump[b][p];
        }
    }
    //我们将头结点的祖先设置为0  实际上没有0  这里大多数都是直接返回st[a][0]
    return stjump[a][0]==0?root:stjump[a][0];
}

int main()
{
    cin>>n>>m>>root;
    build();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;

    }
    dfs(root,0);
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
    return 0;
}