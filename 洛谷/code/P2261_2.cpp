// https://www.luogu.com.cn/problem/P2261
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,k;

signed main()
{
    cin>>n>>k;
    int ans=0;
    for(int lt=1,rt;lt<=n;lt=rt+1){
        int v=k/lt;
        if(v==0){
            rt=n;
        }
        else{
            rt=min(k/v,n);
        }
        ans-=1ll*v*(rt+lt)*(rt-lt+1)/2;
        ans+=1ll*(rt-lt+1)*k;
    }
    cout<<ans<<endl;
    return 0;
}