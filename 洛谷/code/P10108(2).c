#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int choice[m+1];
    int Max=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&choice[i]);
        Max=max(Max,choice[i]);
    }
    int val[n+Max+1];
    val[0]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }
    for(int i=n+1;i<=n+Max;i++)
        val[i]=0;
    int dp[Max+n+1];
    for(int i=0;i<=Max+n;i++)
        dp[i]=INT_MIN;
    dp[1]=val[1];
    for(int j=2;j<=Max+n;j++)
    {
        for(int i=1;i<=m;i++)
        {
            if(j>=choice[i])
                dp[j]=max(dp[j],dp[j-choice[i]]+val[j]);
        }
    }
    //for(int i=1;i<=n+Max;i++)
      //  printf("%d\n",dp[i]);
    int ans=0;
    for(int i=n;i<=Max+n;i++)
    {
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}

