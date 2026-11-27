#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXM = 20005;
const int MOD = 1e9+7;

int n,maxx;
int a[MAXN];
int b[MAXN];
int cnt[MAXN];
long long fac[MAXN];

long long dp[MAXN][MAXM];

void compute(){
    dp[0][0]=1;
    maxx=0;
    for(int i=1;i<=n;i++){
        maxx+=b[i];
        for(int j=i;j>=1;j--){
            for(int k=maxx;k>=b[i];k--){
                dp[j][k]=(dp[j][k]+dp[j-1][k-b[i]])%MOD;
            }
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    long long ans=0;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }

    compute();
    for(int i=1;i<=n;i++){
        if(a[i]<=maxx&&a[i]>=1){
            cnt[a[i]]++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=maxx;j++){
            dp[i][j]=(dp[i][j]*cnt[j])%MOD;
        }
    }
    for(int i=1;i<=n;i++){
        int all=0;
        for(int j=1;j<=maxx;j++){
            all=(all+dp[i][j])%MOD;
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=maxx;j++){
    //         ans=(ans+((fac[i]*(dp[i][j]*cnt[j])%MOD)%MOD))%MOD;
    //     }
    // }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         for(int k=b[i];k<=maxx;k++){
    //             ans=(ans-((fac[j]*dp[j-1][k-b[i]])))%MOD;
    //         }
    //     }
    // }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=maxx;j++){
    //         cout<<dp[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }

    // for(int i=1;i<=n;i++){
    //     if(a[i]<=maxx&&a[i]>=1){
    //         cnt[a[i]]--;
    //     }
    // }
    // for(int i=1;i<=n;i++){
    //     a[i]-=b[i];
    // }
    // for(int i=1;i<=n;i++){
    //     if(a[i]<=maxx&&a[i]>=1){
    //         cnt[a[i]]++;
    //     }
    // }
    // long long res=0;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=maxx;j++){
    //         res=(res+((fac[i+1]*(dp[i][j]*cnt[j])%MOD)%MOD))%MOD;
    //     }
    // }

    // cout<<ans<<' '<<res<<endl;
    // ans=(ans-res+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}
/*
3
1 2 3
2 1 1
*/