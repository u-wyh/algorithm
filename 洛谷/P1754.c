#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    long long dp[2*n+1][n+1];
    for(int i=0;i<=2*n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=0;
            if(i==j)
                dp[i][j]=1;
        }
    }
    for(int i=1;i<=2*n;i++)
    {
        for(int j=0;j<=n&&j<i;j++)
        {
            if(j==0)
                dp[i][j]+=dp[i-1][j+1];
            else if(j==n)
                dp[i][j]+=dp[i-1][j-1];
            else
                dp[i][j]+=(dp[i-1][j-1]+dp[i-1][j+1]);
        }
    }
    /*
    for(int i=0;i<=2*n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            printf("%5d",dp[i][j]);
        }
        printf("\n");
    }
    */
    printf("%lld\n",dp[2*n][0]);
    return 0;
}
