#include<stdio.h>
#include<math.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    scanf("\n");
    char str[n];
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%c",&str[i]);
        if(str[i]=='r')
            nums[i]=1;
        else if(str[i]=='w')
            nums[i]=2;
        else
            nums[i]=3;
        printf("%d",nums[i]);
    }
    printf("\n");
    int dp[n][2];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<2;j++)
        {
            dp[i][j]=1;
        }
    }
    for(int i=0;i<n;i++)
    {
        if(abs(nums[i]-nums[i-1])<=1)
            dp[i][0]=dp[(i-1+n)%n][0]+1;
        if(abs(nums[i]-nums[i+1])<=1)
            dp[i][1]=dp[(i+1)==n?0:(i+1)][1]+1;
    }
    int ans=dp[n-1][0]+dp[0][1];
    for(int i=0;i<n-1;i++)
        ans=max(ans,dp[i][0]+dp[i+1][1]);
    printf("%d\n",ans);
    return 0;
}
