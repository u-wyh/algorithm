// https://www.luogu.com.cn/problem/P6240
// 题意：n 个商店排成一列，第 i 个商店出售热量为 h_i、美味度为 w_i 的小吃（每个商店最多吃一次）。
// m 次询问在区间 [l_i, r_i] 内选取总热量不超过 t_i 的最大美味度和。
// 数据范围：1 <= n <= 4*10^4，1 <= m <= 2*10^5，1 <= l_i <= r_i <= n
// 1 <= h_i, t_i <= 200，1 <= w_i <= 10^7。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&cost[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }

    int left[m+1],right[m+1],heat[m+1],count[m+1];

    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d",&left[i],&right[i],&heat[i]);
        count[i]=right[i]-left[i]+1;
        long long dp[heat[i]+1];
        for(int k=0;k<=heat[i];k++)
        {
            dp[k]=0;
        }
        for(int k=1;k<=count[i];k++)
        {
            for(int l=heat[i];l>=0;l--)
            {
                if(l>=cost[left[i]+k-1])
                    dp[l]=max(dp[l],dp[l-cost[left[i]+k-1]]+val[left[i]+k-1]);
            }
        }
        printf("%lld\n",dp[heat[i]]);
    }
    return 0;
}
