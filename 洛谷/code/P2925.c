#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int c,n;
    scanf("%d %d",&c,&n);
    int v[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    int dp[n+1][c+1];
    for(int i=0;i<=c;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=c;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=v[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-v[i]]+v[i]);
        }
    }
    printf("%d\n",dp[n][c]);
    return 0;
}
