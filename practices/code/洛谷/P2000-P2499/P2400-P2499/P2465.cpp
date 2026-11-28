// https://www.luogu.com.cn/problem/P2465
// 题意：n 个节点的树（根为 1），建 p 个分部（可同点），
// 第 i 点建第 j 个分部花费 a_{i,j}。
// 分部管辖其到根路径上的所有点，
// 另有 t 条组合收益/损失（指定分部同时管辖某点时触发）。
// 求最大总收益。
// 数据范围：1 <= p <= 12，1 <= n <= 100，
// 1 <= t <= 2^p，|v|, a_{i,j} <= 10^8。
// 难度评分：2600（洛谷分级换算）
// 算法标签：树形动态规划、状态压缩动态规划
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXM = 12;

int n,m,q;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int cost[MAXN][MAXM];
int val[1<<MAXM];
int dp[MAXN][1<<MAXM];

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void init(){
    for(int i=1;i<=n;i++){
        dp[i][0]=0;
        for(int j=1;j<(1<<m);j++){
            int low=j&-j;
            int bit=log2(low);
            dp[i][j]=dp[i][j-low]-cost[i][bit];
        }
    }
}

void dfs(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            for(int j=(1<<m)-1;j>=0;j--){
                for(int k=j;k;k=(k-1)&j){
                    dp[u][j]=max(dp[u][j],dp[u][j^k]+dp[v][k]);
                }
            }
        }
    }
    for(int i=0;i<(1<<m);i++){
        dp[u][i]+=val[i];
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            cin>>cost[i][j];
        }
    }
    init();
    cin>>q;
    for(int i=1;i<=q;i++){
        int value,cnt;
        cin>>value>>cnt;
        int mask=0;
        for(int j=1;j<=cnt;j++){
            int v;
            cin>>v;
            mask|=(1<<(v-1));
        }
        val[mask]+=value;
        int rest=(1<<m)-1-mask;
        for(int subset=rest;subset;subset=(subset-1)&rest){
            val[mask|subset]+=value;
        }
    }
    dfs(1,0);
    cout<<dp[1][(1<<m)-1]<<endl;
    return 0;
}