// https://www.luogu.com.cn/problem/P4802
// 题意：给定 n 点（0~n-1）m
// 条有向带权边（无重边自环，保证 0 可达 n-1），
// 求从 0 到 n-1 不重复经过城市的最长路径长度。
// 数据范围：2 <= n <= 18，1 <= m <= n^2 - n，
// 0 <= s, d <= n-1 (s != d)
// 1 <= l <= 10000。
// 难度评分：1700（洛谷分级换算）
// 算法标签：状态压缩动态规划、记忆化搜索
#include<bits/stdc++.h>
using namespace std;

int dp[1<<18][20];
int head[18];
int Next[400];
int to[400];
int weight[400];
int cnt;
int n,m;

int dfs(int status,int now){
    if(now==(n-1)){
        return 0;
    }
    if(dp[status][now]){
        return dp[status][now];
    }
    int ans=-1<<25;
    for(int i=head[now];i>0;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if((status&(1<<v))==0){
            ans=max(ans,w+dfs(status|(1<<v),v));
        }
    }
    dp[status][now]=ans;
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j]=0;
        }
    }
    cout<<dfs(1,0);
    return 0;
}
