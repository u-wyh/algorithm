#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n;
int ans;
int f[MAXN];
int g[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs1(int u,int fa){
    f[u]=0,g[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        f[u]+=g[v];
        g[u]+=f[v];
    }
}

void dfs2(int u,int fa){
    if(fa!=0){
        // int t1=f[u],t2=g[u];
        f[u]=g[fa];
        g[u]=f[fa];
        ans+=g[u];
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
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        ans=0;
        for(int i=1;i<=n;i++){
            head[i]=0;
        }
        cnt=1;
        for(int i=1;i<n;i++){
            int u,v;
            cin>>u>>v;
            addedge(u,v);
            addedge(v,u);
        }
        dfs1(1,0);
        ans+=g[1];
        
        for(int i=1;i<=n;i++){
            cout<<f[i]<<' ';
        }
        cout<<endl;
        for(int i=1;i<=n;i++){
            cout<<g[i]<<' ';
        }
        cout<<endl;
        cout<<endl;

        dfs2(1,0);
        ans-=n;
        ans/=2;
        cout<<ans<<endl;
    }
    return 0;
}