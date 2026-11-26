// https://www.luogu.com.cn/problem/P2925
// 题意：输入马车最大容积 C、稻草捆数 H，以及每捆稻草各自的体积 V_i。
// 从 H 捆稻草中挑选若干捆装上马车（每捆不可分割，要么全买要么不买），总体积不能超过 C。
// 计算在不超过马车最大容积的前提下能买到的最大稻草总体积。
// 输出一个整数，表示能买到的最大稻草体积。
// 数据范围：对于 100% 的数据，1 <= C <= 5*10^4，1 <= H <= 5*10^3，1 <= V_i <= C。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int c,n;
    scanf("%d %d",&c,&n);
    int v[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    int dp[c+1];
    for(int i=0;i<=c;i++)
    {
        dp[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=c;j>=0;j--)
        {
            if(j>=v[i])
                dp[j]=max(dp[j],dp[j-v[i]]+v[i]);
        }
    }
    printf("%d\n",dp[c]);
    return 0;
}

