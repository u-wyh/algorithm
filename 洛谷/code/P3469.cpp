// https://www.luogu.com.cn/problem/P3469
// 题意：输入无向连通图的点数 n（1..n）和边数 m，以及 m 条无向边 (a, b)。
// 对每个点 i，求删去与点 i 相连的所有边（不删点 i 本身）后，图中有多少个有序点对 (x, y)（x != y）互不连通。
// 输出 n 行，第 i 行表示删去点 i 关联边后的不连通有序点对数量。
// 数据范围：1 <= n <= 10^5，1 <= m <= 5*10^5，初始图连通且无重边。
#include<bits/stdc++.h>
// 算法标签：Tarjan、割点
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 5e5+5;

int n,m;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int low[MAXN];
int dfn[MAXN];
int dfncnt;
int sz[MAXN];

long long ans[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++dfncnt;
    sz[u]=1;
    long long sum=1;
    long long res=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v,u);
            sz[u]+=sz[v];
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                sum+=sz[v];
                res+=sz[v]*sz[v];
            }
        }
        else if(v!=fa){
            low[u]=min(low[u],dfn[v]);
        }
    }
    ans[u]=n*n-1-res-(n-sum)*(n-sum);
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    tarjan(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}