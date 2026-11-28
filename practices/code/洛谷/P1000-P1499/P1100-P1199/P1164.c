// https://www.luogu.com.cn/problem/P1164
// 题意：有 N 种菜，每种只有一份，价格是 a[i]，手上正好有 M 元。
// 统计选择若干菜使总价等于 M 的不同选法。即使价格相同，菜品不同也分别计数。
// 数据范围：1 ≤ N ≤ 100，1 ≤ M ≤ 10000，
// 1 ≤ a[i] ≤ 1000，答案在 [0,2^31-1]。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划、递归

#include<stdio.h>
#define N 101
#define M 10001

int dp[N][M];

int f1(int *nums,int n,int m,int i)
{
    if(m==0)
        return 1;
    if(i>=n)
        return 0;
    return f1(nums,n,m,i+1)+f1(nums,n,m-nums[i],i+1);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    printf("%d\n",f1(nums,n,m,0));
    for(int i=0;i<=n;i++)
    {
        dp[i][0]=1;
    }
    for(int i=1;i<=m;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i-1])
            {
                dp[i][j]+=dp[i-1][j-nums[i-1]];
            }
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
