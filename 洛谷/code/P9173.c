#include <stdio.h>
#include <string.h>
int dp[2][5005][5005];
int min(int a,int b)
{
    return a<b?a:b;
}
int main()
{
    int n,m;
    scanf("%d",&n);
    int a[5005]={0},b[5005]={0};
    int i,j;
    for (i=1;i<=n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    for (i=1;i<=m;i++)
        scanf("%d",&b[i]);
    int inf = (n + m) * 5000;
    int add;
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= m; j++)
        {
            if (i==0 && j==0) continue;
            dp[0][i][j]=inf;
            if (i!=0)
            {
                add=1;
                if (a[i]==a[i-1]) add++;
                dp[0][i][j]=min(dp[0][i][j],dp[0][i-1][j]+add);
                add=1;
                if (a[i]==b[j]) add++;
                dp[0][i][j]=min(dp[0][i][j],dp[1][i-1][j]+add);
            }
            dp[1][i][j]=inf;
            if (j!=0)
            {
                add=1;
                if (b[j]==b[j-1]) add++;
                dp[1][i][j]=min(dp[1][i][j],dp[1][i][j-1]+add);
                add=1;
                if (b[j]==a[i]) add++;
                dp[1][i][j]=min(dp[1][i][j],dp[0][i][j-1]+add);
            }
        }
    }
    printf("%d\n",min(dp[0][n][m], dp[1][n][m]));
}
