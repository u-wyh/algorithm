// https://www.luogu.com.cn/problem/P6192
// 题意：给定 n 点 m 边的带权无向连通图 G（可能有重边和自环）
// 以及包含 k 个点的集合 S
// 求包含 S 中所有点的连通子图 G' 的最小边权和（最小斯坦纳树）。
// 数据范围：1 <= n <= 100，1 <= m <= 500，
// 1 <= k <= 10，1 <= u, v <= n，
// 1 <= w <= 10^6。
// 算法标签：最小斯坦纳树、状态压缩动态规划、Dijkstra
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 505;
const int MAXK = 10;
const int MAXS = 1024;
const int INF = 1e9;

int n,m,k;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
int cnt=1;

int key[MAXK];
int dp[MAXS][MAXN];
bool vis[MAXN];

struct node{
    int u,d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

int main()
{
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=0;i<k;i++){
        scanf("%d",&key[i]);
    }
    int statue=(1<<k)-1;
    for(int i=0;i<=statue;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=INF;
        }
    }
    for(int i=0;i<k;i++){
        dp[1<<i][key[i]]=0;
    }
    for(int s=1;s<=statue;s++){
        for(int sub=(s-1)&s;sub;sub=(sub-1)&s){
            int other=s-sub;
            for(int u=1;u<=n;u++){
                if(dp[sub][u]<INF&&dp[other][u]<INF){
                    dp[s][u]=min(dp[s][u],dp[sub][u]+dp[other][u]);
                }
            }
        }

        for(int i=1;i<=n;i++){
            vis[i]=false;
        }
        for(int u=1;u<=n;u++){
            if(dp[s][u]<INF){
                heap.push({u,dp[s][u]});
            }
        }
        while(!heap.empty()){
            int u=heap.top().u;
            heap.pop();
            if(vis[u]){
                vis[u]=true;
            }
            vis[u]=true;
            for(int i=head[u];i;i=nxt[i]){
                int v=to[i];
                int w=weight[i];
                if(dp[s][v]>dp[s][u]+w){
                    dp[s][v]=dp[s][u]+w;
                    heap.push({v,dp[s][v]});
                }
            }
        }
    }
    int ans=INF;
    for(int i=1;i<=n;i++){
        ans=min(ans,dp[statue][i]);
    }
    cout<<ans<<endl;
    return 0;
}