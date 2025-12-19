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
