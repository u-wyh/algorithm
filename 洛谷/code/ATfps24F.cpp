// https://atcoder.jp/contests/fps-24/tasks/fps_24_f
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
    int ans=(n&1)?1:-1;
    ans+=power(3,n);
    ans*=power(4,MOD-2);
    ans%=MOD;
    cout<<ans<<endl;
    return 0;
}