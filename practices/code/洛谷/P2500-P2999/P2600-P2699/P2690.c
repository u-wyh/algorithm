// https://www.luogu.com.cn/problem/P2690
// 题意：两棵树（1 和 2），共 T 分钟每分钟掉落一个苹果，初始在 1 号树下。
// 最多在两棵树间移动 W 次，求最多能接到的苹果数。
// 输出最多苹果数。
// 数据范围：1 <= T <= 1000，1 <= W <= 30。
// 难度评分：1300（洛谷分级换算）
// 算法标签：动态规划
#include<stdio.h>

int max(int a,int b){
    return a>b?a:b;
}

int dp[1010][31],T,w,a[1010],ans;
int main()
{
    scanf("%d %d",&T,&w);
    for(int i=1;i<=T;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=T;i++){
        for(int j=0;j<=T&&j<=w;j++){
            if(j==0)
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
            if(a[i]==j%2+1)
                dp[i][j]++;
        }
    }
    for(int i=0;i<=w;i++)
        ans=max(ans,dp[T][i]);
    printf("%d\n",ans);
    return 0;
}
