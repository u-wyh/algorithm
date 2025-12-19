#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin>>n;
    int arr[n+1];
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    long long ans=0;
    for(int i=0;i<=20;i++){
        int s=0,n0=0,n1=0;
        for(int j=1;j<=n;j++){
            s+=(arr[j]>>i)&1;
            if(s%2==1){
                ans+=(1+n0)*(1<<i);
                n1++;
            }
            else{
                ans+=(n1)*(1<<i);
                n0++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
