// https://www.luogu.com.cn/problem/P8707
// 题意：输入整数 n, m，在 n 行 m 列网格中从 (1, 1) 走到 (n, m)，每次只能向右或向下移动一格，且不能走入行号和列号均为偶数的格子
// 输出总方案数。
// 数据范围：1 <= n, m <= 30。
// 算法标签：动态规划
#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int dp[n+1][m+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dp[i][j]=0;
            if(i==1||j==1)
                dp[i][j]=1;
            if(i%2==0&&j%2==0)
                dp[i][j]=-1;
        }
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=2;j<=m;j++)
        {
            if(dp[i][j]==-1)
                j++;
            if(dp[i-1][j]!=-1)
                dp[i][j]+=dp[i-1][j];
            if(dp[i][j-1]!=-1)
                dp[i][j]+=dp[i][j-1];
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
