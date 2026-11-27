// https://www.luogu.com.cn/problem/P1466
// 题意：把 1 到 n 的每个整数分到两个集合之一，让两边元素和相等。求不同分法的数量，交换两个集合视为同一分法。无法等分时计数为 0。
// 数据范围：1 ≤ n ≤ 39。
// 算法标签：背包动态规划

#include<stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int sum=(n*n+n)/2;
    if(sum%2==0)
        sum/=2;
    else
    {
        int ans=0;
        printf("%d\n",ans);
        return 0;
    }
    long long dp[n+1][sum+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=0;
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=i)
                dp[i][j]+=dp[i-1][j-i];
        }
    }
    printf("%lld\n",dp[n][sum]/2);
    return 0;
}
