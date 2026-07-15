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
    int dp[r+2][c+2];
    for(int i=0;i<=r;i++)
    {
        for(int j=0;j<=c;j++)
        {
            dp[i][j]=0;
        }
    }
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {

        }
    }
    return 0;
}
