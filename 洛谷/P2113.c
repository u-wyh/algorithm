#include<stdio.h>
#include<limits.h>

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    int n,m,k,c;
    scanf("%d %d %d %d",&n,&m,&k,&c);
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
    }
    int p[m+1],q[m+1],A[m+1],B[m+1];
    int sum=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&p[i],&q[i]);
        A[i]=a[p[i]]*a[q[i]];
        B[i]=b[p[i]]+b[q[i]];
        sum+=B[i];
    }
    int dp[m+1][sum+1];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=sum;j++)
        {
            dp[i][j]=INT_MIN;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=m;i++)
    {
        for(int j=i;j>=1;j--)
        {
            for(int k=sum;k>=B[i];k--)
            {
                dp[j][k]=max(dp[j][k],dp[j-1][k-B[i]]+A[i]);
            }
        }
    }
    int ans=-1;
    for(int i=c;i<=sum;i++)
    {
        ans=max(ans,dp[k][i]);
    }
    printf("%d\n",ans);
    return 0;
}
