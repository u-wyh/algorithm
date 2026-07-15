#include<bits/stdc++.h>
using namespace std;
#define int long long

int euler(int n){
    // cout<<n<<' ';
    int ans=1;
    for(int i=2;i*i<=n;i++){
        if(n%i){
            continue;
        }
        ans*=(i-1);
        n/=i;
        while(n%i==0){
            ans*=i;
            n/=i;
        }
    }
    if(n>1){
        ans*=(n-1);
    }
    // cout<<ans<<endl;
    return ans;
}

signed main()
{
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i*i<=n;i++){
        if(n%i){
            continue;
        }
        ans+=euler(i)*n/i;
        if(i!=n/i){
            ans+=euler(n/i)*i;
        }
        // cout<<ans<<' ';
    }
    cout<<ans<<endl;
    return 0;
}