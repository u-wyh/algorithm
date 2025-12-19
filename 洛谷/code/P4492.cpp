#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2005;

int n,mod;
int fac[MAXN];
int comb[MAXN][MAXN];

signed main()
{
    scanf("%lld %lld",&n,&mod);
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%mod;
    }
    for(int i=0;i<=n;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%mod;
        }
    }
    int ans=0;
    for(int i=2;i<=n;i++){
        for(int sz=1;sz<=n-i+1;sz++){
            ans=(ans+((((((comb[n-i][sz-1]*fac[sz])%mod*(i-1))%mod*i)%mod*fac[n-sz-1])%mod*sz)%mod*(n-sz))%mod)%mod;
        }
    }
    cout<<ans<<endl;
    return 0;
}