#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n;

int sz[MAXN];
int sum[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

void dfs1(int u,int fa){
    sz[u]=1;
    sum[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        sum[u]+=(sum[v]+sz[v]);
    }
}

void dfs2(int u,int fa){
    if(u!=1){
        sum[u]=sum[fa]-sz[u]+n-sz[u];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u);
    }
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    int sub=0,ans=0;
    for(int i=1;i<=n;i++){
        if(sum[i]>=ans){
            ans=sum[i];
            sub=i;
        }
    }
    cout<<sub;
    return 0;
}