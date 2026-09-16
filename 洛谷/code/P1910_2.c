#include<stdio.h>
#define N 101
#define M 1001
#define X 1001

int dp[N][M][X];

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,x;
    scanf("%d %d %d",&n,&m,&x);
    /*int a[n+1],b[n+1],c[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
    }*/
    int a,b,c;
    int dp[m+1][x+1];

    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=x;j++)
        {
            dp[i][j]=0;
        }
    }

    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d",&a,&b,&c);
        for(int j=m;j>=b;j--)
        {
            for(int k=x;k>=c;k--)
            {
                dp[j][k]=max(dp[j][k],dp[j-b][k-c]+a);
            }
        }
    }
    printf("%d\n",dp[m][x]);
    return 0;
}
