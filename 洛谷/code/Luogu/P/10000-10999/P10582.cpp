#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

bool check(int x){
    if(((n+x)/(1+x)*(n+x)/(1+x)>=x)){
        return true;
    }
    return false;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        if(n==1){
            cout<<1<<endl;
            continue;
        }
        if(n==2){
            cout<<3<<endl;
            continue;
        }
        int l=3,r=n*n,ans=3;
        while(l<=r){
            int mid=(l+r)/2;
            if(check(mid-2)){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}