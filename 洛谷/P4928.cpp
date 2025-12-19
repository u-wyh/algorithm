#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;
const long long INF = 1e15;

int n,m;
int x[5];
int y[5];
int z[MAXN];
int power[5];
int cnt[5];
long long dp[MAXN][8*8*8*8];

int main()
{
    cin>>n>>m;
    power[0]=1;
    for(int i=1;i<=n;i++){
        power[i]=power[i-1]*7;
    }
    for(int i=0;i<n;i++){
        cin>>x[i];
    }
    for(int i=0;i<n;i++){
        cin>>y[i];
    }
    for(int i=1;i<=m;i++){
        cin>>z[i];
    }
    for(int i=0;i<=m;i++){
        for(int j=0;j<power[n];j++){
            dp[i][j]=-INF;
        }
    }
    dp[0][0]=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cnt[j]=0;
        }
        for(int j=0;j<power[n];j++){
            if(dp[i][j]==-INF){
                continue;
            }
            for(int k=0;k<n;k++){
                cnt[k]=(j/power[k])%7;
            }
            
            int num=0;
            for(int k=0;k<n;k++){
                num+=max(0,cnt[k]-1)*power[k];
            }

            for(int k=0;k<n;k++){
                if(!cnt[k]){
                    int v=num+(y[k]*power[k]);
                    dp[i+1][v]=max(dp[i+1][v],dp[i][j]+x[k]*z[i+1]);
                }
            }
        }
    }
    long long ans=-INF;
    for(int i=0;i<power[n];i++){
        ans=max(ans,dp[m][i]);
    }
    if(ans<=-INF){
        cout << "gcd loves her clothes!";
		return 0;
    }
    cout<<ans<<endl;
    return 0;
}