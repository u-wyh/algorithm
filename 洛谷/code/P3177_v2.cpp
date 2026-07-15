#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int sz[MAXN];
int f[MAXN][MAXN];

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    sz[u]=1;
    f[u][0]=f[u][1]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
        sz[u]+=sz[v];
        for(int j=min(sz[u],m);j>=0;j--){
            for(int k=0;k<=min(j,sz[v]);k++){
                if(f[u][j-k]==-1){
                    continue;
                }
                int val=weight[i]*(k*(m-k)+(sz[v]-k)*(n-m-sz[v]+k));
                f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]+val);
            }
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j]=-1;
        }
    }
    dfs(1,0);
    cout<<f[1][m]<<endl;
    return 0;
}