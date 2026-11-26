// https://www.luogu.com.cn/problem/P1510
// 题意：输入所需最小体积 v、木石数 n、剩余体力 c，及每块木石体积与耗力。
// 选若干木石，使其体积和 >= v 且耗力总和 <= c。
// 若能填平，输出最多能剩下的体力；否则输出 Impossible。
// 数据范围：
// 0 < n <= 10^4（木石数量）
// 所有读入的数均在 [0, 10^4] 内（v, n, c 及木石体积和耗力）
// 保证最终答案不超过 c
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int v,n,c;
    scanf("%d %d %d",&v,&n,&c);
    int val[n+1],cost[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&val[i],&cost[i]);
    }
    int dp[n+1][c+1];
    for(int i=0;i<=c;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=c;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=cost[i])
                dp[i][j]=max(dp[i][j],dp[i-1][j-cost[i]]+val[i]);
        }
    }
    for(int i=0;i<=c;i++)
    {
        if(dp[n][i]>=v)
        {
            printf("%d\n",c-i);
            return 0;
        }
    }
    printf("Impossible\n");
    return 0;
}
