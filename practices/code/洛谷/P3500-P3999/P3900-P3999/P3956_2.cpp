// https://www.luogu.com.cn/problem/P3956
// 题意：m * m 棋盘中有 n 个格子有颜色（0 红或 1 黄），其余无色，
// 保证 (1, 1) 有色。
// 从 (1, 1) 走到 (m, m)，每次上下左右移动：
// 相邻两格同色花费 0 金币，异色花费 1 金币；
// 也可花 2 金币施展魔法把下一个无色格子临时变为指定颜色，
// 但不能连续对无色格子使用魔法（离开临时变色格后它恢复无色）。
// 求到达 (m, m) 的最少金币数，不可达输出 -1。
// 数据范围：1 <= m <= 100，1 <= n <= 10^3，
// 0 <= c <= 1。
// 难度评分：1400（洛谷分级换算）
// 算法标签：深度优先搜索、剪枝
#include<bits/stdc++.h>
using namespace std;
const int MAXM = 105;

int nums[MAXM][MAXM];
int vis[MAXM][MAXM];
int t[MAXM][MAXM];
int n,m;
int ans=INT_MAX;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

void dfs(int x,int y,int k,int f){
    //表示到了xy  花费为k  f=1表示可用魔法
    if(k>=ans||k>t[x][y]){
        return;
    }
    t[x][y]=min(t[x][y],k);
    if(x==m&&y==m){
        ans=k;
        return;
    }
    for(int i=0;i<4;i++){
        int ux=x+walk[i][0];
        int uy=y+walk[i][1];
        if(vis[ux][uy]||ux>m||uy>m||ux<=0||uy<=0||(f==0&&nums[ux][uy]==0)){
            continue;
        }
        vis[ux][uy]=true;
        if(nums[ux][uy]==0){
            nums[ux][uy]=nums[x][y];
            dfs(ux,uy,k+2,0);
            nums[ux][uy]=0;
        }
        else if(nums[ux][uy]==nums[x][y]){
            dfs(ux,uy,k,1);
        }
        else if(nums[ux][uy]!=nums[x][y]){
            dfs(ux,uy,k+1,1);
        }
        vis[ux][uy]=false;
    }
}

int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        nums[u][v]=w+1;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            t[i][j]=INT_MAX;
        }
    }
    vis[1][1]=true;
    dfs(1,1,0,1);
    if(ans==INT_MAX)
        ans=-1;
    cout<<ans;
    return 0;
}
