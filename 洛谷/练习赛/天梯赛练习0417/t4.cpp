#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int a,b;
    cin>>a>>b;
    int ans=1;
    for(int i=1;i<=(a+b);i++){
        ans*=i;
    }
    cout<<ans<<endl;
    return 0;
}