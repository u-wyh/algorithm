// https://www.luogu.com.cn/problem/P1073
// 题意：从城市 1 出发最终到 n。
// 途中可以至多买一次水晶球并在之后卖一次，也可以不交易。
// 允许重过城市，求最大利润。
// 道路 (x,y,z) 在 z=1 时只允许 x 到 y，z=2 时可双向。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ m ≤ 5 × 10^5，
// 1 ≤ x,y ≤ n，z 为 1 或 2，各地价格不超过 100。
// 算法标签：深度优先搜索、动态规划

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m;
int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt=1;
int nums[MAXN];
int dp[MAXN];
int mi[MAXN];

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int now,int pre,int minn){
    int flag=1;
    minn=min(minn,nums[now]);
    if(minn<mi[now]){
        mi[now]=minn;
        flag=0;
    }
    int maxx=max(dp[pre],nums[now]-minn);
    if(maxx>dp[now]){
        dp[now]=maxx;
        flag=0;
    }
    if(flag)
        return ;
    for(int i=head[now];i>0;i=Next[i]){
        int v=to[i];
        dfs(v,now,minn);
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
        mi[i]=INT_MAX;
    }
    for(int i=1;i<=m;i++){
        int u,v,opt;
        cin>>u>>v>>opt;
        addedge(u,v);
        if(opt==2){
            addedge(v,u);
        }
    }
    dfs(1,0,INT_MAX);
    cout<<dp[n]<<endl;
    return 0;
}