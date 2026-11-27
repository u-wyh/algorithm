// https://www.luogu.com.cn/problem/P3133
// 题意：输入两人路径步数 N, M、各自起点 (fx, fy) 和
// (bx, by)，以及两个由 N/E/S/W 组成的移动串。
// 每个时刻（只要还没到各自终点），两人可各自选择原地不动或沿自己的路径走下一步；
// 每步结束后消耗当前两人欧氏距离的平方的能量。
// 求两人都到达终点时消耗总能量的最小值（不含初始位置）。
// 输出一个整数表示最小总能量消耗。
// 数据范围：1 <= N, M <= 1000，
// 0 <= fx, fy, bx, by <= 1000。
// 算法标签：动态规划
#include<bits/stdc++.h>
using namespace std;

struct node{
    int x,y;
}f[1005],b[1005];
int n,m;
char c;
int dis[1005][1005];
int dp[1005][1005];

int main()
{
    cin>>n>>m;
    cin>>f[0].x>>f[0].y>>b[0].x>>b[0].y;
    for(int i=1;i<=n;i++){
        cin>>c;
        if(c=='N'){
            f[i].x=f[i-1].x;
            f[i].y=f[i-1].y+1;
        }
        else if(c=='E'){
            f[i].x=f[i-1].x+1;
            f[i].y=f[i-1].y;
        }
        else if(c=='S'){
            f[i].x=f[i-1].x;
            f[i].y=f[i-1].y-1;
        }
        else if(c=='W'){
            f[i].x=f[i-1].x-1;
            f[i].y=f[i-1].y;
        }
    }
    for(int i=1;i<=m;i++){
        cin>>c;
        if(c=='N'){
            b[i].x=b[i-1].x;
            b[i].y=b[i-1].y+1;
        }
        else if(c=='E'){
            b[i].x=b[i-1].x+1;
            b[i].y=b[i-1].y;
        }
        else if(c=='S'){
            b[i].x=b[i-1].x;
            b[i].y=b[i-1].y-1;
        }
        else if(c=='W'){
            b[i].x=b[i-1].x-1;
            b[i].y=b[i-1].y;
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dis[i][j]=pow(f[i].x-b[j].x,2)+pow(f[i].y-b[j].y,2);
        }
    }
    for(int i=1;i<=m;i++){
        dp[0][i]=dp[0][i-1]+dis[0][i];
    }
    for(int i=1;i<=n;i++){
        dp[i][0]=dp[i-1][0]+dis[i][0];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+dis[i][j];
        }
    }
    cout<<dp[n][m];
    return 0;
}
