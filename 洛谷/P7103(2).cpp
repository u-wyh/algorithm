#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;
const int INF = 1e9;

int n,m;
int ans[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int dep[MAXN];
int dfn[MAXN];
int seg[MAXN];
int dfncnt;

int dfnmin[MAXN];
int dfnmax[MAXN];

int headq[MAXN];
int nxtq[MAXN<<1];
int toq[MAXN<<1];
int idq[MAXN<<1];
int cntq=1;

int fa[MAXN];
bool vis[MAXN];

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

void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void addedgeq(int u,int v,int w){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=w;
    headq[u]=cntq++;
}

void dfs(int u,int d){
    dep[u]=d;
    dfn[u]=++dfncnt;
    seg[dfncnt]=u;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,d+1);
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void tarjan(int u){
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        tarjan(v);
        fa[v]=u;
    }

    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        if(vis[v]){
            ans[idq[i]]=find(v);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int fa=read();
        addedge(fa,i);
    }
    dfs(1,1);
    int maxdep=0;
    for(int i=1;i<=n;i++){
        maxdep=max(maxdep,dep[i]);
    }
    for(int i=1;i<=maxdep;i++){
        dfnmin[i]=INF;
        dfnmax[i]=-INF;
    }
    for(int i=1;i<=n;i++){
        dfnmin[dep[i]]=min(dfnmin[dep[i]],dfn[i]);
        dfnmax[dep[i]]=max(dfnmax[dep[i]],dfn[i]);
    }
    for(int i=1;i<=maxdep;i++){
        if(dfnmin[i]==dfnmax[i]){
            ans[i]=seg[dfnmin[i]];
        }
        else{
            addedgeq(seg[dfnmin[i]],seg[dfnmax[i]],i);
            addedgeq(seg[dfnmax[i]],seg[dfnmin[i]],i);
        }
    }

    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    tarjan(1);

    for(int i=1;i<=m;i++){
        int d=read();
        write(ans[d]);
        putchar('\n');
    }
    return 0;
}