#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n;
int ans;

int sz[MAXN];
int deg[MAXN];
int f[MAXN];
int g[MAXN];
int F[MAXN];
int G[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

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
    f[u]=deg[u];
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        f[u]=(f[u]+f[v])%MOD;
    }
    // for(int i=head[u];i;i=nxt[i]){
    //     int v=to[i];
    //     if(v!=fa){
    //         g[v]=(g[u]+f[u]-f[v]+MOD)%MOD;
    //     }
    // }
}

void dfs2(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            g[v]=(g[u]+f[u]-f[v])%MOD;
            dfs2(v,u);
            F[v]=(F[v]+(f[v]*sz[v])%MOD)%MOD;
            G[v]=(G[v]+(g[v]*sz[v])%MOD)%MOD;
            ans=(ans+(F[v]*(sz[u]-sz[v])%MOD))%MOD;
            ans=(ans+(G[v]*(sz[u]-sz[v])%MOD))%MOD;
            F[u]=(F[u]+F[v])%MOD;
            G[u]=(G[u]+G[v])%MOD;
        }
    }
}

signed main()
{
    n=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        deg[u]++,deg[v]++;
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    int inv=power(n*n%MOD,MOD-2);
    ans=(ans*inv)%MOD;
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}