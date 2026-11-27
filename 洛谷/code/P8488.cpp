// https://www.luogu.com.cn/problem/P8488
// 题意：n*m 棋盘第 i 行第 j 列写有 a_{i-1, j-1}（0-indexed 记为 a_{i,j}）。
// 骰子按前、后、左、右、上、下依次写有 w_0..w_5，初始置于 (0,0)
// 每步可向下一行（Front 方向）或下一列（Right 方向）翻滚一格直到 (n-1, m-1)。
// 求整个路径上（含起点终点）每次底面数字与所在格数字乘积之和的最大值。
// 数据范围：100% 数据满足 1 <= n, m <= 10^3，|a_{i,j}| <= 10^3，|w_i| <= 10^3。
// 算法标签：动态规划
#include<bits/stdc++.h>
using namespace std;

int d[6][6]={{0,0,5,6,4,3},{0,0,6,5,3,4},
                {0,0,6,5,1,2},{5,6,0,0,2,1},{3,4,2,1,0,0},{4,3,1,2,0,0}};
int arr[1005][1005];
int nums[6];
int n,m;
int dp[1005][1005][6][6];

signed main()
{
    memset(dp,0xc0,sizeof(dp));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<6;i++){
        cin>>nums[i];
    }
    dp[1][1][0][3]=nums[5]*arr[1][1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int u=0;u<6;u++){
                for(int v=0;v<6;v++){
                    if(v==u||(v^1)==u||(i==1&&j==1)){
                        continue;
                    }
                    dp[i][j][u][v]=max(dp[i-1][j][d[u][v]][v],dp[i][j-1][u][d[u][v]])+arr[i][j]*nums[d[u][v]];
                }
            }
        }
    }
    int ans=0xc0c0c0c0;
    for(int u=0;u<6;u++){
        for(int v=0;v<6;v++){
            //cout<<u<<' '<<v<<endl;
            ans=max(dp[n][m][u][v],ans);
        }
    }
    cout<<ans<<endl;
    return 0;
}
