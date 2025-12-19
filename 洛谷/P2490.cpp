#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 2e4+5;
const int MAXM = 1e4+5;
const int LEN = 15;

int n,k,d,m,all;
int fac[MAXN];
int inv[MAXN];
int dp[LEN+1][MAXM];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void prepare(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    inv[n]=power(fac[n],MOD-2);
    for(int i=n-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

int comb(int a,int b){
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main()
{
    cin>>n>>k>>d;
    m=k/2;
    all=n-k;
    prepare(n+m);
    dp[0][0]=1;
    for(int i=0;i<LEN;i++){
        for(int j=0;j<=all;j++){
            if(dp[i][j]==0){
                continue;
            }
            for(int c=0;c<=m;c+=(d+1)){
                int ways=(dp[i][j]*comb(m,c))%MOD;
                int val=c*(1<<i);
                if(val+j<=all){
                    dp[i+1][j+val]=(dp[i+1][j+val]+ways)%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int j=0;j<=all;j++){
        int res=all-j;
        ans=(ans+dp[LEN][j]*comb(res+m,m)%MOD)%MOD;
    }
    ans=((comb(n,k)-ans)%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}