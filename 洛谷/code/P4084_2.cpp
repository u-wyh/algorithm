// https://www.luogu.com.cn/problem/P4084
// 题意：第一行输入谷仓数 N 和已涂色数 K；接下来 N-1 行输入树的无向边 (x, y)；
// 最后 K 行每行输入谷仓 b 及其已涂颜色 c（共 3 种颜色）。
// 要求给其余未涂色谷仓涂上颜色 1~3 中的一种，使得任意直接相连的两个谷仓颜色不同。
// 输出合法涂色方案数对 10^9 + 7 取模的结果。
// 数据范围：1 <= N <= 10^5，0 <= K <= N，1 <= x, y <= N（x != y），1 <= b <= N
// 1 <= c <= 3。
#include<bits/stdc++.h>
// 算法标签：树形动态规划、深度优先搜索
using namespace std;
const int MAXN = 200005;
const int MOD = 1e9+7;

int head[MAXN];
int Next[MAXN];
int to[MAXN];
int cnt=1;
int n,m;
long long dp[MAXN][3];

void dfs(int u,int p){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=p){
            dfs(v,u);
            dp[u][0]=(dp[u][0]*((dp[v][1]+dp[v][2])%MOD))%MOD;
            dp[u][1]=(dp[u][1]*((dp[v][0]+dp[v][2])%MOD))%MOD;
            dp[u][2]=(dp[u][2]*((dp[v][0]+dp[v][1])%MOD))%MOD;
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=0;j<3;j++){
            dp[i][j]=1;
        }
    }
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        v--;
        if(v==0){
            dp[u][1]=0;
            dp[u][2]=0;
        }else if(v==1){
            dp[u][0]=0;
            dp[u][2]=0;
        }else {
            dp[u][0]=0;
            dp[u][1]=0;
        }
    }
    dfs(1,0);
    cout<<(dp[1][0]+dp[1][1]+dp[1][2])%MOD;
    return 0;
}
