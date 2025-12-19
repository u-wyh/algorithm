#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e6+5;

int mod,n,inv;

int cnt;
int prime[MAXN];
bool vis[MAXN];

int phi[MAXN];
map<int,int>mp;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}

void prepare(int n){
    inv=power(6,mod-2);
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i]%mod;
                break;
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i]%mod;
            }
        }
    }
    for(int i=1;i<=n;i++){
        phi[i]=(phi[i]*(1ll*i*i%mod)%mod+phi[i-1])%mod;
    }
}

int s3(int n){
    n%=mod;
    return ((n*(n+1)/2)%mod)*(n*(n+1)/2%mod)%mod;
}

int s2(int n){
    n%=mod;
    return ((n*(n+1)%mod)*((2*n+1)*inv%mod))%mod;
}

// // 计算立方和：∑i³ = [n(n+1)/2]²
// int s3(int n) {
//     n %= mod;
//     int t = n * (n + 1) / 2 % mod;
//     return t * t % mod;
// }

// // 计算平方和：∑i² = n(n+1)(2n+1)/6
// int s2(int n) {
//     n %= mod;
//     return n * (n + 1) % mod * (2 * n + 1) % mod * inv % mod;
// }

int sn(int n){
    if(n<MAXN){
        return phi[n];
    }
    if(mp[n]){
        return mp[n];
    }
    int ans=s3(n);
    for(int l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        ans=(ans-((s2(r)-s2(l-1)+mod)%mod)*sn(n/l)%mod+mod)%mod;
    }
    mp[n]=ans;
    return ans;
}

int compute(){
    int ans=0;
    for(int l=1,r;l<=n;l=r+1){
        r=(n/(n/l));
        ans=(ans+((sn(r)-sn(l-1)+mod)%mod)*s3(n/l)%mod)%mod;
    }
    return ans;
}

signed main()
{
    cin>>mod>>n;
    prepare(min(n,MAXN-1));
    cout<<compute()<<endl;
    return 0;
}