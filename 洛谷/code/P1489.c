// https://www.luogu.com.cn/problem/P1489
// 题意：给 n 个数，把全部数分进两组，组大小相差至多 1。求使两组元素和尽量接近的一种分法，按从小到大的顺序输出两组的和。
// 数据范围：1 ≤ n ≤ 200，1 ≤ a[i] ≤ 40。

#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int sum=0;
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    int dp[sum/2+1];
    for(int j=0;j<=sum/2;j++)
    {
        dp[j]=0;
        if(j==0)
            dp[j]=1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=min(n/2,i);j>=1;j--)
        {
            for(int k=sum/2;k>=nums[i];k--)
            {
                dp[k]|=dp[k-nums[i]];
            }
        }
    }
    for(int i=sum/2;i>=0;i--)
    {
        if(dp[i])
        {
            printf("%d %d\n",i,sum-i);
            return 0;
        }
    }
    return 0;
}
