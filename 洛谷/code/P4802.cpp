// https://www.luogu.com.cn/problem/P4802
// 题意：给定 n 点（0~n-1）m 条有向带权边（无重边自环，保证 0 可达 n-1），求从 0 到 n-1 不重复经过城市的最长路径长度。
// 数据范围：2 <= n <= 18，1 <= m <= n^2 - n，0 <= s, d <= n-1 (s != d)
// 1 <= l <= 10000。
#include <iostream>
#include <cstdio>
#include <vector>
// 算法标签：状态压缩动态规划、记忆化搜索
using namespace std;

int dp[1<<18][20],n,m,t1,t2,t3;
vector<int> to[20],co[20];
bool vis[1<<18][20];

int dfs(int now,int vis){
    if(now==n)
        return 0;
    if(dp[vis][now])
        return dp[vis][now];
    int len=-1<<25;
    for(int i=0;i<to[now].size();i++)
        if(!(vis&(1<<to[now][i]-1)))
            len=max(len,co[now][i]+dfs(to[now][i],vis|(1<<to[now][i]-1)));
    return dp[vis][now]=len;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>t1>>t2>>t3;
        to[t1+1].push_back(t2+1);
        co[t1+1].push_back(t3);
    }
    cout<<dfs(1,1);
    return 0;
}
