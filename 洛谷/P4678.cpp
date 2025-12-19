#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 124755;

int n,m;
int dp[501][MAXN];
int limit[501];
int fac[501];
int c[501][501];

signed main()
{
    fac[0]=1;
    for(int i=1;i<=500;i++){
        fac[i]=(1ll*fac[i-1]*i)%MOD;
    }
    for(int i=1;i<=500;i++){
        limit[i]=(i*(i+1))/2;
    }
    limit[500]=124750;
    for(int i=1;i<=500;i++){
        dp[i][0]=1;
        for(int j=1;j<=limit[i-1];j++){
            if(j>=i){
                dp[i][j]=dp[i-1][j]-dp[i-1][j-i];
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
            dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
        }
        for(int j=limit[i-1]+1;j<=limit[i];j++){
            dp[i][j]=dp[i][j-1];
        }
    }
    for(int i=0;i<=500;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
        }
    }

    for(int i=0;i<=500;i++){
        for(int j=0;j<=i;j++){
            c[i][j]=(c[i][j]*c[i][j])%MOD;
        }
    }
    for(int i=0;i<=500;i++){
        fac[i]=(fac[i]*fac[i])%MOD;
    }
    // for(int i=0;i<=5;i++){
    //     for(int j=0;j<=i;j++){
    //         cout<<c[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    // for(int i=1;i<=5;i++){
    //     cout<<i<<' '<<limit[i]<<": ";
    //     for(int j=0;j<=limit[i-1];j++){
    //         cout<<dp[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    int T;
    cin>>T;
    while(T--){
        scanf("%lld %lld",&n,&m);
        int ans=0;
        int tmp=0;
        for(int i=1;i<=n;i++){
            if(m>=limit[i]){
                tmp=dp[i][limit[i]];
            }
            else{
                tmp=dp[i][m];
            }
            ans=(ans+1ll*(n-i+1)*tmp%MOD*fac[n-i]%MOD*c[n][i])%MOD;
        }
        ans=(ans+MOD)%MOD;
        printf("%lld\n",ans);
    }
    return 0;
}