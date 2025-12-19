#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int r,c;
    scanf("%d %d",&r,&c);
    int nums[r+1][c+1];
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int dp[r+2][c+1];
    for(int i=0;i<=r+1;i++)
    {
        for(int j=0;j<=c;j++)
        {
            if(i==0||j==0||i==r+1||j<i)
                dp[i][j]=0;
        }
    }
    dp[1][1]=nums[1][1];
    for(int j=2;j<=c;j++)
    {
        for(int i=1;i<=r&&i<=j;i++)
        {
            dp[i][j]=max(max(dp[i-1][j-1],dp[i][j-1]),dp[i+1][j-1])+nums[i][j];
        }
    }
    /*for(int i=0;i<=r+1;i++)
    {
        for(int j=0;j<=c;j++)
        {
            printf("%5d",dp[i][j]);
        }
        printf("\n");
    }*/
    printf("%d\n",dp[r][c]);
    return 0;
}
