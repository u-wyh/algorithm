#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int nums[n+1][m+1];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&nums[i][j]);
        }
    }
    int dp[m+1][m+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;i+j<=m;j++)
        {
            dp[i][j]=nums[1][i]+nums[2][j]+nums[3][m-i-j];
        }
    }
    int a,b,max=0;
    for(int i=0;i<=m;i++)
    {
        for(int j=0;i+j<=m;j++)
        {
            if(dp[i][j]>max)
            {
                max=dp[i][j];
                a=i;
                b=j;
            }
        }
    }
    printf("%d\n1 %d\n2 %d\n3 %d",max,a,b,m-a-b);
    return 0;
}
