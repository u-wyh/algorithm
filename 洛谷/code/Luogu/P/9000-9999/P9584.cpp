#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 2e5+5;

int n,m;

int val[MAXN];
int sz[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN<<1];
int weight[MAXN<<1];
int to[MAXN<<1];

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs1(int u,int f){
    sz[u]=1;
    val[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==f){
            continue;
        }
        dfs1(v,u);
        sz[u]+=sz[v];
        val[u]+=sz[v]*w+val[v];
    }
    val[u]%=MOD;
}

void dfs2(int u,int f,int w){
    if(f!=0){
        val[u]=val[f]-sz[u]*w+w*(n-sz[u]);
        val[u]%=MOD;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int wi=weight[i];
        if(v==f){
            continue;
        }
        dfs2(v,u,wi);
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,0,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        // cout<<' '<<i<<' '<<val[i]<<endl;
        ans+=val[i];
        ans%=MOD;
    }
    for(int i=1;i<=m;i++){
        int u,w;
        u=read(),w=read();
        int res=ans+2*n*w+2*val[u];
        res=(res%MOD+MOD)%MOD;
        printf("%lld\n",res);
    }
    return 0;
}