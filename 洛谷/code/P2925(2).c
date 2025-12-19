#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int c,n;
    scanf("%d %d",&c,&n);
    int v[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    int dp[c+1];
    for(int i=0;i<=c;i++)
    {
        dp[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=c;j>=0;j--)
        {
            if(j>=v[i])
                dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
        }
    }
    printf("%d\n",dp[c]);
    return 0;
}

