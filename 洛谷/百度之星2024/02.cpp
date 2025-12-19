#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 998244353;
const int MAXN = 1e7+5;

int n;
int inv[MAXN];

bool vis[MAXN];
int prime[MAXN];
int cnt;

void euler(int n){
    for(int  i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[prime[j]*i]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

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

signed main()
{
    scanf("%lld",&n);
    euler(n);
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(MOD-inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
    }
    int lcm=1;
    for(int i=1;i<=cnt;i++){
        lcm=(lcm*power(prime[i],log(n)/log(prime[i])))%MOD;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+lcm*inv[i]%MOD*(n-2*i+1)%MOD)%MOD;
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}