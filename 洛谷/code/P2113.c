// https://www.luogu.com.cn/problem/P2113
// 题意：有 n 支球队和 m 场比赛，每支球队有实力值 a_i 和帅哥数 b_i。
// 每场比赛由 p_i 对阵 q_i，小明精彩度为 a_{p_i}*a_{q_i}，小红精彩度为 b_{p_i}+b_{q_i}。
// 最多看 k 场比赛，在小红精彩度总和不小于 c 的前提下，求小明精彩度总和的最大值。
// 若无法满足小红的要求，输出 -1。
// 数据范围：1 <= n <= 100，1 <= k <= m <= 100，1 <= a_i, b_i <= 10，1 <= c <= 10^3。
#include<stdio.h>
#include<limits.h>
// 算法标签：动态规划、0-1背包

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,k,c;
    scanf("%d %d %d %d",&n,&m,&k,&c);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
    }
    int p[m+1],q[m+1],A[m+1],B[m+1];
    int sum=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&p[i],&q[i]);
        A[i]=a[p[i]]*a[q[i]];
        B[i]=b[p[i]]+b[q[i]];
        sum+=B[i];
    }
    int dp[m+1][sum+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=INT_MIN;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=i;j>=1;j--)
        {
            for(int k=sum;k>=B[i];k--)
            {
                dp[j][k]=max(dp[j][k],dp[j-1][k-B[i]]+A[i]);
            }
        }
    }
    int ans=-1;
    for(int i=c;i<=sum;i++)
    {
        ans=max(ans,dp[k][i]);
    }
    printf("%d\n",ans);
    return 0;
}
