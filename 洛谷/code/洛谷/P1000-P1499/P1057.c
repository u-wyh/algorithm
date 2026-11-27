// https://www.luogu.com.cn/problem/P1057
// 题意：n 人坐成一圈，每次把球传给左邻或右邻。
// 球从指定同学手里出发，求恰好传 m 次后回到该同学手里的不同接球顺序数。
// 数据范围：3 ≤ n ≤ 30，1 ≤ m ≤ 30。
// 算法标签：动态规划

#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int dp[m+1][n+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
        }
    }
    dp[0][1]=1;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(j==1)
                dp[i][j]=dp[i-1][j+1]+dp[i-1][n];
            else if(j==n)
                dp[i][j]=dp[i-1][1]+dp[i-1][j-1];
            else
                dp[i][j]=dp[i-1][j+1]+dp[i-1][j-1];
        }
    }
    /*for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            printf("%4d",dp[i][j]);
        }
        printf("\n");
    }*/
    printf("%d\n",dp[m][1]);
    return 0;
}
