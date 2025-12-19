#include<stdio.h>

double max(double a,double b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    double nums[n+1];
    for(int i=1;i<=n;i++)
        scanf("%lf",&nums[i]);
    double dp[n+1][2];
    dp[1][0]=100;
    dp[1][1]=nums[1];
    for(int i=2;i<=n;i++)
    {
        dp[i][0]=max(dp[i-1][0],dp[i-1][1]*100/nums[i]);
        dp[i][1]=max(dp[i-1][1],dp[i-1][0]*nums[i]/100.0);
    }
    printf("%.2lf\n",max(dp[n][0],dp[n][1]*100/nums[n]));
    return 0;
}
