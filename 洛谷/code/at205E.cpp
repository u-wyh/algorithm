#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 2e6+5;

int n,m,k;
long long fac[MAXN];

long long power(long long val,int b){
    // cout<<' '<<val;
    long long ans=1;
    while(b){
        if(b&1){
            ans*=val;
            ans%=MOD;
        }
        val*=val;
        val%=MOD;
        b>>=1;
    }
    // cout<<' '<<ans<<endl;
    return ans;
}

int main()
{
    cin>>n>>m>>k;
    if(n>m+k){
        cout<<0<<endl;
        return 0;
    }
    fac[0]=1;
    for(int i=1;i<=(n+m);i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    long long ans=0;
    ans=fac[n+m]*power(fac[n],MOD-2)%MOD*power(fac[m],MOD-2)%MOD-fac[n+m]*power(fac[m+k+1],MOD-2)%MOD*power(fac[n-k-1],MOD-2)%MOD;
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}