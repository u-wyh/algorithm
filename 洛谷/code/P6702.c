#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int dp[n+1];
    for(int i=0;i<=n;i++)
        dp[i]=-1;
    dp[0]=0;
    dp[3]=1;
    dp[5]=1;
    for(int i=6;i<=n;i++)
    {
        if(dp[i-3]!=-1)
            dp[i]=dp[i-3]+1;
        if(dp[i-5]!=-1&&dp[i]!=-1)
            dp[i]=min(dp[i-5]+1,dp[i]);
        else if(dp[i-5]!=-1)
            dp[i]=dp[i-5]+1;
    }
    printf("%d\n",dp[n]);
    return 0;
}
