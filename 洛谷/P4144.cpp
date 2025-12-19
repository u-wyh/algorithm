#include<bits/stdc++.h>
using namespace std;

int n,b,p,mod;

int ksm(int x,int k){
    int ans=1,base=x;
    while(k){
        if(k&1)
            ans=1ll*ans*base%mod;
        base=1ll*base*base%mod;
        k>>=1;
    }
    return ans;
}

int main()
{
    cin>>n>>b>>mod;
    for(int i=1,x;i<=n;i++) cin>>x,p=max(x,p);
    cout<<ksm(p*2+233,b)%mod;
}
