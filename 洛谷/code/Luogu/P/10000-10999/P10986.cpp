#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e5+5;

int n,m;

int p[MAXN];
int fac[MAXN];
int inv[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void prepare(int n){
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=(p[i-1]*10)%MOD;
    }
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
    cin>>n>>m;
    prepare(n);
    int ans=0;
    for(int i=m;i<=n/4;i++){
        int res=comb(i,m)*comb(n-3*i,i)%MOD*p[n-4*i]%MOD;
        if((i-m)%2){
            res=MOD-res;
        }
        ans=(ans+res)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}