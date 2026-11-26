// https://www.luogu.com.cn/problem/P1336
// 题意：要完成 n 篇论文，有 m 种课题。第 i 种写 x 篇的总耗时为 A[i]×x^B[i]，同一课题可写多篇，也可不写。求恰好写完 n 篇的最少总耗时。
// 数据范围：1 ≤ n ≤ 200，1 ≤ m ≤ 20，1 ≤ A[i] ≤ 100，1 ≤ B[i] ≤ 5。

#include<stdio.h>
#include<math.h>
#include<limits.h>

long long min(long long  a,long long  b)
{
    return a<b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
    }
    long long dp[n+1][m+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=INT_MAX/2;
            if(j==0)
                dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=1;j--)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=j;k++)
                dp[i][j]=min(dp[i][j],dp[i-1][j-k]+a[i]*pow(k,b[i]));
        }
    }
    /*for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            printf("%5d",dp[i][j]);
        }
        printf("\n");
    }*/
    printf("%lld\n",dp[n][m]);
    return 0;
}
