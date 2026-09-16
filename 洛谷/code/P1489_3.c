#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int cmp(const void* a,const void* b)
{
    return (*(int *)a-*(int *)b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int sum=0;
    int nums[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    qsort(nums+1,n,sizeof(int),cmp);
    int dp[n/2+2][sum/2+1];
    for(int i=0;i<=n/2+1;i++)
    {
        for(int j=0;j<=sum/2;j++)
        {
            dp[i][j]=0;
            if(j==0)
                dp[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n/2+1&&j<=i;j++)
        {
            for(int k=nums[i];k<=sum/2;k++)
            {
                dp[j][k]|=dp[j-1][k];
                dp[j][k]|=dp[j-1][k-nums[i]];
            }
        }
    }
    for(int i=sum/2;i>=0;i--)
    {
        if((dp[n/2+1][i]||dp[n/2+1][sum-i])&&(n%2==1))
        {
            printf("%d %d\n",i,sum-i);
            return 0;
        }
        else if(dp[n/2+1][i]||dp[n/2][sum-i])
        {
            printf("%d %d\n",i,sum-i);
            return 0;
        }
    }
    return 0;
}

