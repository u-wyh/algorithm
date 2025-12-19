#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 2e6+5;

int n,m;
int logg[MAXN],p[30];
int l[MAXN],r[MAXN];
int f[MAXN];

int fac[MAXN],inv[MAXN];

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

void build(){
    int k=min(n,m-1);
    fac[0]=inv[0]=1;
    for(int i=1;i<=k;i++){
        fac[i]=(fac[i-1]*i)%m;
    }
    inv[k]=power(fac[k],m-2,m);
    for(int i=k-1;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%m;
    }
}

int comb(int n,int m,int mod){
    if(n<m){
        return 0;
    }
    return ((fac[n]*inv[m]%mod*inv[n-m]%mod)+mod)%mod;
}

int lucas(int n,int m,int mod){
    if(m==0){
        return 1;
    }
    else{
        return lucas(n/mod,m/mod,mod)%mod*comb(n%mod,m%mod,mod)%mod;
    }
}

signed main()
{
    cin>>n>>m;
    build();
    logg[0]=-1;
    for(int i=1;i<=n;i++){
        logg[i]=logg[i>>1]+1;
    }
    p[0]=1;
    for(int i=1;i<=logg[n];i++){
        p[i]=(p[i-1]*2);
    }
    l[1]=r[1]=0;
    f[1]=f[2]=1;
    for(int i=2;i<=n;i++){
        l[i]=r[i]=p[logg[i]-1]-1;
        l[i]+=min(i-p[logg[i]]+1,p[logg[i]-1]);
        r[i]+=max(0ll,i-p[logg[i]]+1-p[logg[i]-1]);
        // cout<<i<<": "<<l[i]<<' '<<r[i]<<endl;
    }
    for(int i=3;i<=n;i++){
        f[i]=lucas(i-1,l[i],m)%m*f[l[i]]%m*f[r[i]]%m;
    }
    cout<<f[n]<<endl;
    return 0;
}