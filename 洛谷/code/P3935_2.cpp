// https://www.luogu.com.cn/problem/P3935
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int INV = (MOD+1)/2;

int x,y;

int solve(int n){
    if(n==0){
        return 0;
    }
    int ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=n/lt;
        rt=n/v;

        ans+=1ll*v*(rt-lt+1);
        ans%=MOD;
    }
    return ans;
}

signed main()
{
    cin>>x>>y;
    int ans=0;
    ans=solve(y);
    ans-=solve(x-1);
    ans=(ans%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}