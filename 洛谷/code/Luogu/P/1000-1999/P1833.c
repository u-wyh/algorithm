#include<stdio.h>

typedef struct time
{
    int hh;
    int mm;
}T;

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    T s[2];
    for(int i=0;i<2;i++)
    {
        scanf("%d:%d",&s[i].hh,&s[i].mm);
    }
    int times=(s[1].hh-s[0].hh)*60+s[1].mm-s[0].mm;
    //printf("%d\n",times);
    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1],c[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        if(c[i]==0)
            c[i]=1e7;
    }
    int dp[times+1];
    for(int j=0;j<=times;j++)
        dp[j]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=times;j>=a[i];j--)
        {
            for(int k=1;k<=c[i]&&k*a[i]<=j;k++)
                dp[j]=max(dp[j],dp[j-k*a[i]]+k*b[i]);
        }
    }
    int ans=0;
    for(int j=1;j<=times;j++)
    {
        ans=max(ans,dp[j]);
    }
    printf("%d\n",ans);
    return 0;
}
