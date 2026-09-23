// https://www.luogu.com.cn/problem/P2054
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,m,l;

int mul(int a,int b,int mod){
    return (__int128)a*b%mod;
}

int power(int a,int b,int mod){
    int ans=1;
    while(b){
        if(b&1){
            ans=mul(a,ans,mod);
        }
        b>>=1;
        a=mul(a,a,mod);
    }
    return ans;
}

signed main()
{
    cin>>n>>m>>l;
    int mod=n+1;
    int inv2=(n+2)/2;
    int ans=mul(l,power(inv2,m,mod),mod);
    cout<<ans<<endl;
    return 0;
}