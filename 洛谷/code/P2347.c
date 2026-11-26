// https://www.luogu.com.cn/problem/P2347
// 题意：给出 1g、2g、3g、5g、10g、20g 砝码的各自数量。
// 求用这些砝码能称出的不同正整数重量个数。
// 按 Total=N 格式输出。
// 数据范围：所有砝码总重 <= 1000。
#include<stdio.h>

int main()
{
    int nums[7];
    for(int i=1;i<=6;i++)
    {
        scanf("%d",&nums[i]);
    }
    int count[7]={0,1,2,3,5,10,20};
    int dp[1001];
    for(int i=1;i<=1000;i++)
        dp[i]=0;
    dp[0]=1;

    int ans=0;
    for(int i=1;i<=1000;i++)
    {
        if(dp[i])
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
