#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 998244353;
const int MAXN = 5e5+5;

int n,k;
int fac[MAXN];
int inv[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(int n){
    fac[0]=1;
    inv[0]=1;
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
    cin>>n>>k;
    prepare(n);
    int ans=0;
    for(int i=1;i<=n-k;i++){
        ans=(ans+(comb(n-i,k-1)*fac[n-k]%MOD*fac[k-1]%MOD*(n-k))%MOD+(comb(n-i,k)*fac[n-k-1]%MOD*fac[k]%MOD*(n-k)%MOD)-(comb(n-i,k-1)*fac[n-k-1]%MOD*fac[k-1]%MOD*(n-k)%MOD*(i-1)%MOD)+MOD)%MOD;
    }
    ans=((ans+fac[n])%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}