#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int dp[n+1];
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        dp[i]=dp[i-1]+1;
        if(i>=5)
            dp[i]=min(dp[i],dp[i-5]+1);
        if(i>=11)
            dp[i]=min(dp[i],dp[i-11]+1);

    }
    printf("%d\n",dp[n]);
    return 0;
}
