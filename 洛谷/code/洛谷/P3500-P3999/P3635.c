// https://www.luogu.com.cn/problem/P3635
// 题意：输入广场列数 W、行数 H、忍者数 N，
// 以及每位忍者的位置 (X_i, Y_i) 和朝向
// D_i（0 右、1 上、2 左、3 下）。
// 时刻 0 所有忍者同时向朝向方向以单位速度直线发射苦无，
// 若某时刻同一位置有超过 1 支苦无则它们立即碰撞并全部消失。
// 输出经过足够长时间后，W*H 广场中被苦无经过过的格子总数（含忍者所在格）。
// 数据范围：1 <= N <= 10^5，1 <= W, H <= 10^9，
// 1 <= X_i <= W，1 <= Y_i <= H，忍者位置互异。
// 算法标签：动态规划
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
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        dp[i]=dp[i-1]+1;
        if(i>=5)
            dp[i]=min(dp[i],dp[i-5]+1);
        if(i>=11)
            dp[i]=min(dp[i],dp[i-11]+1);

    }
    printf("%d\n",dp[n]);
    return 0;
}
