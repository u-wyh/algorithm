#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k;
int ans;

signed main()
{
    cin>>n>>k;
    ans=n*k;
    int l=1,r;
    while(l<=min(n,k)){
        int t=k/l;
        // r=min(n,n/t);
        r=min(k/t,n);
        ans-=t*(l+r)*(r-l+1)/2;
        l=r+1;
    }
    cout<<ans<<endl;
    return 0;
}