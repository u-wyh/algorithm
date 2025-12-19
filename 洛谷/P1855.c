#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,M,T;
    scanf("%d %d %d",&n,&M,&T);
    int m[n+1],t[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d %d",&m[i],&t[i]);
    int dp[n+1][M+1][T+1];
    for(int i=0;i<=M;i++)
    {
        for(int j=0;j<=T;j++)
        {
            dp[0][i][j]=0;
        }
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=0;i<=M;i++)
        {
            for(int j=0;j<=T;j++)
            {
                dp[k][i][j]=dp[k-1][i][j];
                if(i>=m[k]&&j>=t[k])
                    dp[k][i][j]=max(dp[k][i][j],dp[k-1][i-m[k]][j-t[k]]+1);
            }
        }
    }
    printf("%d\n",dp[n][M][T]);
    return 0;
}
