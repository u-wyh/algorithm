#include<stdio.h>
#include<math.h>

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    int dp[n+1][sum+1];
    for(int i=0;i<=sum+1;i++)
        for(int j=0;j<=n;j++)
            dp[j][i]=0;
    for(int i=1;i<=n;i++){
		for(int j=sum;j>=0;j--){
            if(j==nums[i]) dp[i][j]=1;
            else if(dp[i-1][j]) dp[i][j]=1;
			else if(dp[i-1][j+nums[i]]) dp[i][j]=1;
            else if(dp[i-1][abs(j-nums[i])]) dp[i][j]=1;
        }
	}
    int count =0;
    for(int i=1;i<=sum;i++)
    {
        count+=dp[n][i];
    }
    printf("%d\n",count);
    return 0;
}
