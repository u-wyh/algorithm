#include<bits/stdc++.h>
using namespace std;
const int MAXN = 30005;
const int MAXM = 60005;
const int LIMIT = 16;

int n,m,power;
int sum[MAXN];
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
    return stjump[a][0];
    //我们将头结点的祖先设置为0  实际上没有0
}

int main()
{
    cin>>n;
    sum[0]=-1;
    power=log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs(1,0);
    cin>>m;
    int pre,ans=0;
    cin>>pre;
    for(int i=1;i<m;i++){
        int v,w;
        cin>>v;
        w=lca(pre,v);
        ans+=deep[pre]+deep[v]-2*deep[w];
        pre=v;
    }
    cout<<ans<<endl;
    return 0;
}
