#include<bits/stdc++.h>
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