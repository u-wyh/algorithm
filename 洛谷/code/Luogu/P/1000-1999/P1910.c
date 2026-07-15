#include<stdio.h>
#define N 101
#define M 1001
#define X 1001

int dp[N][M][X];

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,x;
    scanf("%d %d %d",&n,&m,&x);
    int a[n+1],b[n+1],c[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
    }
    int dp[n+1][m+1][x+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=x;j++)
        {
            dp[0][i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            for(int k=0;k<=x;k++)
            {
                dp[i][j][k]=dp[i-1][j][k];
                if(j>=b[i]&&k>=c[i])
                    dp[i][j][k]=max(dp[i][j][k],dp[i-1][j-b[i]][k-c[i]]+a[i]);
            }
        }
    }
    printf("%d\n",dp[n][m][x]);
    return 0;
}
