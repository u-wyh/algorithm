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
