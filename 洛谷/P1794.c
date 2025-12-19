#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int V,G,n;
    scanf("%d %d %d",&V,&G,&n);
    int v[n+1],g[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&val[i],&v[i],&g[i]);
    }
    int dp[V+1][G+1];
    for(int i=0;i<=V;i++)
    {
        for(int j=0;j<=G;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=V;j>=0;j--)
        {
            for(int k=G;k>=0;k--)
            {
                if(j>=v[i]&&k>=g[i])
                    dp[j][k]=max(dp[j][k],dp[j-v[i]][k-g[i]]+val[i]);
            }
        }
    }
    printf("%d\n",dp[V][G]);
    return 0;
}
