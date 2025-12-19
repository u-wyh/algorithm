#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 3e6+5;

int fac[MAXN];
int inv[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(a*ans)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

void prepare(int n){
    inv[0]=1;
    fac[0]=1;
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
    int n,m,q,k,a,b;
    cin>>n>>m>>q>>k>>a>>b;
    if(q<m){
        cout<<0<<endl;
        return 0;
    }
    prepare(m);
    int ans=0;
    int v=1;
    for(int i=0;i<=m;i++){
        ans=((ans+v*comb(m,i)*power(n-i,q))%MOD+MOD)%MOD;
        v*=-1;
    }
    ans=(ans*power(k,q-m))%MOD;
    ans=(ans*(n-m+1))%MOD;
    cout<<ans<<endl;
    return 0;
}