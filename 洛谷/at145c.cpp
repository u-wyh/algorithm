#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main()
{
    int n;
    cin>>n;
    if(n==1){
        cout<<2<<endl;
        return 0;
    }
    long long ans=1;
    for(int i=n+2;i<=2*n;i++){
        ans*=i;
        ans%=MOD;
    }
    for(int i=1;i<=n;i++){
        ans*=2;
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}