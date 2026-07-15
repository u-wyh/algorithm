#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int compute(int n){
    if(n<=0){
        return 0;
    }
    int l=1,r;
    int ans=0;
    while(l<=n){
        int k=n/l;
        r=n/k;
        ans+=(r-l+1)*k;
        ans%=MOD;
        l=r+1;
    }
    return ans;
}

signed main()
{
    int l,r;
    cin>>l>>r;
    int ans=compute(r)-compute(l-1);
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}