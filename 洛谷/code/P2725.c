// https://www.luogu.com.cn/problem/P2725
// 题意：有 n 种面值 a_i 的邮票（数量无限），最多贴 k 张。
// 求最大的正整数 m，使 1~m 都能用不超过 k 张邮票组合出来（不存在输出 0）。
// 数据范围：1 <= k <= 200，1 <= n <= 50，1 <= a_i <= 10^4。
#include<stdio.h>
#include<limits.h>
// 算法标签：完全背包、动态规划

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int k,n;
    scanf("%d %d",&k,&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[2000001];
    for(int i=1;i<=2000000;i++)
        dp[i]=INT_MAX;
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=nums[i];j<=2000000;j++)
        {
            if(dp[j-nums[i]]<k)
                dp[j]=min(dp[j],dp[j-nums[i]]+1);
        }
    }
    int ans=0;
    for(int i=1;i<=2000000;i++)
    {
        if(dp[i]==INT_MAX)
        {
            printf("%d\n",ans);
            return 0;
        }
        else
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
