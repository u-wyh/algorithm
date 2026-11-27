// https://www.luogu.com.cn/problem/P6323
// 题意：求长度为 n 且逆序对数量恰好为 c 的排列总数，答案对 10^9+7 取模。
// 数据范围：1 <= n <= 10^3，1 <= c <= 10^4。
// 算法标签：动态规划
#include<stdio.h>
#define mod 1000000007

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,c;
    scanf("%d %d",&n,&c);
    int dp[c+1];
    for(int i=0;i<=c;i++)
        dp[i]=0;
    dp[0]=1;
    dp[1]=1;
    for(int i=3;i<=n;i++)
    {
        for(int j=min(c,i*(i-1)/2);j>=1;j--)
        {
            for(int k=1;k<=i-1&&k<=j;k++)
                dp[j]=(dp[j]+dp[j-k])%mod;
        }
    }
    printf("%d\n",dp[c]);
    return 0;
}
