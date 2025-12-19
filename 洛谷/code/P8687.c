#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int nums[n+1][k+1];
    int num[n+1];
    int dp[1<<m];
    //memset(dp,INT_MAX,sizeof(dp));
    for (int i = 0; i < (1 << m); ++i) {
        dp[i] = INT_MAX;
    }
    for(int i=0;i<=n;i++)
        num[i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            scanf("%d",&nums[i][j]);
            num[i]|=(1<<(nums[i][j]-1));
        }
        dp[num[i]]=1;
       // printf("%d\n",num[i]);
       // printf("%d\n",dp[num[i]]);
    }
    //int dp[n+1][1<<m];
    //printf("%d",0b11111111111111111111);
    /*for(int i=1;i<=n;i++)
    {
        dp[i][num[i]]=1;
    }*/
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<(1<<m);j++)
        {
            int k=j|num[i];
            if(dp[j]!=INT_MAX)
            {
                dp[k]=min(dp[k],dp[j]+1);
            }
        }
    }
    if(dp[(1<<m)-1]==INT_MAX)
        dp[(1<<m)-1]=-1;
    printf("%d",dp[(1<<m)-1]);
    return 0;
}
