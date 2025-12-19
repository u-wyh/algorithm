#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[4][n+1];
    int sum[4][n+1];
    sum[1][0]=0;
    sum[2][0]=0;
    sum[3][0]=0;
    for(int i=1;i<4;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&nums[i][j]);
            sum[i][j]=sum[i][j-1]+nums[i][j];
            printf("%3d",sum[i][j]);
        }
        printf("\n");
    }
    int ans=INT_MAX;
    for(int i=2;i<=n-2;i++)
    {
        for(int j=i;j<=n-1;j++)
        {
            ans=min(ans,sum[1][i-1]+sum[2][j]-sum[2][i-1]+sum[3][n]-sum[3][j]);
            ans=min(ans,sum[1][i-1]+sum[3][j]-sum[3][i-1]+sum[2][n]-sum[2][j]);
            ans=min(ans,sum[2][i-1]+sum[3][j]-sum[3][i-1]+sum[1][n]-sum[1][j]);
            ans=min(ans,sum[2][i-1]+sum[1][j]-sum[1][i-1]+sum[3][n]-sum[3][j]);
            ans=min(ans,sum[3][i-1]+sum[2][j]-sum[2][i-1]+sum[1][n]-sum[1][j]);
            ans=min(ans,sum[3][i-1]+sum[1][j]-sum[1][i-1]+sum[2][n]-sum[2][j]);
        }
    }
    printf("%d",ans);
    return 0;
}
