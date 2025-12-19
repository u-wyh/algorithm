#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10;
const int MAXM = 100;
const int INF = 1e9;

int n;
int a[MAXN];
int b[MAXN];
int dp[MAXN][MAXM];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int all=0;
    for(int i=1;i<=n;i++){
        all+=a[i];
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<=all;j++){
            dp[i][j]=INF;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=all;j++){
            if(dp[i-1][j]!=INF){
                dp[i][j]=min(dp[i][j],dp[i-1][j]+b[i]);
            }
            if(j>=a[i]&&dp[i-1][j-a[i]]!=INF){
                dp[i][j]=min(dp[i][j],dp[i-1][j-a[i]]);
            }
        }
    }
    int ans=INF;
    for(int i=0;i<=all;i++){
        if(dp[n][i]!=INF){
            ans=min(ans,max(i,dp[n][i]));
        }
    }
    cout<<ans<<endl;
    return 0;
}
/*
6
2 5 7 10 5 2
3 8 4 11 3 4
*/