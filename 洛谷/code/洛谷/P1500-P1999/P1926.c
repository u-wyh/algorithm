// https://www.luogu.com.cn/problem/P1926
// 题意：有 n 道想刷的题和 m 项作业，完成任一项都要花时间，作业还能得分。
// 总时间不超过 r，作业分至少达到 k。求最多能刷几道题。
// 数据范围：n,m ≤ 10，k ≤ 50，r ≤ 150，保证能及格。
// 算法标签：0-1背包、动态规划

#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m,k,r;
    scanf("%d %d %d %d",&n,&m,&k,&r);
    int t[n+1];
    for(int i=1;i<= n;i++)
    {
        scanf("%d",&t[i]);
    }
    int cost[m+1],val[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&cost[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&val[i]);
    }
    int dp[m+1][r+1];
    for(int i=0;i<=r;i++)
        dp[0][i]=0;
    for(int i=0;i<=m;i++)
        dp[i][0]=0;
    int least=r;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=r;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i])
                dp[i][j]=max(dp[i-1][j-cost[i]]+val[i],dp[i][j]);
            if(dp[i][j]>=k)
            {
                least=min(least,j);
            }
        }
    }
    r-=least;
    int dp2[n+1][r+1];
    for(int i=0;i<=r;i++)
    {
        dp2[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=r;j++)
        {
            dp2[i][j]=dp2[i-1][j];
            if(j>=t[i])
                dp2[i][j]=max(dp2[i][j],dp2[i-1][j-t[i]]+1);
        }
    }
    printf("%d\n",dp2[n][r]);
    return 0;
}
