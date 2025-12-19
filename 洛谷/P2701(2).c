#include<stdio.h>
#include<limits.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,t;
    scanf("%d %d",&n,&t);
    int nums[n+1][n+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            nums[i][j]=1;
        }
    }
    int x,y;
    for(int i=0;i<t;i++)
    {
        scanf("%d %d",&x,&y);
        nums[x][y]=0;
    }
    int dp[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(i==0||j==0)
                dp[i][j]=0;
            else
                dp[i][j]=nums[i][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(nums[i][j])
                dp[i][j]=min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1])+1;
        }
    }
    int ans=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			ans=max(ans,dp[i][j]);	//ans记录最大值
	printf("%d\n",ans);
    return 0;
}
