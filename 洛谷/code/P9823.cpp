#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 1e7+5;


int n,k;
int fac[MAXN];
int inv[MAXN];

int f[MAXN];
int g[MAXN];

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

signed main()
{
    cin>>n>>k;
    prepare(n);
    if(n<=k){
        cout<<fac[n]<<endl;
        return 0;
    }
    for(int i=1;i<=k;i++){
        f[i]=fac[i];
    }
    f[0]=g[0]=1;
    for(int i=1;i<=n;i++){
        f[i]=g[i-1];
        if(i-1-k>=0){
            f[i]=(f[i]-g[i-k-1]+MOD)%MOD;
        }
        f[i]=(f[i]*fac[i-1])%MOD;
        g[i]=(g[i-1]+f[i]*inv[i]%MOD)%MOD;
    }
    cout<<f[n]<<endl;
    return 0;
}