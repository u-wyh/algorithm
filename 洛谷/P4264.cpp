#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 9999991;

signed main()
{
    int n;
    cin>>n;
    int ans=1;
    for(int i=1;i<n;i++){
        ans=(ans*i)%MOD;
    }
    for(int i=1;i<n-1;i++){
        ans=(ans*n)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}