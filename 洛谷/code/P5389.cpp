#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

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
    int n;
    cin>>n;
    if(n==0){
        cout<<power(2,MOD-2)<<endl;
    }
    else{
        n%=MOD;
        int k=(n*n%MOD+2*n%MOD)%MOD;
        int ans=((k-3)*power(2*k%MOD,MOD-2))%MOD;
        ans=(ans+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}