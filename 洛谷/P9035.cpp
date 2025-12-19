#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 2e7+5;

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
    prepare(20000000);
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        int ans;
        if(k%2){
            ans=(comb(n+(k+1)/2-1,(k+1)/2-1)+comb(n+k-(k+1)/2-1,n))%MOD;
        }
        else{
            ans=(comb(n+k/2-1,k/2-1)+comb(n+k/2-1,n))%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}