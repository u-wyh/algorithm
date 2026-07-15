#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int mod;

bool isprime[MAXN];
int prime[MAXN];

int fac[MAXN];
int phi[MAXN];

void prepare(int n){
    int cnt=0;
    isprime[0]=isprime[1]=1;
    for(int i=2;i<=n;i++){
        if(isprime[i]==0){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            isprime[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break;
            }
        }
    }
    fac[0]=phi[0]=1;
    for(int i=1;i<=n;i++){
        int tmp=i;
        while(tmp%mod==0){
            tmp/=mod;
        }
        fac[i]=fac[i-1]*i%mod;
        tmp=i-1+isprime[i];
        while(tmp%mod==0){
            tmp/=mod;
        }
        phi[i]=phi[i-1]*tmp%mod;
    }
}

int power(int a,int b){
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

signed main()
{
    int T;
    cin>>T>>mod;
    prepare(10000000);
    while(T--){
        int n,m;
        cin>>n>>m;
        int ans=fac[n]*phi[m]%mod*power(fac[m],mod-2)%mod;
        // cout<<ans<<' ';
        if(n/mod>m/mod){
            ans=0;
        }
        cout<<ans<<endl;
    }
    return 0;
}