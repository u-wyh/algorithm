// https://www.luogu.com.cn/problem/P1052
// 题意：青蛙从桥的 0 点起跳，每次可向前跳任意整数距离 S 到 T，
// 落到 L 或更远就算过桥。
// 给桥上 M 颗石子的坐标，求过桥最少会落在多少颗石子上。
// 数据范围：1 ≤ L ≤ 10^9，1 ≤ S ≤ T ≤ 10，
// 1 ≤ M ≤ 100，石子坐标互异且位于桥的两个端点之间。
// 难度评分：1500（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>
#define Max 100000005

int flag[Max];
int dp[Max];

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int len,s,t,m;
    scanf("%d %d %d %d",&len,&s,&t,&m);
    int nums[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&nums[i]);
        flag[nums[i]]=1;
    }
    memset(dp,1e9,sizeof(dp));
    for(int i=0;i<=len;i++)
    {
        if(i<s)
            dp[i]=0;
        for(int j=s;j<=t&&j<=i;j++)
            dp[i]=min(dp[i],dp[i-j]+flag[i]);
    }
    printf("%d\n",dp[len]);
    return 0;
}
