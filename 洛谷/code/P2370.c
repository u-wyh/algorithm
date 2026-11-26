// https://www.luogu.com.cn/problem/P2370
// 题意：有 n 个文件（大小 W_i，价值 V_i），U 盘容量为 S。
// 只能装入大小不超过 L 的文件，求总价值 >= p 且总大小 <= S 时的最小 L。
// 若无解输出 No Solution!。
// 数据范围：1 <= n, W_i, S <= 10^3，1 <= V_i <= 10^6，1 <= p <= 10^9。
#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int cost[n+1],val[n+1];
    for(int i=1;i<=n;i++)
        scanf("%d %d",&cost[i],&val[i]);

    return 0;
}
