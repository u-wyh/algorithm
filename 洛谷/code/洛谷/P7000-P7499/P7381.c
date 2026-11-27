// https://www.luogu.com.cn/problem/P7381
// 题意：N 支球队每队 M 张照片，第 i 队已有 P_i 张；
// 当某队集齐 x 张时得 B_x 分（B 单调不降）。
// 最多再获得 K 张照片（不超过总缺口），求最大总得分。
// 数据范围：1 <= N, M <= 500，
// 1 <= K <= min(N*M, 500)，0 <= P_i <= M，
// 0 <= B_i <= 10^5。
// 算法标签：背包动态规划
#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int nums[n+1];
    int score[m+1];
    for(int i=1;i<=n;i++)
        scanf("%d",&nums[i]);
    for(int i=0;i<=m;i++)
        scanf("%d",&score[i]);
    int dp[n+1][k+1];
    for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			dp[i][j]=INT_MIN;
		}
	}
	dp[0][0]=0;
    for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			for(int kk=0;kk<=j;kk++){
				dp[i][j]=max(dp[i-1][kk]+score[nums[i]+j-kk],dp[i][j]);
			}
		}
	}
	printf("%d\n",dp[n][k]);
    return 0;
}
