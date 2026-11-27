// https://www.luogu.com.cn/problem/P1049
// 题意：给容量为 V 的箱子和 n 个物品的体积。每件最多放一次，可以一件也不放，装入的总体积不能超过 V。求最小的剩余体积。
// 数据范围：1 ≤ n ≤ 30，1 ≤ V ≤ 20000，各物品体积为正整数。
// 算法标签：背包动态规划

#include<stdio.h>
#include<limits.h>
#define Max1 31
#define Max2 20001

int dp[Max1][Max2];

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int f1(int i,int n,int *nums,int v)
{
    int ans;
    if(i>=n)
        return 0;
    ans=f1(i+1,n,nums,v);
    if(v>=nums[i])
        ans=max(ans,f1(i+1,n,nums,v-nums[i])+nums[i]);
    return ans;
}

int main()
{
    int n,V;
    scanf("%d %d",&V,&n);
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    //printf("%d\n",V-f1(0,n,nums,V));
    for(int i=0;i<=V;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=V;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=nums[i-1])
                dp[i][j]=max(dp[i][j],dp[i-1][j-nums[i-1]]+nums[i-1]);
        }
    }
    printf("%d\n",V-dp[n][V]);
    return 0;
}
