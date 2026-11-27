// https://www.luogu.com.cn/problem/P5628
// 题意：给定一棵 n 个点的树，某条边的重要性定义为删去后无法互通的点对数；
// 若未知某点发生施工且关闭距其距离不超过 k 的所有点及相连边，求被影响道路的重要度总和最大值。
// 输入 n, k 及树边；输出最大受影响道路重要度之和。
// 数据范围：n <= 30000，0 <= k <= 200。
#include<bits/stdc++.h>
// 算法标签：换根动态规划、树形动态规划
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 205;

int n,m;
int sz[MAXN];
int dp[MAXN][MAXM];//dp[i][j]表示到i距离不到j的破坏

int cnt=2;//这里是为了方便给边添加边权
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

void addedge(int u,int v){
    //cout<<u<<' '<<v<<' '<<cnt<<endl;
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=0;
    head[u]=cnt++;
}

//建立边权
void dfs(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
            weight[i]=weight[i^1]=sz[v]*(n-sz[v]);
            sz[u]+=sz[v];
        }
    }
}

void dfs1(int u,int fa){
    dp[u][0]=0;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs1(v,u);
        for(int j=1;j<=m+1;j++){
            dp[u][j]+=dp[v][j-1]+weight[i];
        }
    }
}

void dfs2(int u,int fa,int val){
    if(fa!=0){
        for(int j=m+1;j>=2;j--){
            dp[u][j]+=dp[fa][j-1];
            dp[u][j]-=dp[u][j-2];
        }
        dp[u][1]+=val;
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs2(v,u,weight[i]);
        //cout<<' '<<v<<' '<<u<<' '<<weight[i]<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;//最终输出的答案是dp[n][m+1]  m实际上加1
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v),addedge(v,u);
    }
    dfs(1,0);
    dfs1(1,0);
    dfs2(1,0,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i][m+1]);
    }
    cout<<ans<<endl;
    return 0;
}
