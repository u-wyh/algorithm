#include<stdio.h>
#include<string.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums[i]);
    }
    int a[n+1],b[n+1],maxn=0;
    a[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(a[i-1]!=0)
            b[i]=a[i]+1-a[i-1];
        else
            b[i]=a[i];
        maxn=max(maxn,b[i]);
        //printf("%-3d",b[i]);
    }
    //printf("%d\n",maxn);
    int dp[maxn+1];
    //memset(dp,1e9,sizeof(dp));
    for(int j=1;j<=maxn;j++)
    {
        dp[j]=1e9;
    }
    dp[0]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=maxn;j>=nums[i];j--)
        {
            for(int k=1;k*nums[i]<=j;k++)
                dp[j]=min(dp[j],dp[j-k*nums[i]]+k);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=dp[b[i]];
    }
    if(ans==0&&maxn!=0)
        printf("-1\n");
    else
        printf("%d\n",ans);
    return 0;
}
