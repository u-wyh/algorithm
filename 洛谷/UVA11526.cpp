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
        ans+=k*(r-l+1);
        l=r+1;
    }
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        cout<<compute(n)<<endl;
    }
    return 0;
}