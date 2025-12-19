#include<stdio.h>

int  max(int  a,int  b)
{
    return a>b?a:b;
}

int main()
{
    int x1,x2,k;
    scanf("%d %d",&x1,&x2);
    k=x2/x1;
    int n,m;
    scanf("%d %d",&n,&m);
    int t2[m+1],t1[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&t2[i]);
        t1[i]=(t2[i]*k);
    }
    int cost[n+1],val[n+1];
    int p[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&p[i],&val[i]);
        cost[i]=t1[p[i]];
    }
    int t;
    scanf("%d",&t);
    int dp[n+1][t+1];
    for(int i=0;i<=t;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=t;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]]+val[i]);
        }
    }
    printf("%d\n",dp[n][t]);
    return 0;
}
