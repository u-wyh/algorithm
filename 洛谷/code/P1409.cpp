#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m;
double p[MAXN];
double dp[MAXN][MAXN];

int main()
{
    cin>>n>>m;
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*0.5;
    }
    dp[1][1]=1;
    for(int i=2;i<=n;i++){
        double sum=0;
        for(int j=1;j<i;j++){
            sum+=p[i-j]*dp[i-1][j];
        }
        sum/=3;
        sum=sum+1.0/6;
        dp[i][1]=sum/(1-p[i]);
        for(int j=2;j<=i;j++){
            dp[i][j]=0.5*dp[i][j-1]+1.0/3*dp[i-1][j-1];
        }
    }
    printf("%.9lf",dp[n][m]);
    return 0;
}