// https://www.luogu.com.cn/problem/P1507
// 题意：选一些食品装进飞船，每种食品只有一份，给每件的体积、质量与热量。总体积不能超过 H，总质量不能超过 T。求可装食品的最大总热量。
// 数据范围：H,T 和每件体积、质量均不超过 400，n ≤ 50，单件热量不超过 500。

#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int H,T,n;
    scanf("%d %d",&H,&T);
    scanf("%d",&n);
    int h[n+1],t[n+1],v[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&h[i],&t[i],&v[i]);
    }
    int dp[n+1][H+1][T+1];
    for(int i=0;i<=H;i++)
    {
        for(int j=0;j<=T;j++)
        {
            dp[0][i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=H;j++)
        {
            for(int k=0;k<=T;k++)
            {
                dp[i][j][k]=dp[i-1][j][k];
                if(j>=h[i]&&k>=t[i])
                    dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-h[i]][k-t[i]]+v[i]);
            }
        }
    }
    printf("%d\n",dp[n][H][T]);
    return 0;
}
