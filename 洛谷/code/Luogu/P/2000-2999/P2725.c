#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int k,n;
    scanf("%d %d",&k,&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[2000001];
    for(int i=1;i<=2000000;i++)
        dp[i]=INT_MAX;
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=nums[i];j<=2000000;j++)
        {
            if(dp[j-nums[i]]<k)
                dp[j]=min(dp[j],dp[j-nums[i]]+1);
        }
    }
    int ans=0;
    for(int i=1;i<=2000000;i++)
    {
        if(dp[i]==INT_MAX)
        {
            printf("%d\n",ans);
            return 0;
        }
        else
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
