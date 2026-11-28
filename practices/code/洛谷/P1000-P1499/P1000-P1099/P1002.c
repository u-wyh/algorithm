// https://www.luogu.com.cn/problem/P1002
// 题意：卒从 (0, 0) 出发，每步只能向下或向右，目标是 (n, m)。
// 给出一匹位置固定的马。卒要避开马所在的格子和马一步能跳到的格子。
// 输出到达目标的走法数，保证起点安全。
// 数据范围：1 ≤ n, m ≤ 20，马的两个坐标均在 [0, 20]。
// 难度评分：1100（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>
#include<math.h>
#define Max 21

long long dp[Max][Max];
/*
long long f1(int i,int j,int n,int m,int a,int b)
{
    if(((i==a)&&(j==b))     ||((i==a-1)&&(j==b+2))|| ((i==a-1)&&(j==b-2))||
       ((i==a+1)&&(j==b+2)) ||((i==a+1)&&(j==b-2))|| ((i==a+2)&&(j==b+1))||
       ((i==a+2)&&(j==b-1)) ||((i==a-2)&&(j==b+1))|| ((i==a-2)&&(j==b-1)))
        return 0;
    if(i==n&&j==m)
        return 1;
    if(i==n)
        return f1(i,j+1,n,m,a,b);
    if(j==m)
        return f1(i+1,j,n,m,a,b);
    return f1(i,j+1,n,m,a,b)+f1(i+1,j,n,m,a,b);
}
*/
int main()
{
    int n,m,a,b;
    scanf("%d %d %d %d",&n,&m,&a,&b);
    //printf("%lld\n",f1(0,0,n,m,a,b));
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=-1;
        }
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(i==0||j==0)
                dp[i][j]=1;
            if(((i==a)&&(j==b))     ||((i==a-1)&&(j==b+2))|| ((i==a-1)&&(j==b-2))||
               ((i==a+1)&&(j==b+2)) ||((i==a+1)&&(j==b-2))|| ((i==a+2)&&(j==b+1))||
               ((i==a+2)&&(j==b-1)) ||((i==a-2)&&(j==b+1))|| ((i==a-2)&&(j==b-1)))
                dp[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(dp[i][j]==-1)
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    printf("%lld\n",dp[n][m]);
    return 0;
}
