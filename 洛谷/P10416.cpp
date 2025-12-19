#include<bits/stdc++.h>
using namespace std;
#define int long long

int l,r;
unsigned long long ans=0;

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>l>>r;
        if(r-l<l){
            cout<<0<<endl;
            continue;
        }
        ans=1ll*(r-2*l+2)*(r-2*l+1)/2;
        cout<<ans<<endl;
    }
    return 0;
}