// https://www.luogu.com.cn/problem/P3177
// 题意：输入树节点数 n、需染成黑色的点数 k，
// 以及 n-1 条带权无向边 (u, v, w)。
// 选择恰好 k 个点染成黑色、其余 n-k 个点染成白色，
// 收益定义为所有黑点两两间路径距离之和加上所有白点两两间路径距离之和。
// 输出能获得的最大收益值。
// 数据范围：0 <= k <= n <= 2000，1 <= w <= 10^4。
// 算法标签：树形动态规划、树上背包
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