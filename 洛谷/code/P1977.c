// https://www.luogu.com.cn/problem/P1977
// 题意：N 人要在截止时间 S 前打车。
// 第 i 辆车在 T_i 时到，有 Z_i 个空位，上车人数不超过空位。
// 用一辆车付 D 元，上车的每个人还要计入其等待时间。
// 求所有人都上车的最小总花费，无解输出 impossible。
// 数据范围：N,K,D,S ≤ 100，1 ≤ Z_i ≤ 4，1 ≤ T_i ≤ S，车辆按到达时间非降序输入。
// 算法标签：动态规划

#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n,m,d,s;
    scanf("%d %d %d %d",&n,&m,&d,&s);
    int a[m+1],b[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&a[i],&b[i]);
    }
    int dp[m+1][n+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=1e9;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=b[i];k++)
            {
                dp[i][j]=min(dp[i][j],dp[i-1][j-k]+k*a[i]+d);
            }
        }
    }
    if(dp[m][n]>=1e9)
        printf("impossible\n");
    else
        printf("%d\n",dp[m][n]);
    return 0;
}
