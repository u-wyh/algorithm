#include<stdio.h>
#define mod 1000000007

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,c;
    scanf("%d %d",&n,&c);
    int dp[c+1];
    for(int i=0;i<=c;i++)
        dp[i]=0;
    dp[0]=1;
    dp[1]=1;
    for(int i=3;i<=n;i++)
    {
        for(int j=min(c,i*(i-1)/2);j>=1;j--)
        {
            for(int k=1;k<=i-1&&k<=j;k++)
                dp[j]=(dp[j]+dp[j-k])%mod;
        }
    }
    printf("%d\n",dp[c]);
    return 0;
}
