// https://www.luogu.com.cn/problem/P3636
// 题意：输入两个正整数 a 和 b。
// 对 k in [a, b]，定义 P(k) 为方程 xyz = k 的所有整数解 (x, y, z) 到原点的曼哈顿距离平方 (|x|+|y|+|z|)^2 之和。
// 输出 sum_{k=a..b} P(k) 对 10007 取模的结果。
// 数据范围：1 <= a, b <= 3*10^8。
#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int dp[n+1];
    dp[1]=0;
    for(int i=2;i<=n;i++)
    {
        dp[i]=dp[i-1]+1;
        if(i%2==0)
            dp[i]=min(dp[i],dp[i/2]+1);
    }
    printf("%d\n",dp[n]);
    return 0;
}
