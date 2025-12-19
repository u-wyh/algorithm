#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int x;
    scanf("%d",&x);
    int dp[3]={1e9,1e9,1e9};
    dp[x+1]=0;
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&x);
        if(x==-1)
        {
            dp[1]=1e9;
            dp[2]+=2;
        }
        if(x==0)
        {
            dp[1]=min(dp[1],dp[0]);
            dp[0]++;
            dp[2]++;
        }
        if(x==1)
        {
            dp[2]=min(dp[2],min(dp[1],dp[0]));
            dp[1]=dp[0]+1;
            dp[0]+=2;
        }
    }
    int ans=min(dp[0],min(dp[1],dp[2]));
    if(ans>=1e9)
        printf("BRAK\n");
    else
        printf("%d\n",ans);
    return 0;
}

