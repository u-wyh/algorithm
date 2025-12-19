#include<stdio.h>

#define mod 1000000007

int main()
{
    int d,t,m;
    scanf("%d %d %d",&d,&t,&m);
    if(d+2*m-t<=0||m>t)
    {
        int ans=0;
        printf("%d",ans);
        return 0;
    }
    int dp[t+1][d+m+2];
    for(int i=0;i<=t;i++)
    {
        for(int j=0;j<=d+m+1;j++)
        {
            if(i==0||j==0||j==d+m+1)
                dp[i][j]=0;
        }
    }
    dp[0][d]=1;
    for(int i=1;i<=t;i++)
    {
        for(int j=1;j<=d+m;j++)
        {
            dp[i][j]=(dp[i-1][j-1]%mod+dp[i-1][j+1]%mod)%mod;
        }
    }
    printf("%d\n",dp[t][d+2*m-t]);
    return 0;
}
