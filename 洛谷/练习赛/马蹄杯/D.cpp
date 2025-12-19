#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int n;
int ans;

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
    cin>>n;
    ans=(((power(26,n)-(3*power(25,n)))%MOD)%MOD+((3*power(24,n))%MOD-power(23,n))%MOD)%MOD;
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}