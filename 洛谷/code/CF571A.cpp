#include<bits/stdc++.h>
using namespace std;
#define int long long

int a,b,c,l;

int compute(int d){
    int ans=0;
    int st=max(0ll,d);
    for(int i=st;i<=l;i++){
        int res=l-i;
        int t=min(res,i-d);
        ans+=(t+1)*(t+2)/2;
    }
    return ans;
}

signed main()
{
    cin>>a>>b>>c>>l;
    int total=(l+3)*(l+2)*(l+1)/6;
    int bad=0;
    bad+=compute(b+c-a);
    bad+=compute(a+c-b);
    bad+=compute(a+b-c);
    total-=bad;
    cout<<total<<endl;
    return 0;
}