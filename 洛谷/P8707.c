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
