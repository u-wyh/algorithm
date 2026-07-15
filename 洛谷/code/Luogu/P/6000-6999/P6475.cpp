#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXN = 6e5+5;

int m,n,x,y;
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
    if(b>a){
        return 0;
    }
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main()
{
    cin>>m>>n>>x>>y;
    prepare(2*n+m);
    int ans=0;
    if(x<=n&&y<=n){
        for(int i=1;i<=m;i++){
            ans=(ans+(comb(i+x-2,x-1)*comb(n+m-i-y,n-y))%MOD)%MOD;
        }
        ans=(ans*(comb(m+n-1,n)))%MOD;
        ans=(ans+MOD)%MOD;
    }
    else if(x>n&&y>n){
        x-=n,y-=n;
        for(int i=1;i<=m;i++){
            ans=(ans+(comb(m+x-1-i,x-1)*comb(n+i-1-y,n-y))%MOD)%MOD;
        }
        ans=(ans*(comb(m+n-1,n)))%MOD;
        ans=(ans+MOD)%MOD;
    }
    else{
        for(int i=1;i<=m;i++){
            ans=(ans+((((comb(i+x-2,x-1)*comb(2*n-y-1+i,2*n-y))%MOD)*comb(m+n-x-i,n-x))%MOD*comb(m-n-i+y-1,y-n-1))%MOD)%MOD;
        }
        ans=(ans+MOD)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}