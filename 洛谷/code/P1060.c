#include<stdio.h>
#define N 25
#define M 30000

int dp[N][M];

int max(int a,int b)
{
    return a>b?a:b;
}

int f1(int i,int *val,int *v,int m,int n)
{
    int ans;
    if(i>=n)
        return 0;
    ans=f1(i+1,val,v,m,n);
    if(v[i]<=m)
        ans=max(ans,f1(i+1,val,v,m-v[i],n)+val[i]);
    return ans;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    int v[n],p[n],val[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d %d",&v[i],&p[i]);
        val[i]=v[i]*p[i];
    }
    //printf("%d\n",f1(0,val,v,m,n));
    for(int i=0;i<=m;i++)
    {
        dp[0][i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(j>=v[i-1])
                dp[i][j]=max(dp[i][j],dp[i-1][j-v[i-1]]+val[i-1]);
        }
    }
    printf("%d\n",dp[n][m]);
    return 0;
}
