#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19940417;

int n,m,inv6;

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int calc(int n){
    int ans=(n*n)%MOD;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        int res=((l+r)*(r-l+1)/2)%MOD*(n/l)%MOD;
        ans=(ans-res+MOD)%MOD;
    }
    return ans;
}

int fun(int n){
    return n*(n+1)%MOD*(2*n+1)%MOD*inv6%MOD;
}

int compute(int n,int m){
    int ans=(n*n%MOD)*m%MOD;
    // cout<<ans<<endl;
    int ans1=0;
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        int res=((fun(r)-fun(l-1)+MOD)%MOD)*(n/l)%MOD*(m/l)%MOD;
        ans1=(ans1+res)%MOD;
    }
    // cout<<ans1<<endl;
    ans=(ans1+ans)%MOD;

    ans1=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        int res=((l+r)*(r-l+1)/2%MOD)*(n/l)%MOD;
        res=(res*m)%MOD;
        ans1=(ans1+res)%MOD;
    }
    // cout<<ans1<<endl;
    ans=(ans-ans1+MOD)%MOD;

    ans1=0;    
    for(int l=1,r;l<=n;l=r+1){
        r=min(m/(m/l),n);
        int res=((l+r)*(r-l+1)/2%MOD)*(m/l)%MOD;
        res=(res*n)%MOD;
        ans1=(ans1+res)%MOD;
    }
    // cout<<ans1<<endl;
    ans=(ans-ans1+MOD)%MOD;
    return ans;
}

signed main()
{
    // cout<<(1+MOD%MOD);
    cin>>n>>m;
    // inv6=power(6,MOD-2);
    // inv2=power(2,MOD-2);
    inv6=3323403;
    // cout<<' '<<inv6<<endl;
    if(n>m){
        swap(n,m);
    }
    int ans=(calc(n)*calc(m))%MOD;
    // cout<<ans<<endl;
    ans=(ans-compute(n,m)+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}