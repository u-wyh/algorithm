#include<stdio.h>
#include<math.h>

double max(double a,double b)
{
    return a>b?a:b;
}

int check(int x, int y, int z) {
    if (x + y > z && x + z > y && y + z > x) return 1;
    return 0;
}

double work(int x,int y, int  z) {
    double p = (x + y + z) / 2.0;
    return sqrt(p * (p - x) * (p - y) * (p - z));
}

int main()
{
    int n;
    scanf("%d",&n);
    int nums[n+1];
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&nums[i]);
        sum+=nums[i];
    }
    int dp[n+1][sum/2+1][sum/2+1];
    for(int i=0;i<=sum/2;i++)
    {
        for(int j=0;j<=sum/2;j++)
        {
            dp[0][i][j]=0;
        }
    }
    dp[0][0][0]=1;
    for(int k=1;k<=n;k++)
    {
        for(int i=0;i<=sum/2;i++)
        {
            for(int j=0;j<=sum/2;j++)
            {
                dp[k][i][j]=dp[k-1][i][j];
                if (i - nums[k] >= 0 && dp[k-1][i - nums[k]][j]) dp[k][i][j] = 1;
                if (j - nums[k] >= 0 && dp[k-1][i][j - nums[k]]) dp[k][i][j] = 1;
            }
        }
    }
    double ans=-1;
    for(int i=0;i<=sum/2;i++)
    {
        for(int j=0;j<=sum/2;j++)
        {
            if(dp[n][i][j]&&check(i,j,sum-i-j))
            {
                ans=max(ans,work(i,j,sum-i-j));
                //printf("%lf\n",ans);
            }
        }
    }
    if (ans != -1.0) printf("%lld\n", (long long)(ans * 100));
    else printf("%.0f\n", ans);
    return 0;
}
