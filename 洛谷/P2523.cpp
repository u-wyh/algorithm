#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 305;

int comb[MAXN][MAXN];
int dp[MAXN][MAXN];
int sum[MAXN];

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n,m,mod;
        cin>>n>>m>>mod;
        comb[0][0]=1;
        for(int i=1;i<=n;i++){
            comb[i][0]=comb[i][i]=1;
            for(int j=1;j<i;j++){
                comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
            }
        }
        for(int i=1;i<=n+1;i++){
            sum[i]=1;//这里添加一个位置 用于判断
        }
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            sum[v]--;
        }
        for(int i=1;i<=n+1;i++){
            if(sum[i-1]<0){
                sum[i]+=sum[i-1];
                sum[i-1]=0;
            }
        }
        if(sum[n+1]<=0){
            cout<<"NO"<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){
            sum[i]+=sum[i-1];
            // cout<<sum[i]<<' ';
        }
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n-m;j++){
                dp[i][j]=0;
            }
        }
        dp[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=sum[i];j<=n-m;j++){
                for(int k=0;k<=j;k++){
                    dp[i][j]=(dp[i][j]+dp[i-1][k]*comb[n-m-k][j-k])%mod;
                }
            }
        }
        cout<<"YES "<<dp[n][n-m]<<endl;
    }
    return 0;
}