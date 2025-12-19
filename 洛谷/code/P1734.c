#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int m;
    scanf("%d",&m);
    int nums[1001];
    for(int i=1;i<=1000;i++)
    {
        nums[i]=0;
        for(int j=1;j<=i/2;j++)
        {
            if(i%j==0)
                nums[i]+=j;
        }
        //printf("%5d",nums[i]);
    }
    int dp[1001][m+1];
    for(int i=0;i<=m;i++)
        dp[0][i]=0;
    for(int i=1;i<=1000;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=i)
                dp[i][j]=max(dp[i][j],dp[i-1][j-i]+nums[i]);
        }
    }
    printf("%d\n",dp[1000][m]);
    return 0;
}
