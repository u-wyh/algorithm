#include<bits/stdc++.h>
using namespace std;
#define int long long

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
        l=r+1;
    }
    return ans;
}

signed main()
{
    int l,r;
    cin>>l>>r;
    cout<<(compute(r)-compute(l-1))<<endl;
    return 0;
}