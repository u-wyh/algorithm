#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e3+5;
const int MOD = 998244353;

int n,k;
int x[MAXN];
int y[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=ans*a%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&x[i],&y[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int a=y[i],b=1;
        for(int j=1;j<=n;j++){
            if(i!=j){
                a=(a*(k-x[j]))%MOD;
                b=(b*(x[i]-x[j]))%MOD;
            }
        }
        b=power(b,MOD-2);
        ans=(ans+(a*b%MOD))%MOD;
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}