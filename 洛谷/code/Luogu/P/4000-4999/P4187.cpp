#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 1e9+7;
const int MAXN = 1e6+5;

int n,m,k;
int f[MAXN];
int g[MAXN];

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

signed main()
{
    cin>>n>>m>>k;
    if(k>n){
        cout<<0<<endl;
        return 0;
    }
    f[0]=1;
    for(int i=1;i<k;i++){
        f[i]=(m*f[i-1])%MOD;
        g[i]=(g[i-1]+f[i])%MOD;
    }
    for(int i=k;i<=n;i++){
        f[i]=(m-1)*(g[i-1]-g[i-k])%MOD;
        g[i]=(g[i-1]+f[i])%MOD;
    }
    int ans=power(m,n);
    ans=((ans-f[n])%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}