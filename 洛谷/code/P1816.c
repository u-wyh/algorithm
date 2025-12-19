#include<stdio.h>

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int nums[m+1],left[n+1],right[n+1];
    for(int i=1;i<=m;i++)
        scanf("%d",&nums[i]);
    int dp[m+1][m+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=m;i++)
        dp[i][i]=nums[i];
    for(int r=2;r<=n;r++)
    {
        for(int l=1;l<=r-1;l++)
        {
            dp[l][r]=min(dp[l][r-1],nums[r]);
        }
    }

    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&left[i],&right[i]);
        printf("%d ",dp[left[i]][right[i]]);
    }
    return 0;
}
