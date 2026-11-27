// https://www.luogu.com.cn/problem/P1203
// 题意：给定环形项链上 n 颗珠子的颜色序列（r 红、b 蓝、w 白）。
// 题意：从某处打断展开成链，分别从两端收集同色珠子（白色可按红或蓝算，两端独立）。
// 题意：求能收集到的最大珠子总数（同一颗珠子不能重复收集）。
// 输入：第一行输入珠子数 n，第二行输入长度为 n 的 r/b/w 字符串。
// 输出：一行输出能收集到的最大珠子数量。
// 数据范围：3 <= n <= 350。
// 算法标签：动态规划
#include<stdio.h>
#include<math.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    scanf("\n");
    char str[n];
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%c",&str[i]);
        if(str[i]=='r')
            nums[i]=1;
        else if(str[i]=='w')
            nums[i]=2;
        else
            nums[i]=3;
        printf("%d",nums[i]);
    }
    printf("\n");
    int dp[n][2];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<2;j++)
        {
            dp[i][j]=1;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(abs(nums[i]-nums[i-1])<=1)
            dp[i][0]=dp[(i-1+n)%n][0]+1;
        if(abs(nums[i]-nums[i+1])<=1)
            dp[i][1]=dp[(i+1)==n?0:(i+1)][1]+1;
    }
    int ans=dp[n-1][0]+dp[0][1];
    for(int i=0;i<n-1;i++)
        ans=max(ans,dp[i][0]+dp[i+1][1]);
    printf("%d\n",ans);
    return 0;
}
