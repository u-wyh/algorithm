// https://www.luogu.com.cn/problem/P2049
// 题意：棋子初值为 1，从左上角走到右下角，每步只能向右或向下，
// 经过每格都乘上该格的数。
// 求最终乘积对 K 取模可能得到的所有余数，先输出个数，再升序输出余数。
// 数据范围：1 ≤ M,N,K ≤ 100，棋盘有 M 行 N 列。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划

#include<stdio.h>
#define Max 105

int dp[Max][Max][Max];

int main()
{
    int m,n,k;
    scanf("%d %d %d",&m,&n,&k);
    int nums[m+1][n+1];
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
            nums[i][j]%=k;
        }
    }
    dp[1][1][nums[1][1]]=1;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int h=0;h<k;h++)
            {
                if(dp[i-1][j][h]==1)
                    dp[i][j][(h*nums[i][j])%k]=1;
                if(dp[i][j-1][h]==1)
                    dp[i][j][(h*nums[i][j])%k]=1;
            }
        }
    }
    int num[k+1];
    int cnt=0;
    for(int i=0;i<=k;i++)
    {
        if(dp[m][n][i]==1)
            num[cnt++]=i;
    }
    printf("%d\n",cnt);
    for(int i=0;i<cnt;i++)
        printf("%d ",num[i]);
    return 0;
}
