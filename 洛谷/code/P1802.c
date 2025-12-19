#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}
;
int main()
{
    int n,x;
    scanf("%d %d",&n,&x);
    int lose[n+1],win[n+1],use[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&lose[i],&win[i],&use[i]);
    }
    long long  dp[n+1][x+1];
    for(int i=0;i<=x;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=x;j++)
        {
            dp[i][j]=dp[i-1][j]+lose[i];
            if(j>=use[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-use[i]]+win[i]);
        }
    }
    printf("%lld\n",5*dp[n][x]);
    return 0;
}
