// https://www.luogu.com.cn/problem/P1351
// 题意：给一棵树，每个点有权值。
// 每对相距恰好两条边的有序点对 (u,v)，贡献是两点权值的乘积。
// 输出最大贡献和所有贡献的和，只有总和对 10007 取模。
// 数据范围：3 ≤ n ≤ 2 × 10^5，1 ≤ W[i] ≤ 10000，
// 保证有符合条件的点对。
// 算法标签：树形动态规划、换根动态规划、深度优先搜索

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MOD = 10007;

int n;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
int arr[MAXN];
int sum[MAXN][3];
// sum[u][i] : 以u为头的子树内，距离为i的节点权值和
int dp[MAXN][3];
// dp[u][i] : 以u做根，整棵树上，距离为i的节点权值和
int maxans=0;

void dfs1(int u,int f){
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            for(int j=1;j<=2;j++){
                sum[u][j]+=sum[v][j-1];
            }
        }
    }
}

void dfs2(int u,int f){
    for (int e = head[u], v; e != 0; e = Next[e]) {
        v = to[e];
        if (v != f) {
            dp[v][0] = sum[v][0];
            dp[v][1] = sum[v][1] + dp[u][0];
            for (int i = 2; i <= 2; i++) {
                dp[v][i] = sum[v][i] + dp[u][i - 1] - sum[v][i - 2];
            }
            dfs2(v, u);
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    for(int i=1;i<=n;i++){
        cin>>sum[i][0];
    }
    dfs1(1,0);
    for(int i=0;i<=2;i++){
        dp[1][i]=sum[1][i];
    }
    dfs2(1,0);
    long ans=0;
    for (int i = 1; i <= n; i++) {
        ans=(ans+dp[i][0]*dp[i][2])%MOD;
    }
    cout<<ans;
    return 0;
}
