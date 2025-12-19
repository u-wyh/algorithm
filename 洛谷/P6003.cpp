#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k,m;

bool check(int x){
    int r=n,t=k;
    while(t&&r>0){
        int y=r/x;
        if(y<=m){
            r-=m*t;
            t=0;
        }
        else{
            int a=min(t,r/y-x+1);
            r-=a*y;
            t-=a;
        }
    }
    return r<=0;
}

signed main()
{
    cin>>n>>k>>m;
    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}