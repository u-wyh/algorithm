#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 105;
const int INF = 2e9;

int n,k;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int weight[MAXN];
int cntg=1;

int w[MAXN];
// 每个节点到达零号节点的距离
int dis[MAXN];
int fa[MAXN];
int dp[MAXN][MAXN][MAXN];
int dp0[MAXN];
int sz[MAXN];

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs1(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        dis[v]=dis[u]+w;
        dfs1(v);
    }
}

// 用于收集dp数组
void dfs2(int u){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs2(v);
        sz[u]+=sz[v];
    }

    int build[MAXN];
    int nobuild[MAXN];
    int temp[MAXN];

    for(int j=0;j<=k;j++){
        build[j]=INF;
    }
    build[1]=0;

    int usedsize=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        for(int j=0;j<=k;j++){
            temp[j]=INF;
        }

        for(int x=1;x<=min(k,usedsize);x++){
            if(build[x]==INF){
                continue;
            }

            for(int y=0;y<=min(k-x,sz[v]);y++){
                if(dp[v][y][u]==INF){
                    continue;
                }

                temp[x+y]=min(temp[x+y],build[x]+dp[v][y][u]);
            }
        }

        usedsize+=sz[v];
        for(int j=1;j<=k;j++){
            build[j]=temp[j];
        }
    }

    for(int a=fa[u];a!=-1;a=fa[a]){
        for(int j=0;j<=k;j++){
            nobuild[j]=INF;
        }

        nobuild[0]=w[u]*(dis[u]-dis[a]);
        usedsize=1;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];

            for(int j=0;j<=k;j++){
                temp[j]=INF;
            }

            for(int x=0;x<=min(k,usedsize-1);x++){
                if(nobuild[x]==INF){
                    continue;
                }

                for(int y=0;y<=min(k-x,sz[v]);y++){
                    if(dp[v][y][a]==INF){
                        continue;
                    }

                    temp[x+y]=min(temp[x+y],dp[v][y][a]+nobuild[x]);
                }
            }
            usedsize+=sz[v];
            for(int j=0;j<=k;j++){
                nobuild[j]=temp[j];
            }
        }

        for(int j=0;j<=min(k,sz[u]);j++){
            dp[u][j][a]=min(build[j],nobuild[j]);
        }
    }
}

signed main()
{
    cin>>n>>k;
    fa[0]=-1;
    for(int i=1;i<=n;i++){
        int d;
        cin>>w[i]>>fa[i]>>d;
        addedge(fa[i],i,d);
    }

    for(int u=1;u<=n;u++){
        for(int i=1;i<=k;i++){
            for(int a=1;a<=n;a++){
                dp[u][i][a]=INF;
            }
        }
    }
    for(int i=1;i<=k;i++){
        dp0[i]=INF;
    }

    dfs1(0);

    for(int i=head[0];i;i=nxt[i]){
        int v=to[i];
        dfs2(v);
    }

    dp0[0]=0;
    int temp[MAXN];
    int allsz=0;

    for(int i=head[0];i;i=nxt[i]){
        int v=to[i];

        for(int j=0;j<=k;j++){
            temp[j]=INF;
        }

        for(int x=0;x<=min(k,allsz);x++){
            if(dp0[x]==INF){
                continue;
            }

            for(int y=0;y<=min(k-x,sz[v]);y++){
                if(dp[v][y][0]==INF){
                    continue;
                }

                temp[x+y]=min(temp[x+y],dp0[x]+dp[v][y][0]);
            }
        }

        allsz+=sz[v];
        for(int j=0;j<=k;j++){
            dp0[j]=temp[j];
        }
    }

    cout<<dp0[k]<<endl;
    return 0;
}