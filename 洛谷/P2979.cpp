#include<bits/stdc++.h>
using namespace std;

int n,m,K;
int dp[1005];
int cost[105],val[105];

int main()
{
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        cin>>val[i]>>cost[i];
    }
    for(int i=1;i<=n;i++){
        if(cost[i]>=K){
            continue;
        }
        for (int j = cost[i]; j <= m; j++) {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    int ans=0;
    ans=max(ans,dp[m]);
    for(int u=1;u<=n;u++){
        if(cost[u]>=K&&cost[u]<=m){
            for(int i=1;i<=m;i++){
                dp[i]=0;
            }
            for(int i=1;i<=n;i++){
                for (int j = cost[i]*4/5; j <= m-cost[u]; j++) {
                    dp[j] = max(dp[j], dp[j - cost[i]*4/5] + val[i]);
                }
            }
            ans=max(ans,dp[m-cost[u]]+val[u]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
