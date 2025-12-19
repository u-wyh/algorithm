#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        n++;
        int ans=0;
        int p=1;
        while(n){
            if(n&1){
                ans=(ans*2%MOD+p)%MOD;
            }
            n>>=1;
            p=(p*3)%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}