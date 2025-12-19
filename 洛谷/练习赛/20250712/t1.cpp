#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int inv = 332748118;

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
    // cout<<power(3,MOD-2)<<endl;
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int ans=(power(2,n)+MOD-1)%MOD;
        if(n%2==1){
            ans=(ans+MOD-1)%MOD;
            ans=(ans*inv)%MOD;
            ans=(2*ans%MOD+1)%MOD;
            ans=(ans+MOD)%MOD;
        }
        else{
            ans=(ans*inv)%MOD;
            ans=2*ans%MOD;
            ans=(ans+MOD)%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}