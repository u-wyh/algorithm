#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5005;

int n;
long double dp[MAXN];
long double sum[MAXN];
int val[MAXN];

signed main()
{
    cin>>n;
    for(int i=0;i<=n;i++){
        cin>>val[i];
    }
    dp[n]=0;
    for(int i=n-1;i>=0;i--){
        dp[i]=LLONG_MAX;
        for(int j=i+1;j<=n;j++){
            dp[i]=min(dp[i],(sum[i+1]-sum[j+1])/(j-i)+1.0*(j-i+1)/(j-i)*val[j]);
        }
        sum[i]=sum[i+1]+dp[i];
    }
    printf("%.10Lf\n",dp[0]);
    return 0;
}