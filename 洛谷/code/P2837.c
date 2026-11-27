// https://www.luogu.com.cn/problem/P2837
// 题意：N 头牛排成一排，各有编号 1 或 2。
// 求最少修改多少头牛的编号，使所有 1 在前、所有 2 在后（允许全 1 或全 2）。
// 输出最少修改次数。
// 数据范围：1 <= N <= 3*10^4。
#include<stdio.h>
// 算法标签：动态规划、线性动态规划

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int dp[n+1][2];
    dp[1][nums[1]-1]=0;
    dp[1][2-nums[1]]=1;
    for (int i=2;i<=n;++i){
        if (nums[i]==1){
            dp[i][0]=dp[i-1][0];
            dp[i][1]=min(dp[i-1][1],dp[i-1][0])+1;
        }else{
            dp[i][0]=dp[i-1][0]+1;
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
        }
    }
    printf("%d\n",min(dp[n][0],dp[n][1]));
    return 0;
}
