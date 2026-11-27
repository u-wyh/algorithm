// https://www.luogu.com.cn/problem/P1060
// 题意：有预算 n 和 m 件可选物品。每件物品的得分是价格 v 乘重要度 p。每件最多买一次，求总价不超过预算时的最大总得分。
// 数据范围：1 ≤ n < 30000，1 ≤ m < 25，0 ≤ v ≤ 10000，1 ≤ p ≤ 5，答案小于 10^8。
// 算法标签：背包动态规划

#include<stdio.h>
#define N 25
#define M 30000

int dp[N][M];

int max(int a,int b)
{
    return a>b?a:b;
}

int f1(int i,int *val,int *v,int m,int n)
{
    int ans;
    if(i>=n)
        return 0;
    ans=f1(i+1,val,v,m,n);
    if(v[i]<=m)
        ans=max(ans,f1(i+1,val,v,m-v[i],n)+val[i]);
    return ans;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int v[n],p[n],val[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&v[i],&p[i]);
        val[i]=v[i]*p[i];
    }
    //printf("%d\n",f1(0,val,v,m,n));
    for(int i=0;i<=m;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=v[i-1])
                dp[i][j]=max(dp[i][j],dp[i-1][j-v[i-1]]+val[i-1]);
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
