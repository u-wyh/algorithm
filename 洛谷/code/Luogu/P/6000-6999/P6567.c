#include<stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int a[n+1],b[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
        sum+=a[i]*b[i];
    }
    int dp[sum+1];
    for(int j=0;j<=sum;j++)
    {
        dp[j]=0;
        if(j==0)
            dp[j]=1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=sum;j>=1;j--)
        {
            for(int k=1;k<=b[i]&&j>=k*a[i];k++)
            {
                dp[j]|=dp[j-k*a[i]];
            }
        }
    }
    int nums;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums);
        if(dp[nums])
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
