#include<stdio.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int v[m],p[m],q[m],cost[m],val[m],king[m],fans[m],follows[m][2];
    for(int i=0;i<m;i++)
    {
        fans[i]=0;
        scanf("%d %d %d",&v[i],&p[i],&q[i]);
        cost[i]=v[i];
        val[i]=v[i]*p[i];
        if(q[i]==0)
            king[i]=1;
        else
            king[i]=0;
    }
    for(int i=0;i<m;i++)
    {
        if(king[i]==0)
            follows[q[i]-1][fans[q[i]-1]++]=i+1;
    }
    long long dp[m+1][n+1];
    for(int i=0;i<=n;i++)
        dp[0][i]=0;
    int k = -1;
    for (int i = 1, fan1, fan2; i <= m; i++) {
        if (king[i-1]) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = dp[k+1][j];
                if (j - cost[i-1] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[k+1][j - cost[i-1]] + val[i-1]);
                }
                fan1 = fans[i-1] >= 1 ? follows[i-1][0] : -1;
                fan2 = fans[i-1] >= 2 ? follows[i-1][1] : -1;
                if (fan1 != -1 && j - cost[i-1] - cost[fan1-1] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[k+1][j - cost[i-1] - cost[fan1-1]] + val[i-1] + val[fan1-1]);
                }
                if (fan2 != -1 && j - cost[i-1] - cost[fan2-1] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[k+1][j - cost[i-1] - cost[fan2-1]] + val[i-1] + val[fan2-1]);
                }
                if (fan1 != -1 && fan2 != -1 && j - cost[i-1] - cost[fan1-1] - cost[fan2-1] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[k+1][j - cost[i-1] - cost[fan1-1] - cost[fan2-1]]
                                    + val[i-1] + val[fan1-1] + val[fan2-1]);
                }
            }
        k = i-1;
        }
    }
    printf("%lld\n",dp[m][n]);
    return 0;
}
