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
