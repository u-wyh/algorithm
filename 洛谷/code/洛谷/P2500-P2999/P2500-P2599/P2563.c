// https://www.luogu.com.cn/problem/P2563
// 题意：多组数据（EOF 结束），每组给定自然数 n。
// 求 n 可以写成多少种本质不同的质数和表达式（顺序无关）。
// 每组输出一行方案数。
// 数据范围：2 <= n <= 200。
// 算法标签：完全背包、动态规划
#include <stdio.h>
#include <string.h>
#include <math.h>


int pan(int x) {
    for (int i = 2; i <= (int)sqrt(x); i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int main()
{
    int su[47];
    int num=0;
    for (int i = 2; i <= 200; i++) {
        if (pan(i)) {
            su[++num] = i;
        }
    }
    int dp[201];
    for(int i=0;i<=200;i++)
        dp[i]=0;
    dp[0]=1;
    for(int i=1;i<=46;i++)
    {
        for(int j=su[i];j<=200;j++)
        {
            dp[j]+=dp[j-su[i]];
        }
    }
    int n;
    while(scanf("%d",&n)==1)
    {
        printf("%d\n",dp[n]);
    }
}
